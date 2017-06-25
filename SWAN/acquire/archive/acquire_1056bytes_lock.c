/* acquire_1056bytes_lock.c
 * Program to read packets from the specified Ethernet interface using the
 * libpcap library and write them to the disk. Running multiple instances of
 * this program is prohibited by the use of lock files.
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

//TODO: capture some signal to terminate the program and remove the lock file

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
#include <errno.h>
#include <signal.h>

#define MBR_FALSE               0
#define MBR_TRUE                1
#define MBR_RET_SUCCESS         0
#define MBR_RET_ERROR           -1
#define MBR_PATH_LOCKFILE       "/home/das/lock/acquire.lock"
#define MBR_PATH_KILLSCRIPT     "/home/das/scripts/mbr_killacquire.py"

#define MAX_LEN_FILENAME        32
#define MAX_SIZE_PACKET         65536
#define MAX_SIZE_FILE           ((unsigned int) 2048 * 1024 * 1024)
#define SIZE_PACKET             1056
#define MAX_NUM_PKTSPERFILE     (((int) ((MAX_SIZE_FILE/SIZE_PACKET)/256))*256)
#define MAX_NUM_FILES           200
#define TIMEOUT                 1000
#define MODE_PROMISC            1
#define MBR_TEST_FILE_PREFIX    "packet"
#define MBR_NAME_CHANNEL        "ch01"
#define MBR_NAME_PSR            "J0737-3039"
#define MBR_DATAFILE_EXT        "mbr"
#define MBR_LEN_NAME_CHANNEL    (strlen(MBR_NAME_CHANNEL))
#define MBR_LEN_NAME_PSR        (strlen(MBR_NAME_PSR))
#define MBR_LEN_COUNT           3
#define MBR_LEN_DATAFILE_EXT    (strlen(MBR_DATAFILE_EXT))
/* length of the timestamp string in the format 'yyyymmdd_hhmmss' */
#define MBR_LEN_TIMESTAMP       15
/* filename is of the format 'dasXX_XXXXXXXXXX_yyyymmdd_hhmmss_XXX.ext',
   the '1' being for the underscores and the period */
#define MBR_LEN_FILENAME        (MBR_LEN_NAME_CHANNEL + 1 \
                                 + MBR_LEN_NAME_PSR + 1 \
                                 + MBR_LEN_TIMESTAMP + 1 \
                                 + MBR_LEN_COUNT + 1 \
                                 + MBR_LEN_DATAFILE_EXT)
#define MBR_DAS_UID             1001
#define MBR_DAS_GID             1001
#define MBR_ACQMODE_OBS         0
#define MBR_ACQMODE_TEST        1
#define MBR_PCAP_USER           ((unsigned char *) "das01")

typedef unsigned char BYTE;

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket);
void BuildFilename(struct tm *pstTime, int iCount, char acFilename[]);
int OpenFiles();
void CloseFiles();
void PrintUsage(const char *pcProgName);
void HandleSIGINT(int iSigNo);

int g_aiFiles[MAX_NUM_FILES] = {0};
int g_iCurrentFile = 0;
int g_iNumFiles = 1;    /* default is 1 file */
int g_iCurrentFileIndex = 0;
int g_iPacketCount = 0;
int g_iAcqMode = 0;     /* default is MBR_ACQMODE_OBS */
int g_iLockFile = 0;
pcap_t *g_pstHandle = NULL;

