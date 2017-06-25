/*
 * mbr_set.cpp
 * SET commands
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
#include "mbr_serialport.h"
#include "mbr_config.h"

extern fstream g_ErrLog;

#ifdef MBR_LOCAL
#ifdef MBR_SET
int MBR_Set(char *argv[])
{
    int iRet = MBR_RET_SUCCESS;

    if (0 == strcmp(argv[1], MBR_CMD_DASID))
    {
        iRet = MBR_SetDASID(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetDASID(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: DAS ID setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_SOURCE))
    {
        iRet = MBR_SetSource(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetSource(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Source name setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ETHDEV))
    {
        iRet = MBR_SetEthDev(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetEthDev(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Ethernet device setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ACQDUR))
    {
        iRet = MBR_SetAcqDur(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetAcqDur(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Acquisition duration setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ACQMODE))
    {
        iRet = MBR_SetAcqMode(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetAcqMode(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Mode setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_PKTOFFSET))
    {
        iRet = MBR_SetPktOffset(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetPktOffset(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Packet offset setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ACQUISITION))
    {
        if ((0 == strcmp(argv[2], MBR_STATUS_ON))
            || (0 == strcmp(argv[2], MBR_STATUS_OFF)))
        {
            iRet = MBR_SetAcq(argv[2]);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_SetAcq(" << argv[2] << ") returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Acquisition status setting failed!" << endl;
                return iRet;
            }
        }
        else
        {
            cerr << "ERROR: Invalid command!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ATTENUATOR))
    {
        if (NULL == argv[2])
        {
            /* the user has not given the attenuator ID and value, so set the
               last configured values for all attenuators */
            iRet = MBR_SetAttenuatorLastConf();
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_SetAttenuatorLastConf() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Setting attenuation values failed!" << endl;
                return iRet;
            }
        }
        else if ((argv[2] != NULL) && (argv[3] != NULL))
        {
            /* the user has given both the attenuator ID and value, so first
               validate the attenuator ID and then set the attenuation */
            iRet = MBR_ValidateAttenuatorSetting(argv[2], argv[3]);
            if (iRet != MBR_RET_SUCCESS)
            {
                cerr << "ERROR: Invalid command!" << endl;
                return iRet;
            }

            iRet = MBR_SetAttenuator(argv[2], argv[3]);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_SetAttenuator(" << argv[2] << ", " << argv[3]
                         << ") returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Setting attenuation failed!" << endl;
                return iRet;
            }
        }
        else
        {
            cerr << "ERROR: Invalid command!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOFREQ))
    {
        if (NULL == argv[2])
        {
            /* the user has not given the LO frequency, so set the last
               configured value for the oscillator */
            iRet = MBR_SetLOFreqLastConf();
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_SetLOLastConf() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: LO frequency setting failed!" << endl;
                return iRet;
            }
        }
        else
        {
            /* the user has given either the absolute LO frequency or the
               frequency increment/decrement */
            iRet = MBR_SetLOFreq(argv[2]);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_SetLOFreq(" << argv[2] << ") returned "
                         << iRet
                         << endl;
                cerr << "ERROR: LO frequency setting failed!" << endl;
                return iRet;
            }
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOMIN))
    {
        iRet = MBR_SetLOMin(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetLOMin(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: LO minimum setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOMAX))
    {
        iRet = MBR_SetLOMax(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetLOMax(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: LO maximum setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOSTEP))
    {
        iRet = MBR_SetLOStep(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetLOStep(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: LO step setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LODWELL))
    {
        iRet = MBR_SetLODwell(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetLODwell(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: LO dwell setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_DATAMODE))
    {
        iRet = MBR_SetDataMode(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetDataMode(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Acquisition mode setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_BITPACKMODE))
    {
        iRet = MBR_SetBitpackMode(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBitpackMode(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Bitpacking mode setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_SAMPCLKFREQ))
    {
        iRet = MBR_SetSampClkFreq(argv[2]);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetSampClkFreq(" << argv[2] << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Sampling clock frequency setting failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_RFHIST))
    {
        iRet = MBR_SetRFHist();
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetRFHist() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting RF history failed!" << endl;
            return iRet;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_TIMESTAMP))
    {
        iRet = MBR_SetTimestamp();
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetTimestamp() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting timestamp failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_HEADERINFO))
    {
        iRet = MBR_DownloadHeaderInfo();
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DownloadHeaderInfo() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Downloading the header info failed!" << endl;
            return iRet;
        }
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    cout << "DONE" << endl;

    return MBR_RET_SUCCESS;
}

int MBR_SetTimestamp(void)
{
    CSocket *pSocket = NULL;
    MBR_CONTROL stControl = {0};
    int iRet = MBR_RET_SUCCESS;
    time_t Time;
    struct tm *pstTime = NULL;
    int iSecSince12 = 0;

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

    /* read the number of seconds since 12 o' clock */
    Time = time(NULL);
    pstTime = localtime(&Time);
    iSecSince12 = (pstTime->tm_hour % 12) * 3600
                  + (pstTime->tm_min * 60)
                  + pstTime->tm_sec;
    cout << "Seconds since 12 o' clock: " << iSecSince12 << endl;

    /* fill the stControl structure, along with the number of seconds */
    stControl.iCmd = MBR_FC_TIMESTAMP_HIGH | (htons(iSecSince12) << 16);

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

    (void) sleep(1);

    /* fill the stControl structure */
    stControl.iCmd = MBR_FC_TIMESTAMP_LOW;

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

int MBR_SetDataMode(const char *pcDataMode)
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
    if (0 == strcmp(pcDataMode, MBR_CMD_DIAG))
    {
        stControl.iCmd = MBR_FC_DATAMODE_DIAG;
    }
    else if (0 == strcmp(pcDataMode, MBR_CMD_OBS))
    {
        stControl.iCmd = MBR_FC_DATAMODE_OBS;
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

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

    /* now that the information has been downloaded to the hardware,
       update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_FPGA,
                           MBR_XML_ATT_DATAMODE,
                           0,
                           (char *) pcDataMode);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "]"
                 << "MBR_ConfigEntry(" << MBR_CMD_DATAMODE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetBitpackMode(const char *pcBitpackMode)
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
    if (0 == strcmp(pcBitpackMode, MBR_CMD_BITPACK_4))
    {
        stControl.iCmd = MBR_FC_BITPACKMODE_4;
    }
    else if (0 == strcmp(pcBitpackMode, MBR_CMD_BITPACK_8))
    {
        stControl.iCmd = MBR_FC_BITPACKMODE_8;
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

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

    /* now that the information has been downloaded to the hardware,
       update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_FPGA,
                           MBR_XML_ATT_BITPACKMODE,
                           0,
                           (char *) pcBitpackMode);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "]"
                 << "MBR_ConfigEntry(" << MBR_CMD_BITPACKMODE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetSampClkFreq(const char *pcFreq)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if ((strcmp(pcFreq, MBR_CMD_SAMPCLKFREQ_66) != 0)
        && (strcmp(pcFreq, MBR_CMD_SAMPCLKFREQ_62D5) != 0))
    {
        cerr << "ERROR: Sampling clock frequency should be either of "
             << MBR_CMD_SAMPCLKFREQ_66 << " or "
             << MBR_CMD_SAMPCLKFREQ_62D5 << "!"
             << endl;
        return MBR_RET_ERROR;
    }

    /* update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_FPGA,
                           MBR_XML_ATT_SAMPCLKFREQ,
                           0,
                           (char *) pcFreq);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_SAMPCLKFREQ << ") returned "
                 << iRet
             << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetDASID(const char *pcDASID)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcDASID)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_DAS,
                           MBR_XML_ATT_ID,
                           0,
                           (char *) pcDASID);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_DASID << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetSource(const char *pcSource)
{
    int iLen = 0;
    char acSource[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcSource)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iLen = strlen(pcSource);
    if (iLen > MBR_SIZE_HEADERINFO)
    {
        cerr << "WARNING: Length of source name exceeds total size of "
             << "user-configurable header!"
             << endl
             << "Using only the first "
             << MBR_SIZE_HEADERINFO
             << " characters."
             << endl;
    }
    (void) strncpy(acSource, pcSource, MBR_SIZE_HEADERINFO);

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_SOURCE,
                           MBR_XML_ATT_NAME,
                           0,
                           (char *) acSource);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_SOURCE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    /* download the header info, including the recently-updated source name, to
       the FPGA board */
    iRet = MBR_DownloadHeaderInfo();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DownloadHeaderInfo() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Downloading header info failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetEthDev(const char *pcEthDev)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcEthDev)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_DEVICE,
                           0,
                           (char *) pcEthDev);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_ETHDEV << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetAcqMode(const char *pcAcqMode)
{
    int iRet = MBR_RET_SUCCESS;

    if ((0 != strcmp(pcAcqMode, MBR_CMD_ACQMODE_OBS))
        && (0 != strcmp(pcAcqMode, MBR_CMD_ACQMODE_SNIFF))
        && (0 != strcmp(pcAcqMode, MBR_CMD_ACQMODE_SNIFFACQ))
        && (0 != strcmp(pcAcqMode, MBR_CMD_ACQMODE_CHECK)))
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_ACQMODE,
                           0,
                           (char *) pcAcqMode);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_ACQMODE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetPktOffset(const char *pcOffset)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcOffset)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_OFFSET,
                           0,
                           (char *) pcOffset);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_PKTOFFSET << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetAcqDur(const char *pcDuration)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcDuration)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_DURATION,
                           0,
                           (char *) pcDuration);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_ACQDUR << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetLOFreq(const char *pcFreq)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iFreq = 0;
    int iFreqChange = 0;
    int iRet = MBR_RET_SUCCESS;

    /* if the LO frequency has been given by the user as an increment/decrement,
       calculate the new value */
    if (('+' == pcFreq[0]) || ('-' == pcFreq[0]))
    {
        /* read the LO frequency from the config file */
        iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                               MBR_CFG_DAS,
                               MBR_XML_ENT_LO,
                               MBR_XML_ATT_FREQ,
                               0,
                               acValue);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_ConfigEntry(" << MBR_CMD_LOFREQ << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Configuration file read failed!" << endl;
            return iRet;
        }

        iFreq = atoi(acValue);
        iFreqChange = atoi(pcFreq);
        iFreq = iFreq + iFreqChange;

        (void) sprintf(acValue, "%d", iFreq);
    }
    else
    {
        (void) strcpy(acValue, pcFreq);
    }

    /* download the value to hardware */
    iRet = MBR_Download(MBR_CMD_LOFREQ, acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Download() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Hardware update failed!" << endl;
        return iRet;
    }

    /* now that the information has been downloaded to the hardware,
       update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_FREQ,
                           0,
                           (char *) acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_LOFREQ << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    /* update the RF history */
    iRet = MBR_UpdateRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_UpdateRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Updating RF history failed!" << endl;
        return iRet;
    }

    /* download RF history to the FPGA board */
    iRet = MBR_DownloadRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DownloadRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Downloading RF history failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetLOFreqLastConf(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;

    /* read the LO frequency from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_FREQ,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_LOFREQ << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }

    cout << "New " << MBR_XML_ATT_FREQ << " of " << MBR_XML_ENT_LO << " is "
         << acValue
         << endl;

    /* download to hardware */
    iRet = MBR_Download(MBR_CMD_LOFREQ, acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Download() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Hardware update failed!" << endl;
        return iRet;
    }

    /* update the RF history */
    iRet = MBR_UpdateRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_UpdateRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Updating RF history failed!" << endl;
        return iRet;
    }

    /* download RF history to the FPGA board */
    iRet = MBR_DownloadRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DownloadRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Downloading RF history failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetLOMin(const char *pcFreq)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcFreq)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_MIN,
                           0,
                           (char *) pcFreq);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_LOMIN << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetLOMax(const char *pcFreq)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcFreq)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_MAX,
                           0,
                           (char *) pcFreq);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_LOMAX << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetLOStep(const char *pcFreq)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcFreq)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_STEP,
                           0,
                           (char *) pcFreq);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_LOSTEP << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetLODwell(const char *pcTime)
{
    int iRet = MBR_RET_SUCCESS;

    /* validate the input */
    if (NULL == pcTime)
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_DWELL,
                           0,
                           (char *) pcTime);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_LODWELL << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetAcq(const char *pcStatus)
{
    int iRet = MBR_RET_SUCCESS;
    CSocket *pSocket = NULL;
    MBR_CONTROL stControl = {0};

    if (0 == strcmp(pcStatus, MBR_CMD_ON))
    {
        /* download information that needs to be in the data header before switching
           acquisition on */

        /* download RF history to the FPGA board */
        iRet = MBR_DownloadRFHist();
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DownloadRFHist() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Downloading RF history failed!" << endl;
            return iRet;
        }

        /* download the header info, including the source name, to the FPGA board */
        iRet = MBR_DownloadHeaderInfo();
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_DownloadHeaderInfo() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Downloading header info failed!" << endl;
            return iRet;
        }

        /* give the FPGA board some time */
        (void) usleep(100000);
    }

    /* switch on acquisition */

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
    if (0 == strcmp(pcStatus, MBR_CMD_ON))
    {
        stControl.iCmd = MBR_FC_ACQ_ON;
    }
    else if (0 == strcmp(pcStatus, MBR_CMD_OFF))
    {
        stControl.iCmd = MBR_FC_ACQ_OFF;
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

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

    /* now that the information has been downloaded to the hardware,
       update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_STATUS,
                           0,
                           (char *) pcStatus);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(" << MBR_CMD_ACQUISITION << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    /* sleep for 3 seconds because acquisition status change happens at
       the GPS 1pps pulse */
    (void) sleep(3);

    return MBR_RET_SUCCESS;
}

