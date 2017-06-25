/*
 * mbr_common.h
 * Common definitions for the GBT-RRI Multi-Band Receiver software
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_COMMON_H__
#define __MBR_COMMON_H__

#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stddef.h>
#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <syslog.h>
#include <net/if.h>
#include <sys/wait.h>

using namespace std;

/* OPEN: rethink error values */
/* error and warning return values */
#define MBR_RET_SUCCESS             0
#define MBR_RET_ERROR               -1
#define MBR_RET_ERROR_SYS           10
#define MBR_RET_PEERSHUTDOWN        -2
#define MBR_RET_ENTRYNOTFOUND       -3
#define MBR_RET_WARNING             4
#define MBR_RET_CLEANUP             5

/* true and false */
#define MBR_FALSE                   0
#define MBR_TRUE                    1

/* socket types */
#define MBR_SOCKTYPE_SERVER         0
#define MBR_SOCKTYPE_CLIENT         1

/* acquisition status */
#define MBR_ACQSTATUS_OFF           0
#define MBR_ACQSTATUS_ON            1

#define MBR_DO_PROC_VIEW            1
#define MBR_DO_ABORT_LASTOP         0
#define MBR_DO_ABORT_ALL            1

/* number of arguments for the mbracquire program */
#define MBR_ACQ_MAX_ARGS            10

/* number of attenuators and phaseshifters */
#define MBR_MAX_DEV_ATTENUATORS     4
#define MBR_DEVID_ATTENUATOR_START  1
#define MBR_DEVID_ATTENUATOR_STOP   (MBR_MAX_DEV_ATTENUATORS                   \
                                     - MBR_DEVID_ATTENUATOR_START + 1)

#define MBR_MAX_ATTENUATION         31.5

/* RF history file fields */
#define MBR_RFHIST_NUM_FIELDS       5
#define MBR_RFHIST_ATTEN1           0
#define MBR_RFHIST_ATTEN2           1
#define MBR_RFHIST_ATTEN3           2
#define MBR_RFHIST_ATTEN4           3
#define MBR_RFHIST_LOFREQ           4

/* maximum size of a command packet */
#define MBR_MAX_SIZE_PACKET         256

#define MBR_MAX_NUM_ARGS            10
#define MBR_MAX_LEN_ARG             64

/* maximum length of a generic character array */
#define MBR_MAX_LEN_GENSTRING       256

#define MBR_LEN_BACKLOGQUEUE        10

/* length of the timestamp string in the format 'yyyy-mm-dd hh:mm:ss' */
#define MBR_LEN_TIMESTAMP           19

/* number of seconds in 12 hours */
#define MBR_SEC_IN_12_HOURS         43200

/* port numbers */
/* NOTE: the minimum and maximum allowable port numbers are as per IANA
   guidelines (http://www.iana.org/assignments/port-numbers), DO NOT change
   them */
#define MBR_PORT_USEMIN             49152   /* DO NOT change this */
#define MBR_PORT_USEMAX             65535   /* DO NOT change this */
#define MBR_PORT_MCDPARSER          50000   /* mcd parser listens here
                                               for commands */
#define MBR_PORT_DAS                50001   /* dasd listens here for commands */
#define MBR_PORT_SRC_RAWDATA        55000
#define MBR_PORT_DST_RAWDATA        55001
#define MBR_PORT_DST_SNIFFDATA      55002
#define MBR_PORT_DSP                60000   /* control commands are sent here */

/* IP address of the DSP board */
#define MBR_IP_DSP                  "10.0.1.1"

/* the number of DAS machines */
#define MBR_MAX_DAS                 10

#define MBR_UID_DAS                 1001
#define MBR_GID_DAS                 1001

#define MBR_ARG_HELPLONG            "--help"
#define MBR_ARG_HELPSHORT           "-h"

#define MBR_ARG_VERLONG            "--version"
#define MBR_ARG_VERSHORT           "-v"

