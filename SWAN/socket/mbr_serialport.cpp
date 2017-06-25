/*
 * mbr_serialport.cpp
 * Serial port interfacing functions
 *
 * Authors:
 *  G. Gurushanth (2003.07.23)
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Harshad Sahasrabudhe
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#include "mbr_common.h"
#include "mbr_serialport.h"

extern fstream g_ErrLog;
MBR_LookUp g_DeviceLookUp[MBR_MAX_NUM_DEVICES] = {{{0}}};
int g_iNumDevice = 0;
int g_iSerialPort = 0;

//#ifdef MBR_LOCAL

int MBR_Download(const char *pcParam, const char *pcValue)
{
    int iRet = MBR_RET_SUCCESS;
    int iStartBit = 0;
    int iStopBit = 0;
    int iCount = 0;
    int iVal = 0;
    int iIndex = 0;
    long long llmask = 0;
    float fAttenValue = 0;
    int iInt = 0;
    char acAttenVal[MBR_MAX_LEN_GENSTRING] = {0};
    char acAttenValLatchOff[MBR_MAX_LEN_GENSTRING] = {0};

    /* init - this needs to be done each time as there is a possibility of the
       hardware being power-cycled while dasd is still running */
    iRet = MBR_SerialPortInit();
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_SerialPortInit() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Device initialisation failed!" << endl;
        return iRet;
    }

    if (0 == strcmp(pcParam, MBR_CMD_ATTENUATOR1))
    {
        iIndex = 0;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        fAttenValue = atof(pcValue);
        iInt = (int) fAttenValue;
        MBR_Int2Bitmap(iInt, acAttenVal);
        if (MBR_IsInteger(fAttenValue))
        {
            (void) strcat(acAttenVal, "0");
        }
        else
        {
            (void) strcat(acAttenVal, "1");
        }

        (void) strcpy(acAttenValLatchOff, acAttenVal);
        (void) strcat(acAttenValLatchOff, "0");

        /* the latch bit */
        (void) strcat(acAttenVal, "1");

        iCount = MBR_Bitmap2Int(acAttenVal);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR1
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR1
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR1
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }

        (void) sleep(1);

        /* now set the latch to off */
        iCount = MBR_Bitmap2Int(acAttenValLatchOff);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR1
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR1
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR1
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_ATTENUATOR2))
    {
        iCount = MBR_Bitmap2Int(pcValue);

        iIndex = 0;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        fAttenValue = atof(pcValue);
        iInt = (int) fAttenValue;
        MBR_Int2Bitmap(iInt, acAttenVal);
        if (MBR_IsInteger(fAttenValue))
        {
            (void) strcat(acAttenVal, "0");
        }
        else
        {
            (void) strcat(acAttenVal, "1");
        }

        (void) strcpy(acAttenValLatchOff, acAttenVal);
        (void) strcat(acAttenValLatchOff, "0");

        /* the latch bit */
        (void) strcat(acAttenVal, "1");

        iCount = MBR_Bitmap2Int(acAttenVal);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR2
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR2
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR2
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }

        (void) sleep(1);

        /* now set the latch to off */
        iCount = MBR_Bitmap2Int(acAttenValLatchOff);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR2
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR2
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR2
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_ATTENUATOR3))
    {
        iCount = MBR_Bitmap2Int(pcValue);

        iIndex = 0;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        fAttenValue = atof(pcValue);
        iInt = (int) fAttenValue;
        MBR_Int2Bitmap(iInt, acAttenVal);
        if (MBR_IsInteger(fAttenValue))
        {
            (void) strcat(acAttenVal, "0");
        }
        else
        {
            (void) strcat(acAttenVal, "1");
        }

        (void) strcpy(acAttenValLatchOff, acAttenVal);
        (void) strcat(acAttenValLatchOff, "0");

        /* the latch bit */
        (void) strcat(acAttenVal, "1");

        iCount = MBR_Bitmap2Int(acAttenVal);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR3
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR3
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR3
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }

        (void) sleep(1);

        /* now set the latch to off */
        iCount = MBR_Bitmap2Int(acAttenValLatchOff);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR3
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR3
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR3
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_ATTENUATOR4))
    {
        iCount = MBR_Bitmap2Int(pcValue);

        iIndex = 0;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        fAttenValue = atof(pcValue);
        iInt = (int) fAttenValue;
        MBR_Int2Bitmap(iInt, acAttenVal);
        if (MBR_IsInteger(fAttenValue))
        {
            (void) strcat(acAttenVal, "0");
        }
        else
        {
            (void) strcat(acAttenVal, "1");
        }

        (void) strcpy(acAttenValLatchOff, acAttenVal);
        (void) strcat(acAttenValLatchOff, "0");

        /* the latch bit */
        (void) strcat(acAttenVal, "1");

        iCount = MBR_Bitmap2Int(acAttenVal);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR4
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR4
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR4
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }

        (void) sleep(1);

        /* now set the latch to off */
        iCount = MBR_Bitmap2Int(acAttenValLatchOff);
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_ATTENUATOR4
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_ATTENUATOR4
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_ATTENUATOR4
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_GPS))
    {
        /* simulate a single GPS pulse */

        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        iCount = 0;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_GPS
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_GPS
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_GPS
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iCount = 1;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_GPS
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_GPS
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_GPS
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iCount = 0;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_GPS
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_GPS
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_GPS
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_ACQUISITION))
    {
        iIndex = 0;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice,
                            MBR_FPGABIT_ENABLE))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        if (0 == strcmp(pcValue, MBR_CMD_ON))
        {
            iCount = 0;
        }
        else if (0 == strcmp(pcValue, MBR_CMD_OFF))
        {
            iCount = 1;
        }
        else
        {
            cerr << "ERROR: Invalid command!" << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        iRet = MBR_SetBits(iStartBit , iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_FPGABIT_ENABLE
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_FPGABIT_ENABLE
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_FPGABIT_ENABLE
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_FPGARESET))
    {
        iIndex = 0;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        iCount = 0;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_FPGARESET
                << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_FPGARESET
                     << "returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_FPGARESET
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iCount = 1;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_FPGARESET
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_FPGARESET
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_FPGARESET
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }

        /* sleep for 600ms */
        (void) usleep(600000);

        iCount = 0;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_FPGARESET
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_FPGARESET
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_FPGARESET
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_FPGAPROG))
    {
        int iValue = 1;
        iCount = iValue ;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        iCount = 0;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_FPGAPROG
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_FPGAPROG
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_FPGAPROG
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iCount = 1;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_FPGAPROG
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_FPGAPROG
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_FPGAPROG
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }

        (void) usleep(500000);

        iCount = 0;
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_FPGAPROG
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_FPGAPROG
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_FPGAPROG
                 << "failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_DATAMODE))
    {
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        if (0 == strcmp(pcValue, MBR_CMD_DIAG))
        {
            iCount = 0;     // 0000
        }
        else if (0 == strcmp(pcValue, MBR_CMD_OBS))
        {
            iCount = 1;     // 1000
        }
        else
        {
            cerr << "ERROR: Invalid command!" << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_DATAMODE
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_DATAMODE
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_DATAMODE
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_BITPACKMODE))
    {
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        if (0 == strcmp(pcValue, MBR_CMD_BITPACK_4))
        {
            iCount = 0;
        }
        else if (0 == strcmp(pcValue, MBR_CMD_BITPACK_8))
        {
            iCount = 1;
        }
        else
        {
            cerr << "ERROR: Invalid command!" << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }
        iRet = MBR_SetBits(iStartBit, iStopBit, iCount, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for " << MBR_CMD_BITPACKMODE
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for " << MBR_CMD_BITPACKMODE
                     << " returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for " << MBR_CMD_BITPACKMODE
                 << " failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else if (0 == strcmp(pcParam, MBR_CMD_LOFREQ))
    {
        int i = 0;
        int iValue = 0;
        int iLE = 0;
        iLE = MBR_LE_LOW;
        iLE <<= 2;
        iIndex = 0;
        while (iIndex != g_iNumDevice)
        {
            if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcParam))
            {
                iStartBit = g_DeviceLookUp[iIndex].iStart;
                iStopBit = g_DeviceLookUp[iIndex].iStop;
                break;
            }
            iIndex++;
        }
        if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "No match found for " << pcParam
                     << endl;
            cerr << "ERROR: No match found for " << pcParam << "!"
                 << endl;
            MBR_DevClose();
            return MBR_RET_ERROR;
        }

        /* frequency synthesizer init - this needs to be done each time as
           there is a possibility of the hardware being power-cycled while dasd
           is still running */
        iRet = MBR_FreqSynthInit(iStartBit, iStopBit);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_FreqSynthInit() returned"
                     << iRet
                     << endl;
            cerr << "ERROR: Initializing frequency synthesizer failed!" << endl;
            MBR_DevClose();
            return iRet;
        }

        iCount = MBR_Freq2AB(pcValue);
        for (i = MBR_NUM_BIT; i >= 0; --i)
        {
            /* get the value MSB first, and send it to MBR_DevWrite() */
            iVal = (iCount >> i) & 0x1;
            iVal <<= 1;
            iValue = (iVal | iLE | MBR_CLK_LOW);
            iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                         << ") returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Setting bits for LO failed!" << endl;
                MBR_DevClose();
                return iRet;
            }
            iRet = MBR_WriteBitmap(llmask);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_WriteBitmap() for LO returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Writing bits for LO failed!" << endl;
                MBR_DevClose();
                return iRet;
            }

            iValue = (iVal | iLE | MBR_CLK_HIGH);
            iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                         << ") returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Setting bits for LO failed!" << endl;
                MBR_DevClose();
                return iRet;
            }
            iRet = MBR_WriteBitmap(llmask);
            if (iRet != MBR_RET_SUCCESS)
            {
                g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                         << "MBR_WriteBitmap() for LO returned "
                         << iRet
                         << endl;
                cerr << "ERROR: Writing bits for LO failed!" << endl;
                MBR_DevClose();
                return iRet;
            }
        }

        iLE = MBR_LE_HIGH;
        iLE <<= 2;
        iValue = (iVal | iLE | MBR_CLK_LOW);
        iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for LO failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for LO returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for LO failed!" << endl;
            MBR_DevClose();
            return iRet;
        }
    }
    else
    {
        cerr << "ERROR: Invalid command!" << endl;
        MBR_DevClose();
        return MBR_RET_ERROR;
    }

    MBR_DevClose();

    return MBR_RET_SUCCESS;
}

