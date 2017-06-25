/* acquire_1056bytes_sample.c
 * Program to read packets from the specified Ethernet interface using the
 * libpcap library and write them to the disk, putting sampled packets in
 * a shared memory segment.
 *
 * Compiling: ./make_acquire_1056bytes
 *
 * Usage: acquire_1056bytes [options]
 *     -h  --help                 Display this usage information
 *     -d  --device <dev_name>    Select the input device
 *                                (default is 'eth0')
 *     -f  --files <num_files>    Set the number of 2GB files to be written
 *                                (default is 1)
 *     -m  --mode                 Acquisition mode
 *                                (0 is 'observation' - filenames are formatted;
 *                                 1 is 'test' - filenames are not formatted;
 *                                 default is 'observation')
 *
 * pep/10apr08
 * Modified by Jayanth Chennamangalam on 2008.04.23
 * desh: bytes to be written changed to 1030 instead of 1024   2008.04.24; 17:27
 * Modified by Jayanth Chennamangalam on 2008.04.26 - writing to multiple files
 *     and cosmetic changes, also changed filename from rawpcap.c to acquire.c
 * desh: bytes to be written changed to 1056 instead of 1030, as marker bytes
 *     are increased to 26; 2008.05.01; 18:22
 *     the 26 bytes of Marker may contain some FFFFFs and 00000s, followed by a
 *     name of the DAS etc.
 *     the GPS 1-sec pulse count then follows with 2 bytes, and then a 4-byte
 *     packet counter value.
 *     Thus 32 total bytes preceed 1024 bytes of data.. making the (non-udp)
 *     packet size of interest as 1056
 * Modified by Jayanth Chennamangalam on 2008.07.09 - replaced fopen, fwrite,
 *     and fclose with open, write, and close, respectively
 * Modified by Jayanth Chennamangalam on 2008.07.09 - filenames are timestamped
 */

//TODO: adding header - struct

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pcap.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <assert.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#include "das.h"
#include "das_shm.h"
#include "mbr_dataheader.h"
//TODO: put all in the same directory
#include "../socket/mbr_common.h"
#include "../socket/mbr_serialport.h"
#include "../socket/mbr_config.h"

#define MAX_LEN_FILENAME        32
#define MAX_SIZE_PACKET         65536
//#define MAX_SIZE_FILE           ((unsigned int) 2048 * 1024 * 1024)
#define MAX_SIZE_FILE           (99 * DAS_SIZE_SHM_DATA)
#define SIZE_PACKET             1056
#define MAX_NUM_PKTSPERFILE     (((int) ((MAX_SIZE_FILE/SIZE_PACKET)/256))*256)
#define MAX_NUM_FILES           200
#define TIMEOUT                 1000
#define MODE_PROMISC            1
#define SIZE_PKTBUFFER          105600
#define MBR_TEST_FILE_PREFIX    "packet"
#define MBR_NAME_DAS            "ch01"
#define MBR_NAME_PSR            "J0737-3039"
#define MBR_DATAFILE_EXT        "mbr"
#define MBR_LEN_NAME_DAS        5
#define MBR_LEN_NAME_PSR        10
#define MBR_LEN_COUNT           3
#define MBR_LEN_DATAFILE_EXT    3
/* length of the timestamp string in the format 'yyyymmdd_hhmmss' */
#define MBR_LEN_TS              15
/* filename is of the format 'dasXX_XXXXXXXXXX_yyyymmdd_hhmmss_XXX.ext',
   the '1' being for the underscores and the period */
#define MBR_LEN_FILENAME        (MBR_LEN_NAME_DAS + 1 \
                                 + MBR_LEN_NAME_PSR + 1 \
                                 + MBR_LEN_TS + 1 \
                                 + MBR_LEN_COUNT + 1 \
                                 + MBR_LEN_DATAFILE_EXT)
