/*
 * mbr_command.cpp
 * Command sending ('remote') and processing ('local') program
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#include "mbr_common.h"
#include "mbr_command.h"
#include "mbr_config.h"

#ifdef MBR_LOCAL
#ifdef MBR_SET
#include "mbr_set.h"
#elif MBR_GET
#include "mbr_get.h"
#elif MBR_DO
#include "mbr_do.h"
#endif  /* MBR_SET */
#endif  /* MBR_LOCAL */

extern const char *g_pcVersion;
extern fstream g_ErrLog;
extern char g_acTimestamp[MBR_LEN_TIMESTAMP+1];

#ifdef MBR_REMOTE
CSocket *g_pSocket = NULL;
bool g_abIsDASLive[MBR_MAX_DAS+1] = {false};
#endif

/*
 * main()
 *
 * The entry point of the command
 */
int main(int argc, char* argv[])
{
    int iRet = MBR_RET_SUCCESS;

    /* basic user input validation */
    if (!(argc > 1))
    {
        cerr << "ERROR: Invalid user input!" << endl;
        return MBR_RET_ERROR;
    }

    /* parse input options */
    if ((0 == strcmp(argv[1], MBR_ARG_HELPLONG))
        || (0 == strcmp(argv[1], MBR_ARG_HELPSHORT)))
    {
#ifdef MBR_SET
        MBR_PrintUsage(MBR_CMDTYPE_SET);
#elif MBR_GET
        MBR_PrintUsage(MBR_CMDTYPE_GET);
#elif MBR_DO
        MBR_PrintUsage(MBR_CMDTYPE_DO);
#endif
        return MBR_RET_SUCCESS;
    }
    else if ((0 == strcmp(argv[1], MBR_ARG_VERLONG))
        || (0 == strcmp(argv[1], MBR_ARG_VERSHORT)))
    {
        cout << g_pcVersion << endl;
        return MBR_RET_SUCCESS;
    }

    /* open the error log file */
    iRet = MBR_OpenErrLog(false);
    if (MBR_RET_ERROR == iRet)
    {
        cerr << "ERROR: Opening error log file failed!" << endl;
        return MBR_RET_ERROR;
    }

#ifdef MBR_REMOTE   /* code for the 'remote' program - mbrset/mbrget/mbrdo */
    struct sigaction stSigHandler = {{0}};
    char *apcArgv[MBR_MAX_LEN_GENSTRING] = {NULL};
    MBR_PACKET stPacket = {0};
    MBR_RET_INFO stRetInfo = {0};
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iDASID = 0;
    int iArgc = 0;
    float fAttn = 0.0;
    float fFrac = 0.0;
    time_t Time;
    struct tm *pstTime = NULL;
    int i = 0;

    if (argc < MBR_ARG_MIN)
    {
        cerr << "ERROR: Invalid user input!" << endl;
#ifdef MBR_SET
        MBR_PrintUsage(MBR_CMDTYPE_SET);
#elif MBR_GET
        MBR_PrintUsage(MBR_CMDTYPE_GET);
#elif MBR_DO
        MBR_PrintUsage(MBR_CMDTYPE_DO);
#endif
        return MBR_RET_ERROR;
    }

    /* check if the first character of the DAS ID string is a digit */
    if (!(isdigit(argv[1][0])))
    {
        cerr << "ERROR: Invalid user input!" << endl;
#ifdef MBR_SET
        MBR_PrintUsage(MBR_CMDTYPE_SET);
#elif MBR_GET
        MBR_PrintUsage(MBR_CMDTYPE_GET);
#elif MBR_DO
        MBR_PrintUsage(MBR_CMDTYPE_DO);
#endif
        return MBR_RET_ERROR;
    }

    /* get the DAS ID from the user input */
    iDASID = atoi(argv[1]);
    if ((iDASID < MBR_DASID_MIN) || (iDASID > MBR_DASID_MAX))
    {
        cerr << "ERROR: Invalid user input! DAS ID should be between "
             << MBR_DASID_MIN << " and " << MBR_DASID_MAX << "!"
             << endl;
#ifdef MBR_SET
        MBR_PrintUsage(MBR_CMDTYPE_SET);
#elif MBR_GET
        MBR_PrintUsage(MBR_CMDTYPE_GET);
#elif MBR_DO
        MBR_PrintUsage(MBR_CMDTYPE_DO);
#endif
        return MBR_RET_ERROR;
    }

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
        return MBR_RET_ERROR;
    }

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
                     << "MBR_ConfigEntry  returned "
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

    /* remove the DAS ID from the command string */
    iArgc = MBR_FormCommand(apcArgv, argv, argc);

    /* form the command packet that would be sent to the M&C daemon */
    iRet = MBR_Command2Packet(iDASID, iArgc, apcArgv, &stPacket);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Command2Packet() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Command to packet conversion failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* if the command is 'mbrdo timesync', get the local system time and append
       it to the command string */
    if (0 == strcmp(argv[2], MBR_CMD_TIMESYNC))
    {
        Time = time(NULL);
        pstTime = localtime(&Time);

        /* reusing the g_acTimestamp array */
        (void) strftime(g_acTimestamp,
                        sizeof(g_acTimestamp),
                        " %m%d%H%M.%S",
                        pstTime);

        (void) strcat(stPacket.Cmd_acCommand, g_acTimestamp);
    }

    /* if the command is 'mbrset mcethdev', cheat by replacing the user-supplied
       DAS ID with some non-zero value - this is done so that the command sender
       does not wait for ten return info packets */
    if (0 == strncmp(stPacket.Cmd_acCommand,
                     MBR_CMD_MCETHDEV,
                     strlen(MBR_CMD_MCETHDEV)))
    {
        iDASID = 1;
    }

    /* open a socket to send it across to the mcd */
    g_pSocket = new CSocket(MBR_SOCKTYPE_CLIENT,
                            MBR_PORT_MCDPARSER,
                            MBR_ID_MCDPARSER);
    if (NULL == g_pSocket)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::CSocket() returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Socket creation failed!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = g_pSocket->Send(stPacket);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::Send() returned  "
                 << iRet
                 << endl;
        cerr << "ERROR: Sending command failed!" << endl;
        /* clean up */
        delete g_pSocket;
        return MBR_RET_ERROR;
    }

    if (0 == iDASID)
    {
        for (i = 1; i <= MBR_MAX_DAS; ++i)
        {
            if (!(g_abIsDASLive[i]))
            {
                continue;
            }

            cout << "DAS " << i << ": ";
            iRet = g_pSocket->Receive(&stRetInfo);
            if (MBR_RET_PEERSHUTDOWN == iRet)
            {
                /* normally, this case would not happen in the case of commands
                        being received by the parser */
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Receive() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Peer has shut down!" << endl;
                /* clean up */
                delete g_pSocket;
                return MBR_RET_ERROR;
            }
            else if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "CSocket::Receive() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Receiving return info failed!" << endl;
                /* clean up */
                delete g_pSocket;
                return MBR_RET_ERROR;
            }

            if (0 == strcmp(apcArgv[0], MBR_CMD_GET))
            {
                if (MBR_RET_ERROR == stRetInfo.RetInfo_iRet)
                {
                    cout << stRetInfo.RetInfo_iRet
                         << ": "
                         << stRetInfo.RetInfo_acRet
                         << endl;
                }
                else
                {
                    if (0 == strcmp(argv[2], MBR_CMD_ATTENUATOR))
                    {
                        if (1 == (stRetInfo.RetInfo_iRet & MBR_MASK_ATTNFRAC))
                        {
                            fFrac = MBR_ATTN_FRAC;
                        }
                        else
                        {
                            fFrac = 0;
                        }

                        fAttn = (stRetInfo.RetInfo_iRet / MBR_ATTN_FACTOR)
                                + fFrac;
                        cout << fAttn << endl;
                    }
                    else if (0 == strcmp(argv[2], MBR_CMD_SAMPCLKFREQ))
                    {
                        if (1 == (stRetInfo.RetInfo_iRet & MBR_MASK_ATTNFRAC))
                        {
                            fFrac = MBR_ATTN_FRAC;
                        }
                        else
                        {
                            fFrac = 0;
                        }

                        fAttn = (stRetInfo.RetInfo_iRet >> 1) + fFrac;
                        cout << fAttn << endl;
                    }
                    else if ((0 == strcmp(argv[2], MBR_CMD_LOFREQ))
                             || (0 == strcmp(argv[2], MBR_CMD_BITPACKMODE))
                             || (0 == strcmp(argv[2], MBR_CMD_DASID))
                             || (0 == strcmp(argv[2], MBR_CMD_LOMAX))
                             || (0 == strcmp(argv[2], MBR_CMD_LOMIN))
                             || (0 == strcmp(argv[2], MBR_CMD_LOSTEP))
                             || (0 == strcmp(argv[2], MBR_CMD_LODWELL))
                             || (0 == strcmp(argv[2], MBR_CMD_SAMPCLKFREQ))
                             || (0 == strcmp(argv[2], MBR_CMD_PKTOFFSET))
                             || (0 == strcmp(argv[2], MBR_CMD_ACQDUR)))
                    {
                        cout << stRetInfo.RetInfo_iRet << endl;
                    }
                    else if (0 == strcmp(argv[2], MBR_CMD_ACQUISITION))
                    {
                        if (MBR_ACQSTATUS_ON == stRetInfo.RetInfo_iRet)
                        {
                            cout << MBR_CMD_ON << endl;
                        }
                        else
                        {
                            cout << MBR_CMD_OFF << endl;
                        }
                    }
                    else if (0 == strcmp(argv[2], MBR_CMD_ACQMODE))
                    {
                        if (MBR_ACQMODE_OBS == stRetInfo.RetInfo_iRet)
                        {
                            cout << MBR_CMD_ACQMODE_OBS << endl;
                        }
                        else if (MBR_ACQMODE_SNIFF == stRetInfo.RetInfo_iRet)
                        {
                            cout << MBR_CMD_ACQMODE_SNIFF << endl;
                        }
                        else if (MBR_ACQMODE_SNIFFACQ == stRetInfo.RetInfo_iRet)
                        {
                            cout << MBR_CMD_ACQMODE_SNIFFACQ << endl;
                        }
                        else if (MBR_ACQMODE_CHECK == stRetInfo.RetInfo_iRet)
                        {
                            cout << MBR_CMD_ACQMODE_CHECK << endl;
                        }
                    }
                    else if (0 == strcmp(argv[2], MBR_CMD_ETHDEV))
                    {
                        cout << MBR_PREFIX_ETHDEV
                             << stRetInfo.RetInfo_iRet
                             << endl;
                    }
                    else if (0 == strcmp(argv[2], MBR_CMD_DATAMODE))
                    {
                        if (MBR_DATAMODE_DIAG == stRetInfo.RetInfo_iRet)
                        {
                            cout << MBR_CMD_DIAG << endl;
                        }
                        else
                        {
                            cout << MBR_CMD_OBS << endl;
                        }
                    }
                    else if (0 == strcmp(argv[2], MBR_CMD_SOURCE))
                    {
                        cout << stRetInfo.RetInfo_acRet << endl;
                    }
                }
            }
            else
            {
                cout << stRetInfo.RetInfo_iRet
                     << ": "
                     << stRetInfo.RetInfo_acRet
                     << endl;
            }
        }
    }
    else
    {
        iRet = g_pSocket->Receive(&stRetInfo);
        if (MBR_RET_PEERSHUTDOWN == iRet)
        {
            /* normally, this case would not happen in the case of commands
                    being received by the parser */
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CSocket::Receive() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Peer has shut down!" << endl;
            /* clean up */
            delete g_pSocket;
            return MBR_RET_ERROR;
        }
        else if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CSocket::Receive() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Receiving return info failed!" << endl;
            /* clean up */
            delete g_pSocket;
            return MBR_RET_ERROR;
        }

        if (0 == strcmp(apcArgv[0], MBR_CMD_GET))
        {
            if (MBR_RET_ERROR == stRetInfo.RetInfo_iRet)
            {
                cout << stRetInfo.RetInfo_iRet
                     << ": "
                     << stRetInfo.RetInfo_acRet
                     << endl;
            }
            else
            {
                if ((0 == strcmp(argv[2], MBR_CMD_ATTENUATOR))
                    || (0 == strcmp(argv[2], MBR_CMD_SAMPCLKFREQ)))
                {
                    if (1 == (stRetInfo.RetInfo_iRet & MBR_MASK_ATTNFRAC))
                    {
                        fFrac = MBR_ATTN_FRAC;
                    }
                    else
                    {
                        fFrac = 0;
                    }

                    fAttn = (stRetInfo.RetInfo_iRet / MBR_ATTN_FACTOR) + fFrac;
                    cout << fAttn << endl;
                }
                else if (0 == strcmp(argv[2], MBR_CMD_SAMPCLKFREQ))
                {
                    if (1 == (stRetInfo.RetInfo_iRet & MBR_MASK_ATTNFRAC))
                    {
                        fFrac = MBR_ATTN_FRAC;
                    }
                    else
                    {
                        fFrac = 0;
                    }

                    fAttn = (stRetInfo.RetInfo_iRet >> 1) + fFrac;
                    cout << fAttn << endl;
                }
                else if ((0 == strcmp(argv[2], MBR_CMD_LOFREQ))
                         || (0 == strcmp(argv[2], MBR_CMD_BITPACKMODE))
                         || (0 == strcmp(argv[2], MBR_CMD_DASID))
                         || (0 == strcmp(argv[2], MBR_CMD_LOMAX))
                         || (0 == strcmp(argv[2], MBR_CMD_LOMIN))
                         || (0 == strcmp(argv[2], MBR_CMD_LOSTEP))
                         || (0 == strcmp(argv[2], MBR_CMD_LODWELL))
                         || (0 == strcmp(argv[2], MBR_CMD_SAMPCLKFREQ))
                         || (0 == strcmp(argv[2], MBR_CMD_PKTOFFSET))
                         || (0 == strcmp(argv[2], MBR_CMD_ACQDUR)))
                {
                    cout << stRetInfo.RetInfo_iRet << endl;
                }
                else if (0 == strcmp(argv[2], MBR_CMD_ACQUISITION))
                {
                    if (MBR_ACQSTATUS_ON == stRetInfo.RetInfo_iRet)
                    {
                        cout << MBR_CMD_ON << endl;
                    }
                    else
                    {
                        cout << MBR_CMD_OFF << endl;
                    }
                }
                else if (0 == strcmp(argv[2], MBR_CMD_ACQMODE))
                {
                    if (MBR_ACQMODE_OBS == stRetInfo.RetInfo_iRet)
                    {
                        cout << MBR_CMD_ACQMODE_OBS << endl;
                    }
                    else if (MBR_ACQMODE_SNIFF == stRetInfo.RetInfo_iRet)
                    {
                        cout << MBR_CMD_ACQMODE_SNIFF << endl;
                    }
                    else if (MBR_ACQMODE_SNIFFACQ == stRetInfo.RetInfo_iRet)
                    {
                        cout << MBR_CMD_ACQMODE_SNIFFACQ << endl;
                    }
                    else if (MBR_ACQMODE_CHECK == stRetInfo.RetInfo_iRet)
                    {
                        cout << MBR_CMD_ACQMODE_CHECK << endl;
                    }
                }
                else if (0 == strcmp(argv[2], MBR_CMD_ETHDEV))
                {
                    cout << MBR_PREFIX_ETHDEV << stRetInfo.RetInfo_iRet << endl;
                }
                else if (0 == strcmp(argv[2], MBR_CMD_DATAMODE))
                {
                    if (MBR_DATAMODE_DIAG == stRetInfo.RetInfo_iRet)
                    {
                        cout << MBR_CMD_DIAG << endl;
                    }
                    else
                    {
                        cout << MBR_CMD_OBS << endl;
                    }
                }
                else if (0 == strcmp(argv[2], MBR_CMD_SOURCE))
                {
                    cout << stRetInfo.RetInfo_acRet << endl;
                }
            }
        }
        else
        {
            cout << stRetInfo.RetInfo_iRet << ": " << stRetInfo.RetInfo_acRet
                 << endl;
        }
    }

    /* clean up */
    delete g_pSocket;
