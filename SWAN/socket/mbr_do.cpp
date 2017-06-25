/*
 * mbr_do.cpp
 * DO commands
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Harshad Sahasrabudhe
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#include "mbr_common.h"
#include "mbr_set.h"
#include "mbr_do.h"
#include "mbr_serialport.h"
#include "mbr_config.h"

extern fstream g_ErrLog;

#ifdef MBR_LOCAL
#ifdef MBR_DO
int MBR_Do(int argc, char *argv[])
{
    int iRet = MBR_RET_SUCCESS;

    if (0 == strcmp(argv[1], MBR_CMD_SHUTDOWN))
    {
        iRet = MBR_DoShutdown();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DoShutdown() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Attempt to shut down failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_REBOOT))
    {
        iRet = MBR_DoReboot();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DoReboot() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Attempt to reboot failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_DATACHECK))
    {
        iRet = MBR_DoTxCheck();
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DoTxCheck() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Transmission check failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ACQUIRE))
    {
        iRet = MBR_DoAcquire();
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DoAcquire() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Data acquisition failed to commence!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_RUN))
    {
        iRet = MBR_DoRun(argc, argv);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DoRun(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Running command failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_TIMESYNC))
    {
        iRet = MBR_DoTimeSync(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DoTimeSync() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Time synchronisation failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_FPGARESET))
    {
        iRet = MBR_DoFPGAReset(argv[1]);
        if (iRet != MBR_RET_SUCCESS)
        {
             g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                      << "MBR_DoFPGAReset() returned "
                      << iRet
                      << endl;
             cerr << "ERROR: FPGA reset failed!" << endl;
             return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_FPGAPROG))
    {
        iRet = MBR_DoFPGAProg();
        if (iRet != MBR_RET_SUCCESS)
        {
           g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                    << "MBR_DoFPGAProg() returned "
                    << iRet
                    << endl;
           cerr << "ERROR: FPGA programming failed!" << endl;
           return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_GPS))
    {
        iRet = MBR_DoSimGPS();
        if (iRet != MBR_RET_SUCCESS)
        {
           g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                    << "MBR_DoSimGPS" << argv[2] << ") returned "
                    << iRet
                    << endl;
           cerr << "ERROR: FPGA GPS pulse simulation failed!" << endl;
           return iRet;
        }
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}

int MBR_DoFPGAReset(const char *pcReset)
{
    int iRet = MBR_RET_SUCCESS;

    /* download the value to hardware */
    iRet = MBR_Download(pcReset, NULL);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Download() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Hardware update failed!"<< endl;
        return iRet;
    }

    /* force sleep for 2 seconds */
    (void) sleep(2);

    return MBR_RET_SUCCESS;
}

int MBR_DoFPGAProg(void)
{
    int iRet = MBR_RET_SUCCESS;

    iRet = MBR_Download(MBR_CMD_FPGAPROG, NULL);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Download() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Hardware update failed!"<< endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_DoSimGPS(void)
{
    CSocket *pSocket = NULL;
    MBR_CONTROL stControl = {0};
    int iRet = MBR_RET_SUCCESS;

    pSocket = new CSocket();
    if (NULL == pSocket)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::CSocket() returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Socket creation failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* fill the stControl structure */
    stControl.iCmd = MBR_FC_GPS_HIGH;

    iRet = pSocket->Send(stControl);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::Send() returned  "
                 << iRet
                 << endl;
        cerr << "ERROR: Sending command failed!" << endl;
        /* clean up */
        delete pSocket;
        return MBR_RET_ERROR;
    }

    /* fill the stControl structure */
    stControl.iCmd = MBR_FC_GPS_LOW;

    iRet = pSocket->Send(stControl);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::Send() returned  "
                 << iRet
                 << endl;
        cerr << "ERROR: Sending command failed!" << endl;
        /* clean up */
        delete pSocket;
        return MBR_RET_ERROR;
    }

    /* clean up */
    delete pSocket;

    return MBR_RET_SUCCESS;
}

