/* mbr_acqsniff.cpp
 * Reads data from shared memory and sends it to the specified IP address
 *
 * Usage: mbracqsniff [options]
 *     -h  --help                 Display this usage information
 *     -v  --version              Display the version
 *
 * Created by Jayanth Chennamangalam
 */

#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <getopt.h>

#include "das.h"
#include "das_shm.h"

#include "mbr_acqsniff.h"
#include "mbr_common.h"

extern const char *g_pcVersion;
extern fstream g_ErrLog;

int g_iSocket = 0;

int main(int argc, char *argv[])
{
    DAS_SHMINFO_S *pstShmInfoIn = NULL;
    DAS_BLOCKADDS_S stBlockInAdds[DAS_NUM_BUFS] = {{0}};
    DAS_SHM_DATATYPE *pDataIn = NULL;
    int iBlockIDIn = DAS_BLOCKID_START;   /* first block */
    int iWrittenBlocks = 0;
    int iReadData = 0;
    int iBufLeft = 0;
    int iBuffer = 0;
    int iBufferChange = 0;
    int iFlagBreak = DAS_FALSE;
    struct sockaddr_in stSockAddr = {0};
    int i = 0;
    int iFlagFirst = MBR_TRUE;
    int iFlagFirstChange = 0;
    int iRet = MBR_RET_SUCCESS;
    struct sigaction stSigHandler = {{0}};
    const char *pcProgName = NULL;
    int iNextOpt = 0;
    /* valid short options */
    const char* const sShortOpts = "hv";
    /* valid long options */
    const struct option stLongOpts[] = {
        { "help",       0,  NULL,   'h' },
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

    /* open the socket for sniffing */
    g_iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == g_iSocket)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "socket() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        fprintf(stderr, "ERROR: Socket creation failed!\n");
        return MBR_RET_ERROR;
    }

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(MBR_PORT_DATA);
    stSockAddr.sin_addr.s_addr = inet_addr(MBR_MC_IP);
    (void) memset(stSockAddr.sin_zero, '\0', sizeof(stSockAddr.sin_zero));

    /* get the input shminfo data structure */
    pstShmInfoIn = DAS_ShmInit(DAS_KEY_FL_OUT, DAS_PID_CHK);

    /* wait for the writer to start writing */
    while (pstShmInfoIn->iStatus != DAS_STATUS_WRITESTART)
    {
        /* if the writer has finished writing, break */
        if (DAS_STATUS_WRITEDONE == pstShmInfoIn->iStatus)
        {
            break;
        }
    }

    /* get buffers */
    for (i = 0; i < DAS_NUM_BUFS; ++i)
    {
        printf("%s: Locating block %d...", pcProgName, iBlockIDIn);
        fflush(stdout);
        stBlockInAdds[i] = DAS_GetBlockByBlockID(iBlockIDIn,
                                                 DAS_KEY_FL_OUT,
                                                 DAS_PID_CHK);
        if (NULL == stBlockInAdds[i].pstBlock)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "DAS_GetBlockByBlockID(" << iBlockIDIn << ") returned "
                     << "NULL"
                     << endl;
            fprintf(stderr, "ERROR: Getting block by block ID failed!\n");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);
            (void) close(g_iSocket);

            return DAS_RET_ERROR;
        }
        printf("Base pointer = %X\n", (int) stBlockInAdds[i].pData);
        printf("DONE\n");
        ++iBlockIDIn;
    }
    /* the first buffer will be read from now, so set the data flag
       to DAS_STATUS_READ */
    stBlockInAdds[0].pstBlock->iFlagData = DAS_STATUS_READ;

    /* set the read pointer to the first buffer */
    iBuffer = 0;
    pDataIn = stBlockInAdds[0].pData;

    while (DAS_TRUE)
    {
        if ((DAS_STATUS_WRITEDONE == pstShmInfoIn->iStatus)
            && ((iWrittenBlocks + 1)
                > (signed) (((pstShmInfoIn->iWrittenData - 1)
                   * sizeof(DAS_SHM_DATATYPE)) / DAS_CHK_SIZE_DATABLOCK)))
        {
            (void) sendto(g_iSocket,
                          pDataIn,
                          (DAS_CHK_SIZE_DATABLOCK
                           * sizeof(DAS_SHM_DATATYPE)),
                          0,
                          (const struct sockaddr *) &stSockAddr,
                          sizeof(struct sockaddr));
            pDataIn += DAS_CHK_SIZE_DATABLOCK_DT;
            iReadData += DAS_CHK_SIZE_DATABLOCK_DT;
            printf("BROKE!\n");
            break;
        }

        /* read the data block and increment the read pointer */
        DAS_Delay(pstShmInfoIn, DAS_CHK_SIZE_DATABLOCK, iReadData);

        /* calculate buffer space left in terms of DAS_BYTE */
        iBufLeft = sizeof(DAS_SHM_DATATYPE)
                    * ((stBlockInAdds[iBuffer].pData + DAS_SIZE_SHM_DATA_DT)
                       - pDataIn);

        if (iBufLeft <= DAS_CHK_SIZE_DATABLOCK)
        {
            (void) sendto(g_iSocket,
                          pDataIn,
                          (iBufLeft * sizeof(DAS_SHM_DATATYPE)),
                          0,
                          (const struct sockaddr *) &stSockAddr,
                          sizeof(struct sockaddr));
            pDataIn += DAS_CHK_SIZE_DATABLOCK_DT;
            iReadData += DAS_CHK_SIZE_DATABLOCK_DT;

            ++iBufferChange;
            if (iBuffer != (DAS_NUM_BUFS - 1))  /* not the last buffer */
            {
                ++iBuffer;
            }
            else    /* the current buffer is the last buffer */
            {
                iBuffer = 0;
            }

            iFlagFirstChange = iFlagFirst;

            /* wait for the writer to start filling this buffer with
               fresh data */
            while (stBlockInAdds[iBuffer].pstBlock->iFlagData
                   != DAS_STATUS_FRESH)
            {
                if (MBR_TRUE == iFlagFirst)
                {
                    printf("Waiting for fresh data in buffer %d...\n", iBuffer);
                    iFlagFirst = MBR_FALSE;
                }
                if ((DAS_STATUS_WRITEDONE == pstShmInfoIn->iStatus)
                    && ((iWrittenBlocks + 1)
                        > (signed) (((pstShmInfoIn->iWrittenData - 1)
                            * sizeof(DAS_SHM_DATATYPE))
                           / DAS_CHK_SIZE_DATABLOCK)))
                {
                    printf("BROKE!\n");
                    iFlagBreak = DAS_TRUE;
                    break;
                }
            }

            if (iFlagFirst != iFlagFirstChange)
            {
                /* got fresh data */
                printf("Got fresh data in buffer %d.\n", iBuffer);
                iFlagFirst = MBR_TRUE;
            }

            if (DAS_TRUE == iFlagBreak)
            {
                break;
            }

            stBlockInAdds[iBuffer].pstBlock->iFlagData = DAS_STATUS_READ;
            pDataIn = stBlockInAdds[iBuffer].pData;

            (void) sendto(g_iSocket,
                          pDataIn,
                          ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                          * sizeof(DAS_SHM_DATATYPE)),
                          0,
                          (const struct sockaddr *) &stSockAddr,
                          sizeof(struct sockaddr));
            pDataIn += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                        / sizeof(DAS_SHM_DATATYPE));
            iReadData += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                          / sizeof(DAS_SHM_DATATYPE));
        }
        else
        {
            (void) sendto(g_iSocket,
                          pDataIn,
                          (DAS_CHK_SIZE_DATABLOCK
                          * sizeof(DAS_SHM_DATATYPE)),
                          0,
                          (const struct sockaddr *) &stSockAddr,
                          sizeof(struct sockaddr));
            pDataIn += DAS_CHK_SIZE_DATABLOCK_DT;
            iReadData += DAS_CHK_SIZE_DATABLOCK_DT;
        }

        ++iWrittenBlocks;
    }

    printf("%d blocks processed.\n", iWrittenBlocks);
    printf("%d buffer changes.\n", iBufferChange);

    /* clean up */
    DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);
    (void) close(g_iSocket);

    return DAS_RET_SUCCESS;
}

/*
 * void MBR_HandleStopSignals(int iSigNo)
 *
 * Catches SIGTERM and CTRL+C and cleans up before exiting
 */
void MBR_HandleStopSignals(int iSigNo)
{
    /* clean up */
    DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);
    (void) close(g_iSocket);

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
    printf("    -v  --version              Display the version\n");

    return;
}

