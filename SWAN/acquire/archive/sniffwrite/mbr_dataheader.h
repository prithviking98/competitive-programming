/* mbr_dataheader.h
 * Data header description
 *
 * Created by Jayanth Chennamangalam on 2008.07.22
 */

#ifndef __MBR_DATAHEADER_H__
#define __MBR_DATAHEADER_H__

#if 0
#define MBR_LEN_SDH_DASID        5
#define MBR_LEN_SDH_RESERVED     6

#pragma pack(push, 1)
typedef struct MBR_SDataHeader
{
    /* 'long long int' is not valid ISO C; it is valid only from
       ISO/IEC 9899:1999 ('C99') onwards */
    long long int llMarker;                 /* FFFF FFFF FFFF FFFF */
    char acDASID[MBR_LEN_SDH_DASID];        /* 'DASXX' */
    /* attenuations are in the bitmap format, as it is stored
       in the bitmap file */
    unsigned short int iAtten1Val:6;                 /* Channel V RF attenuation */
    unsigned short int iAtten2Val:6;                 /* Channel V IF attenuation */
    unsigned short int iAtten3Val:6;                 /* Channel H RF attenuation */
    unsigned short int iAtten4Val:6;                 /* Channel H IF attenuation */

#define MBR_SDH_SIZE_ATTENUATORS                     3
    
    unsigned short int iLOFreq;                      /* LO frequency */
    char acReserved[MBR_LEN_SDH_RESERVED];  /* reserved bytes */
    unsigned short int iReserved: 7;                 /* reserved bits */
    unsigned short int iReset: 1;                    /* FPGA status - reset bit */
    unsigned short int iEnable: 1;                   /* FPGA status - enable bit */
    unsigned short int iProgram: 1;                  /* FPGA status - program status */
    unsigned short int iSync: 1;                     /* FPGA status - sync signal bit */
    unsigned short int iBitPacking: 2;               /* FPGA status - bit packing */
    unsigned short int iMode: 2;                     /* FPGA status - mode */
    unsigned short int iClock: 1;                    /* FPGA status - ADC clock status */
    unsigned short int iGPS;                         /* GPS pulse */
    unsigned int       iCount;                       /* counter value */
} MBR_DATA_HEADER_S;
#pragma pack(pop)
#endif

//TODO: TEMPORARY: to be changed once Vinutha gets back
#if 1
#define MBR_LEN_SDH_DASID        5
#define MBR_LEN_SDH_RESERVED     6

#pragma pack(push, 1)
typedef struct MBR_SDataHeader
{
    /* 'long long int' is not valid ISO C; it is valid only from
       ISO/IEC 9899:1999 ('C99') onwards */
    long long int llMarker;                 /* FFFF FFFF FFFF FFFF */
    /* attenuations are in the bitmap format, as it is stored
       in the bitmap file */
    unsigned short int iAtten1Val:6;                 /* Channel V RF attenuation */
    unsigned short int iAtten2Val:6;                 /* Channel V IF attenuation */
    unsigned short int iAtten3Val:6;                 /* Channel H RF attenuation */
    unsigned short int iAtten4Val:6;                 /* Channel H IF attenuation */

#define MBR_SDH_SIZE_ATTENUATORS                     3
    
    unsigned short int iLOFreq;                      /* LO frequency */
    char acReserved[MBR_LEN_SDH_RESERVED];  /* reserved bytes */
    char acDASID[MBR_LEN_SDH_DASID];        /* 'DSPXX' */
    unsigned short int iReserved: 7;                 /* reserved bits */
    unsigned short int iReset: 1;                    /* FPGA status - reset bit */
    unsigned short int iEnable: 1;                   /* FPGA status - enable bit */
    unsigned short int iProgram: 1;                  /* FPGA status - program status */
    unsigned short int iSync: 1;                     /* FPGA status - sync signal bit */
    unsigned short int iBitPacking: 2;               /* FPGA status - bit packing */
    unsigned short int iMode: 2;                     /* FPGA status - mode */
    unsigned short int iClock: 1;                    /* FPGA status - ADC clock status */
    unsigned short int iGPS;                         /* GPS pulse */
    unsigned int       iCount;                       /* counter value */
} MBR_DATA_HEADER_S;
#pragma pack(pop)
#endif

/* mask which extracts the fraction bit of the attenuation value */
#define MBR_SDH_MASKATTENFRAC                       0x01

#if 0
/* distance of the first attenuator value from the base, for retrieving
   its address */
#define MBR_SDH_GetAtten1Pos(pstDH)         (sizeof(pstDH->llMarker)           \
                                             + sizeof(pstDH->acDASID))
#endif
#if 1
/* distance of the first attenuator value from the base, for retrieving
   its address */
#define MBR_SDH_GetAtten1Pos(pstDH)         (sizeof(pstDH->llMarker))
#endif

#if 0
#define MBR_SDH_GetFPGAStatusPos(pstDH)     (sizeof(pstDH->llMarker)           \
                                             + sizeof(pstDH->acDASID)          \
                                             + MBR_SDH_SIZE_ATTENUATORS        \
                                             + sizeof(pstDH->iLOFreq)          \
                                             + sizeof(pstDH->acReserved))
#endif
#if 1
#define MBR_SDH_GetFPGAStatusPos(pstDH)     (sizeof(pstDH->llMarker)           \
                                             + MBR_SDH_SIZE_ATTENUATORS        \
                                             + sizeof(pstDH->iLOFreq)          \
                                             + sizeof(pstDH->acReserved))      \
                                             + sizeof(pstDH->acDASID)
#endif

/* macros for getting structure fields */
#define MBR_SDH_GetDASID(pstDH)             (pstDH->acDASID)
#define MBR_SDH_GetAtten1Val(pstDH)         ((float) ((pstDH->iAtten1Val >> 1) \
                                            + ((pstDH->iAtten1Val              \
                                                && MBR_SDH_MASKATTENFRAC)      \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetAtten2Val(pstDH)         ((float) ((pstDH->iAtten1Val >> 1) \
                                            + ((pstDH->iAtten2Val              \
                                                && MBR_SDH_MASKATTENFRAC)      \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetAtten3Val(pstDH)         ((float) ((pstDH->iAtten1Val >> 1) \
                                            + ((pstDH->iAtten3Val              \
                                                && MBR_SDH_MASKATTENFRAC)      \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetAtten4Val(pstDH)         ((float) ((pstDH->iAtten1Val >> 1) \
                                            + ((pstDH->iAtten4Val              \
                                                && MBR_SDH_MASKATTENFRAC)      \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetResetBit(pstDH)          (pstDH->iReset)
#define MBR_SDH_GetEnableBit(pstDH)         (pstDH->iEnable)
#define MBR_SDH_GetProgramStatus(pstDH)     (pstDH->iProgram)
#define MBR_SDH_GetSyncBit(pstDH)           (pstDH->iSync)
#define MBR_SDH_GetBitPacking(pstDH)        (pstDH->iBitPacking)
#define MBR_SDH_GetMode(pstDH)              (pstDH->iMode)
#define MBR_SDH_GetADCClockStatus(pstDH)    (pstDH->iClock)
#define MBR_SDH_GetGPS(pstDH)               (pstDH->iGPS)
#define MBR_SDH_GetCount(pstDH)             (pstDH->iCount)

#endif  /* __MBR_DATAHEADER_H__ */
