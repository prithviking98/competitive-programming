/*
 * mbr_mcd.cpp
 * The M&C daemon
 *
 * Usage: mbrmcd [options]
 *     -h  --help                 Display this usage information
 *     -n  --non-daemonise        Run the program in the console
 *     -v  --version              Display the version
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#include "mbr_common.h"
#include "mbr_mcd.h"
#include "mbr_config.h"

/* for getopt_long() and related stuff */
/* unlike what the man page for getopt_long() suggests, #define _GNU_SOURCE is
   not needed because the gcc compiler has the definition somewhere in one of
   its header files - and from the GNU mailing list, it seems to be the case
   that even the GCC developers are not sure what to do about it */
#include <getopt.h>

extern const char *g_pcVersion;
extern fstream g_ErrLog;

CMsgQ *g_apMsgQCmd[MBR_MAX_DAS+1] = {NULL};
CMsgQ *g_apMsgQRetInfo[MBR_MAX_DAS+1] = {NULL};
bool g_abIsDASLive[MBR_MAX_DAS+1] = {false};
CSocket *g_pSocketParser = NULL;
CSocket *g_pSocketDispatcher = NULL;
CSocket *g_pNewSocketParser = NULL;
int g_iParentPID = 0;
int g_iDispatcherID = 0;
bool g_bDaemon = true;

/*
 * main()
 *
 * The entry point of the M&C daemon
 */
