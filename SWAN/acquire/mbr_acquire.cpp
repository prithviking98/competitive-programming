/* mbr_acquire.cpp
 * Program to read packets from the specified Ethernet interface using the
 * libpcap library and write them to the disk. Running multiple instances of
 * this program is prohibited by the use of lock files. This program - along
 * with mbracqsniff - is used for data sniffing, wherein every (MBR_SAMPINT)th
 * packet is written to shared memory. Another use of this program is to test if
 * data is being received on the Ethernet interface specified, and check for
 * slips in that data without writing to the disk.
 *
 * Usage: mbracquire [options]
 *     -h  --help                 Display this usage information
 *     -d  --device <dev_name>    Select the input device
 *                                (default is 'eth0')
 *     -f  --files <num_files>    Set the number of 2GB files to be written
 *                                (default is 1)
 *     -t  --time <time_in_min>   Set the acquisition time in minutes
 *                                (default is 1)
 *     -m  --mode                 Acquisition mode
 *                                ('obs' is 'observation' - filenames are
 *                                 formatted;
 *                                 'sniffacq' is 'sniff and acquire' - filenames
 *                                 are formatted, and are prefixed with
 *                                 'raw_';
 *                                 'sniff' is 'sniff' - no files are created,
 *                                 data is just sniffed;
 *                                 'check' is 'check' - no files are created;
 *                                 default is 'observation')
 *     -s  --source <name>        Override the source name read from the
 *                                config file
 *     -o  --offset <offset>      In sniff modes, sets the packet offset
 *     -k  --kill                 Kills the existing instance of this program
 *     -c  --control              Use the M&C config file
 *     -v  --version              Display the version
 *
 * Authors:
 *  Peeyush Prasad (2008.04.10)
 *  Jayanth Chennamangalam
 *  Desh
 */

#include <iostream>
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
#include <math.h>

#include "mbr_common.h"
#include "mbr_acquire.h"
#include "das.h"
#include "das_shm.h"
#include "mbr_dataheader.h"
#include "mbr_serialport.h"
#include "mbr_config.h"

extern const char *g_pcVersion;
extern fstream g_ErrLog;

