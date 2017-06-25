/*
 * mbr_dasd.cpp
 * The DAS daemon
 *
 * Usage: mbrdasd [options]
 *     -h  --help                 Display this usage information
 *     -n  --non-daemonise        Run the program in the console
 *     -p  --port                 Port ID on which to listen on, for commands
 *     (available only when compiled with MBR_RUN_MODE defined as MBR_RUN_LOCAL)
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
#include "mbr_dasd.h"
#include "mbr_get.h"
#include "mbr_serialport.h"

/* for getopt_long() and related stuff */
/* unlike what the man page for getopt_long() suggests, #define _GNU_SOURCE is
   not needed because the gcc compiler has the definition somewhere in one of
   its header files - and from the GNU mailing list, it seems to be the case
   that even the GCC developers are not sure what to do about it */
#include <getopt.h>

extern const char *g_pcVersion;
extern fstream g_ErrLog;
extern int MBR_Get(char *argv[]);

CSocket *g_pSocket = NULL;
CSocket *g_pNewSocket = NULL;
int g_iFlagRun = MBR_RUN_MODE;
bool g_bDaemon = true;

/*
 * main()
 *
 * The entry point of the DAS daemon
 */
int main(int argc, char* argv[])
{
    struct sigaction stSigHandler = {{0}};
    char *apcCmdArgv[MBR_MAX_NUM_ARGS] = {0};
    MBR_PACKET stPacket = {0};
    MBR_RET_INFO stRetInfo = {0};
    int iCmdArgc = 0;
    int iPort = 0;
    int iRet = MBR_RET_SUCCESS;
    int i = 0;
    bool bPort = false;
    int iFlagBreak = false;
    char *pcProgName = NULL;
    int iNextOpt = 0;
    const char* const pcShortOpts = "hnp:v";/* valid short options */
    const struct option stLongOpts[] = {    /* valid long options */
        { "help",           0, NULL, 'h' },
        { "non-daemonise",  0, NULL, 'n' },
        { "port",           1, NULL, 'p' },
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

            case 'p':   /* -p or --port */
                /* set the port, if the run mode is MBR_RUN_LOCAL */
                if (MBR_RUN_LOCAL == g_iFlagRun)
                {
                    bPort = true;
                    iPort = atoi(optarg);
                }
                else
                {
                    cerr << "ERROR: Invalid option!" << endl;
                    return MBR_RET_ERROR;
                }
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

    if (MBR_RUN_NETWORK == g_iFlagRun)
    {
        if (optind < argc)
        {
            cerr << "ERROR: Invalid option!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else    /* MBR_RUN_LOCAL */
    {
        if ((optind + 1) < argc)    /* argc includes the port number */
        {
            cerr << "ERROR: Invalid option!" << endl;
            return MBR_RET_ERROR;
        }
        /* if the port number has not been given, exit */
        if (false == bPort)
        {
            cerr << "ERROR: Invalid option!" << endl;
            return MBR_RET_ERROR;
        }
    }

    /* assign the default port number for MBR_RUN_NETWORK mode, or
       validate the input port number for MBR_RUN_LOCAL mode */
    if (MBR_RUN_NETWORK == g_iFlagRun)
    {
        iPort = MBR_PORT_DAS;
    }
    else
    {
        if ((iPort < MBR_PORT_USEMIN) || (iPort > MBR_PORT_USEMAX))
        {
            cerr << "ERROR: Port number should be between " << MBR_PORT_USEMIN
                 << " and " << MBR_PORT_USEMAX << ", both inclusive!" << endl;
            return MBR_RET_ERROR;
        }
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
        iRet = MBR_Daemonise(MBR_DID_DASD);
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Daemonise() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Daemonising process failed!" << endl;
            MBR_SysLog(LOG_ERR, "Exiting");
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
    /* to prevent any confusion, we will use stRetInfo.iRet here even though
       we will not be sending the return info as a reply */
    stRetInfo.RetInfo_iRet = sigaction(SIGINT, &stSigHandler, NULL);
    if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
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
    /* to prevent any confusion, we will use stRetInfo.iRet here even though
       we will not be sending the return info as a reply */
    stRetInfo.RetInfo_iRet = sigaction(SIGTERM, &stSigHandler, NULL);
    if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
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

    cout << "Setting up DAS...";
    fflush(stdout);

    /* to prevent any confusion, we will use stRetInfo.iRet here even though
       we will not be sending the return info as a reply */
    g_pSocket = new CSocket(MBR_SOCKTYPE_SERVER, iPort, MBR_ID_DEFAULTSERVER);
    if (NULL == g_pSocket)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::CSocket() failed"
                 << endl;
        cerr << " ERROR: Socket creation failed!" << endl;
        /* clean up */
        MBR_CloseTermFile();
        MBR_SysLog(LOG_ERR, "Exiting");
        return MBR_RET_ERROR;
    }
    cout << " DONE" << endl;

    g_pNewSocket = g_pSocket->Accept();
    if (NULL == g_pNewSocket)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::Accept() returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Accepting connection failed!" << endl;
        /* clean up */
        delete g_pSocket;
        MBR_CloseTermFile();
        MBR_SysLog(LOG_ERR, "Exiting");
        return MBR_RET_ERROR;
    }

    while (MBR_TRUE)
    {
        /* to prevent any confusion, we will use stRetInfo.iRet here even
           though we will not be sending the return info as a reply */
        stRetInfo.RetInfo_iRet = g_pNewSocket->Receive(&stPacket);
        if (MBR_RET_PEERSHUTDOWN == stRetInfo.RetInfo_iRet)
        {
            /* the M&C has shut down, so wait for it to come up by calling
               accept(), which will block until M&C comes up again */
            cout << "INFO: Peer has shut down!" << endl;

            delete g_pNewSocket;
            g_pNewSocket = NULL;

            g_pNewSocket = g_pSocket->Accept();
            if (NULL == g_pNewSocket)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Accept() returned "
                         << "NULL"
                         << endl;
                cerr << "ERROR: Accepting connection failed!" << endl;
                /* clean up */
                delete g_pSocket;
                MBR_CloseTermFile();
                MBR_SysLog(LOG_ERR, "Exiting");
                return MBR_RET_ERROR;
            }

            cout << "INFO: Peer has booted!" << endl;
            continue;
        }
        else if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CSocket::Receive() returned "
                     << stRetInfo.RetInfo_iRet
                     << endl;
            cerr << "ERROR: Receiving packet failed!" << endl;
            continue;
        }

        cout << "Received command '" << stPacket.Cmd_acCommand << "'" << endl;

        stRetInfo.RetInfo_iRet = MBR_Packet2Command(stPacket,
                                                    &iCmdArgc,
                                                    apcCmdArgv);
        if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Packet2Command() returned "
                     << stRetInfo.RetInfo_iRet
                     << endl;
            cerr << "ERROR: Packet to command conversion failed!" << endl;

            /* error, no point in proceeding, so reply with return info and
               continue reading */
            if (MBR_RET_ERROR == stRetInfo.RetInfo_iRet)
            {
                (void) strncpy(stRetInfo.RetInfo_acRet,
                               MBR_RETSTRING_INVALIDCMD,
                               MBR_MAX_LEN_GENSTRING);
            }
            else
            {
                (void) strncpy(stRetInfo.RetInfo_acRet,
                               strerror(stRetInfo.RetInfo_iRet),
                               MBR_MAX_LEN_GENSTRING);
            }
            /* stRetInfo.iRet is used here to prevent any confusion */
            stRetInfo.RetInfo_iRet = g_pNewSocket->Send(stRetInfo);
            if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                      << "CSocket::Send() returned "
                      << stRetInfo.RetInfo_iRet
                      << endl;
                cerr << "ERROR: Sending return info failed!" << endl;
            }
            continue;
        }

        stRetInfo = MBR_ProcessCommand(iCmdArgc, apcCmdArgv);
        if (0 == strcmp(MBR_CMD_GET, apcCmdArgv[0]))
        {
            if (MBR_RET_ERROR == stRetInfo.RetInfo_iRet)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_ProcessCommand() returned "
                         << stRetInfo.RetInfo_iRet
                         << endl;
                cerr << "ERROR: Command processing failed!" << endl;
                /* proceed to reply with the return info and continue reading */
            }
        }
        else
        {
            if (MBR_RET_CLEANUP == stRetInfo.RetInfo_iRet)
            {
                cout << "DAS daemon exiting" << endl;
                iFlagBreak = true;
                stRetInfo.RetInfo_iRet = MBR_RET_SUCCESS;
                (void) strncpy(stRetInfo.RetInfo_acRet,
                               strerror(stRetInfo.RetInfo_iRet),
                               (sizeof(stRetInfo.RetInfo_acRet) - 1));
            }
            else if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_ProcessCommand() returned "
                         << stRetInfo.RetInfo_iRet
                         << endl;
                cerr << "ERROR: Command processing failed!" << endl;
                /* proceed to reply with the return info and continue reading */
            }
        }

        /* stRetInfo.iRet is used here to prevent any confusion */
        stRetInfo.RetInfo_iRet = g_pNewSocket->Send(stRetInfo);
        if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CSocket::Send() returned "
                     << stRetInfo.RetInfo_iRet
                     << endl;
            cerr << "ERROR: Sending return info failed!" << endl;
        }

        /* clean up */
        for (i = 0; i < iCmdArgc; i++)
        {
            free(apcCmdArgv[i]);
        }

        if (iFlagBreak)
        {
            break;
        }
    }

    /* clean up */
    cout << "Cleaning up" << endl;
    delete g_pSocket;
    delete g_pNewSocket;
    g_ErrLog.close();
    MBR_CloseTermFile();

    MBR_SysLog(LOG_INFO, "Exiting");

    return MBR_RET_SUCCESS;
}