int MBR_ValidateAttenuatorSetting(char *pcID, char *pcValue)
{
    float fVal = 0.0;

    /* ID validation */
    if ((strcmp(pcID, MBR_CMD_VRF) != 0)
        && (strcmp(pcID, MBR_CMD_VIF) != 0)
        && (strcmp(pcID, MBR_CMD_HRF) != 0)
        && (strcmp(pcID, MBR_CMD_HIF) != 0))
    {
        cerr << "ERROR: Attenuator ID should be one of "
             << MBR_CMD_VRF << ", "
             << MBR_CMD_VIF << ", "
             << MBR_CMD_HRF << ", "
             << MBR_CMD_HIF
             << endl;
        return MBR_RET_ERROR;
    }

    if (('+' == pcValue[0]) || ('-' == pcValue[0]))
    {
        return MBR_RET_SUCCESS;
    }

    /* check if the attenuation falls within the proper range */
    fVal = atof(pcValue);
    if (!(fVal >= 0) || !(fVal <= MBR_MAX_ATTENUATION))
    {
        cerr << "ERROR: Attenuation should be between 0 and "
             << MBR_MAX_ATTENUATION << "!" << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetAttenuator(const char *pcID, const char *pcValue)
{
    int iRet = MBR_RET_SUCCESS;
    char *pcConfigCmd = NULL;
    float fValue = 0.0;
    float fAttnChange = 0.0;
    int iValue = 0;
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    char acAttenuator[MBR_MAX_LEN_GENSTRING] = {0};
    char acID[2] = {0};

    if (0 == strcmp(pcID, MBR_CMD_VRF))
    {
        (void) strcpy(acID, "1");
    }
    else if (0 == strcmp(pcID, MBR_CMD_VIF))
    {
        (void) strcpy(acID, "2");
    }
    else if (0 == strcmp(pcID, MBR_CMD_HRF))
    {
        (void) strcpy(acID, "3");
    }
    else if (0 == strcmp(pcID, MBR_CMD_HIF))
    {
        (void) strcpy(acID, "4");
    }

    /* if the attenuation has been given by the user as an increment/decrement,
       calculate the new value */
    if (('+' == pcValue[0]) || ('-' == pcValue[0]))
    {
        (void) sprintf(acAttenuator, "%s%s", MBR_XML_ENT_ATTENUATOR, acID);
        /* read the attenuation from the config file */
        iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                               MBR_CFG_DAS,
                               acAttenuator,
                               MBR_XML_ATT_VALUE,
                               0,
                               acValue);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_ConfigEntry(" << MBR_CMD_ATTENUATOR << acID
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Configuration file read failed!" << endl;
            return iRet;
        }

        fValue = atof(acValue);
        fAttnChange = atof(pcValue);
        fValue = fValue + fAttnChange;
        if (!(fValue >= 0) || !(fValue <= MBR_MAX_ATTENUATION))
        {
            cerr << "ERROR: Attenuation should be between 0 and "
                 << MBR_MAX_ATTENUATION << "!" << endl;
            return MBR_RET_ERROR;
        }
        if (!(MBR_IsInteger(fValue)))
        {
            iValue = (int) fValue;
            fValue = fValue - iValue;
            if (fValue != MBR_ATTN_FRAC)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "Attempt to set attenuation to invalid value "
                         << pcValue
                         << endl;
                cerr << "ERROR: Setting attenuation failed!" << endl;
                return MBR_RET_ERROR;
            }
        }

        (void) sprintf(acValue, "%g", fValue);
    }
    else
    {
        fValue = atof(pcValue);
        if (!(MBR_IsInteger(fValue)))
        {
            iValue = (int) fValue;
            fValue = fValue - iValue;
            if (fValue != MBR_ATTN_FRAC)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "Attempt to set attenuation to invalid value "
                         << pcValue
                         << endl;
                cerr << "ERROR: Setting attenuation failed!" << endl;
                return MBR_RET_ERROR;
            }
        }
        (void) strcpy(acValue, pcValue);
    }

    pcConfigCmd = (char *) malloc(strlen(MBR_XML_ENT_ATTENUATOR)
                                  + strlen(acID)
                                  + 1);     /* for '\0' */
    if (NULL == pcConfigCmd)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        return errno;
    }
    (void) sprintf(pcConfigCmd,
                   MBR_XML_ENT_ATTENUATOR "%s",
                   acID);

    /* download to hardware */
    iRet = MBR_Download(pcConfigCmd, acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_Download() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Hardware update failed!" << endl;
        return iRet;
    }

    /* now that the information has been downloaded to the hardware,
       update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                           MBR_CFG_DAS,
                           pcConfigCmd,
                           MBR_XML_ATT_VALUE,
                           0,
                           (char *) acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry(attenuator" << pcID << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file update failed!" << endl;
        return iRet;
    }

    /* update the RF history */
    iRet = MBR_UpdateRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_UpdateRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Updating RF history failed!" << endl;
        return iRet;
    }

    /* download RF history to the FPGA board */
    iRet = MBR_DownloadRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DownloadRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Downloading RF history failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetAttenuatorLastConf(void)
{
    char acNode[MBR_MAX_LEN_GENSTRING] = {0};
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int i = 0;

    /* 'i' is initialised to 1, not 0 */
    for (i = 1; i <= MBR_MAX_DEV_ATTENUATORS; ++i)
    {
        /* generate the XML entity name */
        (void) sprintf(acNode, MBR_XML_ENT_ATTENUATOR "%d", i);

        /* read the attenuation from the config file */
        iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                               MBR_CFG_DAS,
                               acNode,
                               MBR_XML_ATT_VALUE,
                               0,
                               acValue);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_ConfigEntry(" << MBR_CMD_ATTENUATOR1
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Configuration file update failed!" << endl;
            return iRet;
        }

        cout << "New " << MBR_XML_ATT_VALUE << " of " << acNode << " is "
             << acValue
             << endl;

        /* download to hardware */
        iRet = MBR_Download(acNode, acValue);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_Download() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Hardware update failed!" << endl;
            return iRet;
        }
    }

    /* update the RF history */
    iRet = MBR_UpdateRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_UpdateRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Updating RF history failed!" << endl;
        return iRet;
    }

    /* download RF history to the FPGA board */
    iRet = MBR_DownloadRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DownloadRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Downloading RF history failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetRFHist(void)
{
    int iRet = MBR_RET_SUCCESS;

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

    /* download RF history to the FPGA board */
    iRet = MBR_DownloadRFHist();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DownloadRFHist() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Downloading RF history failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}
