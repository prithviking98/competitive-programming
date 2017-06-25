/*
   das.h
   Header file for common DAS stuff

   Created by Jayanth Chennamangalam
   2007.08.20
*/

#ifndef __DAS_H__
#define __DAS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>

#include <errno.h>

#define DAS_FALSE           0
#define DAS_TRUE            1

#define DAS_RET_SUCCESS     0
#define DAS_RET_ERROR       1

#define DAS_SIZE_HEADER     2048    /* 2KB */

#define DAS_LEN_STRING      32

typedef unsigned char DAS_BYTE;

typedef struct tag_DAS_Header
{
    double      dBandwidth1;
    float       fFreqCentre1;
    float       fDM;
    int         iMarkerInterval;    /* marker interval in words (to be converted to bytes) */
#if 0
    DASDATE_S   stDate;
    DASTIME_S   stTime;     /* includes t.ti_hund (ih[48]) */
#endif
    char        acPulsarName[DAS_LEN_STRING];
    char        acDataFile[DAS_LEN_STRING];
    char        acSiteName[DAS_LEN_STRING];
    int         iNumRFChannels;
    int         iNumBits;
    float       fFreqCentre2;
    double      dBandwidth2;
    char        acObserverName[DAS_LEN_STRING];
    /* int t.ti_hund moved into DASTIME_S stTime */
    float       fPSync;
    float       fOnOffset;
    float       fFreqRef;
    float       fFreqLOCh11;
    float       fFreqLOCh12;
    float       fFreqLOCh21;
    float       fFreqLOCh22;
    float       fFreqIFCh11;
    float       fFreqIFCh12;
    float       fFreqIFCh21;
    float       fFreqIFCh22;
} DAS_HEADER_S;

void DAS_PrintUsage(const char *szProgName);

#endif  /* #ifndef __DAS_H__ */

