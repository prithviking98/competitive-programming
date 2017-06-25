/* mbr_acquire.c
 * Program to read packets from the specified Ethernet interface using the
 * libpcap library and write them to the disk. Running multiple instances of
 * this program is prohibited by the use of lock files. This program can also
 * be used for data sniffing, wherein every (MBR_SAMPINT)th packet is written
 * to shared memory. Another use of this program is to test if data is being
 * received on the Ethernet interface specified, and check for slips in that
 * data without writing to the disk.
 *
 * Usage: mbracquire [options]
 *     -h  --help                 Display this usage information
 *     -d  --device <dev_name>    Select the input device
 *                                (default is 'eth0')
 *     -f  --files <num_files>    Set the number of 2GB files to be written
 *                                (default is 1)
 *     -m  --mode                 Acquisition mode
 *                                ('obs' is 'observation' - filenames are
 *                                 formatted;
 *                                 'sniffacq' is 'sniff and acquire' - filenames
 *                                 are formatted, and are prefixed with
 *                                 'sniff_';
 *                                 'sniff' is 'sniff' - no files are created,
 *                                 data is just sniffed;
 *                                 'check' is 'check' - no files are created;
 *                                 default is 'observation')
 *     -o  --offset <offset>      In sniff modes, sets the packet offset
 *     -k  --kill                 Kills the existing instance of this program
 *
 * Created by Peeyush on 10 April 2008
 * Modified by Jayanth Chennamangalam
 * Modified by Desh
 */

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

#include "mbr_acquire.h"
#include "das.h"
#include "das_shm.h"
#include "mbr_dataheader.h"
#include "../socket/mbr_common.h"
#include "../socket/mbr_serialport.h"
#include "../socket/mbr_config.h"

extern fstream g_ErrLog;

int g_aiFiles[MAX_NUM_FILES] = {0};
int g_iCurrentFile = 0;
int g_iNumFiles = 1;    /* default is 1 file */
int g_iCurrentFileIndex = 0;
int g_iBuffer = 0;
int g_iFirstIter = DAS_TRUE;
int g_iBufferChange = 0;
int g_iPacketCount = 0;
int g_iAcqMode = MBR_ACQMODE_OBS;   /* default is MBR_ACQMODE_OBS */
int g_iLockFile = 0;
pcap_t *g_pstHandle = NULL;
int g_iSampOffset = 0;
DAS_BLOCKADDS_S g_stBlockAdds[DAS_NUM_BUFS] = {{0}};
DAS_SHM_DATATYPE *g_pBufBase[DAS_NUM_BUFS] = {NULL};
DAS_SHM_DATATYPE *g_pBasePointer = NULL;
DAS_SHM_DATATYPE *g_pWritePointer = NULL;
DAS_SHMINFO_S *g_pstShmInfo = NULL;
/* for checking */
int g_iCurrentMarker = 0;
int g_iPrevMarker = 0;
int g_iSlipCount = 0;
int g_aiSlips[MAX_NUM_SLIPS][MAX_NUM_INFOITEMS] = {{0}};