#endif  /* MBR_SET */

#if (MBR_SET || MBR_DO)
/*
 * int MBR_DownloadHeaderInfo(void)
 *
 * Downloads information, including the source name, to the FPGA board, for
 * use in the data packet header
 */
int MBR_DownloadHeaderInfo(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iLen = 0;
    int i = 0;
    int j = 0;
    int iByte = 0;
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

    /* build the packet */

    /* get the source name */
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_SOURCE,
                    MBR_XML_ATT_NAME,
                    0,
                    acValue);
    iLen = strlen(acValue);
    if (iLen > MBR_SIZE_HEADERINFO)
    {
        cerr << "ERROR: Length of source name exceeds total size of "
             << "user-configurable header!"
             << endl
             << "Using only the first "
             << MBR_SIZE_HEADERINFO
             << " characters."
             << endl;
        acValue[MBR_SIZE_HEADERINFO] = '\0';
    }

    /* fill the stControl structure */
    stControl.iCmd = MBR_FC_HEADERINFO_HIGH << 24;
    iByte = 0;
    for (i = 0, j = 16; i < iLen; ++i, j = j - 8)
    {
        switch (iByte)
        {
            case 0:
                stControl.iCmd |= (acValue[i] << j);
                break;

            case 1:
                stControl.iCmd2 |= (acValue[i] << j);
                break;

            case 2:
                stControl.iCmd3 |= (acValue[i] << j);
                break;

            default:
                (void) assert(0);
        }

        if (0 == j)
        {
            ++iByte;
            j = 32;
        }
    }
    stControl.iCmd = htonl(stControl.iCmd);
    stControl.iCmd2 = htonl(stControl.iCmd2);
    stControl.iCmd3 = htonl(stControl.iCmd3);

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

    /* hold it high for 1ms */
    (void) usleep(1000);

    /* fill the stControl structure */
    stControl.iCmd = MBR_FC_HEADERINFO_LOW;
    stControl.iCmd2 = 0;
    stControl.iCmd3 = 0;

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

