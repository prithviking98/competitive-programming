/*
 * mbr_set.h
 * Declarations for the SET commands
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Harshad Sahasrabudhe
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_SET_H__
#define __MBR_SET_H__

#ifdef MBR_LOCAL
#ifdef MBR_SET
int MBR_Set(char *argv[]);
int MBR_SetDASID(const char *pcDASID);
int MBR_SetSource(const char *pcSource);
int MBR_SetEthDev(const char *pcDevice);
int MBR_SetAcqMode(const char *pcAcqMode);
int MBR_SetAcqDur(const char *pcDuration);
int MBR_SetPktOffset(const char *pcOffset);
int MBR_SetLOFreq(const char *pcFreq);
int MBR_SetLOFreqLastConf(void);
int MBR_SetLOMin(const char *pcFreq);
int MBR_SetLOMax(const char *pcFreq);
int MBR_SetLOStep(const char *pcFreq);
int MBR_SetLODwell(const char *pcTime);
int MBR_SetAcq(const char *pcStatus);
int MBR_ValidateAttenuatorSetting(char *pcID, char *pcValue);
int MBR_SetAttenuator(const char *pcID, const char *pcValue);
int MBR_SetAttenuatorLastConf(void);
int MBR_SetDataMode(const char *pcDataMode);
int MBR_SetBitpackMode(const char *pcBitpackMode);
int MBR_SetSampClkFreq(const char *pcFreq);
int MBR_SetRFHist(void);
int MBR_SetTimestamp(void);
#endif

#if (MBR_SET || MBR_DO)
int MBR_DownloadRFHist(void);
int MBR_DownloadHeaderInfo(void);
int MBR_UpdateRFHist(void);
#endif  /* (MBR_SET || MBR_DO) */
#endif  /* MBR_LOCAL */

#endif  /* __MBR_SET_H__ */

