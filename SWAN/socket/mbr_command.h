/*
 * mbr_command.h
 * Declarations for the command program
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_COMMAND_H__
#define __MBR_COMMAND_H__

void MBR_PrintUsage(int iCmdType);

#ifdef MBR_LOCAL
#ifdef MBR_SET
int MBR_OpenRFHist();
#endif  /* MBR_SET */
#endif  /* MBR_LOCAL */

#ifdef MBR_REMOTE
int MBR_FormCommand(char *apcOutArgv[], char *apcInArgv[], int iArgc);
void MBR_HandleStopSignals(int iSigNo);
#endif

#endif  /* __MBR_COMMAND_H__ */

