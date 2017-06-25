/*
 * mbr_common.cpp
 * Common functions for the GBT-RRI Multi-Band Receiver software
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#include "mbr_common.h"

char g_acTimestamp[MBR_LEN_TIMESTAMP+1] = {0};  /* the global timestamp string
                                                   used in error logging */
fstream g_ErrLog;                               /* the error log file */
int g_iTermFile = 0;

/*
 * int MBR_Daemonise(int iDaemonID)
 *
 * Sets up things to be taken care of, while making the calling process
 * a daemon
 */
int MBR_Daemonise(int iDaemonID)
{
    int iPID = 0;
    signed int iSID = 0;
    int iFD = 0;
    struct rlimit stResLimit = {0};
    int iRet = MBR_RET_SUCCESS;
    int i = 0;
    /* OPEN: check why the pidfile thingy is not working with the
       start-stop-daemon */
#if 0
    fstream PIDFile;
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
#endif

    /* daemons should run in the background, so fork a child process (which
       would be running in the background) and terminate the parent process */
    iPID = fork();
    if (iPID != 0)
    {
        /* this is the parent - exit */
        exit(0);
    }

    /* the daemon should be a process group leader, but this orphaned child
       process is not. so create a new session/process group and make this
       process the group leader */
    iSID = setsid();
    if ((pid_t) MBR_RET_ERROR == iSID)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "setsid() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Session creation failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* this process is now the process group leader, and can re-acquire
       a controlling terminal. so fork a child process and terminate. the child
       process, as it is not a process group leader, cannot acquire a
       controlling terminal */
    iPID = fork();
    if (iPID != 0)
    {
        /* this is the parent - exit */
        exit(0);
    }

    /* change the current directory to something that will not be unmounted */
    (void) chdir("/data/");

    /* set the file mode creation mask to 0 */
    (void) umask(0);    /* umask() never fails */

    /* get the number of open file descriptors, and close all of them */
    iRet = getrlimit(RLIMIT_NOFILE, &stResLimit);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getrlimit() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Getting resource limit failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* close the error log file */
    g_ErrLog.close();

    /* close all other open file descriptors */
    for (i = 0; (unsigned int) i < stResLimit.rlim_max; ++i)
    {
        (void) close(i);
    }

    /* open the null device, and duplicate it twice so that the standard file
       descriptors 0 (stdin), 1 (stdout), and 2 (stderr) point to it */
    iFD = open("/dev/null", O_RDWR);    /* stdin */

    iRet = MBR_OpenTermFile();
    if (MBR_RET_ERROR == iRet)
    {
        /* at this point, the error log file descriptor is no more, so no point
           in logging */
        return MBR_RET_ERROR;
    }

    /* OPEN: check why the pidfile thingy is not working with the
       start-stop-daemon */
#if 0
    /* get the process group ID, make it negative, and write it into the PID
       file (this will help the start-stop-dameon kill all the mbrmcd processes
       in one go, also works for mbrdasd) */
    /* form the path to the PID file */
    (void) strcpy(acPath, MBR_PATH_PIDFILEDIR);
    if (MBR_DID_MCD == iDaemonID)
    {
        (void) strcat(acPath, MBR_PIDFNAME_MCD);
    }
    else    /* MRB_DID_DASD */
    {
        (void) strcat(acPath, MBR_PIDFNAME_DASD);
    }

    /* open the PID file for writing */
    PIDFile.open(acPath, fstream::out);
    if (NULL == PIDFile)
    {
        cerr << "WARNING: Opening PID file " << acPath << " failed! "
             << "Daemon stopping may not happen cleanly!"
             << endl;
        return MBR_RET_WARNING;
    }

    /* get the process group ID/session ID, and make it negative */
    iSID = getsid(0);
    if ((pid_t) MBR_RET_ERROR == iSID)
    {
        cerr << "WARNING: Getting session ID failed! "
             << "Daemon stopping may not happen cleanly!"
             << endl;
        return MBR_RET_WARNING;
    }
    iSID = -iSID;

    /* write the negative process group ID to the PID file */
    PIDFile << iSID;

    PIDFile.close();
#endif

    return MBR_RET_SUCCESS;
}