#define MBR_DAS_UID             1001
#define MBR_DAS_GID             1001
#define MBR_ACQMODE_OBS         0
#define MBR_ACQMODE_TEST        1
#define MBR_ACQMODE_SNIFF       2
#define MBR_PCAP_USER           ((unsigned char *) "das01")
/* 1 packet every MBR_SAMPINT will be written to the shared memory */
#define MBR_SAMPINT             1000
#define MBR_SAMPOFFSET          100

typedef unsigned char BYTE;

#pragma pack(push, 1)
typedef struct tagRFVals
{
    unsigned int iAtten1:6;
    unsigned int iAtten2:6;
    unsigned int iAtten3:6;
    unsigned int iAtten4:6;
    short int iLOFreq;
} MBR_RF_VALS_S;
#pragma pack(pop)

void PrintUsage(const char *pcProgName);
void BuildFilename(struct tm *pstTime, int iCount, char acFilename[]);
int OpenFiles();
void CloseFiles();
void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket);

int g_aiFiles[MAX_NUM_FILES] = {0};
int g_iCurrentFile = 0;
int g_iNumFiles = 1;    /* default is 1 file */
int g_iCurrentFileIndex = 0;
int g_iBuffer = 0;
int g_iFirstIter = DAS_TRUE;
int g_iBufferChange = 0;
int g_iPacketCount = 0;
int g_iAcqMode = 0;     /* default is MBR_ACQMODE_OBS */
int g_iSampOffset = 0;
pcap_t *g_pstHandle = NULL;
DAS_BLOCKADDS_S g_stBlockAdds[DAS_NUM_BUFS] = {{0}};
DAS_SHM_DATATYPE *g_pBufBase[DAS_NUM_BUFS] = {NULL};
DAS_SHM_DATATYPE *g_pBasePointer = NULL;
DAS_SHM_DATATYPE *g_pWritePointer = NULL;
DAS_SHMINFO_S *g_pstShmInfo = NULL;
MBR_RF_VALS_S g_stRFVals = {0};

//jayanth
//int g_iTempFile = 0;