int main(int argc, char* argv[])
{
    int iPID = 0;
    int iMsgQHandle = 1;
    int iPort = 0;
    int iRet = 0;
    int i = 0;
    MBR_CMD stCmd = {0};
    MBR_RET_INFO stRetInfo = {0};
    MBR_MSG stMsg = {0};
    MBR_MSG *pstMsg = NULL;
    struct sigaction stSigHandler = {{0}};
    int iFlagRun = MBR_RUN_MODE;
    char *pcProgName = NULL;
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iNextOpt = 0;
    const char* const pcShortOpts = "hnv";  /* valid short options */
    const struct option stLongOpts[] = {    /* valid long options */
        { "help",           0, NULL, 'h' },
        { "non-daemonise",  0, NULL, 'n' },
        { "version",        0, NULL, 'v' },
        { NULL,             0, NULL, 0   }
    };

    /* get the filename of the program from the argument list */
    pcProgName = argv[0];

    /* parse the input */
    do
    {
        iNextOpt = getopt_long(argc, argv, pcShortOpts, stLongOpts, NULL);
        switch (iNextOpt)
        {
            case 'h':   /* -h or --help */
                /* print usage info and terminate */
                MBR_PrintUsage(pcProgName);
                return MBR_RET_SUCCESS;

            case 'n':   /* -n or --non-daemonise */
                /* set the daemonise flag to false */
                g_bDaemon = false;
                break;

            case 'v':   /* -v or --version */
                cout << g_pcVersion << endl;
                return MBR_RET_SUCCESS;

            case '?':   /* user specified an invalid option */
                /* print usage info and terminate with error */
                cerr << "ERROR: Invalid option!" << endl;
                MBR_PrintUsage(pcProgName);
                return MBR_RET_ERROR;

            case -1:    /* done with options */
                break;

            default:    /* unexpected */
                assert(0);
        }
    } while (iNextOpt != -1);

    if (optind < argc)
    {
        cerr << "ERROR: Invalid option!" << endl;
        return MBR_RET_ERROR;
    }

    /* open the error log file - this file descriptor will be closed
       on daemonisation */
    iRet = MBR_OpenErrLog(true);
    if (MBR_RET_ERROR == iRet)
    {
        cerr << "ERROR: Opening error log file failed!" << endl;
        return MBR_RET_ERROR;
    }

    if (true == g_bDaemon)
    {
        /* daemonise mbrmcd */
        iRet = MBR_Daemonise(MBR_DID_MCD);
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Daemonise() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Daemonising process failed!" << endl;
            return MBR_RET_ERROR;
        }

        /* open the error log file - the daemonisation had closed the file
           descriptor */
        iRet = MBR_OpenErrLog(true);
        if (MBR_RET_ERROR == iRet)
        {
            cerr << "ERROR: Opening error log file failed!" << endl;
            /* clean up */
            MBR_CloseTermFile();
            MBR_SysLog(LOG_ERR, "Exiting");
            return MBR_RET_ERROR;
        }
    }

    MBR_SysLog(LOG_INFO, "Starting");

    /* register the CTRL+C-handling function */
    stSigHandler.sa_handler = MBR_HandleStopSignals;
    iRet = sigaction(SIGINT, &stSigHandler, NULL);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "sigaction(SIGINT) failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Signal handler registration failed!" << endl;
        /* clean up */
        MBR_CloseTermFile();
        MBR_SysLog(LOG_ERR, "Exiting");
        return MBR_RET_ERROR;
    }

    /* register the SIGTERM-handling function */
    stSigHandler.sa_handler = MBR_HandleStopSignals;
    iRet = sigaction(SIGTERM, &stSigHandler, NULL);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "sigaction(SIGTERM) failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Signal handler registration failed!" << endl;
        /* clean up */
        MBR_CloseTermFile();
        MBR_SysLog(LOG_ERR, "Exiting");
        return MBR_RET_ERROR;
    }

    /* store the pid of this process - the mbrmcd parent process - for
       use while handling signals */
    g_iParentPID = getpid();

    /* look up the M&C config file and update the DAS status array with
       'true' or 'false' */
    for (i = 1; i <= MBR_MAX_DAS; ++i)
    {
        iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                               MBR_CFG_MC,
                               MBR_XML_ENT_DAS,
                               MBR_XML_ATT_LIVE,
                               i,
                               acValue);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_ConfigEntry(" << MBR_XML_ATT_LIVE << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Configuration file read failed!" << endl;
            return iRet;
        }

        if (0 == strcmp(acValue, "yes"))
        {
            g_abIsDASLive[i] = true;
        }
    }

    cout << "Creating command message queues...";
    fflush(stdout);
    for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
    {
        if (!(g_abIsDASLive[iMsgQHandle]))
        {
            continue;
        }

        try
        {
            g_apMsgQCmd[iMsgQHandle] = new CMsgQ(MBR_MSGQH_CMD | iMsgQHandle);
        }
        catch (int iException)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CMsgQ::CMsgQ(" << iMsgQHandle << ") failed"
                     << endl;
            cerr << "ERROR: Message queue creation failed!" << endl;
            /* clean up */
            /* delete all message queues created so far */
            for (i = 1; i < iMsgQHandle; ++i)
            {
                if (!(g_abIsDASLive[i]))
                {
                    continue;
                }

                delete g_apMsgQCmd[i];
            }
            MBR_CloseTermFile();
            MBR_SysLog(LOG_ERR, "Exiting");
            return MBR_RET_ERROR;
        }
    }
    cout << " DONE" << endl;

    cout << "Creating return info message queues...";
    fflush(stdout);
    for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
    {
        if (!(g_abIsDASLive[iMsgQHandle]))
        {
            continue;
        }

        try
        {
            g_apMsgQRetInfo[iMsgQHandle] = new CMsgQ(MBR_MSGQH_RET_INFO
                                                     | iMsgQHandle);
        }
        catch (int iException)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CMsgQ::CMsgQ(" << iMsgQHandle << ") failed"
                     << endl;
            cerr << "ERROR: Message queue creation failed!" << endl;
            /* clean up */
            /* delete all message queues created so far */
            for (i = 1; i < iMsgQHandle; ++i)
            {
                if (!(g_abIsDASLive[i]))
                {
                    continue;
                }

                delete g_apMsgQRetInfo[i];
            }
            for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
            {
                if (!(g_abIsDASLive[iMsgQHandle]))
                {
                    continue;
                }

                delete g_apMsgQCmd[iMsgQHandle];
            }
            MBR_CloseTermFile();
            MBR_SysLog(LOG_ERR, "Exiting");
            return MBR_RET_ERROR;
        }
    }
    cout << " DONE" << endl;

    /* create the parser and dispatcher processes */
    iPID = fork();
    if (0 != iPID)  /* parent process - parser */
    {
        cout << "Setting up parser...";
        fflush(stdout);
        g_pSocketParser = new CSocket(MBR_SOCKTYPE_SERVER,
                                      MBR_PORT_MCDPARSER,
                                      MBR_ID_DEFAULTSERVER);
        if (NULL == g_pSocketParser)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CSocket::CSocket() returned "
                     << "NULL"
                     << endl;
            cerr << "ERROR: Socket creation failed!" << endl;
            /* clean up */
            for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
            {
                if (!(g_abIsDASLive[iMsgQHandle]))
                {
                    continue;
                }

                delete g_apMsgQCmd[iMsgQHandle];
            }
            for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
            {
                if (!(g_abIsDASLive[iMsgQHandle]))
                {
                    continue;
                }

                delete g_apMsgQRetInfo[iMsgQHandle];
            }
            MBR_CloseTermFile();
            MBR_SysLog(LOG_ERR, "Exiting");
            return MBR_RET_ERROR;
        }
        cout << " DONE" << endl;

        while (MBR_TRUE)
        {
            g_pNewSocketParser = g_pSocketParser->Accept();
            if (NULL == g_pNewSocketParser)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Accept() returned "
                         << "NULL"
                         << endl;
                cerr << "ERROR: Accepting connection failed!" << endl;
                /* clean up */
                delete g_pSocketParser;
                for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
                {
                    if (!(g_abIsDASLive[iMsgQHandle]))
                    {
                        continue;
                    }

                    delete g_apMsgQCmd[iMsgQHandle];
                }
                for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
                {
                    if (!(g_abIsDASLive[iMsgQHandle]))
                    {
                        continue;
                    }

                    delete g_apMsgQRetInfo[iMsgQHandle];
                }
                MBR_CloseTermFile();
                MBR_SysLog(LOG_ERR, "Exiting");
                return MBR_RET_ERROR;
            }

            iRet = g_pNewSocketParser->Receive(&stCmd);
            if (MBR_RET_PEERSHUTDOWN == iRet)
            {
                /* normally, this case would not happen in the case of commands
                   being received by the parser */
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Receive() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Peer shutdown detected by parser!" << endl;
                continue;
            }
            else if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Receive() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Receiving packet failed!" << endl;
                continue;
            }

            cout << "Received command '" << stCmd.Cmd_acCommand
                 << "' for DAS ID " << stCmd.Cmd_iDASID << endl;

            /* check if this is an mcd service command - there is only one
               as of now */
            if (0 == strcmp(stCmd.Cmd_acCommand, MBR_CMD_MCD_FLUSHMSGQ))
            {
                if (0 == stCmd.Cmd_iDASID)
                {
                    /* flush the return info message queues */
                    for (iMsgQHandle = 1;
                         iMsgQHandle <= MBR_MAX_DAS;
                         ++iMsgQHandle)
                    {
                        if (!(g_abIsDASLive[iMsgQHandle]))
                        {
                            continue;
                        }

                        iRet = g_apMsgQRetInfo[iMsgQHandle]->Flush();
                        if (iRet != MBR_RET_SUCCESS)
                        {
                            /* log and print error, but DON'T return */
                            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                     << "CMsgQ::Flush(" << iMsgQHandle
                                     << ") returned "
                                     << iRet
                                     << endl;
                            cerr << "ERROR: "
                                 << "Flushing message queue failed!"
                                 << endl;
                            stRetInfo.RetInfo_iRet = MBR_RET_ERROR;
                            (void) strncpy(stRetInfo.RetInfo_acRet,
                                           MBR_RETSTRING_ERROR,
                                           MBR_MAX_LEN_GENSTRING);
                        }
                        else
                        {
                            stRetInfo.RetInfo_iRet = MBR_RET_SUCCESS;
                            (void) strncpy(stRetInfo.RetInfo_acRet,
                                           strerror(stRetInfo.RetInfo_iRet),
                                           MBR_MAX_LEN_GENSTRING);
                        }

                        iRet = g_pNewSocketParser->Send(stRetInfo);
                        if (iRet != MBR_RET_SUCCESS)
                        {
                            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                     << "CSocket::Send() returned "
                                     << iRet
                                     << endl;
                            cerr << "ERROR: Sending return info failed!"
                                 << endl;
                            /* log error but DON'T return */
                        }
                    }

                    cout << "Looks like message queues are flushed." << endl;
                }
                else
                {
                    /* if this DAS is not up, ignore this message */
                    if (!(g_abIsDASLive[stCmd.Cmd_iDASID]))
                    {
                        cerr << "WARNING: DAS is not up! Ignoring command!" << endl;

                        stRetInfo.RetInfo_iRet = MBR_RET_ERROR;
                        (void) strncpy(stRetInfo.RetInfo_acRet,
                                       MBR_RETSTRING_DASDOWN,
                                       MBR_MAX_LEN_GENSTRING);

                        iRet = g_pNewSocketParser->Send(stRetInfo);
                        if (iRet != MBR_RET_SUCCESS)
                        {
                            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                     << "CSocket::Send() returned "
                                     << iRet
                                     << endl;
                            cerr << "ERROR: Sending return info failed!" << endl;
                            continue;
                        }

                        continue;
                    }

                    iRet = g_apMsgQRetInfo[stCmd.Cmd_iDASID]->Flush();
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        /* log and print error, but DON'T return */
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "CMsgQ::Flush(" << stCmd.Cmd_iDASID
                                 << ") returned "
                                 << iRet
                                 << endl;
                        cerr << "ERROR: "
                             << "Flushing message queue failed!"
                             << endl;
                        stRetInfo.RetInfo_iRet = MBR_RET_ERROR;
                        (void) strncpy(stRetInfo.RetInfo_acRet,
                                       MBR_RETSTRING_ERROR,
                                       MBR_MAX_LEN_GENSTRING);
                    }
                    else
                    {
                        stRetInfo.RetInfo_iRet = MBR_RET_SUCCESS;
                        (void) strncpy(stRetInfo.RetInfo_acRet,
                                       strerror(stRetInfo.RetInfo_iRet),
                                       MBR_MAX_LEN_GENSTRING);
                    }

                    iRet = g_pNewSocketParser->Send(stRetInfo);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "CSocket::Send() returned "
                                 << iRet
                                 << endl;
                        cerr << "ERROR: Sending return info failed!"
                             << endl;
                        /* log error but DO NOT return */
                    }

                    cout << "Looks like message queue is flushed." << endl;
                }

                delete g_pNewSocketParser;
                g_pNewSocketParser = NULL;

                /* wait for the next command */
                continue;
            }
            /* this is not an mcd service command, but nevertheless one intended
               for the exclusive use of mcd */
            else if (0 == strncmp(stCmd.Cmd_acCommand,
                                  MBR_CMD_MCETHDEV,
                                  strlen(MBR_CMD_MCETHDEV)))
            {
                char *pcEthDev = NULL;

                /* extract the source name from the command */
                pcEthDev = stCmd.Cmd_acCommand
                           + strlen(MBR_CMD_MCETHDEV)
                           + 1;     /* including the trailing space
                                       in 'mbrset source ' */
                iRet = MBR_UpdateEthDev(pcEthDev);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "MBR_UpdateEthDev(" << pcEthDev
                             << ") returned "
                             << iRet
                             << endl;
                    cerr << "WARNING: Updating Ethernet device name failed!"
                         << endl;
                    stRetInfo.RetInfo_iRet = MBR_RET_ERROR;
                    (void) strncpy(stRetInfo.RetInfo_acRet,
                                   MBR_RETSTRING_ERROR,
                                   MBR_MAX_LEN_GENSTRING);
                }
                else
                {
                    stRetInfo.RetInfo_iRet = MBR_RET_SUCCESS;
                    (void) strncpy(stRetInfo.RetInfo_acRet,
                                   strerror(stRetInfo.RetInfo_iRet),
                                   MBR_MAX_LEN_GENSTRING);
                }

                iRet = g_pNewSocketParser->Send(stRetInfo);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "CSocket::Send() returned "
                             << iRet
                             << endl;
                    cerr << "ERROR: Sending return info failed!"
                         << endl;
                    /* log error but DO NOT return */
                }

                delete g_pNewSocketParser;
                g_pNewSocketParser = NULL;

                /* wait for the next command */
                continue;
            }
            /* these are das commands, but used by mcd */
            else
            {
                /* if this is not an mcd service command, and the command is
                   to set the source name, update the source name in the mc
                   config file too */
                if (0 == strncmp(stCmd.Cmd_acCommand,
                                 MBR_CMD_MCSOURCE,
                                 strlen(MBR_CMD_MCSOURCE)))
                {
                    char *pcSource = NULL;

                    /* extract the source name from the command */
                    pcSource = stCmd.Cmd_acCommand
                               + strlen(MBR_CMD_MCSOURCE)
                               + 1;     /* including the trailing space
                                           in 'mbrset source ' */
                    iRet = MBR_UpdateSourceName(pcSource);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "MBR_UpdateSourceName(" << pcSource
                                 << ") returned "
                                 << iRet
                                 << endl;
                        cerr << "WARNING: Updating source name failed!"
                             << endl;
                        /* log error but DO NOT return */
                    }
                }
                else if (0 == strncmp(stCmd.Cmd_acCommand,
                                      MBR_CMD_MCACQDUR,
                                      strlen(MBR_CMD_MCACQDUR)))
                {
                    char *pcAcqDur = NULL;

                    /* extract the source name from the command */
                    pcAcqDur = stCmd.Cmd_acCommand
                               + strlen(MBR_CMD_MCACQDUR)
                               + 1;     /* including the trailing space
                                           in 'mbrset source ' */
                    iRet = MBR_UpdateAcqDur(pcAcqDur);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "MBR_UpdateAcqDur(" << pcAcqDur
                                 << ") returned "
                                 << iRet
                                 << endl;
                        cerr << "WARNING: Updating acquisition duration failed!"
                             << endl;
                        /* log error but DO NOT return */
                    }
                }
                else if (0 == strncmp(stCmd.Cmd_acCommand,
                                      MBR_CMD_MCACQUIRE,
                                      strlen(MBR_CMD_MCACQUIRE)))
                {
                    iRet = MBR_RunAcquire();
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "MBR_RunAcquire() returned "
                                 << iRet
                                 << endl;
                        cerr << "WARNING: Running mbracquire failed!"
                             << endl
                             << "Please run mbracquire manually."
                             << endl;
                        /* log error but DO NOT return */
                    }
                }
            }

            /* encapsulate the received command in an MBR_MSG object, to be
               pushed into the message queue */
            stMsg.lMsgType = MBR_MSG_DEF_TYPE;
            stMsg.stPacket = stCmd;

            /* if DAS ID is 0, send the command to all DAS machines */
            if (0 == stCmd.Cmd_iDASID)
            {
                for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
                {
                    if (!(g_abIsDASLive[iMsgQHandle]))
                    {
                        continue;
                    }

                    iRet = g_apMsgQCmd[iMsgQHandle]->Push(stMsg);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        /* log and print error, but DON'T return */
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "CMsgQ::Push(" << iMsgQHandle
                                 << ") returned "
                                 << iRet
                                 << endl;
                        cerr << "ERROR: "
                             << "Pushing command to message queue failed!"
                             << endl;
                        continue;
                    }
                }

                for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
                {
                    if (!(g_abIsDASLive[iMsgQHandle]))
                    {
                        continue;
                    }

                    pstMsg = (MBR_MSG *) g_apMsgQRetInfo[iMsgQHandle]->Pop(
                                MBR_MSGTYPE_RET_INFO,
                                false);
                    if (NULL == pstMsg)
                    {
                        /* log and print error, but DON'T return, continue
                           instead */
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "CMsgQ::Pop(" << iMsgQHandle
                                 << ") returned "
                                 << "NULL"
                                 << endl;
                        cerr << "ERROR: "
                             << "Popping return info from message queue failed!"
                             << endl;
                        continue;
                    }

                    iRet = g_pNewSocketParser->Send(pstMsg->stPacket);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "CSocket::Send() returned "
                                 << iRet
                                 << endl;
                        cerr << "ERROR: Sending return info failed!" << endl;
                        (void) free(pstMsg);
                        continue;
                    }

                    (void) free(pstMsg);
                }
            }
            else    /* else, send it to the specified DAS machine */
            {
                /* if this DAS is not up, ignore this message */
                if (!(g_abIsDASLive[stCmd.Cmd_iDASID]))
                {
                    cerr << "WARNING: DAS is not up! Ignoring command!" << endl;

                    stRetInfo.RetInfo_iRet = MBR_RET_ERROR;
                    (void) strncpy(stRetInfo.RetInfo_acRet,
                                   MBR_RETSTRING_DASDOWN,
                                   MBR_MAX_LEN_GENSTRING);

                    iRet = g_pNewSocketParser->Send(stRetInfo);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "CSocket::Send() returned "
                                 << iRet
                                 << endl;
                        cerr << "ERROR: Sending return info failed!" << endl;
                        continue;
                    }

                    continue;
                }

                iRet = g_apMsgQCmd[stCmd.Cmd_iDASID]->Push(stMsg);
                if (iRet != MBR_RET_SUCCESS)
                {
                    /* log and print error, but DON'T return */
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "CMsgQ::Push(" << iMsgQHandle << ") returned "
                             << iRet
                             << endl;
                    cerr << "ERROR: Pushing command to message queue failed!"
                         << endl;
                    continue;
                }

                pstMsg = (MBR_MSG *) g_apMsgQRetInfo[stCmd.Cmd_iDASID]->Pop(
                            MBR_MSGTYPE_RET_INFO,
                            false);
                if (NULL == pstMsg)
                {
                    /* log and print error, but DON'T return, continue
                       instead */
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "CMsgQ::Pop(" << stCmd.Cmd_iDASID
                             << ") returned "
                             << "NULL"
                             << endl;
                    cerr << "ERROR: "
                         << "Popping return info from message queue failed!"
                         << endl;
                    continue;
                }

                iRet = g_pNewSocketParser->Send(pstMsg->stPacket);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "CSocket::Send() returned "
                             << iRet
                             << endl;
                    cerr << "ERROR: Sending return info failed!" << endl;
                    (void) free(pstMsg);
                    continue;
                }

                /* no more use for pstMsg */
                (void) free(pstMsg);
            }

            delete g_pNewSocketParser;
            g_pNewSocketParser = NULL;
        }
    }
    else    /* child process - dispatchers */
    {
        /* create MBR_MAX_DAS dispatchers */
        g_iDispatcherID = MBR_CreateDispatchers();

        /* the following executes for each dispatcher process. here, dispatcher
           id, das id, and message queue id are assumed to be the same */

        if (!((g_abIsDASLive[g_iDispatcherID])))
        {
            exit(MBR_RET_SUCCESS);
        }

        if (MBR_RUN_LOCAL == iFlagRun)
        {
            /* in the local run mode, ports start from MBR_PORT_DAS */
            iPort = (MBR_PORT_DAS - 1) + g_iDispatcherID;
        }
        else    /* MBR_RUN_NETWORK */
        {
            /* in the remote run, the port is fixed at MBR_PORT_DAS */
            iPort = MBR_PORT_DAS;
        }

        cout << "Setting up dispatcher " << g_iDispatcherID << "...";
        fflush(stdout);
        g_pSocketDispatcher = new CSocket(MBR_SOCKTYPE_CLIENT,
                                          iPort,
                                          g_iDispatcherID);
        if (NULL == g_pSocketDispatcher)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CSocket::CSocket() returned "
                     << "NULL"
                     << endl;
            cerr << "ERROR: Socket creation failed!" << endl;
            /* clean up */
            for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
            {
                if (!(g_abIsDASLive[iMsgQHandle]))
                {
                    continue;
                }

                delete g_apMsgQCmd[iMsgQHandle];
            }
            for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
            {
                if (!(g_abIsDASLive[iMsgQHandle]))
                {
                    continue;
                }

                delete g_apMsgQRetInfo[iMsgQHandle];
            }
            MBR_CloseTermFile();
            MBR_SysLog(LOG_ERR, "Exiting");
            return MBR_RET_ERROR;
        }
        cout << " DONE" << endl;

        while (MBR_TRUE)
        {
            pstMsg = (MBR_MSG *) g_apMsgQCmd[g_iDispatcherID]->Pop(
                        MBR_MSGTYPE_CMD,
                        false);
            if (NULL == pstMsg)
            {
                /* log and print error, but DON'T return, continue instead */
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CMsgQ::Pop(" << g_iDispatcherID << ") returned "
                         << "NULL"
                         << endl;
                cerr << "ERROR: Popping command from message queue failed!"
                     << endl;
                continue;
            }

            iRet = g_pSocketDispatcher->Send(pstMsg->stPacket);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Send() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Sending packet failed!" << endl;
                (void) free(pstMsg);
                continue;
            }

            iRet = g_pSocketDispatcher->Receive(&stRetInfo);
            if (MBR_RET_PEERSHUTDOWN == iRet)
            {
                /* the DAS has shut down, so try connecting */
                cout << "INFO: Peer " << g_iDispatcherID << " has shut down!"
                     << endl;

                delete g_pSocketDispatcher;
                g_pSocketDispatcher = new CSocket(MBR_SOCKTYPE_CLIENT,
                                                  iPort,
                                                  g_iDispatcherID);
                if (NULL == g_pSocketDispatcher)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "CSocket::CSocket() returned "
                             << "NULL"
                             << endl;
                    cerr << "ERROR: Socket creation failed!" << endl;
                    /* clean up */
                    (void) free(pstMsg);
                    for (iMsgQHandle = 1;
                         iMsgQHandle <= MBR_MAX_DAS;
                         ++iMsgQHandle)
                    {
                        if (!(g_abIsDASLive[iMsgQHandle]))
                        {
                            continue;
                        }

                        delete g_apMsgQCmd[iMsgQHandle];
                    }
                    for (iMsgQHandle = 1;
                         iMsgQHandle <= MBR_MAX_DAS;
                         ++iMsgQHandle)
                    {
                        if (!(g_abIsDASLive[iMsgQHandle]))
                        {
                            continue;
                        }

                        delete g_apMsgQRetInfo[iMsgQHandle];
                    }
                    MBR_CloseTermFile();
                    MBR_SysLog(LOG_ERR, "Exiting");
                    return MBR_RET_ERROR;
                }

                cout << "INFO: Peer " << g_iDispatcherID << " has booted!"
                     << endl;
                iRet = g_pSocketDispatcher->Send(pstMsg->stPacket);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "CSocket::Send() returned "
                             << iRet
                             << endl;
                    cerr << "ERROR: Sending packet failed!" << endl;
                    (void) free(pstMsg);
                    continue;
                }
                iRet = g_pSocketDispatcher->Receive(&stRetInfo);
                if (iRet != MBR_RET_SUCCESS)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "CSocket::Receive() returned "
                             << iRet
                             << endl;
                    cerr << "ERROR: Receiving return info failed!" << endl;
                    (void) free(pstMsg);
                    continue;
                }
            }
            else if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Receive() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Receiving return info failed!" << endl;
                (void) free(pstMsg);
                continue;
            }

            /* no more use for pstMsg */
            (void) free(pstMsg);

            /* encapsulate the received command in an MBR_MSG object, to be
               pushed into the message queue */
            stMsg.lMsgType = MBR_MSG_DEF_TYPE;
            stMsg.stPacket = stRetInfo;

            iRet = g_apMsgQRetInfo[g_iDispatcherID]->Push(stMsg);
            if (iRet != MBR_RET_SUCCESS)
            {
                      /* log and print error, but DON'T return */
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CMsgQ::Push(" << g_iDispatcherID
                         << ") returned "
                         << iRet
                         << endl;
                cerr << "ERROR: "
                     << " Pushing return info to message queue failed!"
                     << endl;
                continue;
            }

            cout << stRetInfo.RetInfo_iRet << endl;
        }
    }

    /* never reached, as the only way out is SIGTERM/SIGKILL */
    MBR_SysLog(LOG_INFO, "Exiting");

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_CreateDispatchers()
 *
 * Creates MBR_MAX_DAS child processes that play the role of dispatchers
 * Idea courtesy of Anand Avati
 */
