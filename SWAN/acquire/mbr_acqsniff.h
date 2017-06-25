/* mbr_acqsniff.h
 * Header file for the data sniffing program
 *
 * Created by Jayanth Chennamangalam
 */

#ifndef __MBR_ACQSNIFF_H__
#define __MBR_ACQSNIFF_H__

#define MBR_FALSE                   0
#define MBR_TRUE                    1

#define SIZE_PACKET                 1056
#define DAS_CHK_SIZE_DATABLOCK      (SIZE_PACKET * 1)
#define DAS_CHK_SIZE_DATABLOCK_DT   (DAS_CHK_SIZE_DATABLOCK \
                                     / sizeof(DAS_SHM_DATATYPE))
#define DAS_PKTSPERBLOCK            (DAS_CHK_SIZE_DATABLOCK / SIZE_PACKET)
#define LEN_DATAHEADER              28
#define MBR_PORT_DATA               55002

#define MBR_MC_IP                   "192.168.1.1"

void MBR_PrintUsage(const char *pcProgName);
void MBR_HandleStopSignals(int iSigNo);

#endif  /* __MBR_ACQSNIFF_H__ */

