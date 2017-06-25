/*
 * mbr_do.h
 * Declarations for the DO commands
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Harshad Sahasrabudhe
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_DO_H__
#define __MBR_DO_H__

#ifdef MBR_LOCAL
#ifdef MBR_DO
int MBR_Do(int argc, char *argv[]);
int MBR_DoFPGAReset(const char *pcReset);
int MBR_DoFPGAProg(void);
int MBR_DoSimGPS(void);
int MBR_DoShutdown(void);
int MBR_DoReboot(void);
int MBR_DoTxCheck(void);
int MBR_DoAcquire(void);
int MBR_DoRun(int iArgC, char *apcArgV[]);
int MBR_DoTimeSync(char *pcTime);
#endif  /* MBR_DO */
#endif  /* MBR_LOCAL */

#endif  /* __MBR_DO_H__ */