int MBR_CreateDispatchers(void)
{
    int i = 0;
    int iPID = 0;

    for (i = 1; i <= MBR_MAX_DAS; ++i)
    {
        iPID = fork();
        if (0 == iPID)  /* child process */
        {
            /* child process returns here */
            return i;
        }
    }

    /* parent process terminates here, becoming a zombie */
    exit(MBR_RET_SUCCESS);

    /* never reached */
    return MBR_RET_SUCCESS;
}

/*
 * int MBR_UpdateSourceName(char *pcSource)
 *
 * Updates the source name in the config file
 */
int MBR_UpdateSourceName(char *pcSource)
{
    int iRet = MBR_RET_SUCCESS;

    if (NULL == pcSource)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Source name is NULL"
                 << endl;
        cerr << "ERROR: Source name not specified!" << endl;
        return MBR_RET_ERROR;
    }

    /* update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_MC,
                           MBR_XML_ENT_SOURCE,
                           MBR_XML_ATT_NAME,
                           0,
                           pcSource);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_XML_ENT_SOURCE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!"
             << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_UpdateAcqDur(char *pcAcqDur)
 *
 * Updates the duration of acquisition in the config file
 */
int MBR_UpdateAcqDur(char *pcAcqDur)
{
    int iRet = MBR_RET_SUCCESS;

    if (NULL == pcAcqDur)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Acquisition duration is NULL"
                 << endl;
        cerr << "ERROR: Duration of acquisition not specified!" << endl;
        return MBR_RET_ERROR;
    }

    /* update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_MC,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_DURATION,
                           0,
                           pcAcqDur);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_XML_ENT_ACQUISITION
                 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!"
             << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_UpdateEthDev(char *pcEthDev)
 *
 * Updates the duration of acquisition in the config file
 */
