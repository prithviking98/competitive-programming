/* acq_sniff.c
 * Reads data from the shared memory and sends it out on the specified
 *     interface. It reads <blocks_to_read> blocks and skips the next
 *     <blocks_to_skip> blocks.
 *
 * Usage: acq_sniff <dev_name> <blocks_to_read> <blocks_to_skip>
 *
 * Created by Jayanth Chennamangalam
 */

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "das.h"
#include "das_shm.h"

#define SIZE_PACKET                 1056
#define DAS_CHK_SIZE_DATABLOCK      (SIZE_PACKET * 64)
#define DAS_CHK_SIZE_DATABLOCK_DT   (DAS_CHK_SIZE_DATABLOCK \
                                     / sizeof(DAS_SHM_DATATYPE))
#define DAS_PKTSPERBLOCK            (DAS_CHK_SIZE_DATABLOCK / SIZE_PACKET)
#define LEN_DATAHEADER              28

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
    int iFlagCopy = DAS_FALSE;
    int iBlocksToRead = 0;
    int iBlocksToSkip = 0;
    int iReadBlocks = 0;
    int iSkippedBlocks = 0;
    int iSocket = 0;
    struct ifreq stIFReq = {{{0}}};
    int iRet = 0;
    int i = 0;

    iBlocksToRead = atoi(argv[2]);
    iBlocksToSkip = atoi(argv[3]);

    /* open the socket for sniffing */
    iSocket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (-1 == iSocket)
    {
        perror("socket");
        return -1;
    }

    /* the socket configuration controls are defined in <linux/sockios.h> */
    /* set the interface to the one specified */
    // TODO: have to test if this works
    (void) strncpy(stIFReq.ifr_name, argv[1], IFNAMSIZ);
    iRet = ioctl(iSocket, SIOCGIFNAME, &stIFReq);
    if (-1 == iRet)
    {
        perror("ioctl");
        return -1;
    }

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
        printf("acq_write2file: Locating block %d...", iBlockIDIn);
        fflush(stdout);
        stBlockInAdds[i] = DAS_GetBlockByBlockID(iBlockIDIn,
                                                 DAS_KEY_FL_OUT,
                                                 DAS_PID_CHK);
        if (NULL == stBlockInAdds[i].pstBlock)
        {
            printf("acq_write2file: ERROR in DAS_GetFirstBlock()");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);

            return DAS_RET_ERROR;
        }
        printf("Base pointer = %X\n", stBlockInAdds[i].pData);
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
                > (((pstShmInfoIn->iWrittenData - 1)
                   * sizeof(DAS_SHM_DATATYPE)) / DAS_CHK_SIZE_DATABLOCK)))
        {
            if (DAS_TRUE == iFlagCopy)
            {
                (void) write(iSocket,
                             pDataIn,
                             (DAS_CHK_SIZE_DATABLOCK
                              * sizeof(DAS_SHM_DATATYPE)));
            }
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
            if (DAS_TRUE == iFlagCopy)
            {
                (void) write(iSocket,
                             pDataIn,
                             (iBufLeft * sizeof(DAS_SHM_DATATYPE)));
            }
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

            /* wait for the writer to start filling this buffer with
               fresh data */
            while (stBlockInAdds[iBuffer].pstBlock->iFlagData
                   != DAS_STATUS_FRESH)
            {
                printf("Waiting for fresh data in buffer %d...\n", iBuffer);
                if ((DAS_STATUS_WRITEDONE == pstShmInfoIn->iStatus)
                    && ((iWrittenBlocks + 1)
                        > (((pstShmInfoIn->iWrittenData - 1)
                            * sizeof(DAS_SHM_DATATYPE))
                           / DAS_CHK_SIZE_DATABLOCK)))
                {
                    printf("BROKE!\n");
                    iFlagBreak = DAS_TRUE;
                    break;
                }
            }

            if (DAS_TRUE == iFlagBreak)
            {
                break;
            }

            stBlockInAdds[iBuffer].pstBlock->iFlagData = DAS_STATUS_READ;
            pDataIn = stBlockInAdds[iBuffer].pData;

            if (DAS_TRUE == iFlagCopy)
            {
                (void) write(iSocket,
                             pDataIn,
                             ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                              * sizeof(DAS_SHM_DATATYPE)));
            }
            pDataIn += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                        / sizeof(DAS_SHM_DATATYPE));
            iReadData += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                          / sizeof(DAS_SHM_DATATYPE));
        }
        else
        {
            if (DAS_TRUE == iFlagCopy)
            {
                (void) write(iSocket,
                             pDataIn,
                             (DAS_CHK_SIZE_DATABLOCK
                              * sizeof(DAS_SHM_DATATYPE)));
            }
            pDataIn += DAS_CHK_SIZE_DATABLOCK_DT;
            iReadData += DAS_CHK_SIZE_DATABLOCK_DT;
        }

        ++iWrittenBlocks;
        if (DAS_TRUE == iFlagCopy)
        {
            ++iReadBlocks;
            if (iReadBlocks == iBlocksToRead)
            {
                iFlagCopy = DAS_FALSE;
                iReadBlocks = 0;
            }
        }
        else
        {
            ++iSkippedBlocks;
            if (iSkippedBlocks == iBlocksToSkip)
            {
                iFlagCopy = DAS_TRUE;
                iSkippedBlocks = 0;
            }
        }
    }

    printf("%d blocks processed.\n", iWrittenBlocks);
    printf("%d buffer changes.\n", iBufferChange);

    /* clean up */
    DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);
    (void) close(iSocket);

    return DAS_RET_SUCCESS;
}

