/* acq_write2file.c
 * Reads data from shared memory and writes it into a file.
 *
 * Created by Jayanth Chennamangalam
 */

#include <stdio.h>
#include <arpa/inet.h>
//#include <unistd.h>

//#include <sys/kdaemon.h>

#include "das.h"
#include "das_shm.h"

#define SIZE_PACKET            1056
#define DAS_CHK_SIZE_DATABLOCK      (SIZE_PACKET * 64)
#define DAS_CHK_SIZE_DATABLOCK_DT   (DAS_CHK_SIZE_DATABLOCK / sizeof(DAS_SHM_DATATYPE))
#define DAS_PKTSPERBLOCK            (DAS_CHK_SIZE_DATABLOCK / SIZE_PACKET)
#define LEN_DATAHEADER      28
#define MAX_NUM_SLIPS       2000
#define MAX_NUM_INFOITEMS   5
#define POS_PREV            0
#define POS_CURRENT         1
#define POS_PKTCOUNT        2
#define POS_WRITDATA        3
#define POS_READDATA        4

int main(int argc, char *argv[])
{
    DAS_SHMINFO_S *pstShmInfoIn = NULL;
    DAS_BLOCKADDS_S stBlockInAdds[DAS_NUM_BUFS] = {{0}};
    DAS_SHM_DATATYPE *pDataIn = NULL;
    FILE *pfDataFile = NULL;
    int iBlockIDIn = DAS_BLOCKID_START;   /* first block */
    int iWrittenBlocks = 0;
    int iReadData = 0;
    int iBufLeft = 0;
    int iBuffer = 0;
    int iBufferChange = 0;
    int iFlagBreak = DAS_FALSE;
    int i = 0;

    pfDataFile = fopen("packet", "w");
    if (NULL == pfDataFile)
    {
        perror("acq_write2file: fopen() failed");
        return DAS_RET_ERROR;
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
            (void) fclose(pfDataFile);

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
            (void) fwrite(pDataIn,
                          sizeof(DAS_SHM_DATATYPE),
                          DAS_CHK_SIZE_DATABLOCK,
                          pfDataFile);
            //sync();
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
            (void) fwrite(pDataIn,
                          sizeof(DAS_SHM_DATATYPE),
                          iBufLeft,
                          pfDataFile);
            //sync();
            //if (bdflush(1, 1))
            //{
            //    printf("error!\n");
            //}
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

            (void) fwrite(pDataIn,
                          sizeof(DAS_SHM_DATATYPE),
                          (DAS_CHK_SIZE_DATABLOCK - iBufLeft),
                          pfDataFile);
            //sync();
            pDataIn += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                        / sizeof(DAS_SHM_DATATYPE));
            iReadData += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft)
                          / sizeof(DAS_SHM_DATATYPE));
        }
        else
        {
            (void) fwrite(pDataIn,
                          sizeof(DAS_SHM_DATATYPE),
                          DAS_CHK_SIZE_DATABLOCK,
                          pfDataFile);
            //sync();
            pDataIn += DAS_CHK_SIZE_DATABLOCK_DT;
            iReadData += DAS_CHK_SIZE_DATABLOCK_DT;
        }

        ++iWrittenBlocks;
    }

    printf("%d blocks processed.\n", iWrittenBlocks);
    printf("%d buffer changes.\n", iBufferChange);

    /* clean up */
    DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);
    (void) fclose(pfDataFile);

    return DAS_RET_SUCCESS;
}