#define MBR_CMDTYPE_SET             0
#define MBR_CMDTYPE_GET             1
#define MBR_CMDTYPE_DO              2

/* the HOME environment variable and paths relative to its value */
#define MBR_ENV_HOME                "HOME"  /* the home directory */
#define MBR_ENV_SOURCE              "MBRSOURCE"
#define MBR_PATH_MSGQKEYFILE        "./"
#define MBR_PATH_PIDFILEDIR         "/var/run/"
#define MBR_PATH_DASMAP             "/config/hostnamemap"
#define MBR_PATH_BIN                "/bin/"
#define MBR_PATH_ERRORLOG           "/log/error.log"
#define MBR_PATH_TERMFILE           "/log/terminal"
#define MBR_PATH_RFHIST             "/log/rfhist"
#define MBR_PATH_HELPFILE           "/docs/commands"

/* for running mbrdo <das-id> run <command> commands */
#define MBR_SHELL                   "/bin/bash"
/* the shell option for reading from a user-supplied string.
   NOTE: this should be changed based on the value of MBR_SHELL */
#define MBR_SHELL_OPT               "-c"

/* daemonising */
#define MBR_DID_MCD                 0
#define MBR_DID_DASD                1
#define MBR_PIDFNAME_MCD            "mbrmcd.pid"
#define MBR_PIDFNAME_DASD           "mbrdasd.pid"

/* Ethernet devices */
#define MBR_ETH_PRIMARY             "eth0"

#define MBR_RETSTRING_ERROR         "Error!"
#define MBR_RETSTRING_INVALIDCMD    "Invalid command!"
#define MBR_RETSTRING_TIMEOUT       "Timeout!"
#define MBR_RETSTRING_DASDOWN       "DAS not up!"

#define MBR_ID_MCDPARSER            0
#define MBR_ID_DEFAULTSERVER        -1

/* the message type for the MBR_MSG object */
#define MBR_MSG_DEF_TYPE            1

#define MBR_STRING_LOCAL            "local"

#define MBR_STATUS_ON               "on"
#define MBR_STATUS_OFF              "off"

/* config file actions */
#define MBR_CONFIG_READ             0
#define MBR_CONFIG_UPDATE           1

#define MBR_DATAMODE_DIAG           0
#define MBR_DATAMODE_OBSV           1

#define MBR_ACQMODE_OBS             0
#define MBR_ACQMODE_SNIFF           1
#define MBR_ACQMODE_SNIFFACQ        2
#define MBR_ACQMODE_CHECK           3

#define MBR_PREFIX_ETHDEV           "eth"
#define MBR_POS_ETH_ID              3   /* the position of the Ethernet device
                                           number in "ethX" - third character,
                                           counting from 0 */

/* mask to get the fractional value of attenuation */
#define MBR_MASK_ATTNFRAC           0x01

/* the fractional value that is possible for the attenuator */
#define MBR_ATTN_FRAC               0.5

/* the factor that has to be taken care of when the LSB contains the fractional
   attenuation value */
#define MBR_ATTN_FACTOR             2

#define MBR_FPGABIT_ENABLE          "enable"

#define MBR_MAX_NUM_DEVICES         20

