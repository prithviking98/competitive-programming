/* mbr_dataheader.c
 * Data header manipulation functions
 *
 * Created by Jayanth Chennamangalam
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mbr_dataheader.h"
#include "mbr_dataheader_v0.h"

MBR_HEADERINFO_S MBR_GetDataHeader(MBR_BYTE *pbPacket)
{
    MBR_HEADERINFO_S stHeaderInfo = {0};
    char acMarker[MBR_LEN_SDH_MARKER] = {0};
    long long int *pllMarker = NULL;
    char acDASID[MBR_LEN_SDH_DASID+1] = {0};

    /* read the first 6 bytes of the packet to find out which header to use */
    (void) strncpy(acMarker, (char *) pbPacket, MBR_LEN_SDH_MARKER);
    pllMarker = (long long int *) pbPacket;
    if (0 == strcmp(acMarker, MBR_SDH_MARKER))          /* new marker */
    {
        /* decode the new header */
        MBR_DATA_HEADER_S *pstDataHeader = NULL;

        pstDataHeader = (MBR_DATA_HEADER_S *) pbPacket;

        (void) strncpy(acDASID, MBR_SDH_GetDASID(pstDataHeader), MBR_LEN_SDH_DASID);
        stHeaderInfo.iDASID = atoi(acDASID);

        stHeaderInfo.fAtten1Val = MBR_SDH_GetAtten1Val(pstDataHeader);
        stHeaderInfo.fAtten2Val = MBR_SDH_GetAtten2Val(pstDataHeader);
        stHeaderInfo.fAtten3Val = MBR_SDH_GetAtten3Val(pstDataHeader);
        stHeaderInfo.fAtten4Val = MBR_SDH_GetAtten4Val(pstDataHeader);
        stHeaderInfo.iLOFreq = MBR_SDH_GetLOFreq(pstDataHeader);
        stHeaderInfo.iTimestamp = MBR_SDH_GetTimestampBit(pstDataHeader);
        stHeaderInfo.iSampClock = MBR_SDH_GetSampClkStatusBit(pstDataHeader);
        stHeaderInfo.iSync = MBR_SDH_GetSyncBit(pstDataHeader);
        stHeaderInfo.iReset = MBR_SDH_GetResetBit(pstDataHeader);
        stHeaderInfo.iEnable = MBR_SDH_GetEnableBit(pstDataHeader);
        stHeaderInfo.iBitPacking = MBR_SDH_GetBitPacking(pstDataHeader);
        stHeaderInfo.iDataMode = MBR_SDH_GetDataMode(pstDataHeader);
        stHeaderInfo.iGPSStatus = MBR_SDH_GetGPSStatusBit(pstDataHeader);
        stHeaderInfo.iGPS = MBR_SDH_GetGPS(pstDataHeader);
        stHeaderInfo.iCount = MBR_SDH_GetCount(pstDataHeader);
    }
    else if (0xFFFFFFFFFFFFFFFFLL == *pllMarker)       /* old marker */
    {
        /* decode the old header */
        MBR_DATA_HEADER_V0_S *pstDataHeader = NULL;

        pstDataHeader = (MBR_DATA_HEADER_V0_S *) pbPacket;

        (void) strncpy(acDASID, (MBR_SDH_V0_GetDASID(pstDataHeader) + 3), MBR_LEN_SDH_V0_DASID);
        stHeaderInfo.iDASID = atoi(acDASID);

        stHeaderInfo.fAtten1Val = MBR_SDH_V0_GetAtten1Val(pstDataHeader);
        stHeaderInfo.fAtten2Val = MBR_SDH_V0_GetAtten2Val(pstDataHeader);
        stHeaderInfo.fAtten3Val = MBR_SDH_V0_GetAtten3Val(pstDataHeader);
        stHeaderInfo.fAtten4Val = MBR_SDH_V0_GetAtten4Val(pstDataHeader);
        stHeaderInfo.iLOFreq = pstDataHeader->iLOFreq;
        stHeaderInfo.iSampClock = MBR_SDH_V0_GetADCClockStatus(pstDataHeader);
        stHeaderInfo.iSync = MBR_SDH_V0_GetSyncBit(pstDataHeader);
        stHeaderInfo.iReset = MBR_SDH_V0_GetResetBit(pstDataHeader);
        stHeaderInfo.iEnable = MBR_SDH_V0_GetEnableBit(pstDataHeader);
        stHeaderInfo.iBitPacking = MBR_SDH_V0_GetBitPacking(pstDataHeader);
        stHeaderInfo.iDataMode = MBR_SDH_V0_GetMode(pstDataHeader);
        stHeaderInfo.iGPS = MBR_SDH_V0_GetGPS(pstDataHeader);
        stHeaderInfo.iCount = MBR_SDH_V0_GetCount(pstDataHeader);
    }
    else
    {
#if 0
        fprintf(stderr, "ERROR: Unknown marker: %s / %lld!\n", acMarker, *pllMarker);
#endif
        return stHeaderInfo;    /* zeroes */
    }

    return stHeaderInfo;
}

