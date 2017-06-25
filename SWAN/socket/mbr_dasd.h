/*
 * mbr_dasd.h
 * Header file for the DAS daemon
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_DAS_H__
#define __MBR_DAS_H__

MBR_RET_INFO MBR_ProcessCommand(int argc, char *argv[]);
void MBR_HandleStopSignals(int iSigNo);
void MBR_HandleSIGCHLD(int iSigNo);
void MBR_PrintUsage(const char *pcProgName);

#endif  /* __MBR_DAS_H__ */