int main(int argc, char *argv[])
{
    char acErrBuf[PCAP_ERRBUF_SIZE] = {0};
    char *pcDevice = (char *) "eth0";   /* default device is eth0 */
    const char *pcProgName = NULL;
    int iNextOpt = 0;
    int iRet = 0;
    DAS_BLOCK_S *pstBlock = NULL;
    int iBlockID = DAS_BLOCKID_START;   /* first block */
    int i = 0;
    char acAtten1[MBR_BITPOS_ATTENLATCH+1] = {0};
    char acAtten2[MBR_BITPOS_ATTENLATCH+1] = {0};
    char acAtten3[MBR_BITPOS_ATTENLATCH+1] = {0};
    char acAtten4[MBR_BITPOS_ATTENLATCH+1] = {0};
    char acTemp[MBR_MAX_LEN_GENSTRING] = {0};
    char acRFHist[MBR_MAX_LEN_GENSTRING] = {0};
    float fTemp = 0.0;
    int iLOFreq = 0;
    const char* const sShortOpts = "hd:f:m:o:"; /* valid short options */
    const struct option stLongOpts[] = {        /* valid long options */
        { "help",       0, NULL, 'h' },
        { "device",     1, NULL, 'd' },
        { "files",      1, NULL, 'f' },
        { "mode",       1, NULL, 'm' },
        { "offset",     1, NULL, 'o' },
        { NULL,         0, NULL, 0   }
    };

    /* get the filename of the program from the argument list */
    pcProgName = argv[0];

    /* parse the input */
    do
    {
        iNextOpt = getopt_long(argc, argv, sShortOpts,
                               stLongOpts, NULL);
        switch (iNextOpt)
        {
            case 'h':   /* -h or --help */
                /* print usage info and terminate */
                PrintUsage(pcProgName);
                return 0;

            case 'd':   /* -d or --device */
                /* set the device name */
                pcDevice = optarg;
                break;

            case 'f':   /* -f or --files */
                /* set the number of 2GB files to be written */
                g_iNumFiles = atoi(optarg);
                if ((g_iNumFiles < 1) || (g_iNumFiles > MAX_NUM_FILES))
                {
                    fprintf(stderr,
                            "ERROR: Number of files should be at least 1 ");
                    fprintf(stderr, "and not more than %d!\n", MAX_NUM_FILES);
                    PrintUsage(pcProgName);
                    return -1;
                }
                break;

            case 'm':   /* -m or --mode */
                /* set the acquisition mode */
                g_iAcqMode = atoi(optarg);
                if ((g_iAcqMode != MBR_ACQMODE_OBS)
                    && (g_iAcqMode != MBR_ACQMODE_TEST)
                    && (g_iAcqMode != MBR_ACQMODE_SNIFF))
                {
                    fprintf(stderr, "ERROR: Mode should be either 0, 1, or 2!\n");
                    PrintUsage(pcProgName);
                    return -1;
                }
                break;
            case 'o':   /* -o or --offset */
                /* set the sampling offset */
                g_iSampOffset = atoi(optarg);
                break;

            case '?':   /* user specified an invalid option */
                /* print usage info and terminate with error */
                fprintf(stderr, "ERROR: Invalid option!\n");
                PrintUsage(pcProgName);
                return -1;

            case -1:    /* done with options */ 
                break;

            default:    /* unexpected */
                assert(0);
        }
    } while (iNextOpt != -1);

    //jayanth
//    g_iTempFile = open("tempdata.mbr",
//                       (O_CREAT | O_WRONLY),
//                       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
//    if (-1 == g_iTempFile)
//    {
//        perror("");
//        exit(1);
//    }

    if (g_iAcqMode != MBR_ACQMODE_SNIFF)
    {
        iRet = OpenFiles();
        if (iRet != 0)
        {
            printf("ERROR: Error opening files!\n");
            return -1;
        }
    }

    iRet = MBR_CreateDeviceLookUp();
    if (iRet != MBR_RET_SUCCESS)
    {
        fprintf(stderr, "ERROR: Device lookup failed!\n");
        if (g_iAcqMode != MBR_ACQMODE_SNIFF)
        {
            CloseFiles();
        }
        return MBR_RET_ERROR;
    }

    (void) MBR_GetLastRFHistEntry(acRFHist);
    iRet = sscanf(acRFHist, "%s %s %g %s\t%g %s\t%g %s\t%g %s\t%i\n",
                  acTemp, acTemp,   /* for date and time */
                  &fTemp, acAtten1,
                  &fTemp, acAtten2,
                  &fTemp, acAtten3,
                  &fTemp, acAtten4,
                  &iLOFreq);
    g_stRFVals.iAtten1 = MBR_Bitmap2Int(acAtten1);
    g_stRFVals.iAtten2 = MBR_Bitmap2Int(acAtten2);
    g_stRFVals.iAtten3 = MBR_Bitmap2Int(acAtten3);
    g_stRFVals.iAtten4 = MBR_Bitmap2Int(acAtten4);
    g_stRFVals.iLOFreq = (short int) iLOFreq;

    g_pstHandle = pcap_open_live(pcDevice,
                                MAX_SIZE_PACKET,
                                MODE_PROMISC,
                                TIMEOUT,
                                acErrBuf);
    if (NULL == g_pstHandle)
    {
        fprintf(stderr, "%s\n", acErrBuf);
        if (g_iAcqMode != MBR_ACQMODE_SNIFF)
        {
            CloseFiles();
        }
        return -1;
    }

    /* create the shminfo data structure in shared memory */
    printf("Creating shminfo...");
    fflush(stdout);
    g_pstShmInfo = DAS_CreateShmInfo(DAS_KEY_FL_OUT, DAS_PID_FL);
    if (NULL == g_pstShmInfo)
    {
        printf("ERROR in ShmAlloc() for g_pstShmInfo\n");

        /* clean up */
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        pcap_close(g_pstHandle);

        return -1;
    }
    printf("DONE\n");

    /* create buffers */
    for (i = 0; i < DAS_NUM_BUFS; ++i)
    {
        printf("Creating block %d...", iBlockID);
        fflush(stdout);
        g_stBlockAdds[i] = DAS_CreateBlock(iBlockID,
                                           DAS_KEY_FL_OUT,
                                           g_pstShmInfo,
                                           DAS_PID_FL);
        pstBlock = g_stBlockAdds[i].pstBlock;
        if (NULL == pstBlock)
        {
            printf("ERROR in DAS_CreateBlock() for block %d\n", iBlockID);

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            pcap_close(g_pstHandle);

            return -1;
        }
        g_pBufBase[i] = g_stBlockAdds[i].pData;
        /* initially, set the data flag to DAS_STATUS_NOP */
        g_stBlockAdds[i].pstBlock->iFlagData = DAS_STATUS_NOP;
        printf("DONE\n");
        ++iBlockID;
    }

    /* the first buffer will be written to now, so set the data flag
       to DAS_STATUS_FRESH */
    g_stBlockAdds[0].pstBlock->iFlagData = DAS_STATUS_FRESH;

    /* set the base and write pointers to the first buffer */
    g_iBuffer = 0;
    g_pBasePointer = g_stBlockAdds[0].pData;
    g_pWritePointer = g_stBlockAdds[0].pData;

    /* set the status flag to DAS_STATUS_WRITESTART */
    g_pstShmInfo->iStatus = DAS_STATUS_WRITESTART;

    if (g_iAcqMode != MBR_ACQMODE_SNIFF)
    {
        printf("Writing to file %d\n", g_iCurrentFileIndex);
    }

    iRet = pcap_loop(g_pstHandle, -1, ProcessPacket, MBR_PCAP_USER);
    if (-1 == iRet)
    {
        fprintf(stderr, "ERROR: pcap_loop() failed!\n");

        /* clean up */
        pcap_close(g_pstHandle);
        if (g_iAcqMode != MBR_ACQMODE_SNIFF)
        {
            CloseFiles();
        }

        return -1;
    }
    else if (-2 == iRet)
    {
        /* pcap_breakloop() encountered, so continue */
    }

    /* set the status flag to DAS_STATUS_WRITEDONE */
    g_pstShmInfo->iStatus = DAS_STATUS_WRITEDONE;

    /* clean up */
    /* delete buffers */    
    iBlockID = DAS_BLOCKID_START;
    for (i = 0; i < DAS_NUM_BUFS; ++i)
    {
        iRet = shmdt(g_stBlockAdds[i].pData);
        if (iRet != 0)
        {
            printf("ERROR in shmdt() for data in block %d: ", iBlockID);
            fflush(stdout);
            perror("");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            pcap_close(g_pstHandle);

            return -1;
        }
        iRet = shmdt(g_stBlockAdds[i].pstBlock);
        if (iRet != 0)
        {
            printf("ERROR in shmdt() for block %d: ", iBlockID);
            fflush(stdout);
            perror("");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            pcap_close(g_pstHandle);
    
            return -1;
        }
        ++iBlockID;
    }

    iRet = shmdt(g_pstShmInfo);
    if (iRet != 0)
    {
        perror("ERROR in shmdt() for g_pstShmInfo");

        /* clean up */
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        pcap_close(g_pstHandle);

        return -1;
    }

    /* clean up */
    pcap_close(g_pstHandle);
    if (g_iAcqMode != MBR_ACQMODE_SNIFF)
    {
        CloseFiles();
    }

    //jayanth
//    (void) close(g_iTempFile);

    return 0;
}

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket)
{
    struct ether_header *stHeaderEth = NULL;
    struct iphdr *stHeaderIP = NULL;
    struct udphdr *stHeaderUDP = NULL;
    BYTE *pbData = NULL;
    MBR_DATA_HEADER_S *pstDataHeader = NULL;
#if 0
    char acValue[5] = {0};
#endif

    assert(pcUser != NULL);
    assert(pstPacketHeader != NULL);
    assert(pbPacket != NULL);

    stHeaderEth = (struct ether_header*) pbPacket;
    stHeaderIP  = (struct iphdr*) (pbPacket + sizeof(struct ether_header));
    stHeaderUDP = (struct udphdr*) (((BYTE *) stHeaderIP)
                                    + sizeof (struct iphdr));
    pbData = (BYTE *) (((BYTE *) stHeaderUDP) + sizeof (struct udphdr));

    /* if the end of the buffer is reached, reset the write pointer to the base
       pointer of the next buffer */
    if ((g_pWritePointer - g_pBasePointer) == DAS_SIZE_SHM_DATA)
    {
        ++g_iBufferChange;
        if (g_iBuffer != (DAS_NUM_BUFS - 1))    /* not the last buffer */
        {
            ++g_iBuffer;
        }
        else    /* the current buffer is the last buffer */
        {
            g_iBuffer = 0;
        }
        if ((DAS_STATUS_FRESH == g_stBlockAdds[g_iBuffer].pstBlock->iFlagData))
        {
            printf("ERROR: Overwriting buffer %d at packet number %d!\n",
                   g_iBuffer,
                   g_iPacketCount);
            printf("Stopping data acquisition...\n");
            printf("%d packets processed.\n", g_iPacketCount);
            printf("%d buffer changes.\n", g_iBufferChange);
            pcap_breakloop(g_pstHandle);
            return;
        }
        g_stBlockAdds[g_iBuffer].pstBlock->iFlagData = DAS_STATUS_FRESH;
        g_pBasePointer = g_stBlockAdds[g_iBuffer].pData;
        g_pWritePointer = g_stBlockAdds[g_iBuffer].pData;
    }

    if (g_iAcqMode != MBR_ACQMODE_SNIFF)
    {
        /* write to the file */
        (void) write(g_iCurrentFile, pbData, SIZE_PACKET);
    }

    /* check if MBR_SAMPINT has passed, and if yes, write to shared memory */
    //if (0 == (g_iPacketCount % MBR_SAMPINT))
    if (g_iSampOffset == (g_iPacketCount % MBR_SAMPINT))
    {
        /* update the values of attenuators and LO */
        pstDataHeader = (MBR_DATA_HEADER_S *) pbData;
        (void) memcpy((((char *) pstDataHeader)
                        + MBR_SDH_GetAtten1Pos(pstDataHeader)),
                      &g_stRFVals,
                      sizeof(g_stRFVals));
        (void) memcpy(g_pWritePointer, pbData, SIZE_PACKET);
        
        //jayanth
//      (void) write(g_iTempFile, pbData, SIZE_PACKET);

        g_pWritePointer += SIZE_PACKET;
        g_pstShmInfo->iWrittenData += SIZE_PACKET;
    }

    /* increment the packet count, check the limit, and set the current file
       pointer if necessary */
    ++g_iPacketCount;
    if (g_iPacketCount >= MAX_NUM_PKTSPERFILE)
    {
        ++g_iCurrentFileIndex;
        if (g_iCurrentFileIndex == g_iNumFiles)
        {
            printf("Stopping data acquisition...\n");
            printf("%d packets processed.\n", g_iPacketCount);
            printf("%d buffer changes.\n", g_iBufferChange);
            pcap_breakloop(g_pstHandle);
            return;
        }
        if (g_iAcqMode != MBR_ACQMODE_SNIFF)
        {
            g_iCurrentFile = g_aiFiles[g_iCurrentFileIndex];
            printf("Writing to file %d\n", g_iCurrentFileIndex);
        }
        g_iPacketCount = 0;
    }

    return;
}

