/*
   das_shm.c
   Common shared-memory-related function definitions

   Created by Jayanth Chennamangalam
   2007.10.10
*/

#include "das.h"
#include "das_shm.h"

int g_iFlagFirst = DAS_TRUE;

/*
 * DAS_SHMINFO_S* DAS_ShmInit(const char *szKeyFile, int iPID)
 *
 * Initialises one shminfo structure for each szKeyFile, that is,
 * for each stage of the processing pipeline.
 */
DAS_SHMINFO_S* DAS_ShmInit(const char *szKeyFile, int iPID)
{
    DAS_SHMINFO_S *pstShmInfo = NULL;
    int iShmIDShmInfo = 0;
    int *piShmIDShmInfo = &iShmIDShmInfo;

    /* locate shminfo */
    pstShmInfo = (DAS_SHMINFO_S *) DAS_ShmAlloc(szKeyFile,
                                                DAS_ID_SHMINF0,
                                                sizeof(DAS_SHMINFO_S),
                                                0444, /* r--r--r-- */
                                                &piShmIDShmInfo,
                                                iPID);
    while (NULL == pstShmInfo)
    {
        if (DAS_TRUE == g_iFlagFirst)
        {
            printf("DAS_ShmInit(): ERROR in DAS_ShmAlloc() for pstShmInfo ");
            printf("for keyfile %s\n", szKeyFile);
            printf("Trying again...\n");
            g_iFlagFirst = DAS_FALSE;
        }
        pstShmInfo = (DAS_SHMINFO_S *) DAS_ShmAlloc(szKeyFile,
                                                    DAS_ID_SHMINF0,
                                                    sizeof(DAS_SHMINFO_S),
                                                    0444, /* r--r--r-- */
                                                    &piShmIDShmInfo,
                                                    iPID);
    }

    printf("Successful initialisation of shared memory.\n");
    /* for other functions */
    g_iFlagFirst = DAS_TRUE;

    return pstShmInfo;
}

/* void* DAS_ShmAlloc(const char *szPath,
 *                    int iIPCID,
 *                    size_t iSize,
 *                    int iFlag,
 *                    int **ppiShmID,
 *                    int iPID)
 *
 * Allocates/locates and attaches a shared memory segment to the calling
 * process's address space.
 */
void* DAS_ShmAlloc(const char *szPath,
                   int iIPCID,
                   size_t iSize,
                   int iFlag,
                   int **ppiShmID,
                   int iPID)
{
    key_t Key = 0;
    void *pvShm = NULL;

    /* input validation */
    assert(szPath != NULL);
    assert(ppiShmID != NULL);
    assert(*ppiShmID != NULL);

    /* get a shared memory segment */
    Key = ftok(szPath, iIPCID);
    if ((key_t) -1 == Key)
    {
        if (DAS_TRUE == g_iFlagFirst)
        {
            perror("DAS_ShmAlloc(): ERROR in ftok()");
        }
        return NULL;
    }

    **ppiShmID = shmget(Key, iSize, iFlag);
    if (-1 == **ppiShmID)
    {
        if (DAS_TRUE == g_iFlagFirst)
        {
            perror("DAS_ShmAlloc(): ERROR in shmget()");
        }
        return NULL;
    }

    /* attach the shared memory segment to this process's address space */
    pvShm = shmat(**ppiShmID, NULL, 0);
    if ((void *) -1 == pvShm)
    {
        if (DAS_TRUE == g_iFlagFirst)
        {
            perror("DAS_ShmAlloc(): ERROR in shmat()");
        }
        return NULL;
    }

    return pvShm;
}

/*
 * DAS_HEADERADDS_S DAS_GetHeader(int iPID)
 *
 * Gets the header shared memory segment.
 */