int main(int argc, char *argv[])
{
    char acErrBuf[PCAP_ERRBUF_SIZE] = {0};
    char *pcDevice = (char *) "eth0";   /* default device is eth0 */
    struct bpf_program stBPFProgram = {0};
    char *pcFilter = (char *) "udp";
    int iFlagOpt = 0;   /* BPF optimisation, false */
    bpf_u_int32 iNet = 0;
    bpf_u_int32 iMask = 0;
    const char *pcProgName = NULL;
    int iNextOpt = 0;
    int iFlagKill = MBR_FALSE;
    int iRet = 0;
    struct sigaction stSigHandler = {{0}};
    const char* const sShortOpts = "hd:f:m:k";  /* valid short options */
    const struct option stLongOpts[] = {        /* valid long options */
        { "help",       0, NULL, 'h' },
        { "device",     1, NULL, 'd' },
        { "files",      1, NULL, 'f' },
        { "mode",       1, NULL, 'm' },
        { "kill",       0, NULL, 'k' },
        { NULL,         0, NULL, 0   }
    };

    /* register the CTRL+C-handling function */
    stSigHandler.sa_handler = HandleSIGINT;
    iRet = sigaction(SIGINT, &stSigHandler, NULL);
    if (iRet != MBR_RET_SUCCESS)
    {
        perror("ERROR: sigaction");
        fprintf(stderr, "ERROR: Signal handler registration failed!\n");
        return MBR_RET_ERROR;
    }

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
                    && (g_iAcqMode != MBR_ACQMODE_TEST))
                {
                    fprintf(stderr, "ERROR: Mode should be either 0 or 1!\n");
                    PrintUsage(pcProgName);
                    return -1;
                }
                break;

            case 'k':   /* -k or --kill */
                /* kill any acquisition process already running */
                iFlagKill = MBR_TRUE;
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

    /* check if any other instance of this program is running */
    g_iLockFile = open(MBR_PATH_LOCKFILE,
                     (O_CREAT | O_EXCL),
                     (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (-1 == g_iLockFile)
    {
        if (EEXIST == errno)
        {
            /* the lock file already exists */
            if (MBR_TRUE == iFlagKill)
            {
                /* kill the instance that is already running, and continue */
                printf("Another instance found.\n");

                /* run the scrip to kill it */
                iRet = system(MBR_PATH_KILLSCRIPT);
                if (iRet != 0)
                {
                    perror("ERROR: system");
                    return -1;
                }
            }
            else
            {
                /* terminate */
                fprintf(stderr,
                        "ERROR: Another instance found!\n");
                return -1;
            }
        }
        else    /* if it is some other error, print message and exit */
        {
            perror("ERROR: open");
            return -1;
        }
    }

    iRet = OpenFiles();
    if (iRet != 0)
    {
        printf("ERROR: Error opening files!\n");
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != 0)
        {
            perror("ERROR: unlink");
            fprintf(stderr, "Lock file deletion failed! Please remove "
                            MBR_PATH_LOCKFILE " manually.");
            return -1;
        }
        return -1;
    }

    g_pstHandle = pcap_open_live(pcDevice,
                              MAX_SIZE_PACKET,
                              MODE_PROMISC,
                              TIMEOUT,
                              acErrBuf);
    if (NULL == g_pstHandle)
    {
        fprintf(stderr, "%s\n", acErrBuf);
        CloseFiles();
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != 0)
        {
            perror("ERROR: unlink");
            fprintf(stderr, "Lock file deletion failed! Please remove "
                            MBR_PATH_LOCKFILE " manually.");
            return -1;
        }
        return -1;
    }

    /* create a packet filter for UDP packets */
    iRet = pcap_lookupnet(pcDevice, &iNet, &iMask, acErrBuf);
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "%s\n", acErrBuf);
        iNet = 0;
        iMask = 0;
    }
    
    iRet = pcap_compile(g_pstHandle, &stBPFProgram, pcFilter, iFlagOpt, iNet);
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "ERROR: BPF compilation failed!\n");
        pcap_close(g_pstHandle);
        CloseFiles();
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != 0)
        {
            perror("ERROR: unlink");
            fprintf(stderr, "Lock file deletion failed! Please remove "
                            MBR_PATH_LOCKFILE " manually.");
            return -1;
        }
        return MBR_RET_ERROR;
    }

    iRet = pcap_setfilter(g_pstHandle, &stBPFProgram);
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "ERROR: Setting BPF failed!\n");
        pcap_close(g_pstHandle);
        CloseFiles();
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != 0)
        {
            perror("ERROR: unlink");
            fprintf(stderr, "Lock file deletion failed! Please remove "
                            MBR_PATH_LOCKFILE " manually.");
            return -1;
        }
        return MBR_RET_ERROR;
    }

    printf("Writing to file %d\n", g_iCurrentFileIndex);

    iRet = pcap_loop(g_pstHandle, -1, ProcessPacket, MBR_PCAP_USER);
    if (-1 == iRet)
    {
        fprintf(stderr, "ERROR: pcap_loop() failed!\n");
        /* clean up */
        pcap_close(g_pstHandle);
        CloseFiles();
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != 0)
        {
            perror("ERROR: unlink");
            fprintf(stderr, "Lock file deletion failed! Please remove "
                            MBR_PATH_LOCKFILE " manually.");
            return -1;
        }
        return -1;
    }
    else if (-2 == iRet)
    {
        /* pcap_breakloop() encountered, so continue */
    }

    /* clean up */
    pcap_close(g_pstHandle);
    CloseFiles();
    /* close the lock file and delete it */
    (void) close(g_iLockFile);
    iRet = unlink(MBR_PATH_LOCKFILE);
    if (iRet != 0)
    {
        perror("ERROR: unlink");
        fprintf(stderr, "Lock file deletion failed! Please remove "
                        MBR_PATH_LOCKFILE " manually.");
        return -1;
    }

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

    assert(pcUser != NULL);
    assert(pstPacketHeader != NULL);
    assert(pbPacket != NULL);

    stHeaderEth = (struct ether_header*) pbPacket;
    stHeaderIP  = (struct iphdr*) (pbPacket + sizeof(struct ether_header));
    stHeaderUDP = (struct udphdr*) (((BYTE *) stHeaderIP)
                                    + sizeof (struct iphdr));
    pbData = (BYTE *) (((BYTE *) stHeaderUDP) + sizeof (struct udphdr));

    (void) write(g_iCurrentFile, pbData, SIZE_PACKET);

    /* increment the packet count, check the limit, and set the current file
       pointer if necessary */
    ++g_iPacketCount;
    if (g_iPacketCount >= MAX_NUM_PKTSPERFILE)
    {
        ++g_iCurrentFileIndex;
        if (g_iCurrentFileIndex == g_iNumFiles)
        {
            printf("Stopping data acquisition...\n");
            pcap_breakloop(g_pstHandle);
            return;
        }
        g_iCurrentFile = g_aiFiles[g_iCurrentFileIndex];
        g_iPacketCount = 0;
        printf("Writing to file %d\n", g_iCurrentFileIndex);
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
            g_aiFiles[i] = open(acFilename,
                                (O_CREAT | O_EXCL | O_WRONLY),
                                (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
            if (-1 == g_aiFiles[i])
            {
                perror("ERROR: open");
                return -1;
            }
        }
        else
        {
            (void) sprintf(acFilename, MBR_TEST_FILE_PREFIX "%d", i);
            g_aiFiles[i] = open(acFilename,
                                (O_CREAT | O_WRONLY),
                                (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
            if (-1 == g_aiFiles[i])
            {
                perror("ERROR: open");
                return -1;
            }
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
    char acTimestamp[MBR_LEN_TIMESTAMP+1] = {0};
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
                   MBR_NAME_CHANNEL,
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
    printf("                                default is 'observation')\n");
    return;
}

/*
 * void HandleSIGINT(int iSigNo)
 *
 * Catches CTRL+C and cleans up before exiting
 */
void HandleSIGINT(int iSigNo)
{
    int iRet = MBR_RET_SUCCESS;

    /* clean up */
    pcap_close(g_pstHandle);
    CloseFiles();
    /* close the lock file and delete it */
    (void) close(g_iLockFile);
    iRet = unlink(MBR_PATH_LOCKFILE);
    if (iRet != 0)
    {
        perror("ERROR: unlink");
        fprintf(stderr, "Lock file deletion failed! Please remove "
                        MBR_PATH_LOCKFILE " manually.\n");
        /* exit */
        exit(MBR_RET_ERROR);
    }

    /* exit */
    exit(MBR_RET_SUCCESS);

    /* never reached */
    return;
}

