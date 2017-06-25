/*
 * mbr_get.cpp
 * GET commands
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#include "mbr_common.h"
#include "mbr_get.h"
#include "mbr_config.h"

#ifdef MBR_LOCAL
#ifdef MBR_GET
extern fstream g_ErrLog;

int MBR_Get(char *argv[])
{
    int iRet = MBR_RET_SUCCESS;

    if (0 == strcmp(argv[1], MBR_CMD_DASID))
    {
        iRet = MBR_GetDASID();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetDASID() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting DAS ID failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_SOURCE))
    {
        iRet = MBR_GetSource();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetSource() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting source name failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ACQUISITION))
    {
        iRet = MBR_GetAcqStatus();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetAcqStatus() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting acquisition status failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_DASID))
    {
        iRet = MBR_GetDASID();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetDASID() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting DAS ID failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_DASID))
    {
        iRet = MBR_GetDASID();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetDASID() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting DAS ID failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ETHDEV))
    {
        iRet = MBR_GetEthDev();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetEthDev() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting Ethernet device failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ACQMODE))
    {
        iRet = MBR_GetAcqMode();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetAcqMode() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting mode failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ACQDUR))
    {
        iRet = MBR_GetAcqDur();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetAcqDur() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting acquisition duration failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_PKTOFFSET))
    {
        iRet = MBR_GetPktOffset();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetPktOffset() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting packet offset failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOFREQ))
    {
        iRet = MBR_GetLOFreq();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetLOFreq() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting LO frequency failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOMIN))
    {
        iRet = MBR_GetLOMin();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetLOMin() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting LO minimum failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOMAX))
    {
        iRet = MBR_GetLOMax();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetLOMax() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting LO maximum failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LOSTEP))
    {
        iRet = MBR_GetLOStep();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetLOStep() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting LO step failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_LODWELL))
    {
        iRet = MBR_GetLODwell();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetLODwell() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting LO dwell failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_ATTENUATOR))
    {
        if (argv[2] != NULL)
        {
            iRet = MBR_GetAttenuator(argv[2]);
            if (MBR_RET_ERROR == iRet)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_GetAttenuator() returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Getting attenuation failed!" << endl;
                return MBR_RET_ERROR;
            }
        }
        else
        {
            cerr << "ERROR: Invalid command!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_DATAMODE))
    {
        iRet = MBR_GetDataMode();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "]"
                     << "MBR_GetDataMode() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting acquisition mode failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_BITPACKMODE))
    {
        iRet = MBR_GetBitpackMode();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "]"
                     << "MBR_GetBitpackMode() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting bit-packing mode failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else if (0 == strcmp(argv[1], MBR_CMD_SAMPCLKFREQ))
    {
        iRet = MBR_GetSampClkFreq();
        if (MBR_RET_ERROR == iRet)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_GetSampClkFreq() returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Getting sampling clock frequency failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        return MBR_RET_ERROR;
    }

    return iRet;
}

int MBR_GetDASID(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read the DAS ID from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_DAS,
                           MBR_XML_ATT_ID,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_DASID << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetSource(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;

    /* read the DAS ID from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_SOURCE,
                           MBR_XML_ATT_NAME,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_SOURCE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    /* since MBR_Get() returns an int, sending the source name string back to
       dasd requrires updating the MBR_ENV_SOURCE environment variable */
    iRet = setenv(MBR_ENV_SOURCE, acValue, MBR_TRUE);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "setenv("<< MBR_ENV_SOURCE << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Setting environment variable failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_GetAcqStatus(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read the DAS ID from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_STATUS,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_ACQUISITION << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    if (0 == strcmp(acValue, MBR_CMD_ON))
    {
        iValue = MBR_ACQSTATUS_ON;
    }
    else if (0 == strcmp(acValue, MBR_CMD_OFF))
    {
        iValue = MBR_ACQSTATUS_OFF;
    }
    else
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Invalid acquisition status "<< acValue << " read"
                 << endl;
        cerr << "ERROR: Invalid acquisition status read!" << endl;
        return MBR_RET_ERROR;
    }

    return iValue;
}