DAS_HEADERADDS_S DAS_GetHeader(int iPID)
{
    DAS_HEADERADDS_S stHeaderAdds = {0};
    DAS_SHMHEADER_S *pstShmHeader = NULL;
    DAS_BYTE *pbHeader = NULL;
    int iShmIDShmHeader = 0;
    int *piShmIDShmHeader = &iShmIDShmHeader;
    int *piShmIDHeaderInfo = NULL;

    /* locate the header */
    pstShmHeader = (DAS_SHMHEADER_S *) DAS_ShmAlloc(DAS_KEY_FL_OUT,
                                                    DAS_ID_SHMHEADER,
                                                    sizeof(DAS_SHMHEADER_S),
                                                    0444,   /* r--r--r-- */
                                                    &piShmIDShmHeader,
                                                    iPID);
    if (NULL == pstShmHeader)
    {
        printf("DAS_GetHeader(): ERROR in DAS_ShmAlloc() for pstShmHeader\n");
        return stHeaderAdds;
    }

    /* locate the header info memory */
    piShmIDHeaderInfo = &(pstShmHeader->iHeaderInfoShmID);
    pbHeader = (DAS_BYTE *) DAS_ShmAlloc(DAS_KEY_FL_OUT,
                                                       DAS_ID_HEADERINFO,
                                                       DAS_SIZE_HEADER,
                                                       0444,    /* r--r--r-- */
                                                       &piShmIDHeaderInfo,
                                                       iPID);
    if (NULL == pbHeader)
    {
        printf("DAS_GetHeader(): ERROR in DAS_ShmAlloc() for pbHeader\n");
        return stHeaderAdds;
    }

    /* fill the DAS_HEADERADDS_S structure */
    stHeaderAdds.pstShmHeader = pstShmHeader;
    stHeaderAdds.pbHeader = pbHeader;

    return stHeaderAdds;
}

/*
 * DAS_BLOCKADDS_S DAS_GetFirstBlock(const char *szKeyFile, int iPID)
 *
 * Gets the first block shared memory segment.
 */
DAS_BLOCKADDS_S DAS_GetFirstBlock(const char *szKeyFile, int iPID)
{
    DAS_BLOCKADDS_S stBlockAdds = {0};
    DAS_SHM_DATATYPE *pData = NULL;
    DAS_BLOCK_S *pstBlock = NULL;
    int iShmIDBlock = 0;
    int *piShmIDBlock = &iShmIDBlock;
    int *piShmIDData = NULL;
    int iBlockID = DAS_BLOCKID_START;   /* first block ID */

    /* locate the first block */
    pstBlock = (DAS_BLOCK_S *) DAS_ShmAlloc(szKeyFile,
                                            (DAS_ID_BLOCK << DAS_ID_SHIFT)
                                            | iBlockID,
                                            sizeof(DAS_BLOCK_S),
                                            0444,   /* r--r--r-- */
                                            &piShmIDBlock,
                                            iPID);
    if (NULL == pstBlock)
    {
        printf("DAS_GetFirstBlock(): ERROR in DAS_ShmAlloc() for pstBlock ");
        printf("for keyfile %s\n", szKeyFile);
        return stBlockAdds;
    }

    /* locate the first block's data memory */
    piShmIDData = &(pstBlock->iDataShmID);
    pData = (DAS_SHM_DATATYPE *) DAS_ShmAlloc(szKeyFile,
                                                        (DAS_ID_DATA
                                                         << DAS_ID_SHIFT)
                                                        | iBlockID,
                                                        DAS_SIZE_SHM_DATA,
                                                        0444,   /* r--r--r-- */
                                                        &piShmIDData,
                                                        iPID);
    if (NULL == pData)
    {
        printf("DAS_GetFirstBlock(): ERROR in DAS_ShmAlloc() for pData ");
        printf("for keyfile %s\n", szKeyFile);
        return stBlockAdds;
    }

    /* add the returned address to the list of addresses, for use while
       detaching */
    ++pstBlock->iLastShmAdd;
    if (DAS_MAX_SHM_NATTCH == pstBlock->iLastShmAdd)
    {
        printf("DAS_GetFirstBlock(): ERROR: Attachment count reached limit!\n");
        return stBlockAdds;
    }
    pstBlock->iShmBlockAdds[pstBlock->iLastShmAdd] = (int *) pstBlock;
    pstBlock->iShmDataAdds[pstBlock->iLastShmAdd] = (int *) pData;

    /* fill the DAS_BLOCKADDS_S structure */
    stBlockAdds.pstBlock = pstBlock;
    stBlockAdds.pData = pData;

    return stBlockAdds;
}

/*
 * DAS_BLOCKADDS_S DAS_GetNextBlock(int iThisBlockID, const char *szKeyFile, int iPID)
 *
 * Gets the next block shared memory segment, given the current block's
 * block ID.
 */