int MBR_DoShutdown(void)
{
    int iPID = 0;
    char *apcCommand[] = {MBR_EXE_SHUTDOWN,
                         (char *) "-h",
                         (char *) "0",
                          NULL};

    iPID = fork();
    if (0 == iPID)  /* child process */
    {
        (void) execvp(MBR_EXE_SHUTDOWN, apcCommand);
    }
    else            /* parent process */
    {
        return MBR_RET_CLEANUP;
    }

    return MBR_RET_SUCCESS;
}

int MBR_DoReboot(void)
{
    int iPID = 0;
    char *apcCommand[] = {MBR_EXE_REBOOT,
                         (char *) "-r",
                         (char *) "0",
                         NULL};

    iPID = fork();
    if (0 == iPID)  /* child process */
    {
        (void) execvp(MBR_EXE_REBOOT, apcCommand);
    }
    else            /* parent process */
    {
        return MBR_RET_CLEANUP;
    }

    return MBR_RET_SUCCESS;
}

int MBR_DoTxCheck(void)
{
    int iRet = MBR_RET_SUCCESS;
    int iPID = 0;
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    char *apcCmdAcquire[MBR_ACQ_MAX_ARGS] = {NULL};
    bool bIsChildKilled = false;
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

    apcCmdAcquire[1] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_MODEFLAG) + 1));
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
    (void) strcpy(apcCmdAcquire[1], MBR_ACQARG_MODEFLAG);

    apcCmdAcquire[2] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_CMD_ACQMODE_CHECK) + 1));
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
    (void) strcpy(apcCmdAcquire[2], MBR_CMD_ACQMODE_CHECK);

    /* fork() twice, so that mbrdolocal does not wait() and the system() call in
       the DAS daemon does not block */
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
            struct timeval stTimeStart = {0};
            struct timeval stTimeStop = {0};
            int iStatus = 0;

            (void) gettimeofday(&stTimeStart, NULL);

            /* wait for mbracquire to stop, if not, kill it */
            cout << "Waiting on child " << iPID << endl;
            while (MBR_TRUE)
            {
                iRet = waitpid(iPID, &iStatus, WNOHANG);
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
                if (0 == iRet)          /* child is still alive */
                {
                    (void) gettimeofday(&stTimeStop, NULL);
                    if ((stTimeStop.tv_sec - stTimeStart.tv_sec)
                        >= MBR_MSGQ_TIMEOUT)
                    {
                        iRet = kill(iPID, SIGTERM);
                        if (iRet != MBR_RET_SUCCESS)
                        {
                            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                     << "kill() failed, "
                                     << "errno set to " << errno
                                     << " with error: "
                                     << strerror(errno)
                                     << endl;
                            cerr << "ERROR: Killing child process failed!"
                                 << endl;
                            cerr << "Please kill " << apcCmdAcquire[0]
                                 << " manually." << endl;
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
                        bIsChildKilled = true;
                        break;
                    }
                }
                else if (iPID == iRet)  /* child has exited */
                {
                    break;
                }
                else                    /* wait failed */
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "waitpid(" << iPID << ") failed, "
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
            }

            cout << "Child " << iPID << " exited" << endl;
            /* NOTE: the message 'Transmission is ON' will not be displayed
               here, but by the mbracquire program, because, had it been here,
               a lock-file related error would also cause the message to be
               displayed */
            if (bIsChildKilled)
            {
                cout << "Transmission is OFF" << endl;
            }
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

    return MBR_RET_SUCCESS;
}