int MBR_SerialPortInit(void)
{
    struct termios stTermParams;
    int *piDevice = &g_iSerialPort;
    int iRet = MBR_RET_SUCCESS;

    *piDevice = open(MBR_DEV_SERIALPORT, O_WRONLY | O_NOCTTY);
    if (MBR_RET_ERROR == *piDevice)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "open(" << MBR_DEV_SERIALPORT << ") failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Serial port opening failed!" << endl;
        return errno;
    }

    (void) tcgetattr(*piDevice, &stTermParams);
    cfmakeraw(&stTermParams);

    /* from the man page of tcsetattr():

       RETURN VALUE
              ...

              Note that tcsetattr() returns success if any of the requested
              changes could be successfully carried out. Therefore, when making
              multiple changes it may be necessary to follow this call with a
              further call to tcgetattr() to check that all changes have been
              performed successfully.

       instead of calling tcgetattr() after all changes, we call tcsetattr()
       after each change.
    */
    stTermParams.c_cflag |= CSTOPB;
    tcsetattr(*piDevice, TCSANOW, &stTermParams);

    stTermParams.c_cflag |= CS8;
    tcsetattr(*piDevice, TCSANOW, &stTermParams);

    (void) cfsetospeed(&stTermParams, B9600);

    (void) fcntl(*piDevice, F_SETFL, 0);

    /* create the device bit position lookup file */
    iRet = MBR_CreateDeviceLookup();
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_CreateDeviceLookup() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Creating device lookup failed!" << endl;
        return errno;
    }

    /* set control words */
    iRet = MBR_DevWrite(MBR_8255CW_1, MBR_8255MODE_ALLOUT);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() for control word 1 returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing control word to device failed!" << endl;
        return iRet;
    }
    iRet = MBR_DevWrite(MBR_8255CW_2, MBR_8255MODE_ALLOUT);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() for control word 2 returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing control word to device failed!" << endl;
        return iRet;
    }
    return MBR_RET_SUCCESS;
}