DAS_BLOCKADDS_S DAS_GetNextBlock(int iThisBlockID, const char *szKeyFile, int iPID)
{
    DAS_BLOCKADDS_S stBlockAdds = {0};
    DAS_BLOCK_S *pstBlock = NULL;
    DAS_SHM_DATATYPE *pData = NULL;
    int iShmIDBlock = 0;
    int *piShmIDBlock = &iShmIDBlock;
    int *piShmIDData = NULL;

    /* locate the next block */
    pstBlock = (DAS_BLOCK_S *) DAS_ShmAlloc(szKeyFile,
                                            (DAS_ID_BLOCK << DAS_ID_SHIFT)
                                            /* next block */
                                            | (iThisBlockID + 1),
                                            sizeof(DAS_BLOCK_S),
                                            0444,   /* r--r--r-- */
                                            &piShmIDBlock,
                                            iPID);
    if (NULL == pstBlock)
    {
        printf("DAS_GetNextBlock(): ERROR in DAS_ShmAlloc() for pstBlock ");
        printf("for keyfile %s\n", szKeyFile);
        return stBlockAdds;
    }

    /* locate the next block's data memory */
    piShmIDData = &(pstBlock->iDataShmID);
    pData = (DAS_SHM_DATATYPE *) DAS_ShmAlloc(szKeyFile,
                                                        (DAS_ID_DATA
                                                         << DAS_ID_SHIFT)
                                                        /* next block */
                                                        | (iThisBlockID + 1),
                                                        DAS_SIZE_SHM_DATA,
                                                        0444,   /* r--r--r-- */
                                                        &piShmIDData,
                                                        iPID);
    if (NULL == pData)
    {
        printf("DAS_GetNextBlock(): ERROR in DAS_ShmAlloc() for pData ");
        printf("for keyfile %s\n", szKeyFile);
        return stBlockAdds;
    }

    /* add the returned address to the list of addresses, for use while
       detaching */
    ++pstBlock->iLastShmAdd;
    if (DAS_MAX_SHM_NATTCH == pstBlock->iLastShmAdd)
    {
        printf("DAS_GetNextBlock(): ERROR: Attachment count reached limit!\n");
        return stBlockAdds;
    }
    pstBlock->iShmBlockAdds[pstBlock->iLastShmAdd] = (int *) pstBlock;
    pstBlock->iShmDataAdds[pstBlock->iLastShmAdd] = (int *) pData;

    /* fill the DAS_BLOCKADDS_S structure */
    stBlockAdds.pstBlock = pstBlock;
    stBlockAdds.pData = pData;

    return stBlockAdds;
}

/*
 * DAS_BLOCKADDS_S DAS_GetBlockByBlockID(int iBlockID
 *                                    const char *szKeyFile,
 *                                    int iPID)
 *
 * Gets the block shared memory segment, given its block ID.
 */
DAS_BLOCKADDS_S DAS_GetBlockByBlockID(int iBlockID,
                                   const char *szKeyFile,
                                   int iPID)
{
    DAS_BLOCKADDS_S stBlockAdds = {0};
    DAS_BLOCK_S *pstBlock = NULL;
    DAS_SHM_DATATYPE *pData = NULL;
    int iShmIDBlock = 0;
    int *piShmIDBlock = &iShmIDBlock;
    int *piShmIDData = NULL;

    /* locate the block */
    pstBlock = (DAS_BLOCK_S *) DAS_ShmAlloc(szKeyFile,
                                            (DAS_ID_BLOCK << DAS_ID_SHIFT)
                                            | iBlockID, /* block ID to get */
                                            sizeof(DAS_BLOCK_S),
                                            0444,   /* r--r--r-- */
                                            &piShmIDBlock,
                                            iPID);
    if (NULL == pstBlock)
    {
        printf("DAS_GetBlockByBlockID(): ");
        printf("ERROR in DAS_ShmAlloc() for pstBlock ");
        printf("for keyfile %s\n", szKeyFile);
        return stBlockAdds;
    }

    /* locate the block's data memory */
    piShmIDData = &(pstBlock->iDataShmID);
    pData = (DAS_SHM_DATATYPE *) DAS_ShmAlloc(szKeyFile,
                                                        (DAS_ID_DATA
                                                         << DAS_ID_SHIFT)
                                                        /* block ID to get */
                                                        | iBlockID,
                                                        DAS_SIZE_SHM_DATA,
                                                        0444,   /* r--r--r-- */
                                                        &piShmIDData,
                                                        iPID);
    if (NULL == pData)
    {
        printf("DAS_GetBlockByBlockID(): ERROR in DAS_ShmAlloc() for pData ");
        printf("for keyfile %s\n", szKeyFile);
        return stBlockAdds;
    }

    /* add the returned address to the list of addresses, for use while
       detaching */
    ++pstBlock->iLastShmAdd;
    if (DAS_MAX_SHM_NATTCH == pstBlock->iLastShmAdd)
    {
        printf("DAS_GetBlockByBlockID(): ERROR: Attachment count reached ");
        printf("limit!\n");
        return stBlockAdds;
    }
    pstBlock->iShmBlockAdds[pstBlock->iLastShmAdd] = (int *) pstBlock;
    pstBlock->iShmDataAdds[pstBlock->iLastShmAdd] = (int *) pData;

    /* fill the DAS_BLOCKADDS_S structure */
    stBlockAdds.pstBlock = pstBlock;
    stBlockAdds.pData = pData;

    return stBlockAdds;
}