int MBR_DoAcquire(void)
{
    int iRet = MBR_RET_SUCCESS;
    int iPID = 0;
    bool bIsSniffMode = false;
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    char *apcCmdAcquire[MBR_ACQ_MAX_ARGS] = {NULL};
    int i = 0;

    /* update the RF history file with the values of the attenuators
       and the LO */
    iRet = MBR_UpdateRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_UpdateRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Updating RF history file failed!" << endl;
        return iRet;
    }

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

    /* copy the mode flag, MBR_ACQARG_MODEFLAG */
    apcCmdAcquire[1] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_MODEFLAG) + 1));
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
    (void) strcpy(apcCmdAcquire[1], MBR_ACQARG_MODEFLAG);

    /* copy the mode */
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ACQUISITION,
                    MBR_XML_ATT_ACQMODE,
                    0,
                    acValue);
    if ((0 == strcmp(acValue, MBR_CMD_ACQMODE_SNIFF))
        || (0 == strcmp(acValue, MBR_CMD_ACQMODE_SNIFFACQ)))
    {
        bIsSniffMode = true;
    }
    apcCmdAcquire[2] = (char *) malloc(sizeof(char)
                                       * (strlen(acValue) + 1));
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
    (void) strcpy(apcCmdAcquire[2], acValue);

    /* copy the offset flag, MBR_ACQARG_OFFSETFLAG */
    apcCmdAcquire[3] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_OFFSETFLAG) + 1));
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
    (void) strcpy(apcCmdAcquire[3], MBR_ACQARG_OFFSETFLAG);

    /* copy the offset */
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ACQUISITION,
                    MBR_XML_ATT_OFFSET,
                    0,
                    acValue);
    apcCmdAcquire[4] = (char *) malloc(sizeof(char)
                                       * (strlen(acValue) + 1));
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
    (void) strcpy(apcCmdAcquire[4], acValue);

    /* copy the duration flag, MBR_ACQARG_DURFLAG */
    apcCmdAcquire[5] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_DURFLAG) + 1));
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
    (void) strcpy(apcCmdAcquire[5], MBR_ACQARG_DURFLAG);

    /* copy the duration */
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ACQUISITION,
                    MBR_XML_ATT_DURATION,
                    0,
                    acValue);
    apcCmdAcquire[6] = (char *) malloc(sizeof(char)
                                       * (strlen(acValue) + 1));
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
    (void) strcpy(apcCmdAcquire[6], acValue);

    /* copy the Ethernet device flag, MBR_ACQARG_DEVFLAG */
    apcCmdAcquire[7] = (char *) malloc(sizeof(char)
                                       * (strlen(MBR_ACQARG_DEVFLAG) + 1));
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
    (void) strcpy(apcCmdAcquire[7], MBR_ACQARG_DEVFLAG);

    /* copy the Ethernet device name */
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ACQUISITION,
                    MBR_XML_ATT_DEVICE,
                    0,
                    acValue);
    apcCmdAcquire[8] = (char *) malloc(sizeof(char)
                                       * (strlen(acValue) + 1));
    if (NULL == apcCmdAcquire[8])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 8; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    (void) strcpy(apcCmdAcquire[8], acValue);

#if 0
    /* now that all arguments are copied, allocate once more for NULL */
    apcCmdAcquire[9] = (char *) malloc(sizeof(char));
    if (NULL == apcCmdAcquire[9])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < 9; ++i)
        {
            free(apcCmdAcquire[i]);
        }
        return errno;
    }
    apcCmdAcquire[9] = NULL;