/*
 * CSocket methods
 */

/*
 * CSocket::CSocket()
 *
 * Default constructor, for FPGA control
 */
CSocket::CSocket()
{
    int iRet = MBR_RET_SUCCESS;
    struct ifreq stIfReq = {{{0}}};

    m_iSocketFD = socket(PF_INET, SOCK_DGRAM, 0);
    if (MBR_RET_ERROR == m_iSocketFD)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "socket(" << m_iSocketFD << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "Error opening socket!" << endl;
    }

    (void) memset(&stIfReq, 0, sizeof(stIfReq));
    (void) strncpy(stIfReq.ifr_name, MBR_ETH_PRIMARY, sizeof(stIfReq.ifr_name));
    iRet = setsockopt(m_iSocketFD,
                      SOL_SOCKET,
                      SO_BINDTODEVICE,
                      (void *) &stIfReq,
                      sizeof(stIfReq));
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "setsockopt(" << m_iSocketFD << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "Error setting socket option!" << endl;
    }

    bzero((struct sockaddr_in *) &m_stSocketAddr, sizeof(m_stSocketAddr));
    m_stSocketAddr.sin_family = AF_INET;
    m_stSocketAddr.sin_port = htons(MBR_PORT_DSP);
    m_stSocketAddr.sin_addr.s_addr = inet_addr(MBR_IP_DSP);
    (void) memset(m_stSocketAddr.sin_zero,
                  '\0',
                  sizeof(m_stSocketAddr.sin_zero));
}

/*
 * CSocket::CSocket(int iSocketFD)
 *
 * Parameterised constructor, creates a socket
 */
CSocket::CSocket(int iSocketFD)
{
    m_iSocketFD = iSocketFD;
}

/*
 * CSocket::CSocket(int iSocketType, int iPort, int iDASID, int iRunMode)
 *
 * Parameterised constructor, creates a socket of the specified type
 */