#elif MBR_LOCAL     /* code for the 'local' program -
                       mbrsetlocal/mbrgetlocal/mbrdolocal */
#ifdef MBR_SET
    iRet = MBR_Set(argv);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Set() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: SET command failed!" << endl;
        return MBR_RET_ERROR_SYS;
    }
#elif MBR_GET
    iRet = MBR_Get(argv);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Get() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: GET command failed!" << endl;
        return MBR_RET_ERROR_SYS;
    }
#elif MBR_DO
    iRet = MBR_Do(argc, argv);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Do() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: DO command failed!" << endl;
        return MBR_RET_ERROR_SYS;
    }
    else if (MBR_RET_CLEANUP == iRet)
    {
        /* clean up */
        g_ErrLog.close();
        return MBR_RET_CLEANUP;
    }

#endif  /* MBR_SET */
#endif  /* MBR_LOCAL */

    /* clean up */
    g_ErrLog.close();

    return iRet;
}

#ifdef MBR_REMOTE
/*
 * int MBR_FormCommand(char *apcOutArgv[], char *apcInArgv[], int iArgc)
 *
 * Strips apcInArgv[] of the DAS ID, and stores the result in apcOutArgv[]
 */
int MBR_FormCommand(char *apcOutArgv[], char *apcInArgv[], int iArgc)
{
    int iIndex = 0;

    /* fill the first word of apcArgv with either 'mbrset', 'mbrget',
       or 'mbrdo'- this replacement is done here so that the dasd command
       processor does not have to worry about stripping the binary name from the
       path string. for example, the user may run the program as 'mbrset'
       or './mbrset' or '/home/das/bin/mbrset'. for all these inputs, this code
       sends only 'mbrset' to the mcd, to be eventually sent to the dasd. the
       responsibility of freeing the memory being allocated below lies with the
       caller */
#ifdef MBR_SET
    apcOutArgv[0] = (char *) malloc((sizeof(char) * strlen(MBR_CMD_SET)) + 1);
    if (NULL == apcOutArgv[0])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        return errno;
    }

    (void) strcpy(apcOutArgv[0], MBR_CMD_SET);