int main(int argc, char *argv[])
{
    char acErrBuf[PCAP_ERRBUF_SIZE] = {0};
    char *pcDevice = (char *) "eth0";   /* default device is eth0 */
    struct bpf_program stBPFProgram = {0};
    //TODO: check if 'udp' is enough
    char *pcFilter = (char *) "udp";
    int iFlagOpt = 1;                   /* BPF optimisation, true */
    bpf_u_int32 iNet = 0;
    bpf_u_int32 iMask = 0;
    const char *pcProgName = NULL;
    int iNextOpt = 0;
    int iFlagKill = MBR_FALSE;
    int iRet = MBR_RET_SUCCESS;
    char *pcUserAcqMode = NULL;
    struct sigaction stSigHandler = {{0}};
    DAS_BLOCK_S *pstBlock = NULL;
    int iBlockID = DAS_BLOCKID_START;   /* first block */
    int i = 0;
    const char* const sShortOpts = "hd:f:m:o:k";    /* valid short options */
    const struct option stLongOpts[] = {            /* valid long options */
        { "help",   0, NULL, 'h' },
        { "device", 1, NULL, 'd' },
        { "files",  1, NULL, 'f' },
        { "mode",   1, NULL, 'm' },
        { "offset", 1, NULL, 'o' },
        { "kill",   0, NULL, 'k' },
        { NULL,     0, NULL, 0   }
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
                MBR_PrintUsage(pcProgName);
                return MBR_RET_SUCCESS;

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
                    MBR_PrintUsage(pcProgName);
                    return MBR_RET_ERROR;
                }
                break;

            case 'm':   /* -m or --mode */
                /* set the acquisition mode */
                pcUserAcqMode = optarg;
                if (0 == strcmp(pcUserAcqMode, MBR_USERAM_OBS))
                {
                    g_iAcqMode = MBR_ACQMODE_OBS;
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_DIAG))
                {
                    printf("%s is not supported now!\n", MBR_USERAM_DIAG);
                    return MBR_RET_SUCCESS;
#if 0
                    g_iAcqMode = MBR_ACQMODE_DIAG;
#endif
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_SNIFFACQ))
                {
                    g_iAcqMode = MBR_ACQMODE_SNIFFACQ;
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_SNIFF))
                {
                    g_iAcqMode = MBR_ACQMODE_SNIFF;
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_CHECK))
                {
                    g_iAcqMode = MBR_ACQMODE_CHECK;
                }
                else
                {
                    fprintf(stderr, "ERROR: ");
                    fprintf(stderr,
                            "Mode should be either of "
                            "'%s', '%s', '%s', '%s', or '%s'!\n",
                            MBR_USERAM_OBS,
                            MBR_USERAM_DIAG,
                            MBR_USERAM_SNIFFACQ,
                            MBR_USERAM_SNIFF,
                            MBR_USERAM_CHECK);
                    MBR_PrintUsage(pcProgName);
                    return MBR_RET_ERROR;
                }
                break;

            case 'o':   /* -o or --offset */
                /* set the sampling offset */
                g_iSampOffset = atoi(optarg);

            case 'k':   /* -k or --kill */
                /* kill any acquisition process already running */
                iFlagKill = MBR_TRUE;
                break;

            case '?':   /* user specified an invalid option */
                /* print usage info and terminate with error */
                fprintf(stderr, "ERROR: Invalid option!\n");
                MBR_PrintUsage(pcProgName);
                return MBR_RET_ERROR;

            case -1:    /* done with options */ 
                break;

            default:    /* unexpected */
                assert(0);
        }
    } while (iNextOpt != -1);

    /* open the error log file */
    iRet = MBR_OpenErrLog();
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "ERROR: Opening error log file failed!\n");
        return MBR_RET_ERROR;
    }

    /* register the CTRL+C-handling function */
    stSigHandler.sa_handler = MBR_HandleStopSignals;
    iRet = sigaction(SIGINT, &stSigHandler, NULL);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "sigaction(" << SIGINT << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        fprintf(stderr, "ERROR: Signal handler registration failed!\n");
        return MBR_RET_ERROR;
    }

    /* register the SIGTERM-handling function */
    stSigHandler.sa_handler = MBR_HandleStopSignals;
    iRet = sigaction(SIGTERM, &stSigHandler, NULL);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "sigaction(" << SIGTERM << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        fprintf(stderr, "ERROR: Signal handler registration failed!\n");
        return MBR_RET_ERROR;
    }

    /* check if any other instance of this program is running */
    g_iLockFile = open(MBR_PATH_LOCKFILE,
                       (O_CREAT | O_EXCL),
                       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (MBR_RET_ERROR == g_iLockFile)
    {
        if (EEXIST == errno)
        {
            /* the lock file already exists */
            if (MBR_TRUE == iFlagKill)
            {
                /* kill the instance that is already running, and
                   continue */
                printf("Another instance found.\n");

                /* run the script to kill it */
                iRet = system(MBR_PATH_KILLSCRIPT);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "system(" << MBR_PATH_KILLSCRIPT
                             << ") failed, "
                             << "errno set to " << errno << " with error: "
                             << strerror(errno)
                             << endl;
                    fprintf(stderr,
                            "ERROR: Killing existing instance failed!\n");
                    return MBR_RET_ERROR;
                }
            }
            else
            {
                /* terminate */
                fprintf(stderr,
                        "ERROR: Another instance found!\n");
                return MBR_RET_ERROR;
            }
        }
        else    /* if it is some other error, print message and exit */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "open(" << MBR_PATH_LOCKFILE << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            fprintf(stderr, "ERROR: Opening lock file failed!\n");
            return MBR_RET_ERROR;
        }
    }

    if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
    {
        iRet = MBR_OpenFiles();
        if (iRet != MBR_RET_SUCCESS)
        {
            printf("ERROR: Error opening files!\n");
            iRet = unlink(MBR_PATH_LOCKFILE);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "ERROR: Lock file deletion failed! "
                                "Please remove " MBR_PATH_LOCKFILE
                                " manually.");
                return MBR_RET_ERROR;
            }
            return MBR_RET_ERROR;
        }
    }

    if ((g_iAcqMode & MBR_AMMASK_PU) != 0)  /* PU flag is ON */
    {
        iRet = MBR_CreateDeviceLookup();
        if (iRet != MBR_RET_SUCCESS)
        {
            fprintf(stderr, "ERROR: Device lookup failed!\n");
            MBR_CloseFiles();
            iRet = unlink(MBR_PATH_LOCKFILE);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "ERROR: Lock file deletion failed! "
                                "Please remove " MBR_PATH_LOCKFILE
                                " manually.");
                return MBR_RET_ERROR;
            }
            return MBR_RET_ERROR;
        }