CSocket::CSocket(int iSocketType,
                 int iPort,
                 int iDASID,
                 int iRunMode)  /*  = MBR_RUN_MODE */
{
    int iRet = MBR_RET_SUCCESS;
    int iOptVal = MBR_TRUE;
    /* OPEN: even though the variables are called 'hostname', IP addresses are
       used instead of host names. */
#if 0
    struct hostent *pstHostEntry = NULL;
#endif
    char *pcHostName = NULL;
    char acHostName[MBR_MAX_LEN_GENSTRING] = {0};

    m_iSocketFD = socket(PF_INET, SOCK_STREAM, 0);
    if (MBR_RET_ERROR == m_iSocketFD)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "socket(" << m_iSocketFD << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "Error opening socket!" << endl;
    }

    if (MBR_SOCKTYPE_SERVER == iSocketType)
    {
        /* MBR_SOCKTYPE_SERVER is used by the mcd parser and dasd */
        bzero((char *) &m_stSocketAddr, sizeof(m_stSocketAddr));
        m_stSocketAddr.sin_family = AF_INET;
        m_stSocketAddr.sin_addr.s_addr = INADDR_ANY;
        m_stSocketAddr.sin_port = htons(iPort);

        iRet = setsockopt(m_iSocketFD,
                          SOL_SOCKET,
                          SO_REUSEADDR,
                          &iOptVal,
                          sizeof(iOptVal));
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "setsockopt(" << m_iSocketFD << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Setting socket option failed!" << endl;
        }

        iRet = bind(m_iSocketFD,
                    (struct sockaddr*) &m_stSocketAddr,
                    sizeof(m_stSocketAddr));
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "bind(" << m_iSocketFD << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Binding to socket failed!" << endl;
        }

        iRet = listen(m_iSocketFD, MBR_LEN_BACKLOGQUEUE);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "listen(" << m_iSocketFD << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Listening on socket failed!" << endl;
        }
    }
    else if (MBR_SOCKTYPE_CLIENT == iSocketType)
    {
        /* MBR_SOCKTYPE_CLIENT is used by the mbr remote commands and
           the mcd dispatchers */
        if (MBR_RUN_NETWORK == iRunMode)
        {
            pcHostName = acHostName;
            iRet = MBR_LookupHostName(iDASID, pcHostName);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_LookupHostName(" << iDASID << ", "
                         << pcHostName << ") returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Looking up host name failed!" << endl;
            }

            /* OPEN: even though the variables are called 'hostname', IP
               addresses are used instead of host names. */
#if 0
            pstHostEntry = gethostbyname(pcHostName);
            if (NULL == pstHostEntry)
            {
                 g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                          << "gethostbyname(" << m_iSocketFD << ") failed, "
                          << "h_errno set to " << h_errno << " with error: "
                          << hstrerror(h_errno)
                          << endl;
                 cerr << "ERROR: Getting host entry failed!" << endl;
            }
#endif

            bzero((struct sockaddr_in *) &m_stSocketAddr,
                  sizeof(m_stSocketAddr));
            m_stSocketAddr.sin_family = AF_INET;
            m_stSocketAddr.sin_port = htons(iPort);
            /* OPEN: even though the variables are called 'hostname', IP
               addresses are used instead of host names. */
#if 0
            m_stSocketAddr.sin_addr = *((struct in_addr *)pstHostEntry->h_addr);
#endif
            /* OPEN: even though the variables are called 'hostname', IP
               addresses are used instead of host names. */
            m_stSocketAddr.sin_addr.s_addr = inet_addr(pcHostName);
            (void) memset(m_stSocketAddr.sin_zero,
                          '\0',
                          sizeof(m_stSocketAddr.sin_zero));
        }
        else    /* MBR_RUN_LOCAL */
        {
            bzero((struct sockaddr_in *) &m_stSocketAddr,
                  sizeof(m_stSocketAddr));
            m_stSocketAddr.sin_family = AF_INET;
            m_stSocketAddr.sin_addr.s_addr = INADDR_ANY;
            m_stSocketAddr.sin_port = htons(iPort);
            (void) memset(m_stSocketAddr.sin_zero,
                          '\0',
                          sizeof(m_stSocketAddr.sin_zero));
        }

        while (MBR_RET_ERROR == connect(m_iSocketFD,
                                        (struct sockaddr *) &m_stSocketAddr,
                                        sizeof(m_stSocketAddr)))
        {
            /* empty */
        }
    }
    else
    {
         g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                  << "Invalid socket type " << iSocketType
                  << endl;
         cerr << "ERROR: Invalid socket type!" << endl;
    }
}

/*
 * CSocket::~CSocket()
 *
 * Destructor, deletes the socket
 */
CSocket::~CSocket()
{
    int iRet;

    iRet = close(m_iSocketFD);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "close(" << m_iSocketFD << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Closing socket failed!" << endl;
    }
}

/*
 * CSocket* CSocket::Accept(void)
 *
 * Wrapper for the accept() function
 */
CSocket* CSocket::Accept(void)
{
    int iNewSocketFD = 0;
    int iSockAddrLen = 0;
    CSocket* pSocket = NULL;

    iSockAddrLen = sizeof(m_stSocketAddr);
    iNewSocketFD = accept(m_iSocketFD,
                          (struct sockaddr *) &m_stSocketAddr,
                          (socklen_t*) &iSockAddrLen);
    if (MBR_RET_ERROR == iNewSocketFD)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "accept(" << m_iSocketFD << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Accepting connection failed!" << endl;
        return NULL;
    }

    pSocket = new CSocket(iNewSocketFD);
    if (NULL == pSocket)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "CSocket::CSocket() failed"
                 << endl;
        cerr << "ERROR: Socket creation failed!" << endl;
        return NULL;
    }

    return pSocket;
}

/*
 * int CSocket::Send(MBR_PACKET stPacket)
 *
 * The send() function for MBR_PACKET data
 */