int MBR_DevWrite(int iAddress, int iVal)
{
    int iRet = MBR_RET_SUCCESS;

    iRet = write(g_iSerialPort, &iAddress, MBR_SIZE_WRITE);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "write() failed, while writing to "
                 << g_iSerialPort
                 << ", errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Writing to device failed!" << endl;
        return errno;
    }

    iRet = write(g_iSerialPort, &iVal, MBR_SIZE_WRITE);
    if (MBR_RET_ERROR == iRet)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "write() failed, while writing to "
                 << g_iSerialPort
                 << ", errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Writing to device failed!" << endl;
        return errno;
    }

    return MBR_RET_SUCCESS;
}

int MBR_WriteBitmap(long long llBitmap)
{
    int iRet = MBR_RET_SUCCESS;

    /* MBR_8255PORT_A1: attenuator vrf, attenuator vif */
    iRet = MBR_DevWrite(MBR_8255PORT_A1, (char) llBitmap);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits to device failed!" << endl;
        return iRet;
    }

    /* MBR_8255PORT_B1: attenuator vif, attenuator hrf */
    iRet = MBR_DevWrite(MBR_8255PORT_B1, (char) (llBitmap >> 8));
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits to device failed!" << endl;
        return iRet;
    }

    /* MBR_8255PORT_C1: attenuator hrf, lofreq  */
    iRet = MBR_DevWrite(MBR_8255PORT_C1, (char) (llBitmap >> 16));
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits to device failed!" << endl;
        return iRet;
    }

    /* MBR_8255PORT_A2: fpga settings */
    iRet = MBR_DevWrite(MBR_8255PORT_A2, (char) (llBitmap >> 24));
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits to device failed!" << endl;
        return iRet;
    }

    /* MBR_8255PORT_B2: attenuator hif, reserved */
    iRet = MBR_DevWrite( MBR_8255PORT_B2, (char) (llBitmap >> 32));
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits to device failed!" << endl;
        return iRet;
    }

    /* MBR_8255PORT_C2: reserved */
    iRet = MBR_DevWrite(MBR_8255PORT_C2, (char) (llBitmap >> 40));
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_DevWrite() returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits to device failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_SetBits(int iStartBit, int iStopBit, int iValue, long long *pllBitmap)
{
    long long llMask = 0xFFFFFFFFFFFFFFFFLL;    /* ISOC99-compliant */
    long long llValue = 0;
    char acBitmap[MBR_MAX_LEN_GENSTRING] = {0};
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    int iIndex = 0;
    int iLength = 0;
    fstream DASBitmap;

    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getenv(" << MBR_ENV_HOME << ") failed"
                 << endl;
        cerr << "ERROR: Environment variable " << MBR_ENV_HOME
             << " not defined!" << endl;
        return MBR_RET_ERROR;
    }

    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_FILE_DAS_BITMAP);

    DASBitmap.open(acPath, fstream::in);
    if (NULL == DASBitmap)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "DASBitmap.open(" << acPath << ", "
                 << "fstream::in) failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Opening file bitmap failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* read the current bitmap */
    DASBitmap.getline(acBitmap, MBR_MAX_LEN_GENSTRING);
    DASBitmap.close();
    *pllBitmap = MBR_Bitmap2LongLong((char *)acBitmap);
    iLength = sizeof(llMask);

    /* generate mask */
    if (((iStartBit + 1) > (iLength * 8)) || (iStopBit < 0))
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Bit validation failed, start bit is " << iStartBit
                 << ", stop bit is " << iStopBit
                 << endl;
        cerr << "ERROR: Bit validation failed!" << endl;
        return MBR_RET_ERROR;
    }

    if (iStartBit < iStopBit)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Bit validation failed, start bit is " << iStartBit
                 << ", stop bit is " << iStopBit
                 << endl;
        cerr << "ERROR: Bit validation failed!" << endl;
        return MBR_RET_ERROR;
    }

    if ((iStartBit + 1) < (iLength * 8))
    {
        llMask >>= (iStartBit + 1);
        llMask <<= (iStartBit + 1);
        llMask = ~llMask;
    }

    llMask >>= iStopBit;
    llMask <<= iStopBit;
    llMask = ~llMask;

    /* write the new bitmap */
    *pllBitmap &= llMask;

    llValue = iValue;
    llValue <<= iStopBit;

    llValue &= ~llMask;
    *pllBitmap |= llValue;

    iLength = 0;
    MBR_LongLong2Bitmap(*pllBitmap, acBitmap);
    iLength = strlen(acBitmap);

    DASBitmap.clear();

    DASBitmap.open(acPath, fstream::out);
    if (NULL == DASBitmap)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "DASBitmap.open(fstream::out) failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Opening file bitmap failed!" << endl;
        return MBR_RET_ERROR;
    }

    while (iIndex < iLength)
    {
        DASBitmap.put(acBitmap[iIndex]);
        iIndex++;
    }

    DASBitmap.close();

    return MBR_RET_SUCCESS;
}