#if 0
        iRet = MBR_GetLastRFHistEntry(acRFHist);
        if (iRet != MBR_RET_SUCCESS)
        {
            fprintf(stderr, "WARNING: Getting the last RF history entry "
                            "failed! Packets will not contain RF "
                            "information!\n");
        }
        (void) sscanf(acRFHist, "%s %s %g %s\t%g %s\t%g %s\t%g %s\t%i\n",
                      acTemp, acTemp,   /* for date and time */
                      &fTemp, acAtten1,
                      &fTemp, acAtten2,
                      &fTemp, acAtten3,
                      &fTemp, acAtten4,
                      &iLOFreq);
        stRFVals.iAtten1 = MBR_Bitmap2Int(acAtten1);
        stRFVals.iAtten2 = MBR_Bitmap2Int(acAtten2);
        stRFVals.iAtten3 = MBR_Bitmap2Int(acAtten3);
        stRFVals.iAtten4 = MBR_Bitmap2Int(acAtten4);
        stRFVals.iLOFreq = (short int) iLOFreq;
#endif
    }

    g_pstHandle = pcap_open_live(pcDevice,
                                 SIZE_FULL_PACKET,
                                 MODE_PROMISC,
                                 TIMEOUT,
                                 acErrBuf);
    if (NULL == g_pstHandle)
    {
        fprintf(stderr, "%s\n", acErrBuf);
        if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
        {
            MBR_CloseFiles();
        }
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            fprintf(stderr, "ERROR: Lock file deletion failed! "
                            "Please remove " MBR_PATH_LOCKFILE
                            " manually.");
            return MBR_RET_ERROR;
        }
        return MBR_RET_ERROR;
    }

    /* create a packet filter for UDP packets */
    iRet = pcap_lookupnet(pcDevice, &iNet, &iMask, acErrBuf);
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "%s\n", acErrBuf);
        iNet = 0;
        iMask = 0;
    }

    iRet = pcap_compile(g_pstHandle,
                        &stBPFProgram,
                        pcFilter,
                        iFlagOpt,
                        iNet);
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "ERROR: BPF compilation failed!\n");
        pcap_close(g_pstHandle);
        if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
        {
            MBR_CloseFiles();
        }
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            fprintf(stderr, "ERROR: Lock file deletion failed! "
                            "Please remove " MBR_PATH_LOCKFILE
                            " manually.");
            return MBR_RET_ERROR;
        }
        return MBR_RET_ERROR;
    }

    iRet = pcap_setfilter(g_pstHandle, &stBPFProgram);
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "ERROR: Setting BPF failed!\n");
        pcap_close(g_pstHandle);
        if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
        {
            MBR_CloseFiles();
        }
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            fprintf(stderr, "ERROR: Lock file deletion failed! "
                            "Please remove " MBR_PATH_LOCKFILE
                            " manually.");
            return MBR_RET_ERROR;
        }
        return MBR_RET_ERROR;
    }

    if ((g_iAcqMode & MBR_AMMASK_SHM) != 0) /* SHM flag is ON */
    {
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
            MBR_CloseFiles();
            iRet = unlink(MBR_PATH_LOCKFILE);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "ERROR: Lock file deletion failed! "
                                "Please remove " MBR_PATH_LOCKFILE
                                " manually.");
                return MBR_RET_ERROR;
            }
            return MBR_RET_ERROR;
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
                MBR_CloseFiles();
                iRet = unlink(MBR_PATH_LOCKFILE);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                             << "errno set to " << errno << " with error: "
                             << strerror(errno)
                             << endl;
                    fprintf(stderr, "ERROR: Lock file deletion failed! "
                                    "Please remove " MBR_PATH_LOCKFILE
                                    " manually.");
                    return MBR_RET_ERROR;
                }
                return MBR_RET_ERROR;
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
    }

    if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
    {
        printf("Writing to file %d\n", g_iCurrentFileIndex);
    }

    iRet = pcap_loop(g_pstHandle, -1, MBR_ProcessPacket, MBR_PCAP_USER);
    if (MBR_RET_ERROR == iRet)
    {
        fprintf(stderr, "ERROR: pcap_loop() failed!\n");
        /* clean up */
        if ((g_iAcqMode & MBR_AMMASK_SHM) != 0) /* SHM flag is ON */
        {
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        }
        pcap_close(g_pstHandle);
        if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
        {
            MBR_CloseFiles();
        }
        iRet = unlink(MBR_PATH_LOCKFILE);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            fprintf(stderr, "ERROR: Lock file deletion failed! "
                            "Please remove " MBR_PATH_LOCKFILE
                            " manually.");
            return MBR_RET_ERROR;
        }
        return MBR_RET_ERROR;
    }
    else if (-2 == iRet)
    {
        /* pcap_breakloop() encountered, so continue */
    }

    if ((g_iAcqMode & MBR_AMMASK_SHM) != 0) /* SHM flag is ON */
	{
	    /* set the status flag to DAS_STATUS_WRITEDONE */
	    g_pstShmInfo->iStatus = DAS_STATUS_WRITEDONE;

	    /* clean up */
	    /* delete buffers */    
	    iBlockID = DAS_BLOCKID_START;
	    for (i = 0; i < DAS_NUM_BUFS; ++i)
	    {
	        iRet = shmdt(g_stBlockAdds[i].pData);
	        if (iRet != MBR_RET_SUCCESS)
	        {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "shmdt(data, " << iBlockID << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "Detaching data segment failed!\n");
	            /* clean up */
	            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
	            pcap_close(g_pstHandle);
                MBR_CloseFiles();
                iRet = unlink(MBR_PATH_LOCKFILE);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                             << "errno set to " << errno << " with error: "
                             << strerror(errno)
                             << endl;
                    fprintf(stderr, "ERROR: Lock file deletion failed! "
                                    "Please remove " MBR_PATH_LOCKFILE
                                    " manually.");
                    return MBR_RET_ERROR;
                }
	            return MBR_RET_ERROR;
	        }
	        iRet = shmdt(g_stBlockAdds[i].pstBlock);
	        if (iRet != MBR_RET_SUCCESS)
	        {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "shmdt(block, " << iBlockID << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "Detaching data segment failed!\n");
	            /* clean up */
	            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
	            pcap_close(g_pstHandle);
                MBR_CloseFiles();
                iRet = unlink(MBR_PATH_LOCKFILE);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                             << "errno set to " << errno << " with error: "
                             << strerror(errno)
                             << endl;
                    fprintf(stderr, "ERROR: Lock file deletion failed! "
                                    "Please remove " MBR_PATH_LOCKFILE
                                    " manually.");
                    return MBR_RET_ERROR;
                }
	            return MBR_RET_ERROR;
	        }
	        ++iBlockID;
	    }

	    iRet = shmdt(g_pstShmInfo);
	    if (iRet != MBR_RET_SUCCESS)
	    {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "shmdt(shminfo) failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            fprintf(stderr, "Detaching shminfo segment failed!\n");
	        /* clean up */
	        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
	        pcap_close(g_pstHandle);
            MBR_CloseFiles();
            iRet = unlink(MBR_PATH_LOCKFILE);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "ERROR: Lock file deletion failed! "
                                "Please remove " MBR_PATH_LOCKFILE
                                " manually.");
                return MBR_RET_ERROR;
            }
	        return MBR_RET_ERROR;
	    }
	}

    /* clean up */
    pcap_close(g_pstHandle);
    if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
    {
        MBR_CloseFiles();
    }
    /* close the lock file and delete it */
    (void) close(g_iLockFile);
    iRet = unlink(MBR_PATH_LOCKFILE);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        fprintf(stderr, "ERROR: Lock file deletion failed! "
                        "Please remove " MBR_PATH_LOCKFILE
                        " manually.");
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}