int CSocket::Send(MBR_PACKET stPacket)
{
    int iRet = MBR_RET_SUCCESS;

    /* OPEN: the parser crash problem - when the command sender is waiting for
       return info packets (<das-id> is 0) from the mcd (this happens when any
       DAS machine is down, and the mcd waits for the return infos until
       timeout), and a CTRL+C is given to it, the parser crashes - temporary
       solution in mbr_command.cpp, MBR_HandleStopSignals() */
    iRet = send(m_iSocketFD, &stPacket, sizeof(MBR_PACKET), 0);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "send(" << m_iSocketFD << ") failed for MBR_PACKET, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Sending packet failed!" << endl;
        return errno;
    }

    return MBR_RET_SUCCESS;
}

/*
 * int CSocket::Send(MBR_CONTROL stControl)
 *
 * The send() function for MBR_CONTROL data
 */
int CSocket::Send(MBR_CONTROL stControl)
{
    int iRet = MBR_RET_SUCCESS;

    iRet = sendto(m_iSocketFD,
                  &stControl,
                  sizeof(stControl),
                  0,
                  (struct sockaddr *) &m_stSocketAddr,
                  sizeof(m_stSocketAddr));
    if(MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "sendto(" << m_iSocketFD << ") failed for MBR_CONTROL, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Sending command failed!" << endl;
        return errno;
    }

    return MBR_RET_SUCCESS;
}

/*
 * int CSocket::Receive(MBR_PACKET *pstPacket)
 *
 * The recv() function for MBR_PACKET data
 */
int CSocket::Receive(MBR_PACKET *pstPacket)
{
    int iRet = MBR_RET_SUCCESS;

    iRet = recv(m_iSocketFD, pstPacket, sizeof(MBR_PACKET), 0);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "recv(" << m_iSocketFD << ") failed for MBR_PACKET, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Receiving packet failed!" << endl;
        return errno;
    }
    else if (0 == iRet)
    {
        /* if recv() returned 0, the peer must have shutdown */
        return MBR_RET_PEERSHUTDOWN;
    }

    return MBR_RET_SUCCESS;
}

/*
 * CMsgQ methods
 */

/*
 * CMsgQ::CMsgQ()
 *
 * Default constructor, should NOT be called
 */
CMsgQ::CMsgQ()
{
    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
             << "Default constructor for CMsgQ called"
             << endl;
    cerr << "ERROR: Default constructor for CMsgQ called!" << endl;
}

/*
 * CMsgQ::CMsgQ(int iMsgQHandle)
 *
 * Parameterised constructor, creates a message queue
 */
CMsgQ::CMsgQ(int iMsgQHandle)
{
    key_t Key = 0;

    m_iMsgQHandle = iMsgQHandle;

    Key = ftok(MBR_PATH_MSGQKEYFILE, m_iMsgQHandle);
    if ((key_t) MBR_RET_ERROR == Key)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "ftok(" << iMsgQHandle << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Message queue key generation failed!" << endl;
    }

    m_iMsgQID = msgget(Key, 0666 | IPC_CREAT);
    if (MBR_RET_ERROR == m_iMsgQID)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "msgget(" << m_iMsgQHandle << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Message queue creation failed!" << endl;
        throw MBR_RET_ERROR;
    }
}

/*
 * CMsgQ::~CMsgQ()
 *
 * Destructor, deletes the message queue
 */
CMsgQ::~CMsgQ()
{
    int iRet = 0;
    iRet = msgctl(m_iMsgQID, IPC_RMID, 0);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "msgctl(" << m_iMsgQHandle << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Message queue deletion failed!" << endl;
    }
}

/*
 * int CMsgQ::Push(MBR_PACKET stPacket)
 *
 * Sends the command contained within stPacket to the message queue
 */