/* command string components */
#define MBR_CMD_SET                 "mbrset"
#define MBR_CMD_GET                 "mbrget"
#define MBR_CMD_DO                  "mbrdo"
#define MBR_CMD_ACQUISITION         "acquisition"
#define MBR_CMD_ON                  "on"
#define MBR_CMD_OFF                 "off"
#define MBR_CMD_ATTENUATOR          "attenuator"
#define MBR_CMD_ATTENUATOR1         "attenuator1"
#define MBR_CMD_ATTENUATOR2         "attenuator2"
#define MBR_CMD_ATTENUATOR3         "attenuator3"
#define MBR_CMD_ATTENUATOR4         "attenuator4"
#define MBR_CMD_VRF                 "vrf"
#define MBR_CMD_VIF                 "vif"
#define MBR_CMD_HRF                 "hrf"
#define MBR_CMD_HIF                 "hif"
#define MBR_CMD_LOFREQ              "lofreq"
#define MBR_CMD_LOMIN               "lomin"
#define MBR_CMD_LOMAX               "lomax"
#define MBR_CMD_LOSTEP              "lostep"
#define MBR_CMD_LODWELL             "lodwell"
#define MBR_CMD_FPGARESET           "fpgareset"
#define MBR_CMD_FPGAPROG            "fpgaprog"
#define MBR_CMD_DASID               "dasid"
#define MBR_CMD_FPGA                "fpga"
#define MBR_CMD_DIAG                "diag"
#define MBR_CMD_OBS                 "obs"
#define MBR_CMD_ACQMODE_SNIFF       "sniff"
#define MBR_CMD_ACQMODE_SNIFFACQ    "sniffacq"
#define MBR_CMD_ACQMODE_OBS         "obs"
#define MBR_CMD_ACQMODE_CHECK       "check"
#define MBR_CMD_DATAMODE            "datamode"
#define MBR_CMD_BITPACKMODE         "bitpackmode"
#define MBR_CMD_BITPACK_4           "4"
#define MBR_CMD_BITPACK_8           "8"
#define MBR_CMD_GPS                 "fpgagps"
#define MBR_CMD_MASTER              "master"
#define MBR_CMD_SHUTDOWN            "shutdown"
#define MBR_CMD_REBOOT              "reboot"
#define MBR_CMD_RESET               "reset"
#define MBR_CMD_STOPDAS             "stopdas"
#define MBR_CMD_DATACHECK           "txcheck"
#define MBR_CMD_ACQUIRE             "acquire"
#define MBR_CMD_RFHIST              "rfhist"
#define MBR_CMD_HEADERINFO          "headerinfo"
#define MBR_CMD_RUN                 "run"
#define MBR_CMD_INIT                "init"
#define MBR_CMD_TIMESYNC            "timesync"
#define MBR_CMD_SOURCE              "source"
#define MBR_CMD_ACQDUR              "acqdur"
#define MBR_CMD_PKTOFFSET           "pktoffset"
#define MBR_CMD_ACQMODE             "acqmode"
#define MBR_CMD_ETHDEV              "ethdev"
#define MBR_CMD_SAMPCLKFREQ         "sampclkfreq"
#define MBR_CMD_SAMPCLKFREQ_66      "66"
#define MBR_CMD_SAMPCLKFREQ_62D5    "62.5"
#define MBR_CMD_TIMESTAMP           "timestamp"

/* mcd service commands - these commands are intended for use by the mcd */
#define MBR_CMD_FLUSHMSGQ           "mbrdo 0 flushmsgq"
#define MBR_CMD_MCD_FLUSHMSGQ       "mbrdo flushmsgq"

/* mcd non-service commands */
#define MBR_CMD_MCETHDEV            "mbrset mcethdev"

/* non-service commands that are used by the mcd */
#define MBR_CMD_MCSOURCE            "mbrset source"
#define MBR_CMD_MCACQDUR            "mbrset acqdur"
#define MBR_CMD_MCACQUIRE           "mbrdo acquire"

/* XML config file entities */
#define MBR_XML_ENT_SOURCE          "source"
#define MBR_XML_ENT_ACQUISITION     "acquisition"
#define MBR_XML_ENT_LO              "lo"
#define MBR_XML_ENT_ATTENUATOR      "attenuator"
#define MBR_XML_ENT_ATTENUATOR1     "attenuator1"
#define MBR_XML_ENT_ATTENUATOR2     "attenuator2"
#define MBR_XML_ENT_ATTENUATOR3     "attenuator3"
#define MBR_XML_ENT_ATTENUATOR4     "attenuator4"
#define MBR_XML_ENT_FPGA            "fpga"
#define MBR_XML_ENT_MASTER          "master"
#define MBR_XML_ENT_DAS             "das"