int OpenFiles()
{
    int i = 0;
    time_t Time;
    struct tm *pstTime = NULL;
    char acFilename[MBR_LEN_FILENAME+1] = {0};
    int iRet = 0;

    /* get the current time */
    Time = time(NULL);
    pstTime = localtime(&Time);

    for (i = 0; i < g_iNumFiles; ++i)
    {
        /* build the file name */
        if (MBR_ACQMODE_OBS == g_iAcqMode)
        {
            BuildFilename(pstTime, i, acFilename);
            /* in the case of MBR_ACQMODE_OBS, the file should not be
               replaced */
            g_aiFiles[i] = open(acFilename,
                                (O_CREAT | O_EXCL | O_WRONLY),
                                (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
        }
        else
        {
            (void) sprintf(acFilename, MBR_TEST_FILE_PREFIX "%d", i);
            /* in the case of MBR_ACQMODE_DIAG, the file may be replaced */
            g_aiFiles[i] = open(acFilename,
                                (O_CREAT | O_WRONLY),
                                (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
        }
        if (-1 == g_aiFiles[i])
        {
            perror("ERROR: open");
            return -1;
        }

        /* set the owner to 'das' */
        iRet = chown(acFilename, MBR_DAS_UID, MBR_DAS_GID);
        if (iRet != 0)
        {
            perror("ERROR: chown");
            return -1;
        }
    }

    /* set the current file pointer to the first file pointer */
    g_iCurrentFile = g_aiFiles[0];

    return 0;
}

void BuildFilename(struct tm *pstTime, int iCount, char acFilename[])
{
    char acTimestamp[MBR_LEN_TS+1] = {0};
    char acCount[MBR_LEN_COUNT+1] = {0};
    char acTemp[2] = {0};
    int iDigits[MBR_LEN_COUNT] = {0};
    int iNumDigits = 0;
    int i = 0;

    /* convert iCount to acCount */
    for (i = 0; i < MBR_LEN_COUNT; ++i)
    {
        if (0 == (iCount / 10))
        {
            iDigits[i] = iCount % 10;
            iNumDigits = i + 1;
            break;
        }
        else
        {
            iDigits[i] = iCount % 10;
            iCount = iCount / 10;
        }
    }

    for (i = (MBR_LEN_COUNT - iNumDigits); i > 0; --i)
    {
        (void) strcat(acCount, "0");
    }

    for (i = iNumDigits; i > 0; --i)
    {
        (void) sprintf(acTemp, "%d", iDigits[i-1]);
        (void) strcat(acCount, acTemp);
    }

    (void) strftime(acTimestamp, sizeof(acTimestamp), "%Y%m%d_%H%M%S", pstTime);
    (void) sprintf(acFilename,
                   "%s_%s_%s_%s.%s",
                   MBR_NAME_DAS,
                   MBR_NAME_PSR,
                   acTimestamp,
                   acCount,
                   MBR_DATAFILE_EXT);

    return;
}

void CloseFiles()
{
    int i = 0;

    for (i = 0; i < g_iNumFiles; ++i)
    {
        (void) close(g_aiFiles[i]);
    }

    return;
}

void PrintUsage(const char *pcProgName)
{
    printf("Usage: %s [options]\n", pcProgName);
    printf("    -h  --help                 Display this usage ");
    printf("information\n");
    printf("    -d  --device <dev_name>    Select the input device\n");
    printf("                               (default is 'eth0')\n");
    printf("    -f  --files <num_files>    Set the number of 2GB files ");
    printf("to be written\n");
    printf("                               (default is 1)\n");
    printf("    -m  --mode                 Acquisition mode\n");
    printf("                               (0 is 'observation' - filenames ");
    printf("are formatted;\n");
    printf("                                1 is 'test' - filenames are ");
    printf("not formatted;\n");
    printf("                                2 is 'sniff' - files are not ");
    printf("created;\n");
    printf("                                default is 'observation')\n");
    return;
}

