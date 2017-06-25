/*
 * mbr_get.h
 * Declarations for the GET commands
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_GET_H__
#define __MBR_GET_H__

#ifdef MBR_LOCAL
#ifdef MBR_GET
#define MBR_EXE_DISPLAY     "cat"

int MBR_Get(char *argv[]);
int MBR_GetDASID(void);
int MBR_GetSource(void);
int MBR_GetAcqStatus(void);
int MBR_GetAcqDur(void);
int MBR_GetPktOffset(void);
int MBR_GetEthDev(void);
int MBR_GetAcqMode(void);
int MBR_GetData(char *pcFile);
int MBR_GetLOFreq(void);
int MBR_GetLOMin(void);
int MBR_GetLOMax(void);
int MBR_GetLOStep(void);
int MBR_GetLODwell(void);
int MBR_GetAttenuator(const char *pcID);
int MBR_GetDataMode(void);
int MBR_GetBitpackMode(void);
int MBR_GetSampClkFreq(void);
#endif  /* MBR_GET */
#endif  /* MBR_LOCAL */

#endif  /* __MBR_GET_H__ */

