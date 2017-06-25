/* mbr_dataheader.h
 * Data header description
 *
 * Created by Jayanth Chennamangalam on 2008.07.22
 * Data header structure changed on 2009.04.19. The old header has now been
 * moved to mbr_dataheader_v0.h.
 */

#ifndef __MBR_DATAHEADER_H__
#define __MBR_DATAHEADER_H__

#define MBR_SDH_MARKER                      "MBRDSP"
#define MBR_SDH_MARKER_V0                   "FFFFFF"

#define MBR_LEN_SDH_MARKER                  6
#define MBR_LEN_SDH_DASID                   2
#define MBR_LEN_SDH_HEADERINFO              10

typedef unsigned char MBR_BYTE;

#pragma pack(push, 1)
typedef struct MBR_SDataHeader
{
    char acMarker[MBR_LEN_SDH_MARKER];      /* MBRDSP */
    char acDASID[MBR_LEN_SDH_DASID];        /* 'XX' */
    char acHdrInfo[MBR_LEN_SDH_HEADERINFO]; /* header info, including source
                                               name */
    MBR_BYTE iAtten1Val;                    /* Channel V RF attenuation */
    MBR_BYTE iAtten2Val;                    /* Channel V IF attenuation */
    MBR_BYTE iAtten3Val;                    /* Channel H RF attenuation */
    MBR_BYTE iAtten4Val;                    /* Channel H IF attenuation */

/* size of all attenuation bits together, in bytes */
#define MBR_SDH_SIZE_ATTENUATORS            4
    
    unsigned short int iLOFreq;             /* LO frequency */
    unsigned short int iReserved: 6;        /* reserved bits */
    unsigned short int iTimestamp: 1;       /* FPGA status - timestamp status */
    unsigned short int iSampClock: 1;       /* FPGA status - sampling clock
                                               status */
    unsigned short int iSync: 1;            /* FPGA status - sync signal bit */
    unsigned short int iReset: 1;           /* FPGA status - reset bit */
    unsigned short int iEnable: 1;          /* FPGA status - enable bit */
    unsigned short int iBitPacking: 2;      /* FPGA status - bit packing */
    unsigned short int iDataMode: 2;        /* FPGA status - data mode */
    unsigned short int iGPSStatus: 1;       /* FPGA status - GPS status */
    unsigned short int iGPS;                /* GPS pulse */
    unsigned int       iCount;              /* counter value */
} MBR_DATA_HEADER_S;
#pragma pack(pop)

/* information extracted from the header */
typedef struct MBR_SHeaderInfo
{
    int iDASID;
    float fAtten1Val;
    float fAtten2Val;
    float fAtten3Val;
    float fAtten4Val;
    int iLOFreq;
    int iTimestamp;
    int iSampClock;
    int iSync;
    int iReset;
    int iEnable;
    int iBitPacking;
    int iDataMode;
    int iGPSStatus;
    int iGPS;
    int iCount;
} MBR_HEADERINFO_S;

/* mask which extracts the fraction bit of the attenuation value */
#define MBR_SDH_MASKATTENFRAC               0x01

/* distance of the first attenuator value from the base, for retrieving
   its address */
#define MBR_SDH_GetAtten1Pos(pstDH)         (sizeof(pstDH->acMarker)           \
                                             + sizeof(pstDH->acDASID)          \
                                             + sizeof(pstDH->acHdrInfo))

#define MBR_SDH_GetFPGAStatusPos(pstDH)     (sizeof(pstDH->acMarker)           \
                                             + sizeof(pstDH->acDASID)          \
                                             + sizeof(pstDH->acHdrInfo)        \
                                             + MBR_SDH_SIZE_ATTENUATORS        \
                                             + sizeof(pstDH->iLOFreq))

/* macros for getting structure fields */
#define MBR_SDH_GetDASID(pstDH)             (pstDH->acDASID)
#define MBR_SDH_GetAtten1Val(pstDH)         ((float) ((pstDH->iAtten1Val >> 1) \
                                            + ((pstDH->iAtten1Val              \
                                                & MBR_SDH_MASKATTENFRAC)       \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetAtten2Val(pstDH)         ((float) ((pstDH->iAtten2Val >> 1) \
                                            + ((pstDH->iAtten2Val              \
                                                & MBR_SDH_MASKATTENFRAC)       \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetAtten3Val(pstDH)         ((float) ((pstDH->iAtten3Val >> 1) \
                                            + ((pstDH->iAtten3Val              \
                                                & MBR_SDH_MASKATTENFRAC)       \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetAtten4Val(pstDH)         ((float) ((pstDH->iAtten4Val >> 1) \
                                            + ((pstDH->iAtten4Val              \
                                                & MBR_SDH_MASKATTENFRAC)       \
                                               ? 0.5 : 0)))
#define MBR_SDH_GetLOFreq(pstDH)            (pstDH->iLOFreq)
#define MBR_SDH_GetTimestampBit(pstDH)      (pstDH->iTimestamp)
#define MBR_SDH_GetSampClkStatusBit(pstDH)  (pstDH->iSampClock)
#define MBR_SDH_GetSyncBit(pstDH)           (pstDH->iSync)
#define MBR_SDH_GetResetBit(pstDH)          (pstDH->iReset)
#define MBR_SDH_GetEnableBit(pstDH)         (pstDH->iEnable)
#define MBR_SDH_GetBitPacking(pstDH)        (pstDH->iBitPacking)
#define MBR_SDH_GetDataMode(pstDH)          (pstDH->iDataMode)
#define MBR_SDH_GetGPSStatusBit(pstDH)      (pstDH->iGPSStatus)
#define MBR_SDH_GetGPS(pstDH)               (pstDH->iGPS)
#define MBR_SDH_GetCount(pstDH)             (pstDH->iCount)

MBR_HEADERINFO_S MBR_GetDataHeader(MBR_BYTE *pbPacket);

#endif  /* __MBR_DATAHEADER_H__ */