int MBR_UpdateEthDev(char *pcEthDev)
{
    int iRet = MBR_RET_SUCCESS;

    if (NULL == pcEthDev)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Ethernet device is NULL"
                 << endl;
        cerr << "ERROR: Ethernet device name not specified!" << endl;
        return MBR_RET_ERROR;
    }

    /* update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_MC,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_DEVICE,
                           0,
                           pcEthDev);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_XML_ENT_ACQUISITION
                 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!"
             << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_RunAcquire(void)
 *
 * Runs the mbracquire program to capture sniffed data
 */
int MBR_RunAcquire(void)
{
    int iRet = MBR_RET_SUCCESS;
    int iPID = 0;
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    char *apcCmdAcquire[MBR_ACQ_MAX_ARGS] = {NULL};
    int i = 0;

    /* build the apcCmdAcquire array based on the configured acquisition
       parameters */

    /* get the environment variable HOME for constructing the path to
       mbracquire */
    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        cerr << "ERROR: Environment variable HOME not defined!" << endl;
        return MBR_RET_ERROR;
    }

    /* form the path to mbracquire binary */
    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_PATH_BIN);
    (void) strcat(acPath, MBR_EXE_ACQUIRE);
    apcCmdAcquire[0] = (char *) malloc(sizeof(char) * (strlen(acPath) + 1));
    if (NULL == apcCmdAcquire[0])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        return errno;
    }
    (void) strcpy(apcCmdAcquire[0], acPath);

    /* copy the M&C config file flag, MBR_ACQARG_MCCFGFLAG */
    apcCmdAcquire[1] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_MCCFGFLAG) + 1));
    if (NULL == apcCmdAcquire[1])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        free(apcCmdAcquire[0]);
        return errno;
    }
    (void) strcpy(apcCmdAcquire[1], MBR_ACQARG_MCCFGFLAG);

    /* copy the mode flag, MBR_ACQARG_MODEFLAG */
    apcCmdAcquire[2] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_MODEFLAG) + 1));
    if (NULL == apcCmdAcquire[2])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 2; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    (void) strcpy(apcCmdAcquire[2], MBR_ACQARG_MODEFLAG);

    /* copy the mode, MBR_CMD_ACQMODE_OBS */
    apcCmdAcquire[3] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_CMD_ACQMODE_OBS) + 1));
    if (NULL == apcCmdAcquire[3])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 3; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    (void) strcpy(apcCmdAcquire[3], MBR_CMD_ACQMODE_OBS);

    /* copy the duration flag, MBR_ACQARG_DURFLAG */
    apcCmdAcquire[4] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_DURFLAG) + 1));
    if (NULL == apcCmdAcquire[4])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 4; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    (void) strcpy(apcCmdAcquire[4], MBR_ACQARG_DURFLAG);

    /* copy the duration */
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_MC,
                    MBR_XML_ENT_ACQUISITION,
                    MBR_XML_ATT_DURATION,
                    0,
                    acValue);
    apcCmdAcquire[5] = (char *) malloc(sizeof(char)
                                       * (strlen(acValue) + 1));
    if (NULL == apcCmdAcquire[5])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 5; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    (void) strcpy(apcCmdAcquire[5], acValue);

    /* copy the Ethernet device flag, MBR_ACQARG_DEVFLAG */
    apcCmdAcquire[6] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_DEVFLAG) + 1));
    if (NULL == apcCmdAcquire[6])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 6; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    (void) strcpy(apcCmdAcquire[6], MBR_ACQARG_DEVFLAG);

    /* copy the Ethernet device name */
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_MC,
                    MBR_XML_ENT_ACQUISITION,
                    MBR_XML_ATT_DEVICE,
                    0,
                    acValue);
    apcCmdAcquire[7] = (char *) malloc(sizeof(char)
                                       * (strlen(acValue) + 1));
    if (NULL == apcCmdAcquire[7])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 7; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    (void) strcpy(apcCmdAcquire[7], acValue);

    /* fork() twice, so that mbrmcd does not wait() */
    iPID = fork();
    if (0 == iPID)  /* child process */
    {
        iPID = fork();
        if (0 == iPID)  /* child process */
        {
            cout << "Running " << apcCmdAcquire[0] << endl;

            /* run mbracquire here */
            iRet = execvp(apcCmdAcquire[0], (char * const *) apcCmdAcquire);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "execvp(" << apcCmdAcquire[0] << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                cerr << "ERROR: Command execution failed!" << endl;
                /* clean up */
                for (i = 0; i < MBR_ACQ_MAX_ARGS; ++i)
                {
                    if (apcCmdAcquire[i] != NULL)
                    {
                        free(apcCmdAcquire[i]);
                    }
                }
                exit(MBR_RET_ERROR);
            }
        }
        else            /* parent process */
        {
            int iStatus = 0;

            cout << "Waiting on child " << iPID << endl;
            iRet = waitpid(iPID, &iStatus, 0);
            if (!(WIFEXITED(iStatus)))
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "wait() failed, with exit status "
                         << WEXITSTATUS(iStatus)
                         << ", "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                cerr << "ERROR: Waiting on child failed!" << endl;
                /* clean up */
                for (i = 0; i < MBR_ACQ_MAX_ARGS; ++i)
                {
                    if (apcCmdAcquire[i] != NULL)
                    {
                        free(apcCmdAcquire[i]);
                    }
                }
                exit(MBR_RET_ERROR);
            }
            cout << "Child " << iPID << " exited" << endl;

            exit(MBR_RET_SUCCESS);
        }
    }

    /* clean up */
    for (i = 0; i < MBR_ACQ_MAX_ARGS; ++i)
    {
        if (apcCmdAcquire[i] != NULL)
        {
            free(apcCmdAcquire[i]);
        }
    }

    /* this will run only on the parent */
    return MBR_RET_SUCCESS;
}