/*
 * int MBR_DownloadRFInfo(void)
 *
 * Downloads the RF values to the FPGA board, for updating
 * the data packet header
 */
int MBR_DownloadRFHist(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    /* numerical values of the attenuators */
    int iAtten1 = 0;
    int iAtten2 = 0;
    int iAtten3 = 0;
    int iAtten4 = 0;
#if 0
    int iAttenAll = 0;
#endif
    /* values of the attenuators in bitmap form */
    char acAtten1[MBR_MAX_LEN_GENSTRING] = {0};
    char acAtten2[MBR_MAX_LEN_GENSTRING] = {0};
    char acAtten3[MBR_MAX_LEN_GENSTRING] = {0};
    char acAtten4[MBR_MAX_LEN_GENSTRING] = {0};
    short int iLOFreq = 0;
    CSocket *pSocket = NULL;
    MBR_CONTROL stControl = {0};
    int iRet = MBR_RET_SUCCESS;

    iRet = MBR_CreateDeviceLookup();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_CreateDeviceLookUp() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Creating device lookup failed!" << endl;
        return MBR_RET_ERROR;
    }

    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR1, acAtten1);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR1 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR2, acAtten2);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR2 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR3, acAtten3);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR3 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR4, acAtten4);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR4 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    /* remove the latch bit from the attenuator bitmaps */
    acAtten1[MBR_BITPOS_ATTENLATCH] = '\0';
    acAtten2[MBR_BITPOS_ATTENLATCH] = '\0';
    acAtten3[MBR_BITPOS_ATTENLATCH] = '\0';
    acAtten4[MBR_BITPOS_ATTENLATCH] = '\0';

    iAtten1 = MBR_Bitmap2Int(acAtten1);
    iAtten2 = MBR_Bitmap2Int(acAtten2);
    iAtten3 = MBR_Bitmap2Int(acAtten3);
    iAtten4 = MBR_Bitmap2Int(acAtten4);

    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_LO,
                    MBR_XML_ATT_FREQ,
                    0,
                    acValue);
    iLOFreq = (short int) atoi((char *) acValue);

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

    /* build the packet */