int CMsgQ::Push(MBR_MSG stMsg)
{
    int iSize = 0;
    int iRet = MBR_RET_SUCCESS;

    iSize = sizeof(stMsg);

    iRet = msgsnd(m_iMsgQID, (const void *) &stMsg, iSize, 0);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "msgsnd(" << m_iMsgQHandle << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Sending command to message queue failed!" << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}

/*
 * MBR_MSG* CMsgQ::Pop(int iMsgType, bool bIsFlushing)
 *
 * Receives a message from the message queue
 */
MBR_MSG* CMsgQ::Pop(int iMsgType, bool bIsFlushing)
{
    int iSize = 0;
    int iRet = MBR_RET_SUCCESS;
    MBR_MSG *pstMsg = NULL;
#if 1
    struct timeval stTimeStart = {0};
    struct timeval stTimeStop = {0};
#else
    clock_t StartTick;
    clock_t StopTick;
#endif
    int iTimeout = 0;

    if (bIsFlushing)
    {
        /* use a shorter wait time if we're flushing the message queue */
        iTimeout = MBR_MSGQ_TIMEOUT_FLUSH;
    }
    else
    {
        iTimeout = MBR_MSGQ_TIMEOUT;
    }

    iSize = sizeof(MBR_MSG);

    pstMsg = (MBR_MSG *) malloc(iSize);
    if (NULL == pstMsg)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed for " << (m_iMsgQHandle & MBR_MSGQH_MASK)
                 << ", "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        /* clean up */
        return NULL;
    }

    if (MBR_MSGTYPE_CMD == iMsgType)
    {
        iRet = msgrcv(m_iMsgQID, pstMsg, iSize, 0, 0);
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "msgrcv(" << (m_iMsgQHandle & MBR_MSGQH_MASK)
                     << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Receiving from message queue failed!" << endl;
            free(pstMsg);
            return NULL;
        }
    }
    else    /* MBR_MSGTYPE_RET_INFO */
    {
#if 1
        (void) gettimeofday(&stTimeStart, NULL);
#else
        StartTick = clock();
#endif
        while (MBR_TRUE)
        {
            iRet = msgrcv(m_iMsgQID, pstMsg, iSize, 0, IPC_NOWAIT);
            if (MBR_RET_ERROR == iRet)
            {
                if (ENOMSG == errno)
                {
                    /* check time */
#if 1
                    (void) gettimeofday(&stTimeStop, NULL);
                    if ((stTimeStop.tv_sec - stTimeStart.tv_sec)
                        >= iTimeout)
#else
                    StopTick = clock();
                    if (((StopTick - StartTick) / CLOCKS_PER_SEC)
                        >= iTimeout)
#endif
                    {
                        if (!(bIsFlushing))
                        {
                            /* print warning if we're not flushing the message
                               queue */
                            cerr << "WARNING: Message queue reception timed out"
                                 << " for " << (m_iMsgQHandle & MBR_MSGQH_MASK)
                                 << "!"
                                 << endl;
                        }
                        /* fill in info about the timeout */
                        pstMsg->lMsgType = MBR_MSG_DEF_TYPE;
                        pstMsg->stPacket.iInt = -1;
                        (void) strncpy(pstMsg->stPacket.acString,
                                       MBR_RETSTRING_TIMEOUT,
                                       (sizeof(pstMsg->stPacket.acString) - 1));
                        return pstMsg;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                             << "msgrcv(" << (m_iMsgQHandle & MBR_MSGQH_MASK)
                             << ") failed, "
                             << "errno set to " << errno << " with error: "
                             << strerror(errno)
                             << endl;
                    cerr << "ERROR: Receiving from message queue failed!"
                         << endl;
                    free(pstMsg);
                    return NULL;
                }
            }

            break;
        }
    }

    return pstMsg;
}

/*
 * int CMsgQ::Flush()
 *
 * Flushes all messages from the message queue
 */
int CMsgQ::Flush(void)
{
    MBR_MSG *pstMsg = NULL;

    while (MBR_TRUE)
    {
        pstMsg = (MBR_MSG *) Pop(MBR_MSGTYPE_RET_INFO, true);
        if (NULL == pstMsg)
        {
            /* log and print error, but DON'T return, continue
               instead */
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "CMsgQ::Pop(" << (m_iMsgQHandle & MBR_MSGQH_MASK)
                     << ") returned "
                     << "NULL"
                     << endl;
            cerr << "ERROR: "
                 << "Popping return info from message queue failed!"
                 << endl;
            continue;
        }
        if (-1 == pstMsg->stPacket.iInt)
        {
            (void) free(pstMsg);
            break;
        }

        (void) free(pstMsg);
    }

    return MBR_RET_SUCCESS;
}