/*
 * int MBR_GetBits(char *pcDevice, char *pcBits)
 *
 * Gets the integer-equivalent of the bitmap corresponding to the specified
 * device, from the ~/config/bitmap file.
 */
int MBR_GetBits(char *pcDevice, char *pcBits)
{
    char acBitmap[MBR_MAX_LEN_GENSTRING] = {0};
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    fstream DASBitmap;
    char *pcPath = NULL;
    int iIndex = 0;
    int iStartBit = 0;
    int iStopBit = 0;
    int iBitmapLen = 0;
    int i = 0;
    int j = 0;

    assert(pcDevice != NULL);
    assert(pcBits != NULL);

    /* get the start and stop bits in the bitmap file for the specified
       device */
    while (iIndex != g_iNumDevice)
    {
        if (0 == strcmp(g_DeviceLookUp[iIndex].acDevice, pcDevice))
        {
            iStartBit = g_DeviceLookUp[iIndex].iStart;
            iStopBit = g_DeviceLookUp[iIndex].iStop;
            break;
        }
       ++iIndex;
    }
    if ((0 == iStartBit) && (0 == iStopBit))    /* no match found */
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "No match found for " << pcDevice
                 << endl;
        cerr << "ERROR: No match found for " << pcDevice << "!"
             << endl;
        return MBR_RET_ERROR;
    }

    /* open the file and get the bits */
    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getenv($HOME) failed"
                 << endl;
        cerr << "ERROR: $HOME not defined!" << endl;
        return MBR_RET_ERROR;
    }

    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_FILE_DAS_BITMAP);

    DASBitmap.open(acPath, fstream::in);
    if (NULL == DASBitmap)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "DASBitmap.open(fstream::in) failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Opening file bitmap failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* read the bitmap and close the file */
    DASBitmap.getline(acBitmap, MBR_MAX_LEN_GENSTRING);
    DASBitmap.close();

    /* read the necessary bits and convert it into an int */
    iBitmapLen = strlen(acBitmap);
    for (i = (iBitmapLen - iStartBit - 1), j = 0;
         i <= (iBitmapLen - iStopBit - 1);
         ++i, ++j)
    {
        pcBits[j] = acBitmap[i];
    }
    pcBits[j] = '\0';

    return MBR_RET_SUCCESS;
}