/*
 * void MBR_HandleStopSignals(int iSigNo)
 *
 * Catches signals that terminate mbrmcd and cleans up before exiting
 */
void MBR_HandleStopSignals(int iSigNo)
{
    int iMsgQHandle = 0;
    char acMsg[MBR_MAX_LEN_GENSTRING] = {0};

    /* clean up for the original parent process */
    if (getpid() == g_iParentPID)
    {
        /* we don't want the message to be printed in all processes, so print
           just here */
        cout << "Cleaning up...";
        fflush(stdout);

        delete g_pSocketParser;

        if (g_pNewSocketParser != NULL)
        {
            delete g_pNewSocketParser;
        }

        for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
        {
            if (!(g_abIsDASLive[iMsgQHandle]))
            {
                continue;
            }

            delete g_apMsgQCmd[iMsgQHandle];
        }

        for (iMsgQHandle = 1; iMsgQHandle <= MBR_MAX_DAS; ++iMsgQHandle)
        {
            if (!(g_abIsDASLive[iMsgQHandle]))
            {
                continue;
            }

            delete g_apMsgQRetInfo[iMsgQHandle];
        }
        g_ErrLog.close();
        cout << " DONE" << endl;

        (void) sprintf(acMsg, "Parser process %d exiting", g_iParentPID);
        MBR_SysLog(LOG_INFO, acMsg);
    }
    else
    {
        delete g_pSocketDispatcher;

        (void) sprintf(acMsg, "Dispatcher process %d exiting", getpid());
        MBR_SysLog(LOG_INFO, acMsg);
    }

    exit(MBR_RET_SUCCESS);

    /* never reached */
    return;
}

void MBR_HandleSIGCHLD(int iSigNo)
{
    int iStatus = 0;
    int iRet = 0;

    iRet = wait(&iStatus);
    if (!(WIFEXITED(iStatus)))
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "wait() failed, with exit status " << WEXITSTATUS(iStatus)
                 << ", "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "WARNING: Waiting on child failed!" << endl;
        return;
    }

    return;
}

/*
 * void MBR_PrintUsage(const char *pcProgName)
 *
 * Prints usage information
 */
void MBR_PrintUsage(const char *pcProgName)
{
    cout << "Usage: " << pcProgName << " [options]" << endl;
    cout << "    -h  --help                 Display this usage information"
         << endl;
    cout << "    -n  --non-daemonise        Run the program in the console"
         << endl;
    cout << "    -v  --version              Display the version"
         << endl;

    return;
}