/*
 * Global functions
 */

/*
 * int MBR_OpenErrLog(bool bDASOwned)
 *
 * Opens the error log file ~/log/error.log
 */
int MBR_OpenErrLog(bool bDASOwned)
{
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    int iRet = MBR_RET_SUCCESS;

    /* get the environment variable HOME for opening the error log file */
    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        cerr << "ERROR: Environment variable HOME not defined!" << endl;
        return MBR_RET_ERROR;
    }

    /* form the path to the log file */
    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_PATH_ERRORLOG);

    /* open the log for writing */
    g_ErrLog.open(acPath, fstream::out | fstream::app);
    if (NULL == g_ErrLog)
    {
        cerr << "WARNING: Opening log file failed! Errors will not be logged!"
             << endl;
        return MBR_RET_WARNING;
    }

    if (bDASOwned)
    {
        /* give the ownership to user 'das' */
        iRet = chown(acPath, MBR_UID_DAS, MBR_GID_DAS);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "chown(" << acPath << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "WARNING: Changing ownership of log file failed! "
                 << "File may belong to a different user!"
                 << endl;
            return MBR_RET_WARNING;
        }
    }

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_OpenTermFile(void)
 *
 * Opens the terminal file ~/log/terminal. Used by the daemonised versions of
 * mbrmcd and mbrdasd.
 */
int MBR_OpenTermFile(void)
{
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    int iRet = MBR_RET_SUCCESS;

    /* get the environment variable HOME for opening the terminal file */
    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getenv(" << MBR_ENV_HOME << ") returned "
                 << "NULL"
                 << endl;
        return MBR_RET_ERROR;
    }

    /* form the path to the terminal file */
    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_PATH_TERMFILE);

    g_iTermFile = open(acPath,
                       (O_CREAT | O_EXCL | O_WRONLY),
                       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (MBR_RET_ERROR == g_iTermFile)
    {
        /* the file exists, so unlink it */
        /* NOTE: ensure that no other process (especially the terminal file
           poll-and-display program) has this file opened. if the file is not
           removed, it may lead to improper display */
        iRet = unlink(acPath);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "unlink(" << acPath << ") failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            return MBR_RET_ERROR;
        }
        /* else continue */
    }
    (void) close(g_iTermFile);

    /* open the terminal file for writing, this will have the
       file descriptor 1 (corresponding to stdout) */
    g_iTermFile = open(acPath,
                       (O_CREAT | O_WRONLY),
                       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (MBR_RET_ERROR == g_iTermFile)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "open(" << acPath << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        return MBR_RET_ERROR;
    }

    /* duplicate the file descriptor, so that 2 (stderr) also points to
       the same file */
    (void) dup(g_iTermFile);

    /* give the ownership to user 'das' */
    iRet = chown(acPath, MBR_UID_DAS, MBR_GID_DAS);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "chown(" << acPath << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "WARNING: Changing ownership of log file failed! "
             << "File may belong to a different user!"
             << endl;
        return MBR_RET_WARNING;
    }

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_CloseTermFile(void)
 *
 * Closes the terminal file ~/log/terminal. Used by the daemonised versions of
 * mbrmcd and mbrdasd.
 */
void MBR_CloseTermFile(void)
{
    (void) close(g_iTermFile);

    return;
}

/*
 * int MBR_Command2Packet(int iDASID,
 *                        int iArgc,
 *                        char *apcArgv[],
 *                        MBR_PACKET *pstPacket)
 *
 * Converts the provided command line arguments (a two-dimensional array)
 * into a string (a single-dimensional array)
 */