int MBR_FreqSynthInit(int iStartBit, int iStopBit)
{
    int iRet = MBR_RET_SUCCESS;
    int iVal = 0;
    int i = 0;
    int iValue = 0;
    int iLE = MBR_LE_LOW;
    long long llmask = 0;

    /* set the IL */
    iLE = MBR_LE_LOW;
    iLE <<= 2;

    for (i = MBR_NUM_BIT; i >= 0; --i)
    {
        /* get the value MSB first, and send it to MBR_DevWrite() */
        iVal = (IL >> i) & 0x1;
        iVal <<= 1;
        iValue = (iVal | iLE | MBR_CLK_LOW);
        iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for LO frequency returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
            return iRet;
        }

        iValue = (iVal | iLE | MBR_CLK_HIGH);
        iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for LO frequency returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
            return iRet;
        }
    }
    iLE = MBR_LE_HIGH;
    iLE <<= 2;
    iValue = (iVal | iLE | MBR_CLK_LOW);
    iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                 << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
        return iRet;
    }
    iRet = MBR_WriteBitmap(llmask);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_WriteBitmap() for LO frequency returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
        return iRet;
    }

    /* set the FL */
    iLE = MBR_LE_LOW;
    iLE <<= 2;

    for (i = MBR_NUM_BIT; i >= 0; --i)
    {
        /* get the value MSB first, and send it to MBR_DevWrite() */
        iVal = (FL >> i) & 0x1;
        iVal <<= 1;
        iValue = (iVal | iLE | MBR_CLK_LOW);
        iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for LO frequency returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
            return iRet;
        }

        iValue = (iVal | iLE | MBR_CLK_HIGH);
        iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for LO frequency returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
            return iRet;
        }
    }
    iLE = MBR_LE_HIGH;
    iLE <<= 2;
    iValue = (iVal | iLE | MBR_CLK_LOW);
    iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                 << ") returned "
                 << iRet
                 << endl;
       cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
       return iRet;
    }
    iRet = MBR_WriteBitmap(llmask);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_WriteBitmap() for LO frequency returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
        return iRet;
    }

    /* set the R counter */
    iLE = MBR_LE_LOW;
    iLE <<= 2;

    for (i = MBR_NUM_BIT; i >= 0; --i)
    {
        /* get the value MSB first, and send it to MBR_DevWrite() */
        iVal = (R >> i) & 0x1;
        iVal <<= 1;
        iValue = (iVal | iLE | MBR_CLK_LOW);
        iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for LO frequency returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
            return iRet;
        }

        iValue = (iVal | iLE | MBR_CLK_HIGH);
        iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
            return iRet;
        }
        iRet = MBR_WriteBitmap(llmask);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "MBR_WriteBitmap() for LO frequency returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
            return iRet;
        }
    }
    iLE = MBR_LE_HIGH;
    iLE <<= 2;
    iValue = (iVal | iLE | MBR_CLK_LOW);
    iRet = MBR_SetBits(iStartBit, iStopBit, iValue, &llmask);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_SetBits(" << iStartBit << ", " << iStopBit
                 << ") returned "
                 << iRet
                 << endl;
       cerr << "ERROR: Setting bits for LO frequency failed!" << endl;
       return iRet;
    }
    iRet = MBR_WriteBitmap(llmask);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "MBR_WriteBitmap() for LO frequency returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Writing bits for LO frequency failed!" << endl;
        return iRet;
    }

    return MBR_RET_SUCCESS;
}

