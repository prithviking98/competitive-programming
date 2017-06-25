/*
 * mbr_mcd.h
 * Header file for the M&C daemon
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_MCD_H__
#define __MBR_MCD_H__

int MBR_CreateDispatchers(void);
int MBR_UpdateSourceName(char *pcSource);
int MBR_UpdateAcqDur(char *pcAcqDur);
int MBR_UpdateEthDev(char *pcEthDev);
int MBR_RunAcquire(void);
void MBR_HandleStopSignals(int iSigNo);
void MBR_HandleSIGCHLD(int iSigNo);
void MBR_PrintUsage(const char *pcProgName);

#endif  /* __MBR_MCD_H__ */