MBR_RET_INFO MBR_ProcessCommand(int argc, char *argv[])
{
    MBR_PACKET stTempPacket = {0};
    MBR_RET_INFO stRetInfo = {0};
    int iPID = 0;
    int iLength = 0;
    int iIndex = 0;
    char *pcArgv[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcCmd = NULL;

    if (0 == strcmp(argv[0], MBR_CMD_SET))
    {
        iLength = strlen(argv[0]);
        iLength += strlen(MBR_STRING_LOCAL);
        pcCmd = (char *) malloc(iLength + 1);
        if (NULL == pcCmd)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "malloc() failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Memory allocation failure!" << endl;
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(errno),
                           MBR_MAX_LEN_GENSTRING);
            stRetInfo.RetInfo_iRet = errno;
            return stRetInfo;
        }
        strcpy(pcCmd, argv[0]);
        strcat(pcCmd, MBR_STRING_LOCAL);
        pcArgv[iIndex] = pcCmd;
        ++iIndex;
        while (iIndex != argc)
        {
            pcArgv[iIndex] = argv[iIndex];
            ++iIndex;
        }
        pcArgv[iIndex] = (char *) '\0';

        stRetInfo.RetInfo_iRet = MBR_Command2Packet(iPID,
                                                    argc,
                                                    pcArgv,
                                                    &stTempPacket);
        if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Command2Packet() returned "
                     << stRetInfo.RetInfo_iRet
                     << endl;
            cerr << "ERROR: Command to packet conversion failed!" << endl;
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(errno),
                           MBR_MAX_LEN_GENSTRING);
            free(pcCmd);
            return stRetInfo;
        }
        free(pcCmd);

        stRetInfo.RetInfo_iRet = system(stTempPacket.Cmd_acCommand);
        if (MBR_RET_ERROR == stRetInfo.RetInfo_iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "system(" << stTempPacket.Cmd_acCommand << "failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Command execution failed!" << endl;
            /* fill the return info */
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           MBR_RETSTRING_INVALIDCMD,
                           MBR_MAX_LEN_GENSTRING);
            return stRetInfo;
        }
        if (!(WIFEXITED(stRetInfo.RetInfo_iRet)))
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "Command " << stTempPacket.Cmd_acCommand << " returned "
                     << WEXITSTATUS(stRetInfo.RetInfo_iRet)
                     << endl;
            cerr << "ERROR: Command failed!" << endl;
        }

        /* fill the return info */
        if (WEXITSTATUS(stRetInfo.RetInfo_iRet) != MBR_RET_SUCCESS)
        {
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           MBR_RETSTRING_ERROR,
                           MBR_MAX_LEN_GENSTRING);
        }
        else
        {
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(WEXITSTATUS(stRetInfo.RetInfo_iRet)),
                           MBR_MAX_LEN_GENSTRING);
        }
    }
    else if (0 == strcmp(argv[0], MBR_CMD_GET))
    {
        iLength = strlen(argv[0]);
        iLength += strlen(MBR_STRING_LOCAL);
        pcCmd = (char *) malloc(iLength + 1);
        if (NULL == pcCmd)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "malloc() failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Memory allocation failure!" << endl;
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(errno),
                           MBR_MAX_LEN_GENSTRING);
            stRetInfo.RetInfo_iRet = errno;
            return stRetInfo;
        }
        strcpy(pcCmd, argv[0]);
        strcat(pcCmd, MBR_STRING_LOCAL);
        pcArgv[iIndex] = pcCmd;
        ++iIndex;
        while (iIndex != argc)
        {
            pcArgv[iIndex] = argv[iIndex];
            ++iIndex;
        }
        pcArgv[iIndex] = (char *) '\0';

        stRetInfo.RetInfo_iRet = MBR_Command2Packet(iPID,
                                                    argc,
                                                    pcArgv,
                                                    &stTempPacket);
        if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Command2Packet() returned "
                     << stRetInfo.RetInfo_iRet
                     << endl;
            cerr << "ERROR: Command to packet conversion failed!" << endl;
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(errno),
                           MBR_MAX_LEN_GENSTRING);
            free(pcCmd);
            return stRetInfo;
        }
        free(pcCmd);

        /* NOTE: unlike the mbrset and mbrdo commands, the way an mbrget command
           is treated is different in that the latter involves a regular
           function call whereas the former involves a system() system call.
           this is done because the MBR_Get() function returns a value that can
           be higher than 2^8, which is the maximum value that can be obtained
           from an executable's return value to the operating system. so using
           system() or fork-execing the mbrgetlocal executable will not enable
           the recovery of the full return value of that program */
        stRetInfo.RetInfo_iRet = MBR_Get(pcArgv);
        if (MBR_RET_ERROR == stRetInfo.RetInfo_iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Get(" << pcArgv[1] << ") returned "
                     << stRetInfo.RetInfo_iRet
                     << endl;
            cerr << "ERROR: Command failed!" << endl;
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           MBR_RETSTRING_INVALIDCMD,
                           MBR_MAX_LEN_GENSTRING);
        }
        else
        {
            /* if the command was to get the source name, read the
               MBR_ENV_SOURCE environment variable to obtain the source name */
            if (0 == strcmp(pcArgv[1], MBR_CMD_SOURCE))
            {
                char *pcSource = NULL;

                pcSource = getenv(MBR_ENV_SOURCE);
                if (NULL == pcSource)
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "getenv("<< MBR_ENV_SOURCE << ") failed, "
                             << "errno set to " << errno << " with error: "
                             << strerror(errno)
                             << endl;
                    cerr << "ERROR: Getting environment variable failed!"
                         << endl;
                    stRetInfo.RetInfo_iRet = errno;
                    (void) strncpy(stRetInfo.RetInfo_acRet,
                                   strerror(errno),
                                   MBR_MAX_LEN_GENSTRING);
                    return stRetInfo;
                }

                stRetInfo.RetInfo_iRet = MBR_RET_SUCCESS;
                (void) strncpy(stRetInfo.RetInfo_acRet,
                               pcSource,
                               MBR_MAX_LEN_GENSTRING);
            }
        }
    }
    else if (0 == strcmp(argv[0], MBR_CMD_DO))
    {
        /* check if the user wants the DAS daemon to stop */
        if (argv[1] != NULL)
        {
            if (0 == strcmp(argv[1], MBR_CMD_STOPDAS))
            {
                stRetInfo.RetInfo_iRet = MBR_RET_CLEANUP;
                return stRetInfo;
            }
        }

        iLength = strlen(argv[0]);
        iLength += strlen(MBR_STRING_LOCAL);
        pcCmd = (char *) malloc(iLength + 1);
        if (NULL == pcCmd)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "malloc() failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Memory allocation failure!" << endl;
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(errno),
                           MBR_MAX_LEN_GENSTRING);
            stRetInfo.RetInfo_iRet = errno;
            return stRetInfo;
        }

        (void) strcpy(pcCmd, argv[0]);
        (void) strcat(pcCmd, MBR_STRING_LOCAL);

        pcArgv[iIndex] = pcCmd;
        ++iIndex;
        while (iIndex != argc)
        {
            pcArgv[iIndex] = argv[iIndex];
            ++iIndex;
        }
        pcArgv[iIndex] = (char *) '\0';

        stRetInfo.RetInfo_iRet = MBR_Command2Packet(iPID,
                                                    argc,
                                                    pcArgv,
                                                    &stTempPacket);
        if (stRetInfo.RetInfo_iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Command2Packet() returned "
                     << stRetInfo.RetInfo_iRet
                     << endl;
            cerr << "ERROR: Command to packet conversion failed!" << endl;
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(errno),
                           MBR_MAX_LEN_GENSTRING);
            free(pcCmd);
            return stRetInfo;
        }
        free(pcCmd);

        stRetInfo.RetInfo_iRet = system(stTempPacket.Cmd_acCommand);
        if (MBR_RET_ERROR == stRetInfo.RetInfo_iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "system(" << stTempPacket.Cmd_acCommand << "failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Command execution failed!" << endl;
            /* fill the return info */
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           MBR_RETSTRING_INVALIDCMD,
                           MBR_MAX_LEN_GENSTRING);
            return stRetInfo;
        }
        if (!(WIFEXITED(stRetInfo.RetInfo_iRet)))
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "Command " << stTempPacket.Cmd_acCommand << " returned "
                     << WEXITSTATUS(stRetInfo.RetInfo_iRet)
                     << endl;
            cerr << "ERROR: Command failed!" << endl;
        }

        /* fill the return info */
        if (WEXITSTATUS(stRetInfo.RetInfo_iRet) != MBR_RET_SUCCESS)
        {
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           MBR_RETSTRING_ERROR,
                           MBR_MAX_LEN_GENSTRING);
        }
        else
        {
            (void) strncpy(stRetInfo.RetInfo_acRet,
                           strerror(WEXITSTATUS(stRetInfo.RetInfo_iRet)),
                           MBR_MAX_LEN_GENSTRING);
        }
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        stRetInfo.RetInfo_iRet = MBR_RET_ERROR;
        (void) strncpy(stRetInfo.RetInfo_acRet,
                       MBR_RETSTRING_INVALIDCMD,
                       MBR_MAX_LEN_GENSTRING);
    }

    return stRetInfo;
}

void MBR_HandleStopSignals(int iSigNo)
{
    /* clean up */
    cout << "Cleaning up...";
    fflush(stdout);

    delete g_pSocket;
    delete g_pNewSocket;
    MBR_DevClose();
    g_ErrLog.close();
    MBR_CloseTermFile();
    cout << " DONE" << endl;

    MBR_SysLog(LOG_INFO, "Exiting");

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

void MBR_PrintUsage(const char *pcProgName)
{
    cout << "Usage: " << pcProgName << " [options]" << endl;
    cout << "    -h  --help                 Display this usage information"
         << endl;
    cout << "    -n  --non-daemonise        Run the program run in the console"
         << endl;

    if (MBR_RUN_LOCAL == g_iFlagRun)
    {
        cout << "    -p  --port                 Port ID on which to listen on,";
        cout << " for commands" << endl;
    }
    cout << "    -v  --version              Display the version"
         << endl;

    return;
}

