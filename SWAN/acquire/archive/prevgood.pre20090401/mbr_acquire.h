/*
 * mbr_acquire.h
 * Header file for the data acquisition program
 *
 * Created by Jayanth Chennamangalam
 */

#ifndef __MBR_ACQUIRE_H__
#define __MBR_ACQUIRE_H__

#define MBR_PATH_LOCKFILE           "/home/das/lock/acquire.lock"
#define MBR_PATH_KILLSCRIPT         "/home/das/scripts/mbr_killacquire.py"

#define MAX_LEN_FILENAME            32
#define MAX_SIZE_PACKET             65536
#define MAX_SIZE_FILE               (99 * DAS_SIZE_SHM_DATA)
#define SIZE_PACKET                 1056
#define SIZE_FULL_PACKET            (SIZE_PACKET + 42)
//TODO: check this:
//#define MAX_NUM_PKTSPERFILE         (((int) ((MAX_SIZE_FILE/SIZE_PACKET)/256))*256)
#define MAX_NUM_PKTSPERFILE         ((int) (MAX_SIZE_FILE/SIZE_PACKET))
#define MAX_NUM_CHECKPKTSPERFILE    100
#define MAX_NUM_FILES               999
#define TIMEOUT                     1000
#define MODE_PROMISC                1
#define MBR_FILENPREFIX_DIAG        "packet"
#define MBR_FILENPREFIX_SNIFFACQ    "sniff"
#define MBR_NAME_CHANNEL            "ch01"
#define MBR_NAME_PSR                "nopulsar"
#define MBR_DATAFILE_EXT            "mbr"
#define MBR_LEN_NAME_CHANNEL        (strlen(MBR_NAME_CHANNEL))
#define MBR_LEN_NAME_PSR            (strlen(MBR_NAME_PSR))
#define MBR_LEN_COUNT               3
#define MBR_LEN_DATAFILE_EXT        (strlen(MBR_DATAFILE_EXT))
/* length of the timestamp string in the format 'yyyymmdd_hhmmss' */
#define MBR_LEN_TS                  15
//TODO: consider replaceing usage with MBR_MAX_LEN_GENSTRING
/* filename is of the format 'dasXX_XXXXXXXXXX_yyyymmdd_hhmmss_XXX.ext',
   the '1' being for the underscores and the period */
#define MBR_LEN_FILENAME            (MBR_LEN_NAME_CHANNEL + 1 \
                                     + MBR_LEN_NAME_PSR + 1 \
                                     + MBR_LEN_TS + 1 \
                                     + MBR_LEN_COUNT + 1 \
                                     + MBR_LEN_DATAFILE_EXT)
#define MBR_DAS_UID                 1001
#define MBR_DAS_GID                 1001
#define MBR_PCAP_USER               ((unsigned char *) "das01")

/* acquisition mode masks */
#define MBR_AMMASK_DW               0x01    /* disk-write */
#define MBR_AMMASK_FF               0x02    /* formatted-filename */
#define MBR_AMMASK_SHM              0x04    /* shared-memory-use */
#define MBR_AMMASK_PU               0x08    /* packet-update */
#define MBR_AMMASK_SC               0x10    /* slip-check */
/* acquisition modes */
#define MBR_ACQMODE_OBS             0x03    /* DW, FF */
#define MBR_ACQMODE_DIAG            0x01    /* DW */
#define MBR_ACQMODE_SNIFFACQ        0x0F    /* DW, FF, SHM, PU */
#define MBR_ACQMODE_SNIFF           0x0C    /* SHM, PU */
#define MBR_ACQMODE_CHECK           0x10    /* SC */
/* acquisition modes, as entered by the user */
#define MBR_USERAM_OBS              ((char *) "obs")
#define MBR_USERAM_DIAG             ((char *) "diag")
#define MBR_USERAM_SNIFFACQ         ((char *) "sniffacq")
#define MBR_USERAM_SNIFF            ((char *) "sniff")
#define MBR_USERAM_CHECK            ((char *) "check")

/* for sampling: 1 packet every MBR_SAMPINT will be written
   to the shared memory */
#define MBR_SAMPINT                 1000
#define MBR_SAMPOFFSET              100

/* for checking */
#define LEN_DATAHEADER              28
#define MAX_NUM_SLIPS               2000
#define MAX_NUM_INFOITEMS           3
#define POS_PREV                    0
#define POS_CURRENT                 1
#define POS_PKTCOUNT                2
#define MBR_PCAP_USER               ((unsigned char *) "das01")

typedef unsigned char BYTE;

#pragma pack(push)
#pragma pack(1)
typedef struct tagRFVals
{
    unsigned int iAtten1:6;
    unsigned int iAtten2:6;
    unsigned int iAtten3:6;
    unsigned int iAtten4:6;
    short int iLOFreq;
} MBR_RF_VALS_S;
#pragma pack(pop)

void MBR_PrintUsage(const char *pcProgName);
void MBR_ProcessPacket(u_char *pcUser,
                       const struct pcap_pkthdr *pstPacketHeader,
                       const u_char *pbPacket);
void MBR_BuildFilename(struct tm *pstTime, int iCount, char acFilename[]);
int MBR_OpenFiles();
void MBR_CloseFiles();
void MBR_HandleStopSignals(int iSigNo);

#endif  /* __MBR_ACQUIRE_H__ */