/* XML config file attributes */
#define MBR_XML_ATT_ID              "id"
#define MBR_XML_ATT_LIVE            "live"
#define MBR_XML_ATT_NAME            "name"
#define MBR_XML_ATT_STATUS          "status"
#define MBR_XML_ATT_DURATION        "acqdur"
#define MBR_XML_ATT_DATAMODE        "datamode"
#define MBR_XML_ATT_OFFSET          "pktoffset"
#define MBR_XML_ATT_DEVICE          "ethdev"
#define MBR_XML_ATT_FREQ            "freq"
#define MBR_XML_ATT_MIN             "min"
#define MBR_XML_ATT_MAX             "max"
#define MBR_XML_ATT_STEP            "step"
#define MBR_XML_ATT_DWELL           "dwell"
#define MBR_XML_ATT_VALUE           "value"
#define MBR_XML_ATT_ACQMODE         "acqmode"
#define MBR_XML_ATT_BITPACKMODE     "bitpackmode"
#define MBR_XML_ATT_SAMPCLKFREQ     "sampclkfreq"
#define MBR_XML_ATT_NODEID          "nodeid"

#define MBR_XML_LIVE_YES            "yes"
#define MBR_XML_LIVE_NO             "no"

/* executables and their input options */
#define MBR_EXE_SHUTDOWN        (char *) "shutdown"
#define MBR_EXE_REBOOT          (char *) "shutdown"
#define MBR_EXE_ACQUIRE         (char *) "mbracquire"
#define MBR_ACQARG_MCCFGFLAG    (char *) "-c"
#define MBR_ACQARG_MODEFLAG     (char *) "-m"
#define MBR_ACQARG_OFFSETFLAG   (char *) "-o"
#define MBR_ACQARG_DURFLAG      (char *) "-t"
#define MBR_ACQARG_DEVFLAG      (char *) "-d"
#define MBR_EXE_ACQSNIFF        (char *) "mbracqsniff"
#define MBR_EXE_DATE            (char *) "date"

/* command validation */
#define MBR_ARG_MIN                 3               /* mbrX <das-id> <action> */
#define MBR_DASID_MIN               0               /* 'all' */
#define MBR_DASID_MAX               MBR_MAX_DAS

/* run modes */
#define MBR_RUN_LOCAL               0               /* mcd and all dasds run on
                                                       the same machine -
                                                       for testing */
#define MBR_RUN_NETWORK             1               /* normal mode of
                                                       operation - mcd and dasds
                                                       run on different
                                                       machines */
#define MBR_RUN_MODE                MBR_RUN_NETWORK /* the chosen mode */

#define MBR_MSGQH_CMD               0x0010
#define MBR_MSGQH_RET_INFO          0x0020

#define MBR_MSGQH_MASK              0x000F

#define MBR_MSGTYPE_CMD             0
#define MBR_MSGTYPE_RET_INFO        1

/* NOTE: corresponds to a little more than the time taken for the command
   that takes the most time (~4 seconds) to run: 'mbrsetlocal attenuator' */
#define MBR_MSGQ_TIMEOUT            5               /* in seconds */
#define MBR_MSGQ_TIMEOUT_FLUSH      2               /* in seconds */

/* config file selection */
#define MBR_CFG_MC                  0               /* use mbr_mc.xml */
#define MBR_CFG_DAS                 1               /* use mbr_das.xml */

/* total size of user-configurable header */
#define MBR_SIZE_HEADERINFO         11              /* in bytes */

/* log pcMsg to the system log with level iLevel, if the program is running as a
   daemon */
#define MBR_SysLog(iLevel, pcMsg)   if (true == g_bDaemon) syslog(iLevel, pcMsg)