/*
 * DAS_HEADERADDS_S DAS_CreateShmHeader(int iPID)
 *
 * Creates the header shared memory segment.
 */
DAS_HEADERADDS_S DAS_CreateShmHeader(int iPID)
{
    DAS_HEADERADDS_S stHeaderAdds = {0};
    DAS_SHMHEADER_S *pstShmHeader = NULL;
    DAS_BYTE *pbHeader = NULL;
    int iShmIDShmHeader = 0;
    int *piShmIDShmHeader = &iShmIDShmHeader;
    int *piShmIDHeaderInfo = NULL;

    /* create the header */
    pstShmHeader = (DAS_SHMHEADER_S *) DAS_ShmAlloc(DAS_KEY_FL_OUT,
                                                    DAS_ID_SHMHEADER,
                                                    sizeof(DAS_SHMHEADER_S),
                                                    /* rw-rw-rw- */
                                                    IPC_CREAT | 0666,
                                                    &piShmIDShmHeader,
                                                    iPID);
    if (NULL == pstShmHeader)
    {
        printf("DAS_CreateShmHeader(): ");
        printf("ERROR in DAS_ShmAlloc() for pstShmHeader\n");
        return stHeaderAdds;
    }

    /* update the shmheader's shmid */
    pstShmHeader->iShmHeaderShmID = iShmIDShmHeader;

    /* create new header info memory */
    piShmIDHeaderInfo = &(pstShmHeader->iHeaderInfoShmID);
    pbHeader = (DAS_BYTE *) DAS_ShmAlloc(DAS_KEY_FL_OUT,
                                                       DAS_ID_HEADERINFO,
                                                       DAS_SIZE_HEADER,
                                                       /* rw-rw-rw- */
                                                       IPC_CREAT | 0666,
                                                       &piShmIDHeaderInfo,
                                                       iPID);
    if (NULL == pbHeader)
    {
        printf("DAS_CreateShmHeader(): ERROR in DAS_ShmAlloc() for pbHeader\n");
        (void) shmctl(iShmIDShmHeader, IPC_RMID, NULL);
        return stHeaderAdds;
    }

    /* fill the DAS_HEADERADDS_S structure */
    stHeaderAdds.pstShmHeader = pstShmHeader;
    stHeaderAdds.pbHeader = pbHeader;

    return stHeaderAdds;
}

/*
 * DAS_SHMHEADER_S* DAS_UpdateShmHeader(int iPID)
 *
 * Updates the header shared memory segment.
 */