void MBR_ProcessPacket(u_char *pcUser,
                       const struct pcap_pkthdr *pstPacketHeader,
                       const u_char *pbPacket)
{
    struct ether_header *stHeaderEth = NULL;
    struct iphdr *stHeaderIP = NULL;
    struct udphdr *stHeaderUDP = NULL;
    BYTE *pbData = NULL;
    MBR_DATA_HEADER_S *pstDataHeader = NULL;
    BYTE *pbMarkerPos = NULL;
    MBR_RF_VALS_S stRFVals = {0};
    int i = 0;

    assert(pcUser != NULL);
    assert(pstPacketHeader != NULL);
    assert(pbPacket != NULL);

    stHeaderEth = (struct ether_header*) pbPacket;
    stHeaderIP  = (struct iphdr*) (pbPacket + sizeof(struct ether_header));
    stHeaderUDP = (struct udphdr*) (((BYTE *) stHeaderIP)
                                    + sizeof (struct iphdr));
    pbData = (BYTE *) (((BYTE *) stHeaderUDP) + sizeof (struct udphdr));

    if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
    {
        (void) write(g_iCurrentFile, pbData, SIZE_PACKET);
    }

    /* check if MBR_SAMPINT has passed, and if yes, write to shared memory */
    if (((g_iAcqMode & MBR_AMMASK_SHM) != 0) /* SHM flag is ON */
		&& (g_iSampOffset == (g_iPacketCount % MBR_SAMPINT)))
    {
	    /* if the end of the buffer is reached, reset the write pointer to
           the base pointer of the next buffer */
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
	        if (DAS_STATUS_FRESH
                == g_stBlockAdds[g_iBuffer].pstBlock->iFlagData)
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

        /* reads attenuator values from the bitmap file and lo frequency from 
           the config file and update the values of attenuators and LO */
        if ((g_iAcqMode & MBR_AMMASK_PU) != 0)  /* PU flag is ON */
        {
            /* declaring temporary variables here, so that the overhead in
               processing non-sampled packets is reduced */
            char acAtten1[MBR_BITPOS_ATTENLATCH+1] = {0};
            char acAtten2[MBR_BITPOS_ATTENLATCH+1] = {0};
            char acAtten3[MBR_BITPOS_ATTENLATCH+1] = {0};
            char acAtten4[MBR_BITPOS_ATTENLATCH+1] = {0};
            char acTemp[MBR_MAX_LEN_GENSTRING] = {0};
            char acRFHist[MBR_MAX_LEN_GENSTRING] = {0};
            float fTemp = 0.0;
            int iLOFreq = 0;
            int iRet = MBR_RET_SUCCESS;

            iRet = MBR_GetLastRFHistEntry(acRFHist);
            if (iRet != MBR_RET_SUCCESS)
            {
                fprintf(stderr, "WARNING: Getting the last RF history entry "
                                "failed! Packets will not contain RF "
                                "information!\n");
            }
            (void) sscanf(acRFHist, "%s %s %g %s\t%g %s\t%g %s\t%g %s\t%i\n",
                          acTemp, acTemp,   /* for date and time */
                          &fTemp, acAtten1,
                          &fTemp, acAtten2,
                          &fTemp, acAtten3,
                          &fTemp, acAtten4,
                          &iLOFreq);
            stRFVals.iAtten1 = MBR_Bitmap2Int(acAtten1);
            stRFVals.iAtten2 = MBR_Bitmap2Int(acAtten2);
            stRFVals.iAtten3 = MBR_Bitmap2Int(acAtten3);
            stRFVals.iAtten4 = MBR_Bitmap2Int(acAtten4);
            stRFVals.iLOFreq = (short int) iLOFreq;

            pstDataHeader = (MBR_DATA_HEADER_S *) pbData;
            (void) memcpy((((char *) pstDataHeader)
                            + MBR_SDH_GetAtten1Pos(pstDataHeader)),
                          &stRFVals,
                          sizeof(stRFVals));
        }
        (void) memcpy(g_pWritePointer, pbData, SIZE_PACKET);
        g_pWritePointer += SIZE_PACKET;
        g_pstShmInfo->iWrittenData += SIZE_PACKET;
    }

    /* increment the packet count, check the limit, and set the current file
       pointer if necessary */
    ++g_iPacketCount;
    if (MAX_NUM_PKTSPERFILE == g_iPacketCount)
    {
        ++g_iCurrentFileIndex;
        if (g_iCurrentFileIndex == g_iNumFiles)
        {
            printf("Stopping data acquisition...\n");
            printf("%d packets processed.\n", g_iPacketCount);
            if ((g_iAcqMode & MBR_AMMASK_SHM) != 0) /* SHM flag is ON */
			{
	            printf("%d buffer changes.\n", g_iBufferChange);
			}
            pcap_breakloop(g_pstHandle);
            return;
        }
        g_iCurrentFile = g_aiFiles[g_iCurrentFileIndex];
        g_iPacketCount = 0;
        if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
        {
            printf("Writing to file %d\n", g_iCurrentFileIndex);
        }
    }
	
    if ((g_iAcqMode & MBR_AMMASK_SC) != 0)  /* SC flag is ON */
	{
	    pbMarkerPos = pbData + LEN_DATAHEADER; 
	    g_iCurrentMarker = (unsigned int) ntohl((*(unsigned int *)pbMarkerPos));
	    if (g_iPacketCount != 1)
	    {
	        /* this is not the first packet */
	        if (g_iCurrentMarker != (g_iPrevMarker + 1))
	        {
	            g_aiSlips[g_iSlipCount][POS_PREV] = g_iPrevMarker;
	            g_aiSlips[g_iSlipCount][POS_CURRENT] = g_iCurrentMarker;
	            g_aiSlips[g_iSlipCount][POS_PKTCOUNT] = g_iPacketCount;
	            ++g_iSlipCount;
	            if (MAX_NUM_SLIPS == g_iSlipCount)
	            {
	                printf("Slip count exceeded limit! Wrapping around!\n");
	                g_iSlipCount = 0;
	            }
	        }
	    }
	    g_iPrevMarker = g_iCurrentMarker;

        if (MAX_NUM_CHECKPKTSPERFILE == g_iPacketCount)
        {
            printf("%d packets processed.\n", g_iPacketCount);
            printf("%d slips detected!\n", g_iSlipCount);
            for (i = 0; i < g_iSlipCount; ++i)
            {
                printf("Slip detected! ");
                printf("Previous = %x, current = %x, diff = %d, "
                       "packet count = %d\n",
                       g_aiSlips[i][POS_PREV],
                       g_aiSlips[i][POS_CURRENT],
                       (g_aiSlips[i][POS_CURRENT] - g_aiSlips[i][POS_PREV]),
                       g_aiSlips[i][POS_PKTCOUNT]);
            }
            pcap_breakloop(g_pstHandle);
            return;
        }
    }

    return;
}