int MBR_Command2Packet(int iDASID,
                       int iArgc,
                       char *apcArgv[],
                       MBR_PACKET *pstPacket)
{
    int iLength = 0;
    int i = 0;

    pstPacket->Cmd_iDASID = iDASID;

    /* calculate the length of strings in the two-dimensional array */
    for (i = 0; i < iArgc; i++)
    {
        iLength += strlen(apcArgv[i]);
        iLength += 1;   /* for the space between words, and also for
                           the terminal NULL */
    }

    for (i = 0; i < iArgc; i++)
    {
        (void) strcat(pstPacket->Cmd_acCommand, apcArgv[i]);
        (void) strcat(pstPacket->Cmd_acCommand, " ");
    }

    /* set the last character to NULL */
    pstPacket->Cmd_acCommand[iLength-1] = '\0';

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_Packet2Command(MBR_PACKET stPacket, int *piArgc, char *apcArgv[])
 *
 * Converts the command string (a one-dimensional array) within the provided
 * stPacket into a two-dimensional array
 */
int MBR_Packet2Command(MBR_PACKET stCommand, int *piArgc, char *apcArgv[])
{
    char *pcWordStart = stCommand.Cmd_acCommand;
    char *pcWordEnd = NULL;
    int iLength = 0;
    int iBreak = MBR_FALSE;
    int i = 0;

    assert(piArgc != NULL);

    /* get the position of the first word ending */
    pcWordEnd = strchr(stCommand.Cmd_acCommand, ' ');
    if (NULL == pcWordEnd)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "strchr() failed to find ' '"
                 << endl;
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    /* reset the value of *piArgc, as the previous command would have
       changed it */
    *piArgc = 0;

    while (MBR_TRUE)
    {
        iLength = pcWordEnd - pcWordStart;
        /* allocate memory for the string - the caller is responsible for
           freeing it */
        apcArgv[*piArgc] = (char *) malloc(iLength + 1);
        if (NULL == apcArgv[*piArgc])
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "malloc() failed, "
                     << "errno set to " << errno << " with error: "
                     << strerror(errno)
                     << endl;
            cerr << "ERROR: Memory allocation failure!" << endl;
            /* clean up */
            for (i = 0; i < *piArgc; ++i)
            {
                free(apcArgv[i]);
            }
            return errno;
        }
        (void) strncpy(apcArgv[*piArgc], pcWordStart, iLength);
        apcArgv[*piArgc][iLength] = '\0';

        pcWordStart = pcWordEnd + 1;
        ++(*piArgc);

        /* check break condition */
        if (MBR_TRUE == iBreak)
        {
            break;
        }

        /* get the position of the next word ending */
        pcWordEnd = strchr(pcWordStart, ' ');
        if (NULL == pcWordEnd)
        {
            int iLen = 0;
            
            iLen = strlen(stCommand.Cmd_acCommand);

            pcWordEnd = &stCommand.Cmd_acCommand[iLen + 1];
            iBreak = MBR_TRUE;
        }
    }

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_LookupHostName(int iDASID, char *pcHostName)
 *
 * Looks up the host name of the specified DAS machine
 */
int MBR_LookupHostName(int iDASID, char *pcHostName)
{
    int iIndex = 0;
    int iCount = 0;
    int iDASIDEntry = 0;
    int iNum = 0;
    char acDasID[MBR_MAX_LEN_GENSTRING] = {0};
    char acName[MBR_MAX_LEN_GENSTRING] = {0};
    char acHostName[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    fstream LookUp;

    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getenv(" << MBR_ENV_HOME << ") returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Environment variable HOME not defined!" << endl;
        return MBR_RET_ERROR;
    }

    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_PATH_DASMAP);
    LookUp.open(acPath, fstream::in);
    if (NULL == LookUp)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "LookUp.open(" << acPath << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Opening file " << acPath << " failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* get the table header */
    LookUp.getline(acHostName, MBR_MAX_LEN_GENSTRING);
    while (!LookUp.eof())
    {
        LookUp.getline(acHostName, MBR_MAX_LEN_GENSTRING);
        iCount = 0;
        iNum = 0;
        iIndex = 0;
        while ((acHostName[iIndex] != ' ') && (acHostName[iIndex] != '\t'))
        {
           acDasID[iCount++] = acHostName[iIndex];
           iIndex++;
        }
        acDasID[iCount] = '\0' ;
        iDASIDEntry = atoi(acDasID);
        if (iDASID == iDASIDEntry)
        {
            while ((' ' == acHostName[iIndex]) || ('\t' == acHostName[iIndex]))
            {
               iIndex++;
            }
            while ((acHostName[iIndex] != ' ')
                   && (acHostName[iIndex] != '\t')
                   && (acHostName[iIndex] != '\0'))
            {
                acName[iNum++] = acHostName[iIndex];
                iIndex++;
            }
            acName[iNum] = '\0';
            strcpy(pcHostName, acName);

            return MBR_RET_SUCCESS;
        }
        acHostName[iIndex]='\n';
    }
    LookUp.close();

    /* if control comes here, the host name corresponding to the provided
       DAS ID has not been found, so return MBR_RET_ENTRYNOTFOUND */
    return MBR_RET_ENTRYNOTFOUND;
}