#endif

    /* fork() twice, so that mbrdolocal does not wait() and the system() call in
       the DAS daemon does not block */
    iPID = fork();
    if (0 == iPID)  /* child process */
    {
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
        else            /* parent process */
        {
            if (bIsSniffMode)
            {
                iPID = fork();
                if (0 == iPID)  /* child process */
                {
                    char *apcCmdAcqSniff[MBR_ACQ_MAX_ARGS] = {NULL};

                    /* form the path to mbracqsniff binary */
                    (void) strcpy(acPath, pcPath);
                    (void) strcat(acPath, MBR_PATH_BIN);
                    (void) strcat(acPath, MBR_EXE_ACQSNIFF);
                    apcCmdAcqSniff[0] = (char *) malloc(sizeof(char) * (strlen(acPath) + 1));
                    if (NULL == apcCmdAcqSniff[0])
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "malloc() failed, "
                                 << "errno set to " << errno << " with error: "
                                 << strerror(errno)
                                 << endl;
                        cerr << "ERROR: Memory allocation failure!" << endl;
                        return errno;
                    }
                    (void) strcpy(apcCmdAcqSniff[0], acPath);

                    cout << "Running " << apcCmdAcqSniff[0] << endl;

                    /* run mbracqsniff here, if in sniff mode */
                    iRet = execvp(apcCmdAcqSniff[0], apcCmdAcqSniff);
                    if (iRet != MBR_RET_SUCCESS)
                    {
                        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                                 << "execvp(" << apcCmdAcqSniff[0]
                                 << ") failed, "
                                 << "errno set to " << errno << " with error: "
                                 << strerror(errno)
                                 << endl;
                        cerr << "ERROR: Command execution failed!" << endl;
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
                        exit(MBR_RET_ERROR);
                    }
                    cout << "Child " << iPID << " exited" << endl;

                    exit(MBR_RET_SUCCESS);
                }
            }
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

int MBR_DoRun(int iArgC, char *apcArgV[])
{
    int iPID = 0;
    int iRet = MBR_RET_SUCCESS;
    char *apcCommand[MBR_MAX_LEN_GENSTRING] = {NULL};
    int iLenCmd = 0;
    int i = 0;

    /* allocate memory for, and copy "/bin/bash" (or equivalent) and
       "-c" (or equivalent) */
    apcCommand[0] = (char *) malloc(sizeof(char) * (strlen(MBR_SHELL) + 1));
    if (NULL == apcCommand[0])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        return errno;
    }
    (void) strcpy(apcCommand[0], MBR_SHELL);
    apcCommand[1] = (char *) malloc(sizeof(char) * (strlen(MBR_SHELL_OPT) + 1));
    if (NULL == apcCommand[1])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        (void) free(apcCommand[0]);
        return errno;
    }
    (void) strcpy(apcCommand[1], MBR_SHELL_OPT);

    /* find the length of the command string that is to be run */
    for (i = 2; i < iArgC; ++i)
    {
        iLenCmd += strlen(apcArgV[i])
                   + 1; /* for the space character in between words, or the NULL
                           character at the end */
    }

    /* allocate memory for, and fill the third element in the apcCommand array
       with the command to be run */
    apcCommand[2] = (char *) calloc(iLenCmd, sizeof(char));
    if (NULL == apcCommand[2])
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
            free(apcCommand[i]);
        }
        return errno;
    }
    (void) strcpy(apcCommand[2], apcArgV[2]);
    for (i = 3; i < iArgC; ++i)
    {
        (void) strcat(apcCommand[2], " ");
        (void) strcat(apcCommand[2], apcArgV[i]);
    }
    (void) strcat(apcCommand[2], "\0");

    /* now that all relevant commands are copied, allocate once more for NULL */
    apcCommand[i] = (char *) malloc(sizeof(char));
    if (NULL == apcCommand[i])
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        for (i = 0; i < iArgC; ++i)
        {
            free(apcCommand[i]);
        }
        return errno;
    }
    apcCommand[i] = NULL;

    /* fork() twice, so that mbrdolocal does not wait() and the system() call in
       the DAS daemon does not block */
    iPID = fork();
    if (0 == iPID)  /* child process */
    {
        iPID = fork();
        if (0 == iPID)  /* child process */
        {
            iRet = execvp(apcCommand[0], apcCommand);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "execvp(" << apcCommand[0] << ") failed, "
                         << "errno set to " << errno << " with error: "
                         << strerror(errno)
                         << endl;
                cerr << "ERROR: Command execution failed!" << endl;
                /* clean up */
                for (i = 0; i < iArgC; ++i)
                {
                    free(apcCommand[i]);
                }
                return iRet;
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
                exit(MBR_RET_ERROR);
            }
            cout << "Child " << iPID << " exited" << endl;

            exit(MBR_RET_SUCCESS);
        }
    }

    /* this will run only on the parent */
    /* clean up */
    for (i = 0; i < iArgC; ++i)
    {
        free(apcCommand[i]);
    }

    return MBR_RET_SUCCESS;
}

int MBR_DoTimeSync(char *pcTime)
{
    char acCmdDate[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcTime)
    {
        cerr << "ERROR: Invalid user input!" << endl;
        return MBR_RET_ERROR;
    }

    (void) sprintf(acCmdDate, MBR_EXE_DATE " %s", pcTime);

    /* call the 'date' command with the user-given time */
    iRet = system(acCmdDate);
    if (!(WIFEXITED(iRet)))
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "system(" << acCmdDate << ") returned "
                 << WEXITSTATUS(iRet)
                 << endl;
        cerr << "ERROR: Time synchronisation failed!" << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}
#endif  /* MBR_DO */
#endif  /* MBR_LOCAL */