int MBR_Freq2AB(const char *pcValue)
{
    int iFreqLO = 0;
    int iA = 0;
    int iB = 0;
    int iAB = 0;

    iFreqLO = atoi(pcValue);
    iB = iFreqLO / P;
    iA = iFreqLO - (P * iB);
    iA <<= 2;
    iB <<= 8;
    iAB = (AB_BASE | iA | iB);

    return iAB;
}

float MBR_GetAttnFromBitmap(const char* pcVal)
{
    int iIndex = 0;
    int iDigit = 0;
    int iRemainder = 0;
    float fFactor = 0.25;   /* easy way to ignore LSB, which is the latch bit */
    int iLength = 0;
    float fValue = 0;

    iLength = strlen(pcVal);
    iDigit = atoi(pcVal);
    while (iIndex < iLength)
    {
        iRemainder = iDigit % 10;
        fValue += iRemainder * (fFactor);
        iIndex++;
        iDigit = iDigit / 10;
        fFactor *= 2;
    }

    return fValue;
}

long long MBR_Bitmap2LongLong(const char *pcVal)
{
    int iIndex = 0;
    long long llSum = 0;
    long long llFactor = 1;
    int iFlag = 0;
    int iLength = 0;
    iLength = strlen(pcVal);

    iIndex = iLength - 1;

    while (iIndex >= 0)
    {
        if ('1' == pcVal[iIndex])
        {
            iFlag = 1;
        }
        llSum += llFactor * iFlag;
        llFactor *= 2;
        iFlag = 0;
        iIndex--;
    }

    return llSum;
}