/*
 * int MBR_GetLastRFHistEntry(char *pcEntry)
 *
 * Gets the queried device's attributes from the RF settings
 * history file ~/log/rfhist
 */
int MBR_GetLastRFHistEntry(char *pcEntry)
{
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char acEntry[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    fstream RFHist;

    /* get the environment variable HOME for opening the error log file */
    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getenv($" << MBR_ENV_HOME << ") returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Environment variable HOME not defined!" << endl;
        return MBR_RET_ERROR;
    }

    /* form the path to the log file */
    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_PATH_RFHIST);

    /* open the log for reading */
    RFHist.open(acPath, fstream::in);
    if (NULL == RFHist)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "fstream::open(" << acPath << ") returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Opening RF history file failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* get the last line in the history file */
    do
    {
        (void) strcpy(pcEntry, acEntry);
        RFHist.getline(acEntry, MBR_MAX_LEN_GENSTRING);
    }
    while (false == RFHist.eof());

    RFHist.close();

    return MBR_RET_SUCCESS;
}

/*
 * char* MBR_GetTimestamp(void)
 *
 * Updates the value of g_acTimestamp to the current time
 */
char* MBR_GetTimestamp(void)
{
    time_t Time;
    struct tm *pstTime = NULL;

    Time = time(NULL);
    pstTime = localtime(&Time);

    (void) strftime(g_acTimestamp, sizeof(g_acTimestamp), "%F %T", pstTime);

    return g_acTimestamp;
}

/*
 * void MBR_Int2Bitmap(int iNum, char acBitmap[])
 *
 * Converts the given integer to a bitmap
 */
void MBR_Int2Bitmap(int iNum, char acBitmap[])
{
    int iIndex = 0;
    int iFlag = 0;
    char acTemp[MBR_MAX_LEN_GENSTRING] = {0};
    int i = 0;
    int j = 0;

    acTemp[iIndex] = '\0';
    ++iIndex;
    while (iNum > 0)
    {
        iFlag = iNum % 2;
        acTemp[iIndex] = iFlag + '0';
        iNum /= 2;
        ++iIndex;
    }

    for (i = 0, j = iIndex - 1; i < iIndex; ++i, --j)
    {
        acBitmap[i] = acTemp[j];
    }

    return;
}

/*
 * int MBR_Bitmap2Int(const char* pcVal)
 *
 * Converts the given bitmap to an integer
 */
int MBR_Bitmap2Int(const char* pcVal)
{
    int iIndex = 0;
    int iDigit = 0;
    int iRemainder = 0;
    int iFactor = 1;
    int iLength = 0;
    int iValue = 0;

    iLength = strlen(pcVal);
    iDigit = atoi(pcVal);
    while (iIndex < iLength)
    {
        iRemainder = iDigit % 10;
        iValue += iRemainder * iFactor;
        iIndex++;
        iDigit = iDigit / 10;
        iFactor *= 2;
    }

    return iValue;
}

/*
 * bool MBR_IsInteger(float fNum)
 *
 * Checks if the given floating-point number contains non-zero decimals
 */
bool MBR_IsInteger(float fNum)
{
    int iNum = (int) fNum;

    return (bool) (fNum == (float) iNum);
}

