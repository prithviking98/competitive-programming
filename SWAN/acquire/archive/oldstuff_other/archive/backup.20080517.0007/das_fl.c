/*
   das_fl.c - File Loader
   Loads the raw data file into shared memory

   Created by Jayanth Chennamangalam
*/

#include "das.h"
#include "das_shm.h"
#include <string.h>
#include <unistd.h>

FILE *g_pDataFile = NULL;

int main(int argc, char *argv[])
{
    DAS_HEADERADDS_S stHeaderAdds = {0};
    DAS_BLOCKADDS_S stBlockAdds = {0};
    DAS_SHMHEADER_S *pstShmHeader = NULL;
    DAS_SHMINFO_S *pstShmInfo = NULL;
    DAS_BLOCK_S *pstBlock = NULL;
    DAS_SHM_DATATYPE *pWritePointer = NULL;
    int iBlockID = DAS_BLOCKID_START;   /* first block */
    int iRet = 0;

    /* create the header in shared memory */
    printf("das_fl: Creating header...");
    fflush(stdout);
    stHeaderAdds = DAS_CreateShmHeader(DAS_PID_FL);
    pstShmHeader = stHeaderAdds.pstShmHeader;
    if (NULL == pstShmHeader)
    {
        printf("das_fl: ERROR in ShmAlloc() for pstShmHeader\n");
        return DAS_RET_ERROR;
    }
    printf("DONE\n");

    /* create the shminfo data structure in shared memory */
    printf("das_fl: Creating shminfo...");
    fflush(stdout);
    pstShmInfo = DAS_CreateShmInfo(DAS_KEY_FL_OUT, DAS_PID_FL);
    if (NULL == pstShmInfo)
    {
        printf("das_fl: ERROR in ShmAlloc() for pstShmInfo\n");
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        return DAS_RET_ERROR;
    }
    printf("DONE\n");

    /* open the raw data file for loading into the shared memory */
    g_pDataFile = fopen(argv[1], "r");
    if (NULL == g_pDataFile)
    {
        perror("das_fl: ERROR in fopen()");
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        return DAS_RET_ERROR;
    }

    printf("das_fl: Writing the header...");
    fflush(stdout);
    /* copy the 2 kilobytes of header from the data file */
    (void) fread(stHeaderAdds.pbHeader,
                 sizeof(DAS_BYTE),
                 DAS_SIZE_HEADER,
                 g_pDataFile);
    /* set the status flag to DAS_STATUS_WRITESTART */
    pstShmInfo->iStatus = DAS_STATUS_WRITESTART;
    printf("DONE\n");

    printf("das_fl: Writing the data...\n");
    pstShmInfo->iWrittenData = 0;
    while (0 == feof(g_pDataFile))
    {
        /* limit checking */
        if (DAS_MAX_SHM_BLOCKS == (iBlockID - DAS_BLOCKID_START))
        {
            printf("das_fl: Number of blocks reached maximum allowed! ");
            printf("Terminating! Wrote %ld bytes of data.\n",
                   (long) (pstShmInfo->iWrittenData * sizeof(DAS_BYTE)));
            return DAS_RET_ERROR;
        }

        printf("das_fl: Creating block %d...", iBlockID);
        fflush(stdout);
        stBlockAdds = DAS_CreateBlock(iBlockID, DAS_KEY_FL_OUT, pstShmInfo, DAS_PID_FL);
        pstBlock = stBlockAdds.pstBlock;
        if (NULL == pstBlock)
        {
            printf("das_fl: ERROR in DAS_CreateBlock() for block %d\n",
                   iBlockID);
            /* do not free memory, the responsibility is with
               the reader */
            (void) fclose(g_pDataFile);
            return DAS_RET_ERROR;
        }
        printf("DONE\n");

        pWritePointer = stBlockAdds.pData;

#if 0
        (void) fread(pWritePointer,
                     sizeof(DAS_SHM_DATATYPE),
                     DAS_SIZE_SHM_DATA_DT,
                     g_pDataFile);
        pWritePointer += DAS_SIZE_SHM_DATA_DT;
        pstShmInfo->iWrittenData += DAS_SIZE_SHM_DATA_DT;
#else
        do
        {
            (void) fread(pWritePointer,
                         sizeof(DAS_SHM_DATATYPE),
                         1,
                         g_pDataFile);
            ++pWritePointer;
            ++(pstShmInfo->iWrittenData);
        }
        while ((0 == feof(g_pDataFile))
               && (0 != (pstShmInfo->iWrittenData % DAS_SIZE_SHM_DATA_DT)));
#endif

        iRet = shmdt(stBlockAdds.pData);
        if (iRet != DAS_RET_SUCCESS)
        {
            printf("das_fl: ERROR in shmdt() for data in block %d: ", iBlockID);
            fflush(stdout);
            perror("");
            return DAS_RET_ERROR;
        }
        iRet = shmdt(pstBlock);
        if (iRet != DAS_RET_SUCCESS)
        {
            printf("das_fl: ERROR in shmdt() for block %d: ", iBlockID);
            fflush(stdout);
            perror("");
            return DAS_RET_ERROR;
        }

        /* increment the block ID for the next interation */
        ++iBlockID;
    }

    /* set the status flag to DAS_STATUS_WRITEDONE */
    pstShmInfo->iStatus = DAS_STATUS_WRITEDONE;
	printf("DONE. Wrote %ld items of data.\n",
           (long) (pstShmInfo->iWrittenData
           + (DAS_SIZE_HEADER/sizeof(DAS_SHM_DATATYPE))));

    /* do not free memory, as that responsibility is with the reader */
    (void) fclose(g_pDataFile);

    /* detach the shared memory segments from this process */
    iRet = shmdt(pstShmInfo);
    if (iRet != DAS_RET_SUCCESS)
    {
        perror("das_fl: ERROR in shmdt() for pstShmInfo");
        return DAS_RET_ERROR;
    }
    iRet = shmdt(stHeaderAdds.pbHeader);
    if (iRet != DAS_RET_SUCCESS)
    {
        perror("das_fl: ERROR in shmdt() for pbHeader");
        return DAS_RET_ERROR;
    }
    iRet = shmdt(pstShmHeader);
    if (iRet != DAS_RET_SUCCESS)
    {
        perror("das_fl: ERROR in shmdt() for pstShmHeader");
        return DAS_RET_ERROR;
    }

// jayanth
//    getchar();

    return DAS_RET_SUCCESS;
}