void MBR_LongLong2Bitmap(long long llnum, char acBitmap[])
{
    int iIndex = 0;
    int iFactor = 2;
    int iFlag = 0;
    int iLength = 0;

    iLength = sizeof(llnum) * 8;
    iIndex = iLength - 1;
    while (iIndex >= 0)
    {
       iFlag = llnum % iFactor;
       acBitmap[iIndex] = iFlag + '0';
       llnum /= 2;
       iIndex--;
    }

    return;
}

int MBR_CreateDeviceLookup(void)
{
    int iIndex = 0;
    int iDeviceID = 0;
    int iNum = 0;
    int iStart = 0;
    int iStop = 0;
    char acBitmap[MBR_MAX_LEN_GENSTRING] = {0};
    char acDevice[MBR_MAX_LEN_GENSTRING] = {0};
    char acStart[MBR_MAX_LEN_GENSTRING] = {0};
    char acStop[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcPath = NULL;
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    fstream LookUp;

    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getenv($HOME) failed"
                 << endl;
        cerr << "ERROR: $HOME not defined!" << endl;
        return MBR_RET_ERROR;
    }

    (void) strcpy(acPath, pcPath);
    (void) strcat(acPath, MBR_FILE_DAS_LOOKUP);

    LookUp.open(acPath, fstream::in);
    if (NULL == LookUp)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "LookUp.open() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Opening file devlookup failed!" << endl;
        return MBR_RET_ERROR;
    }

    LookUp.getline(acBitmap, MBR_MAX_LEN_GENSTRING);
    while (!LookUp.eof())
    {
        LookUp.getline(acBitmap, MBR_MAX_LEN_GENSTRING);
        iIndex = 0;
        iDeviceID = 0;
        iStart = 0;
        iStop = 0;
        while ((acBitmap[iIndex] != ' ') && (acBitmap[iIndex] != '\t'))
        {
            acDevice[iDeviceID++] = acBitmap[iIndex];
            iIndex++;
        }
        acDevice[iDeviceID] = '\0';
        strcpy(g_DeviceLookUp[iNum].acDevice, acDevice);
        while ((' ' == acBitmap[iIndex]) || ('\t' == acBitmap[iIndex]))
        {
            iIndex++;
        }
        while ((acBitmap[iIndex] != ' ') && (acBitmap[iIndex] != '\t'))
        {
            acStart[iStart++] = acBitmap[iIndex];
            iIndex++;
        }
        acStart[iStart] = '\0';
        g_DeviceLookUp[iNum].iStart = atoi(acStart);
        while ((' ' == acBitmap[iIndex]) || ('\t' == acBitmap[iIndex]))
        {
            iIndex++;
        }
        while (acBitmap[iIndex] != '\0')
        {
            acStop[iStop++] = acBitmap[iIndex];
            iIndex++;
        }
        acStop[iStop] = '\0';
        g_DeviceLookUp[iNum++].iStop = atoi(acStop);
        acBitmap[iIndex]='\n';
    }

    LookUp.close();
    g_iNumDevice = iNum;

    return MBR_RET_SUCCESS;
}

void MBR_DevClose()
{
    int iRet = MBR_RET_SUCCESS;

    iRet = close(g_iSerialPort);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "close(" << g_iSerialPort << ") returned "
                 << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "Closing device failed!" << endl;
        return;
    }

    return;
}

//#endif