int DAS_UpdateShmHeader(DAS_BYTE *pbNewHeaderInfo, int iPID)
{
    DAS_SHMHEADER_S *pstShmHeader = NULL;
    DAS_BYTE *pbHeader = NULL;
    int iShmIDShmHeader = 0;
    int *piShmIDShmHeader = &iShmIDShmHeader;
    int *piShmIDHeaderInfo = NULL;

    /* get the shmheader structure in read-only mode */
    pstShmHeader = (DAS_SHMHEADER_S *) DAS_ShmAlloc(DAS_KEY_FL_OUT,
                                                    DAS_ID_SHMHEADER,
                                                    sizeof(DAS_SHMHEADER_S),
                                                    /* r--r--r-- */
                                                    0444,
                                                    &piShmIDShmHeader,
                                                    iPID);
    if (NULL == pstShmHeader)
    {
        printf("DAS_UpdateShmHeader(): ");
        printf("ERROR in DAS_ShmAlloc() for pstShmHeader\n");
        return DAS_RET_ERROR;
    }

    /* update the shmheader's shmid */
    //pstShmHeader->iShmHeaderShmID = iShmIDShmHeader;

    /* get the header info memory in read/write mode */
    piShmIDHeaderInfo = &(pstShmHeader->iHeaderInfoShmID);
    pbHeader = (DAS_BYTE *) DAS_ShmAlloc(DAS_KEY_FL_OUT,
                                                       DAS_ID_HEADERINFO,
                                                       DAS_SIZE_HEADER,
                                                       /* rw-rw-rw- */
                                                       0666,
                                                       &piShmIDHeaderInfo,
                                                       iPID);
    if (NULL == pbHeader)
    {
        printf("DAS_UpdateShmHeader(): ERROR in DAS_ShmAlloc() for pbHeader\n");
        (void) shmctl(iShmIDShmHeader, IPC_RMID, NULL);
        return DAS_RET_ERROR;
    }

    /* copy the contents of the buffer to the header info memory segment */
    (void) memcpy((void *) pbHeader, (void *) pbNewHeaderInfo, DAS_SIZE_HEADER);

    return DAS_RET_SUCCESS;
}

/*
 * DAS_SHMINFO_S* DAS_CreateShmInfo(const char *szKeyFile, int iPID)
 *
 * Creates the input/output shminfo shared memory segment for the stage
 * specified by szKeyFile.
 */
DAS_SHMINFO_S* DAS_CreateShmInfo(const char *szKeyFile, int iPID)
{
    DAS_SHMINFO_S *pstShmInfo = NULL;
    int iShmIDShmInfo = 0;
    int *piShmIDShmInfo = &iShmIDShmInfo;

    pstShmInfo = (DAS_SHMINFO_S *) DAS_ShmAlloc(szKeyFile,
                                                DAS_ID_SHMINF0,
                                                sizeof(DAS_SHMINFO_S),
                                                /* rw-rw-rw- */
                                                IPC_CREAT | 0666,
                                                &piShmIDShmInfo,
                                                iPID);
    if (NULL == pstShmInfo)
    {
        printf("DAS_CreateShmInfo(): ERROR in ShmAlloc()\n");
        return NULL;
    }

    /* set the shmid field in the structure for use while deleting */
    pstShmInfo->iShmID = iShmIDShmInfo;

    return pstShmInfo;
}

/* DAS_BLOCKADDS_S DAS_CreateBlock(int iNewBlockID,
 *                              const char *szKeyFile,
 *                              DAS_SHMINFO_S *pstShmInfo,
 *                              int iPID)
 *
 * Creates a block shared memory segment with block ID iNewBlockID
 * and for the stage specified by szKeyFile, and the shminfo structure
 * specified by pstShmInfo.
 */