int MBR_GetAcqDur(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read the DAS ID from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_DURATION,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_ACQDUR << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetEthDev(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read the DAS ID from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_DEVICE,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_ETHDEV << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(&acValue[MBR_POS_ETH_ID]);

    return iValue;
}

int MBR_GetPktOffset(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read the DAS ID from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_OFFSET,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_PKTOFFSET << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetAcqMode(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read the DAS ID from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_ACQUISITION,
                           MBR_XML_ATT_ACQMODE,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_ACQMODE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    if (0 == strcmp(acValue, MBR_CMD_ACQMODE_OBS))
    {
        iValue = MBR_ACQMODE_OBS;
    }
    else if (0 == strcmp(acValue, MBR_CMD_ACQMODE_SNIFF))
    {
        iValue = MBR_ACQMODE_SNIFF;
    }
    else if (0 == strcmp(acValue, MBR_CMD_ACQMODE_SNIFFACQ))
    {
        iValue = MBR_ACQMODE_SNIFFACQ;
    }
    else if (0 == strcmp(acValue, MBR_CMD_ACQMODE_CHECK))
    {
        iValue = MBR_ACQMODE_CHECK;
    }
    else
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Invalid acquisition mode "<< acValue << " read"
                 << endl;
        cerr << "ERROR: Invalid acquisition mode read!" << endl;
        return MBR_RET_ERROR;
    }

    return iValue;
}

int MBR_GetAttenuator(const char *pcID)
{
    int iRet = MBR_RET_SUCCESS;
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    char acAttenuator[MBR_MAX_LEN_GENSTRING] = {0};
    char acID[2] = {0};
    float fAttenValue = 0;
    int iInt = 0;
    int iValue = 0;
    char acAttenVal[MBR_MAX_LEN_GENSTRING] = {0};

    if (0 == strcmp(pcID,MBR_CMD_VRF))
    {
        (void) strcpy(acID,"1");
    }
    else if (0 == strcmp(pcID,MBR_CMD_VIF))
    {
        (void) strcpy(acID,"2");
    }
    else if (0 == strcmp(pcID,MBR_CMD_HRF))
    {
        (void) strcpy(acID,"3");
    }
    else if (0 == strcmp(pcID,MBR_CMD_HIF))
    {
        (void) strcpy(acID,"4");
    }
    (void) sprintf(acAttenuator, "%s%s", MBR_XML_ENT_ATTENUATOR, acID);

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
                 << ") returned"
                 << iRet
                 << endl;
        cerr << "ERROR: Reading configuration file failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    fAttenValue = atof(acValue);
    iInt = (int) fAttenValue;
    MBR_Int2Bitmap(iInt, acAttenVal);
    if (MBR_IsInteger(fAttenValue))
    {
        strcat(acAttenVal, "0");
    }
    else
    {
        strcat(acAttenVal, "1");
    }
    iValue = MBR_Bitmap2Int(acAttenVal);

    return iValue;
}

int MBR_GetLOFreq(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

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
                 << "MBR_ConfigEntry("<< MBR_CMD_LOFREQ << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetLOMin(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read LO min from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_MIN,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_LOMIN << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetLOMax(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read LO max from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_MAX,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_LOMAX << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetLOStep(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read LO step from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_STEP,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_LOSTEP << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetLODwell(void)
{
    char acValue[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;
    int iValue = 0;

    /* read LO dwell from the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_LO,
                           MBR_XML_ATT_DWELL,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_LODWELL << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetDataMode(void)
{
    int iRet = MBR_RET_SUCCESS;
    char acValue[MBR_MAX_LEN_GENSTRING]={0};
    int iValue = 0;

    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_FPGA,
                           MBR_XML_ATT_DATAMODE,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_DATAMODE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    if (0 == strcmp(acValue, MBR_CMD_DIAG))
    {
        iValue = MBR_DATAMODE_DIAG;
    }
    else if (0 == strcmp(acValue, MBR_CMD_OBS))
    {
        iValue = MBR_DATAMODE_OBSV;
    }
    else
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Invalid data mode "<< acValue << " read"
                 << endl;
        cerr << "ERROR: Invalid data mode read!" << endl;
        return MBR_RET_ERROR;
    }

    return iValue;
}

int MBR_GetBitpackMode(void)
{
    int iRet = MBR_RET_SUCCESS;
    char acValue[MBR_MAX_LEN_GENSTRING]={0};
    int iValue = 0;

    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_FPGA,
                           MBR_XML_ATT_BITPACKMODE,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_BITPACKMODE << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    iValue = atoi(acValue);

    return iValue;
}

int MBR_GetSampClkFreq(void)
{
    int iRet = MBR_RET_SUCCESS;
    char acValue[MBR_MAX_LEN_GENSTRING]={0};
    int iValue = 0;
    float fVal = 0;
    int iInt = 0;
    char acValBitmap[MBR_MAX_LEN_GENSTRING] = {0};

    /* update the config file */
    iRet = MBR_ConfigEntry(MBR_CONFIG_READ,
                           MBR_CFG_DAS,
                           MBR_XML_ENT_FPGA,
                           MBR_XML_ATT_SAMPCLKFREQ,
                           0,
                           acValue);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_ConfigEntry("<< MBR_CMD_SAMPCLKFREQ << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Configuration file read failed!" << endl;
        return iRet;
    }
    cout << acValue << endl;

    fVal = atof(acValue);
    iInt = (int) fVal;
    MBR_Int2Bitmap(iInt, acValBitmap);
    if (MBR_IsInteger(fVal))
    {
        strcat(acValBitmap, "0");
    }
    else
    {
        strcat(acValBitmap, "1");
    }
    iValue = MBR_Bitmap2Int(acValBitmap);

    return iValue;
}

int MBR_GetHelp(void)
{
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    int iRet = MBR_RET_SUCCESS;

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

    (void) strcpy(acPath, MBR_EXE_DISPLAY);
    (void) strcat(acPath, " ");
    (void) strcat(acPath, pcPath);
    (void) strcat(acPath, MBR_PATH_HELPFILE);

    iRet = system(acPath);
    if (!(WIFEXITED(iRet)))
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "system(" << acPath << ") returned "
                 << WEXITSTATUS(iRet)
                 << endl;
        cerr << "ERROR: Opening help file failed!" << endl;
        return MBR_RET_ERROR;
    }

    return MBR_RET_SUCCESS;
}
#endif  /* MBR_GET */
#endif  /* MBR_LOCAL */