int MBR_OpenFiles()
{
    int i = 0;
    time_t Time;
    struct tm *pstTime = NULL;
    char acFilename[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;

    /* get the current time */
    Time = time(NULL);
    pstTime = localtime(&Time);

    for (i = 0; i < g_iNumFiles; ++i)
    {
        /* build the file name */
        if ((g_iAcqMode & MBR_AMMASK_FF) != 0)  /* FF flag is ON */
        {
            MBR_BuildFilename(pstTime, i, acFilename);
            /* in this, the files created should not be replaced */
            g_aiFiles[i] = open(acFilename,
                                (O_CREAT | O_EXCL | O_WRONLY),
                                (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
            if (MBR_RET_ERROR == g_aiFiles[i])
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "open(" << acFilename << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "ERROR: Opening data file failed!\n");
                return MBR_RET_ERROR;
            }
        }
        else                                    /* FF flag is OFF */
        {
            if (MBR_ACQMODE_DIAG == g_iAcqMode)
            {
                (void) sprintf(acFilename, MBR_FILENPREFIX_DIAG "%d", i);
            }
            /* in this case, any files with the same name will be replaced */
            g_aiFiles[i] = open(acFilename,
                                (O_CREAT | O_EXCL | O_WRONLY),
                                (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
            if (MBR_RET_ERROR == g_aiFiles[i])
            {
                if (EEXIST == errno)
                {
                    /* file exists, so delete it */
                    /* NOTE: ensure that no other process has this file opened.
                       if the file is not removed, it will lead to termination
                       of this program */
                    iRet = unlink(acFilename);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "unlink(" << acFilename << ") failed, "
                                 << "errno set to " << errno << " with error: "
                                 << strerror(errno)
                                 << endl;
                        fprintf(stderr,
                                "ERROR: Data file deletion failed! "
                                "Please remove %s manually.",
                                acFilename);
                        return MBR_RET_ERROR;
                    }
                }
            }
            (void) close(g_aiFiles[i]);

            /* now that we have (almost) ensured that a file with the same name
               does not exist, open the file for writing */
            g_aiFiles[i] = open(acFilename,
                                (O_CREAT | O_WRONLY),
                                (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
            if (MBR_RET_ERROR == g_aiFiles[i])
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "open(" << acFilename << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                fprintf(stderr, "ERROR: Opening data file failed!\n");
                return MBR_RET_ERROR;
            }
        }

        /* set the owner to 'das' */
        iRet = chown(acFilename, MBR_DAS_UID, MBR_DAS_GID);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "chown(" << acFilename << ", " << MBR_DAS_UID << ", "
                     << MBR_DAS_GID << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            fprintf(stderr,
                    "ERROR: Changing owndership of data file failed!\n");
            return MBR_RET_ERROR;
        }
    }

    /* set the current file pointer to the first file pointer */
    g_iCurrentFile = g_aiFiles[0];

    return MBR_RET_SUCCESS;
}

void MBR_BuildFilename(struct tm *pstTime, int iCount, char acFilename[])
{
    char acTimestamp[MBR_LEN_TS+1] = {0};
    char acCount[MBR_LEN_COUNT+1] = {0};
    char acPrefix[MBR_MAX_LEN_GENSTRING] = {0};
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

    if (MBR_ACQMODE_SNIFFACQ == g_iAcqMode)
    {
        (void) strcpy(acPrefix, MBR_FILENPREFIX_SNIFFACQ);
        (void) strcat(acPrefix, "_");   /* we don't want a beginning underscore
                                           for MBR_ACQMODE_OBS, where there is
                                           no prefix */
    }

    (void) strftime(acTimestamp, sizeof(acTimestamp), "%Y%m%d_%H%M%S", pstTime);
    (void) sprintf(acFilename,
                   "%s%s_%s_%s_%s.%s",
                   acPrefix,    /* 'NULL', in the case of MBR_ACQMODE_OBS */
                   MBR_NAME_CHANNEL,
                   MBR_NAME_PSR,
                   acTimestamp,
                   acCount,
                   MBR_DATAFILE_EXT);

    return;
}

void MBR_CloseFiles()
{
    int i = 0;

    for (i = 0; i < g_iNumFiles; ++i)
    {
        (void) close(g_aiFiles[i]);
    }

    return;
}

/*
 * void MBR_HandleStopSignals(int iSigNo)
 *
 * Catches SIGTERM and CTRL+C and cleans up before exiting
 */
void MBR_HandleStopSignals(int iSigNo)
{
    int iRet = MBR_RET_SUCCESS;
    int i = 0;

    /* clean up */
    pcap_close(g_pstHandle);
    if ((g_iAcqMode & MBR_AMMASK_DW) != 0)  /* DW flag is ON */
    {
        MBR_CloseFiles();
    }
    if ((g_iAcqMode & MBR_AMMASK_SC) != 0)  /* SC flag is ON */
    {
        printf("%d packets processed.\n", g_iPacketCount);
        printf("%d slips detected!\n", g_iSlipCount);
        for (i = 0; i < g_iSlipCount; ++i)
        {
            printf("Slip detected! ");
            printf("Previous = %x, current = %x, diff = %d, "
                   "packet count = %d\n",
                   g_aiSlips[i][POS_PREV],
                   g_aiSlips[i][POS_CURRENT],
                   (g_aiSlips[i][POS_CURRENT] - g_aiSlips[i][POS_PREV]),
                   g_aiSlips[i][POS_PKTCOUNT]);
        }
    }
    /* close the lock file and delete it */
    (void) close(g_iLockFile);
    iRet = unlink(MBR_PATH_LOCKFILE);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "unlink(" << MBR_PATH_LOCKFILE << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        fprintf(stderr, "ERROR: Lock file deletion failed! "
                        "Please remove " MBR_PATH_LOCKFILE
                        " manually.");
        /* exit */
        exit(MBR_RET_ERROR);
    }

    /* exit */
    exit(MBR_RET_SUCCESS);

    /* never reached */
    return;
}

void MBR_PrintUsage(const char *pcProgName)
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
    printf("                               ('obs' is 'observation' - filenames ");
    printf("are formatted;\n");
    printf("                                'sniffacq' is 'sniff and acquire' - ");
    printf("filenames are\n");
    printf("                                formatted, and are prefixed with ");
    printf("'sniff_';\n");
    printf("                                'sniff' is 'sniff' - no files are ");
    printf("created, data is\n");
    printf("                                just sniffed;\n");
    printf("                                'check' is 'check' - no files are ");
    printf("created;\n");
    printf("                                default is 'observation')\n");
    printf("    -o  --offset <offset>      In sniff modes, sets the packet ");
    printf("offset\n");
    printf("    -k  --kill                 Kills the existing instance of ");
    printf("this program\n");
    
    return;
}