typedef enum tagFPGACmd
{
    MBR_FC_DATAMODE_DIAG = 0x41,
    MBR_FC_DATAMODE_OBS = 0x42,
    MBR_FC_BITPACKMODE_4 = 0x43,
    MBR_FC_BITPACKMODE_8 = 0x44,
    MBR_FC_ACQ_ON = 0x45,           /* pull ENABLE low */
    MBR_FC_ACQ_OFF = 0x46,          /* pull ENABLE high */
    MBR_FC_GPS_HIGH = 0x47,
    MBR_FC_GPS_LOW = 0x48,
    MBR_FC_TIMESTAMP_HIGH = 0x49,
    MBR_FC_TIMESTAMP_LOW = 0x50,
    MBR_FC_RFINFO_HIGH = 0x51,
    MBR_FC_RFINFO_LOW = 0x52,
    MBR_FC_HEADERINFO_HIGH = 0x53,
    MBR_FC_HEADERINFO_LOW = 0x54,
} MBR_FPGACMD;

/*
 * MBR_PACKET
 *
 * Packet information structure. The packet may contain either a command
 * or return info.
 */
typedef struct tagPacket
{
    int iInt;
#define Cmd_iDASID      iInt
#define RetInfo_iRet    iInt
    char acString[MBR_MAX_LEN_GENSTRING];
#define Cmd_acCommand   acString
#define RetInfo_acRet   acString
} MBR_PACKET;

#define MBR_CMD                     MBR_PACKET
#define MBR_RET_INFO                MBR_PACKET

/*
 * MBR_MSG
 *
 * Generic message queue message
 */
typedef struct tagMsg
{
    long lMsgType;
    MBR_PACKET stPacket;
} MBR_MSG;

/*
 * MBR_CONTROL
 *
 * Control information structure
 */
#pragma pack(push, 1)
typedef struct tagControl
{
    int iCmd;   /* usually contains control packet ID, but may also contain
                   information, such as timestamp */
    int iCmd2;  /* used if the 4 bytes provided by iCmd is not sufficient */
    int iCmd3;  /* used if the 8 bytes provided by iCmd and iCmd2 together, is
                   not sufficient */
} MBR_CONTROL;
#pragma pack(pop)

/*
 * CSocket
 *
 * Socket class
 */
class CSocket
{
    int m_iSocketFD;
    struct sockaddr_in m_stSocketAddr;

public:
    CSocket();
    CSocket(int iSocketFD);
    CSocket(int iSocketType,
            int iPort,
            int iDasID,
            int iRunMode = MBR_RUN_MODE);
    ~CSocket();

    CSocket* Accept(void);
    int Send(MBR_PACKET stPacket);
    int Send(MBR_CONTROL stControl);
    int Receive(MBR_PACKET *pstPacket);
};

/*
 * CMsgQ
 *
 * Message queue class
 */
class CMsgQ
{
    int m_iMsgQHandle;
    int m_iMsgQID;

public:
    CMsgQ();
    CMsgQ(int iCMsgQHandle);
    ~CMsgQ();

    int Push(MBR_MSG stMsg);
    MBR_MSG* Pop(int iMsgType, bool bIsFlushing);
    int Flush(void);
};

int MBR_Daemonise(int iDaemonID);
int MBR_OpenErrLog(bool bDASOwned);
int MBR_OpenTermFile(void);
void MBR_CloseTermFile(void);
int MBR_Command2Packet(int iDASID,
                       int iArgc,
                       char *apcArgv[],
                       MBR_PACKET *pstPacket);
int MBR_Packet2Command(MBR_PACKET stCommand, int *piArgc, char *apcArgv[]);
int MBR_FormCommand(char *apcOutArgv[], char *apcInArgv[], int iArgc);
int MBR_LookupHostName(int iDASID, char *pcHostName);
int MBR_UpdateRFHist(void);
int MBR_GetLastRFHistEntry(char *pcEntry);
char* MBR_GetTimestamp(void);
void MBR_Int2Bitmap(int iNum, char acBitmap[]);
int MBR_Bitmap2Int(const char* pcVal);
bool MBR_IsInteger(float fNum);

#endif  /* __MBR_COMMON_H__ */