DAS_BLOCKADDS_S DAS_CreateBlock(int iNewBlockID,
                             const char *szKeyFile,
                             DAS_SHMINFO_S *pstShmInfo,
                             int iPID)
{
    DAS_BLOCKADDS_S stBlockAdds = {0};
    DAS_BLOCK_S *pstBlock = NULL;
    DAS_SHM_DATATYPE *pData = NULL;
    int iShmIDBlock = 0;
    int *piShmIDBlock = &iShmIDBlock;
    int *piShmIDData = NULL;

    /* create new block */
    pstBlock = (DAS_BLOCK_S *) DAS_ShmAlloc(szKeyFile,
                                            (DAS_ID_BLOCK << DAS_ID_SHIFT)
                                            | iNewBlockID,
                                            sizeof(DAS_BLOCK_S),
                                            IPC_CREAT | 0666,   /* rw-rw-rw- */
                                            &piShmIDBlock,
                                            iPID);
    if (NULL == pstBlock)
    {
        printf("DAS_CreateBlock(): ERROR in DAS_ShmAlloc() for pstBlock\n");
        return stBlockAdds;
    }

    /* update the block's IDs */
    pstBlock->iBlockID = iNewBlockID;
    pstBlock->iBlockShmID = iShmIDBlock;

    /* create new data memory */
    piShmIDData = &(pstBlock->iDataShmID);
    pData = (DAS_SHM_DATATYPE *) DAS_ShmAlloc(szKeyFile,
                                                        (DAS_ID_DATA
                                                         << DAS_ID_SHIFT)
                                                        | iNewBlockID,
                                                        DAS_SIZE_SHM_DATA,
                                                        /* rw-rw-rw- */
                                                        IPC_CREAT | 0666,
                                                        &piShmIDData,
                                                        iPID);
    if (NULL == pData)
    {
        printf("DAS_CreateBlock(): ERROR in DAS_ShmAlloc() for pData\n");
        (void) shmctl(iShmIDBlock, IPC_RMID, NULL);
        return stBlockAdds;
    }

    /* if this is the first block, fill the value in the shminfo structure
       and also the last shm address index */
    if (DAS_BLOCKID_START == iNewBlockID)
    {
        pstShmInfo->iFirstBlockID = DAS_BLOCKID_START;
    }

    /* set the last shm address to -1, so that the next call to any Get*Block*
       function will increment it to 0 */
    pstBlock->iLastShmAdd = -1;

    /* update the number of blocks in shminfo */
    ++(pstShmInfo->iNumBlocks);

    /* update the highest block ID so far generated */
    if (iNewBlockID > pstShmInfo->iHighestBlockID)
    {
        pstShmInfo->iHighestBlockID = iNewBlockID;
    }

    /* fill the DAS_BLOCKADDS_S structure */
    stBlockAdds.pstBlock = pstBlock;
    stBlockAdds.pData = pData;

    return stBlockAdds;
}

int DAS_DeleteBlock(int iBlockID,
                    const char *szKeyFile,
                    DAS_SHMINFO_S *pstShmInfo,
                    int iPID)
{
    DAS_BLOCK_S *pstBlock = NULL;
    DAS_SHM_DATATYPE *pData = NULL;
    int iShmIDBlock = 0;
    int *piShmIDBlock = &iShmIDBlock;
    int iShmIDData = 0;
    int *piShmIDData = NULL;
    int iRet = 0;
    int i = 0;
    int iLastShmAdd = 0;

    /* locate the block */
    pstBlock = (DAS_BLOCK_S *) DAS_ShmAlloc(szKeyFile,
                                            (DAS_ID_BLOCK << DAS_ID_SHIFT)
                                            | iBlockID,
                                            sizeof(DAS_BLOCK_S),
                                            0444,   /* r--r--r-- */
                                            &piShmIDBlock,
                                            iPID);
    if (NULL == pstBlock)
    {
        printf("DAS_DeleteBlock(): ERROR in DAS_ShmAlloc() for pstBlock\n");
        return DAS_RET_ERROR;
    }

    /* locate the data memory */
    piShmIDData = &(pstBlock->iDataShmID);
    pData = (DAS_SHM_DATATYPE *) DAS_ShmAlloc(szKeyFile,
                                                        (DAS_ID_DATA
                                                         << DAS_ID_SHIFT)
                                                        | iBlockID,
                                                        DAS_SIZE_SHM_DATA,
                                                        0444,   /* r--r--r-- */
                                                        &piShmIDData,
                                                        iPID);
    if (NULL == pData)
    {
        printf("DAS_DeleteBlock(): ERROR in DAS_ShmAlloc() for pData\n");
        return DAS_RET_ERROR;
    }

    /* copy the data shmid for later deletion of the segment */
    iShmIDData = pstBlock->iDataShmID;

    /* add the returned address to the list of addresses, for use while
       detaching */
    ++pstBlock->iLastShmAdd;
    pstBlock->iShmBlockAdds[pstBlock->iLastShmAdd] = (int *) pstBlock;
    pstBlock->iShmDataAdds[pstBlock->iLastShmAdd] = (int *) pData;

    /* last shm address index should be saved before pstBlock is detached */
    iLastShmAdd = pstBlock->iLastShmAdd;
    for (i = 0; i <= iLastShmAdd; ++i)
    {
        iRet = shmdt((void *) pstBlock->iShmDataAdds[i]);
        if (iRet != DAS_RET_SUCCESS)
        {
            /* print the error and try detaching the next segment */
            perror("DAS_DeleteBlock(): ERROR in shmdt() for data");
        }
        iRet = shmdt((void *) pstBlock->iShmBlockAdds[i]);
        if (iRet != DAS_RET_SUCCESS)
        {
            /* print the error and try detaching the next segment */
            perror("DAS_DeleteBlock(): ERROR in shmdt() for block");
        }
    }

    /* now that nattch has become 0, delete the shared memory segments,
       first data, then block */
    (void) shmctl(iShmIDData, IPC_RMID, NULL);
    (void) shmctl(iShmIDBlock, IPC_RMID, NULL);

    /* update the number of blocks in shminfo */
    --(pstShmInfo->iNumBlocks);

    /* update the first block ID in shminfo - assuming that blocks
       are deleted sequentially */
    pstShmInfo->iFirstBlockID = iBlockID + 1;

    return DAS_RET_SUCCESS;
}