#elif MBR_GET
    apcOutArgv[0] = (char *) malloc((sizeof(char) * strlen(MBR_CMD_GET)) + 1);
    if (NULL == apcOutArgv[0])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        return errno;
    }

    (void) strcpy(apcOutArgv[0], MBR_CMD_GET);
#elif MBR_DO
    apcOutArgv[0] = (char *) malloc((sizeof(char) * strlen(MBR_CMD_DO)) + 1);
    if (NULL == apcOutArgv[0])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        return errno;
    }

    (void) strcpy(apcOutArgv[0], MBR_CMD_DO);
#endif  /* MBR_SET */

    /* increment the index, because the first word is now in the array */
    ++iIndex;

    /* copy the rest of the command, skipping apcInArgv[1], which is
       the DAS ID */
    while (apcInArgv[iIndex+1] != '\0')
    {
        apcOutArgv[iIndex] = apcInArgv[iIndex+1];
        ++iIndex;
    }

    apcOutArgv[iArgc-1] = '\0';

    return iIndex;
}

void MBR_HandleStopSignals(int iSigNo)
{
    /* OPEN: this is a temporary solution to the parser crash problem -
       when the command sender is waiting for return info packets
       (<das-id> is 0) from the mcd (this happens when any DAS machine is down,
       and the mcd waits for the return infos until timeout), and a CTRL+C is
       given to it, the parser crashes */
    (void) sleep(10);

    /* clean up */
    cout << "Cleaning up...";
    fflush(stdout);

    delete g_pSocket;
    g_ErrLog.close();
    cout << " DONE" << endl;

    exit(MBR_RET_SUCCESS);

    /* never reached */
    return;
}
#endif  /* MBR_REMOTE */

void MBR_PrintUsage(int iCmdType)
{
    printf("For usage information, refer the MBR man pages in ~/docs.\n");
}