#if 0
    iAttenAll = (iAtten1 << 18) | (iAtten2 << 12) | (iAtten3 << 6) | (iAtten4);

    /* fill the stControl structure */
    stControl.iCmd = htonl((MBR_FC_RFINFO_HIGH << 24) | iAttenAll);
    stControl.iCmd2 = htons(iLOFreq);
#else
    stControl.iCmd = htonl((MBR_FC_RFINFO_HIGH << 24)
                            | (iAtten1 << 16)
                            | (iAtten2 << 8)
                            | iAtten3);
    stControl.iCmd2 = htonl((iAtten4 << 24) | (iLOFreq  << 8));
#endif

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

    /* hold it high for 1ms */
    (void) usleep(1000);

    /* fill the stControl structure */
    stControl.iCmd = MBR_FC_RFINFO_LOW;
    stControl.iCmd2 = 0;

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

/*
 * int MBR_UpdateRFHist(void)
 *
 * Writes the values of attenuators and LO frequency to the RF settings
 * history file ~/log/rfhist
 */
int MBR_UpdateRFHist(void)
{
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    char acBuffer[MBR_MAX_LEN_GENSTRING] = {0};
    fstream RFHist;
    /* numerical values of the attenuators */
    float fAtten1 = 0.0;
    float fAtten2 = 0.0;
    float fAtten3 = 0.0;
    float fAtten4 = 0.0;
    /* values of the attenuators in bitmap form */
    char acAtten1[MBR_MAX_LEN_GENSTRING] = {0};
    char acAtten2[MBR_MAX_LEN_GENSTRING] = {0};
    char acAtten3[MBR_MAX_LEN_GENSTRING] = {0};
    char acAtten4[MBR_MAX_LEN_GENSTRING] = {0};
    short int iLOFreq = 0;
    int iRet = MBR_RET_SUCCESS;

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

    /* open the log for writing */
    RFHist.open(acPath, fstream::out | fstream::app);
    if (NULL == RFHist)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "fstream::open(" << acPath << ") returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Opening RF history file failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* give the ownership to user 'das' */
    iRet = chown(acPath, MBR_UID_DAS, MBR_GID_DAS);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "chown(" << acPath << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "WARNING: Changing ownership of RF history file failed! "
             << "File may belong to a different user!"
             << endl;
        return MBR_RET_WARNING;
    }

    iRet = MBR_CreateDeviceLookup();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_CreateDeviceLookUp() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Creating device lookup failed!" << endl;
        return MBR_RET_ERROR;
    }

    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ATTENUATOR1,
                    MBR_XML_ATT_VALUE,
                    0,
                    acValue);
    fAtten1 = atof(acValue);
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ATTENUATOR2,
                    MBR_XML_ATT_VALUE,
                    0,
                    acValue);
    fAtten2 = atof(acValue);
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ATTENUATOR3,
                    MBR_XML_ATT_VALUE,
                    0,
                    acValue);
    fAtten3 = atof(acValue);
    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_ATTENUATOR4,
                    MBR_XML_ATT_VALUE,
                    0,
                    acValue);
    fAtten4 = atof(acValue);
    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR1, acAtten1);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR1 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR2, acAtten2);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR2 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR3, acAtten3);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR3 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    iRet = MBR_GetBits((char *) MBR_CMD_ATTENUATOR4, acAtten4);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_GetBits(" << MBR_CMD_ATTENUATOR4 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Getting bits from bitmap file failed!" << endl;
        return MBR_RET_ERROR;
    }
    /* remove the latch bit from the attenuator bitmaps */
    acAtten1[MBR_BITPOS_ATTENLATCH] = '\0';
    acAtten2[MBR_BITPOS_ATTENLATCH] = '\0';
    acAtten3[MBR_BITPOS_ATTENLATCH] = '\0';
    acAtten4[MBR_BITPOS_ATTENLATCH] = '\0';

    MBR_ConfigEntry(MBR_CONFIG_READ,
                    MBR_CFG_DAS,
                    MBR_XML_ENT_LO,
                    MBR_XML_ATT_FREQ,
                    0,
                    acValue);
    iLOFreq = (short int) atoi((char *) acValue);

    (void) sprintf(acBuffer, "[%s] %g %s %g %s %g %s %g %s %i\n",
                   MBR_GetTimestamp(),
                   fAtten1, acAtten1,
                   fAtten2, acAtten2,
                   fAtten3, acAtten3,
                   fAtten4, acAtten4,
                   iLOFreq);

    RFHist.write(acBuffer, strlen(acBuffer));

    RFHist.close();

    return MBR_RET_SUCCESS;
}
#endif  /* (MBR_SET || MBR_DO) */
#endif  /* MBR_LOCAL */