void DAS_Delay(DAS_SHMINFO_S *pstShmInfo, int iDelayCount, int iReadData)
{
    /* delay the reader until the writer writes new data, that is, wait
      until (written data - delay count) becomes greater than read data */
    while (!((pstShmInfo->iWrittenData - iDelayCount) > iReadData))
    {
        /* stop waiting if the writer has finished writing */
        if (DAS_STATUS_WRITEDONE == pstShmInfo->iStatus)
        {
            break;
        }
    }

    return;
}

void DAS_CleanUp(const char *szKeyFile, int iPID)
{
    DAS_SHMINFO_S *pstShmInfo = NULL;
    int iShmIDShmInfo = 0;
    int *piShmIDShmInfo = &iShmIDShmInfo;
    int iBlockID = DAS_BLOCKID_START;   /* first block */
    int iRet = 0;

    /* locate shminfo */
    pstShmInfo = (DAS_SHMINFO_S *) DAS_ShmAlloc(szKeyFile,
                                                DAS_ID_SHMINF0,
                                                sizeof(DAS_SHMINFO_S),
                                                0444, /* r--r--r-- */
                                                &piShmIDShmInfo,
                                                iPID);
    if (NULL == pstShmInfo)
    {
        printf("DAS_CleanUp(): ERROR in DAS_ShmAlloc() for pstShmInfo\n");
        return;
    }

    if (pstShmInfo->iStatus == DAS_STATUS_NOP)
    {
        /* no header or data - delete shminfo */
        (void) shmctl(pstShmInfo->iShmID, IPC_RMID, NULL);
        return;
    }

    for (iBlockID = pstShmInfo->iFirstBlockID;
         iBlockID <= pstShmInfo->iHighestBlockID;
         ++iBlockID)
    {
        iRet = DAS_DeleteBlock(iBlockID, szKeyFile, pstShmInfo, iPID);
        if (iRet != DAS_RET_SUCCESS)
        {
            printf("DAS_CleanUp(): ERROR in DAS_DeleteBlock() for block %d\n",
                   iBlockID);
            printf("First block ID: %d\n", pstShmInfo->iFirstBlockID);
            printf("Highest block ID: %d\n", pstShmInfo->iHighestBlockID);
            printf("Keyfile: %s\n", szKeyFile);
//            assert(DAS_RET_SUCCESS == iRet);   /* abnormal behaviour */
            exit(1);
        }
    }

    /* delete shminfo */
    (void) shmctl(pstShmInfo->iShmID, IPC_RMID, NULL);

    return;
}

void DAS_DeleteHeader(int iPID)
{
    DAS_HEADERADDS_S stHeaderAdds = {0};
    DAS_SHMHEADER_S *pstShmHeader = NULL;

    stHeaderAdds = DAS_GetHeader(iPID);
    pstShmHeader = stHeaderAdds.pstShmHeader;
    if (NULL == pstShmHeader)
    {
        printf("DAS_DeleteHeader(): ERROR in DAS_GetHeader()\n");
        return;
    }

    /* delete shmheader, first header info, then shmheader */
    (void) shmctl(pstShmHeader->iHeaderInfoShmID, IPC_RMID, NULL);
    (void) shmctl(pstShmHeader->iShmHeaderShmID, IPC_RMID, NULL);

    return;
}