int g_aiFiles[MAX_NUM_FILES] = {0};
int g_iCurrentFile = 0;
int g_iNumFiles = 1;                /* default is 1 file */
int g_iTime = 1;                    /* default is 1 minute */
char g_acChannel[MBR_MAX_LEN_GENSTRING] = {0};
char g_acSourceName[MBR_MAX_LEN_GENSTRING] = {0};
int g_iCurrentFileIndex = 0;
int g_iBuffer = 0;
int g_iFirstIter = DAS_TRUE;
int g_iBufferChange = 0;
int g_iPacketCount = 0;
int g_iAcqMode = MBR_MODE_OBS;   /* default is MBR_MODE_OBS */
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
    char acFilter[MBR_MAX_LEN_GENSTRING] = {0};
    int iFlagOpt = 1;                   /* BPF optimisation, true */
    bpf_u_int32 iNet = 0;
    bpf_u_int32 iMask = 0;
    bool bIsDurInFiles = false;
    bool bIsDurInTime = false;
    float fSampRate = 0.0;
    float fTimePerFile = 0.0;
    char acSampRate[MBR_MAX_LEN_GENSTRING] = {0};
    const char *pcProgName = NULL;
    int iNextOpt = 0;
    bool bKillExInst = false;
    int iRet = MBR_RET_SUCCESS;
    char *pcUserAcqMode = NULL;
    struct sigaction stSigHandler = {{0}};
    DAS_BLOCK_S *pstBlock = NULL;
    bool bIsOnMC = false;
    int iCfgFile = MBR_CFG_DAS;
    int iBlockID = DAS_BLOCKID_START;   /* first block */
    int i = 0;
    /* valid short options */
    const char* const sShortOpts = "hd:f:t:m:s:o:kcv";
    /* valid long options */
    const struct option stLongOpts[] = {
        { "help",       0,  NULL,   'h' },
        { "device",     1,  NULL,   'd' },
        { "files",      1,  NULL,   'f' },
        { "time",       1,  NULL,   't' },
        { "mode",       1,  NULL,   'm' },
        { "source",     1,  NULL,   's' },
        { "offset",     1,  NULL,   'o' },
        { "kill",       0,  NULL,   'k' },
        { "control",    0,  NULL,   'c' },
        { "version",    0,  NULL,   'v' },
        { NULL,         0,  NULL,   0   }
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
                if (!(bIsDurInTime))
                {
                    g_iNumFiles = atoi(optarg);
                    if ((g_iNumFiles < 1) || (g_iNumFiles > MAX_NUM_FILES))
                    {
                        fprintf(stderr,
                                "ERROR: Number of files should be at least 1 ");
                        fprintf(stderr,
                                "and not more than %d!\n",
                                MAX_NUM_FILES);
                        MBR_PrintUsage(pcProgName);
                        return MBR_RET_ERROR;
                    }
                    bIsDurInFiles = true;
                }
                break;

            case 't':   /* -t or --time */
                /* set the acquisition time in minutes */
                if (!(bIsDurInFiles))
                {
                    g_iTime = atoi(optarg);         /* in minutes */
                    bIsDurInTime = true;
                }
                break;

            case 'm':   /* -m or --mode */
                /* set the acquisition mode */
                pcUserAcqMode = optarg;
                if (0 == strcmp(pcUserAcqMode, MBR_USERAM_OBS))
                {
                    g_iAcqMode = MBR_MODE_OBS;
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_DIAG))
                {
                    printf("%s is no longer supported!\n", MBR_USERAM_DIAG);
                    return MBR_RET_SUCCESS;
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_SNIFFACQ))
                {
                    g_iAcqMode = MBR_MODE_SNIFFACQ;
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_SNIFF))
                {
                    g_iAcqMode = MBR_MODE_SNIFF;
                }
                else if (0 == strcmp(pcUserAcqMode, MBR_USERAM_CHECK))
                {
                    g_iAcqMode = MBR_MODE_CHECK;
                }
                else
                {
                    fprintf(stderr, "ERROR: ");
                    fprintf(stderr,
                            "Mode should be either of "
                            "'%s', '%s', '%s', or '%s'!\n",
                            MBR_USERAM_OBS,
                            MBR_USERAM_SNIFFACQ,
                            MBR_USERAM_SNIFF,
                            MBR_USERAM_CHECK);
                    MBR_PrintUsage(pcProgName);
                    return MBR_RET_ERROR;
                }
                break;

            case 's':   /* -s or --source */
                /* set the source name */
                (void) strncpy(g_acSourceName, optarg, sizeof(g_acSourceName));
                break;

            case 'o':   /* -o or --offset */
                /* set the sampling offset */
                g_iSampOffset = atoi(optarg);

            case 'k':   /* -k or --kill */
                /* kill any acquisition process already running */
                bKillExInst = true;
                break;

            case 'c':   /* -c or --control */
                /* set the M&C flag, indicating that mbracquire is being run on
                   the M&C machine */
                bIsOnMC = true;
                break;

            case 'v':   /* -v or --version */
                /* display the version and exit */
                cout << g_pcVersion << endl;
                return MBR_RET_SUCCESS;

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
    iRet = MBR_OpenErrLog(true);
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
            if (true == bKillExInst)
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

    if (bIsDurInTime)
    {
        /* convert the time to number of 2GB files */

        if (bIsOnMC)
        {
            /* use the fastest data rate, to create as many number of 2GB files
               as would be needed */
            fSampRate = (((float) MBR_FASTEST_DATARATE) / MBR_SAMPINT)
                        * MBR_MAX_DAS;
            cout << fSampRate << endl;
            fTimePerFile = ((float) MAX_SIZE_FILE) / (fSampRate * 1024 * 1024);
            cout << fTimePerFile << endl;
            g_iNumFiles = (int) ceilf(((float) (g_iTime * 60)) / fTimePerFile);
        }
        else
        {
            /* get the data rate/sampling frequency from the config file */
            iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                                   MBR_CFG_DAS,
                                   MBR_XML_ENT_FPGA,
                                   MBR_XML_ATT_SAMPCLKFREQ,
                                   0,
                                   acSampRate);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_ConfigEntry("<< MBR_XML_ENT_FPGA
                         << ") returned "
                         << iRet
                         << endl;
                fprintf(stderr,
                        "ERROR: Configuration file read failed!\n");
                /* remove the lock file */
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
            printf("Sampling rate: %s\n", acSampRate);

            fSampRate = atof(acSampRate);   /* in MB/s */
            fTimePerFile = ((float) MAX_SIZE_FILE) / (fSampRate * 1024 * 1024);
            g_iNumFiles = (int) ceilf(((float) (g_iTime * 60)) / fTimePerFile);
        }
        printf("Number of files that will be written: %d\n",
               g_iNumFiles);
    }

    if (!(bIsOnMC))
    {
        /* get the channel/band number from the config file */
        iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                               MBR_CFG_DAS,
                               MBR_XML_ENT_DAS,
                               MBR_XML_ATT_ID,
                               0,
                               g_acChannel);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_ConfigEntry("<< MBR_XML_ENT_DAS << ") returned "
                     << iRet
                     << endl;
            fprintf(stderr, "ERROR: Configuration file read failed!\n");
            /* remove the lock file */
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
    else
    {
        /* if mbracquire is running on the M&C machine, set the channel number
           to MBR_MCCHNUM */
        (void) strcpy(g_acChannel, MBR_MCCHNUM);
    }
    printf("Channel number: %s\n", g_acChannel);

    /* read the source name from the config file if the user has not supplied
       any name */
    if (0 == g_acSourceName[0])
    {
        if (bIsOnMC)
        {
            iCfgFile = MBR_CFG_MC;
        }

        iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                               iCfgFile,
                               MBR_XML_ENT_SOURCE,
                               MBR_XML_ATT_NAME,
                               0,
                               g_acSourceName);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_ConfigEntry("<< MBR_XML_ENT_SOURCE << ") returned "
                     << iRet
                     << endl;
            fprintf(stderr, "ERROR: Configuration file read failed!\n");
            /* remove the lock file */
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
    printf("Source name: %s\n", g_acSourceName);

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

    /* build the filter string: capture only UDP packets whose destination port
       matches that of raw or sniffed data packets. raw data packets have UDP
       destination port MBR_PORT_DST_RAWDATA, and sniffed data packets,
       MBR_PORT_DST_SNIFFDATA */
    (void) sprintf(acFilter,
                   "udp and dst port %d or %d",
                   MBR_PORT_DST_RAWDATA,
                   MBR_PORT_DST_SNIFFDATA);

    iRet = pcap_compile(g_pstHandle,
                        &stBPFProgram,
                        acFilter,
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

/*
 * void MBR_ProcessPacket(u_char *pcUser.)
 *                        const struct pcap_pkthdr *pstPacketHeader,
 *                        const u_char *pbPacket)
 *
 * Processes one captured data packet
 */
void MBR_ProcessPacket(u_char *pcUser,
                       const struct pcap_pkthdr *pstPacketHeader,
                       const u_char *pbPacket)
{
    struct ether_header *stHeaderEth = NULL;
    struct iphdr *stHeaderIP = NULL;
    struct udphdr *stHeaderUDP = NULL;
    BYTE *pbData = NULL;
    BYTE *pbMarkerPos = NULL;
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
            printf("Transmission is ON.\n");
            pcap_breakloop(g_pstHandle);
            return;
        }
    }

    return;
}

