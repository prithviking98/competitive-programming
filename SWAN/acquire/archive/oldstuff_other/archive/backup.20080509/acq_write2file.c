/* acq_write2file.c
 * Reads data from the input shared memory and writes it into a file
 *
 * Created by Jayanth Chennamangalam
 */

#include <stdio.h>

#include "das.h"
#include "das_shm.h"

#define DAS_CHK_SIZE_DATABLOCK      1056
#define DAS_CHK_SIZE_DATABLOCK_DT   (DAS_CHK_SIZE_DATABLOCK / sizeof(DAS_SHM_DATATYPE))

#define LEN_DATAHEADER      28
#define MAX_NUM_SLIPS       2000
#define MAX_NUM_INFOITEMS   3
#define POS_PREV            0
#define POS_CURRENT         1
#define POS_PKTCOUNT        2

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
    int i = 0;

    /* for checking for slips */
    int iPacketCount = 0;
    int iCurrentMarker = 0;
    int iPrevMarker = 0;
    int iSlipCount = 0;
    int aiSlips[MAX_NUM_SLIPS][MAX_NUM_INFOITEMS] = {{0}};
    DAS_BYTE *pbMarkerPos = NULL;

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
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);
            return DAS_RET_ERROR;
        }
        printf("DONE\n");
        ++iBlockIDIn;
    }

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
            printf("BROKE!\n");
            break;
        }

        /* read the data block and increment the read pointer */
        DAS_Delay(pstShmInfoIn, DAS_CHK_SIZE_DATABLOCK, iReadData);

        pbMarkerPos = pDataIn + LEN_DATAHEADER;
        iCurrentMarker = (unsigned int) ntohl((*(unsigned int *) pbMarkerPos));

        if (iPacketCount != 0)
        {
            /* this is not the first packet */

            if (iCurrentMarker != (iPrevMarker + 1))
            {
                aiSlips[iSlipCount][POS_PREV] = iPrevMarker;
                aiSlips[iSlipCount][POS_CURRENT] = iCurrentMarker;
                aiSlips[iSlipCount][POS_PKTCOUNT] = iPacketCount;
                ++iSlipCount;
                if (MAX_NUM_SLIPS == iSlipCount)
                {
                    printf("Slip count exceeded limit! Wrapping around!\n");
                    iSlipCount = 0;
                }
            }
        }
        iPrevMarker = iCurrentMarker;

        /* calculate buffer space left in terms of DAS_BYTE */
        iBufLeft = sizeof(DAS_SHM_DATATYPE)
                    * ((stBlockInAdds[iBuffer].pData + DAS_SIZE_SHM_DATA_DT) - pDataIn);

        if (iBufLeft <= DAS_CHK_SIZE_DATABLOCK)
        {
            //printf("-    iBufLeft = %d\n", iBufLeft);

            #if 0
            (void) fwrite(pDataIn, sizeof(DAS_SHM_DATATYPE), iBufLeft, pfDataFile);
            #endif

            if (iBuffer != (DAS_NUM_BUFS - 1))  /* not the last buffer */
            {
                //printf("Moving to the next buffer!\n");
                ++iBuffer;
            }
            else    /* the current buffer is the last buffer */
            {
                //printf("Moving to the next buffer - wraparound!\n");
                iBuffer = 0;
            }
            pDataIn = stBlockInAdds[iBuffer].pData;

            #if 0
            (void) fwrite(pDataIn,
                          sizeof(DAS_SHM_DATATYPE),
                          (DAS_CHK_SIZE_DATABLOCK - iBufLeft),
                          pfDataFile);
            #endif
            pDataIn += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft) / sizeof(DAS_SHM_DATATYPE));
            iReadData += ((DAS_CHK_SIZE_DATABLOCK - iBufLeft) / sizeof(DAS_SHM_DATATYPE));
            //printf("acq_write2file: Buffer wraparound!\n");
        }
        else
        {
            //printf(".    iBufLeft = %d\n", iBufLeft);

            #if 0
            (void) fwrite(pDataIn,
                          sizeof(DAS_SHM_DATATYPE),
                          DAS_CHK_SIZE_DATABLOCK,
                          pfDataFile);
            #endif
            pDataIn += DAS_CHK_SIZE_DATABLOCK_DT;
            iReadData += DAS_CHK_SIZE_DATABLOCK_DT;
        }

        ++iPacketCount;

        ++iWrittenBlocks;
    }

    printf("%d slips detected! Hit any key to view the slips.\n",
            iSlipCount);

    /* wait for a key press */
    getchar();

    for (i = 0; i < iSlipCount; ++i)
    {
        printf("Slip detected! ");
        #if 0
        printf("Previous = %x, current = %x, diff = %d, "
                "packet count = %d\n",
                aiSlips[i][POS_PREV],
                aiSlips[i][POS_CURRENT],
                (aiSlips[i][POS_CURRENT] - aiSlips[i][POS_PREV]),
                aiSlips[i][POS_PKTCOUNT]);
        #endif
        printf("Previous = %x, current = %x, diff = %d\n",
                aiSlips[i][POS_PREV],
                aiSlips[i][POS_CURRENT],
                (aiSlips[i][POS_CURRENT] - aiSlips[i][POS_PREV]));
    }
    printf("%d packets processed.\n", iPacketCount);

    /* clean up */
    DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_CHK);
    (void) fclose(pfDataFile);

    return DAS_RET_SUCCESS;
}

