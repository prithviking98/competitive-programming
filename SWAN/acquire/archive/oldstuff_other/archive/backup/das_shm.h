/*
   das_shm.h
   Common includes, constants, structure definitions, and function declarations

   Created by Jayanth Chennamangalam
   2007.10.10
*/

#ifndef __DAS_SHM_H__
#define __DAS_SHM_H__

#include <sys/shm.h>
#include <sys/ipc.h>

/* IDs used to generate keys for the shmget() function, using ftok() */
/* absolute IDs */
#define DAS_ID_SHMHEADER        0xFD
#define DAS_ID_HEADERINFO       0xFE
#define DAS_ID_SHMINF0          0xFF

/* shift IDs */
#define DAS_ID_BLOCK			0x0
#define DAS_ID_DATA             0x1        /* size of DAS_ID_XXX: 1 bit */

#define DAS_BLOCKID_START       1

/* from ftok() man page:

NOTES
       Under libc4 and libc5 (and under SunOS 4.x) the prototype was
              key_t ftok(char *pathname, char proj_id);
       Today proj_id is an int, but still only 8 bits are used.  Typical usage
       has an ASCII character proj_id, that is why the behavior is said to  be
       undefined when proj_id is zero.

   therefore, DAS_ID_SHIFT should be such that (DAS_ID_BLOCK << DAS_ID_SHIFT)
   does not overflow onto the 9th bit, counted from the LSB; DAS_BLOCKID_START
   should not be 0 either.
*/
#define DAS_ID_SHIFT            7           /* shift IDs by DAS_ID_SHIFT bits
                                               to the left before OR-ing with
                                               individual block IDs.
                                               maximum number of
                                               blocks = 2^DAS_ID_SHIFT */

//TODO: wraparound for  block number
#define DAS_MAX_SHM_BLOCKS      128          /* limit on number of blocks
                                               <= 2^DAS_ID_SHIFT */

#define DAS_MAX_SHM_NATTCH      128

//TODO: modify this
#define DAS_SHM_DATATYPE        int

#define DAS_SIZE_SHM_DATA       15728640    /* 15MB */
//#define DAS_SIZE_SHM_DATA       10485760     /* 10MB */
//#define DAS_SIZE_SHM_DATA       1048576     /* 1MB */
//#define DAS_SIZE_SHM_DATA       5242880     /* 5MB */
/*  size of DAS_SIZE_SHM_DATA in terms of DAS_SHM_DATATYPE */
#define DAS_SIZE_SHM_DATA_DT    (DAS_SIZE_SHM_DATA / sizeof(DAS_SHM_DATATYPE))

#define DAS_KEY_FL_OUT          "./key_das_fl_out"
#define DAS_KEY_CHK_OUT         "./key_chk_n_rmmark_lin_out"
#define DAS_KEY_SPECTRO_OUT     "./key_das_spectro_lin_out"
#define DAS_KEY_STAT_OUT        "./key_das_dyn_stat_lin_out"
#define DAS_KEY_DEDISP_OUT      "./key_das_dyn_dedisp_lin_out"
#define DAS_KEY_EXTRACT_OUT     "./key_das_extract_lin_out"

/* program IDs - for fortran programs, and also used for debugging */
#define DAS_PID_FL              0
#define DAS_PID_CHK             1
#define DAS_PID_SPECTRO         2
#define DAS_PID_STAT            3
#define DAS_PID_DEDISP          4
#define DAS_PID_EXTRACT         5

#define DAS_STATUS_NOP          0
#define DAS_STATUS_WRITESTART   1
#define DAS_STATUS_WRITEDONE    2

/* the structure stored in shared memory containing header information */
typedef struct tag_DAS_ShmHeader
{
    int iShmHeaderShmID;        /* shmid of the shmheader data structure */
    int iHeaderInfoShmID;       /* shmid of the header info */
} DAS_SHMHEADER_S;

/* one shminfo structure is created in shared memory per program */
typedef struct tag_DAS_ShmInfo
{
    int iShmID;                 /* shmid of the shminfo data structure */
    int iNumBlocks;             /* number of allocated blocks */
    int iFirstBlockID;          /* the first block ID */
    int iHighestBlockID;        /* the highest block ID so far */
    int iWrittenData;           /* written data items in terms of
                                   DAS_SHM_DATATYPE */ 
    int iStatus;                /* write status */
    int iConfigStatus;          /* status of config file */
} DAS_SHMINFO_S;

typedef struct tag_DAS_Block
{
    int iBlockID;                       /* block ID of this block */
    int iBlockShmID;                    /* shmid of this block */
    int iDataShmID;                     /* shmid of the data */
    int* iShmBlockAdds[DAS_MAX_SHM_NATTCH];
    int* iShmDataAdds[DAS_MAX_SHM_NATTCH];
    int iLastShmAdd;
} DAS_BLOCK_S;

/* the shmheader and header info addresses that are returned by the
   DAS_CreateShmHeader() and DAS_GetHeader() functions */
typedef struct tag_DAS_HeaderAdds
{
    DAS_SHMHEADER_S *pstShmHeader;  /* pointer to the shmheader */
#if 0
    DAS_HEADER_S *pstHeader;        /* pointer to the header info */
#else
    DAS_BYTE *pbHeader;             /* pointer to the header info */
#endif
} DAS_HEADERADDS_S;

/* the block and data addresses that are returned by the DAS_CreateBlock()
   and DAS_Get*Block*() functions */
typedef struct tag_DAS_BlockAdds
{
    DAS_BLOCK_S *pstBlock;              /* pointer to the block */
    DAS_SHM_DATATYPE *pData;            /* pointer to the data */
} DAS_BLOCKADDS_S;

DAS_SHMINFO_S* DAS_ShmInit(const char *szKeyFile, int iPID);
void* DAS_ShmAlloc(const char *szPath,
                   int iIPCID,
                   size_t iSize,
                   int iFlag,
                   int **ppiShmID,
                   int iPID);
DAS_HEADERADDS_S DAS_GetHeader();
DAS_BLOCKADDS_S DAS_GetFirstBlock(const char *szKeyFile, int iPID);
DAS_BLOCKADDS_S DAS_GetNextBlock(int iThisBlockID,
                              const char *szKeyFile,
                              int iPID);
DAS_BLOCKADDS_S DAS_GetBlockByBlockID(int iBlockID,
                                   const char *szKeyFile,
                                   int iPID);
DAS_HEADERADDS_S DAS_CreateShmHeader(int iPID);
DAS_SHMINFO_S* DAS_CreateShmInfo(const char *szKeyFile, int iPID);
DAS_BLOCKADDS_S DAS_CreateBlock(int iNewBlockID,
                             const char *szKeyFile,
                             DAS_SHMINFO_S *pstShmInfo,
                             int iPID);
int DAS_UpdateShmHeader(DAS_BYTE *pbNewHeaderInfo, int iPID);
int DAS_DeleteBlock(int iBlockID,
                    const char *szKeyFile,
                    DAS_SHMINFO_S *pstShmInfo,
                    int iPID);
void DAS_Delay(DAS_SHMINFO_S *pstShmInfo, int iDelayCount, int iReadData);
void DAS_CleanUp(const char *szKeyFile, int iPID);
void DAS_DeleteHeader(int iPID);
void DAS_HandleSIGINT(int iSigNo);

#endif  /* #ifndef __DAS_SHM_H__ */