/*
 * int MBR_OpenFiles(void)
 *
 * Opens data files
 */
int MBR_OpenFiles(void)
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
            if (MBR_MODE_DIAG == g_iAcqMode)
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

/*
 * void MBR_BuildFilename(struct tm *pstTime, int iCount, char acFilename[])
 *
 * Builds a formatted filename string
 */
void MBR_BuildFilename(struct tm *pstTime, int iCount, char acFilename[])
{
    char acTimestamp[MBR_LEN_TS+1] = {0};
    char acCount[MBR_LEN_COUNT+1] = {0};
    char acChannel[MBR_LEN_CH+1] = {0};
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

    if (MBR_MODE_SNIFFACQ == g_iAcqMode)
    {
        (void) strcpy(acPrefix, MBR_FILENPREFIX_SNIFFACQ);
        (void) strcat(acPrefix, "_");   /* we don't want a beginning underscore
                                           for MBR_MODE_OBS, where there is
                                           no prefix */
    }

    iNumDigits = strlen(g_acChannel);
    for (i = (MBR_LEN_CH - iNumDigits); i > 0; --i)
    {
        (void) strcat(acChannel, "0");
    }
    (void) strcat(acChannel, g_acChannel);

    (void) strftime(acTimestamp, sizeof(acTimestamp), "%Y%m%d_%H%M%S", pstTime);
    (void) sprintf(acFilename,
                   "%s%s%s_%s_%s_%s.%s",
                   acPrefix,    /* 'NULL', in the case of MBR_MODE_OBS */
                   MBR_PREFIX_CH,
                   acChannel,
                   g_acSourceName,
                   acTimestamp,
                   acCount,
                   MBR_DATAFILE_EXT);

    return;
}

/*
 * void MBR_CloseFiles(void)
 *
 * Closes all data files
 */
void MBR_CloseFiles(void)
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

/*
 * void MBR_PrintUsage(const char *pcProgName)
 *
 * Prints usage information
 */
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
    printf("    -t  --time <time_in_min>   Set the acquisition time in ");
    printf("minutes\n");
    printf("                               (default is 1)\n");
    printf("    -m  --mode                 Acquisition mode\n");
    printf("                               ('obs' is 'observation' - ");
    printf("filenames are formatted;\n");
    printf("                                'sniffacq' is 'sniff and acquire'");
    printf(" - filenames are\n");
    printf("                                formatted, and are prefixed with ");
    printf("'raw_';\n");
    printf("                                'sniff' is 'sniff' - no files ");
    printf("are created, data is\n");
    printf("                                just sniffed;\n");
    printf("                                'check' is 'check' - no files ");
    printf("are created;\n");
    printf("                                default is 'observation')\n");
    printf("    -s  --source <name>        Override the source name read ");
    printf("from the\n");
    printf("                               config file\n");
    printf("    -o  --offset <offset>      In sniff modes, sets the packet ");
    printf("offset\n");
    printf("    -k  --kill                 Kills the existing instance of ");
    printf("this program\n");
    printf("    -c  --control              Use the M&C config file");
    printf("    -v  --version              Display the version\n");

    return;
}

