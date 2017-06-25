/*
 * mbr_config.cpp
 * Configuration file management functions
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#include "mbr_common.h"
#include "mbr_config.h"

extern fstream g_ErrLog;

int MBR_ConfigEntry(int iAction,
                    int iCfgFile,
                    const char *pcNodeName,
                    const char *pcAttrName,
                    int iDASID,
                    char *pcAttrValue)
{
    char *pcPath = NULL;
    char acPath[MBR_MAX_LEN_GENSTRING] = {0};
    int iRet = MBR_RET_SUCCESS;

    /* get the environment variable HOME for opening the config file */
    pcPath = getenv(MBR_ENV_HOME);
    if (NULL == pcPath)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "getenv(HOME) returned NULL"
                 << endl;
        cerr << "ERROR: Environment variable HOME not defined!" << endl;
        return MBR_RET_ERROR;
    }

    /* build the path to the config file */
    if (MBR_CFG_MC == iCfgFile)
    {
        (void) strcpy(acPath, pcPath);
        (void) strcat(acPath, MBR_PATH_XML_MC);
    }
    else if (MBR_CFG_DAS == iCfgFile)
    {
        (void) strcpy(acPath, pcPath);
        (void) strcat(acPath, MBR_PATH_XML_DAS);
    }
    else
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Invalid config file ID: "
                 << iCfgFile
                 << endl;
        cerr << "ERROR: Invalid config file ID!" << endl;
        return MBR_RET_ERROR;
    }

    if (MBR_CONFIG_UPDATE == iAction)
    {
        /* update the config file */
        iRet = UpdateConfigFile(acPath,
                                pcNodeName,
                                pcAttrName,
                                iDASID,
                                pcAttrValue);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "UpdateConfigFile(" << pcNodeName << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Updating config file failed!" << endl;
            return MBR_RET_ERROR;
        }
    }
    else    /* MBR_CONFIG_READ */
    {
        /* read the value of the specified element */
        iRet = MBR_ParseDoc(acPath,
                            pcNodeName,
                            pcAttrName,
                            iDASID,
                            (xmlChar *) pcAttrValue);
        if (iRet != MBR_RET_SUCCESS)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "ParseDoc(" << pcNodeName << ", " << pcAttrName
                     << ") returned "
                     << iRet
                     << endl;
            cerr << "ERROR: Reading config file failed!" << endl;
            return MBR_RET_ERROR;
        }
    }

    return MBR_RET_SUCCESS;
}

int UpdateConfigFile(const char *pcConfigFile,
                     const char *pcNodeName,
                     const char *pcAttrName,
                     int iDASIDIn,
                     const char *pcValue)
{
    xmlDocPtr pstDoc = NULL;
    xmlNodePtr pstRootNode = NULL;
    xmlNodePtr pstNode = NULL;
    xmlChar *pcCurValue = NULL;
    char *pcValidateCmd = NULL;
    int iRet = MBR_RET_SUCCESS;
    int iFlagMatch = MBR_FALSE;
    int iDASID = 0;

    pstDoc = xmlParseFile(pcConfigFile);
    if (NULL == pstDoc)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "xmlParseFile(" << pcConfigFile << ") returned NULL"
                 << endl;
        cerr << "ERROR: Parsing configuration file failed!" << endl;
        return MBR_RET_ERROR;
    }

    pstRootNode = xmlDocGetRootElement(pstDoc);
    if (NULL == pstRootNode)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "xmlDocGetRootElement(" << pcConfigFile << ") returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Getting document root element failed!" << endl;
        xmlFreeDoc(pstDoc);
        return MBR_RET_ERROR;
    }

    if (strstr(pcConfigFile, MBR_PATH_XML_MC) != NULL)
    {
        /* updating the file mbr_mc.xml */
        if (xmlStrcmp(pstRootNode->name, MBR_NODE_ROOT_MC) != 0)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "xmlStrcmp() returned non-zero, mismatch between "
                     << pstRootNode->name << " and " << MBR_NODE_ROOT_MC
                     << endl;
            cerr << "ERROR: Root node name mismatch!" << endl;
            xmlFreeDoc(pstDoc);
            return MBR_RET_ERROR;
        }
    }
    else
    {
        /* updating the file mbr_das.xml */
        if (xmlStrcmp(pstRootNode->name, MBR_NODE_ROOT_DAS) != 0)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "xmlStrcmp() returned non-zero, mismatch between "
                     << pstRootNode->name << " and " << MBR_NODE_ROOT_DAS
                     << endl;
            cerr << "ERROR: Root node name mismatch!" << endl;
            xmlFreeDoc(pstDoc);
            return MBR_RET_ERROR;
        }
    }

    if (0 == xmlStrcmp((const xmlChar *) pcNodeName, pstRootNode->name))
    {
        pcCurValue = xmlGetProp(pstRootNode, (const xmlChar *) pcAttrName);
        cout << "Old " << pcAttrName << " of " << pcNodeName << " is "
             << pcCurValue
             << endl;
        xmlFree(pcCurValue);
        (void) xmlSetProp(pstRootNode,
                          (const xmlChar *) pcAttrName,
                          (const xmlChar *) pcValue);
        pcCurValue = xmlGetProp(pstRootNode, (const xmlChar *) pcAttrName);
        cout << "New " << pcAttrName << " of " << pcNodeName << " is "
             << pcCurValue
             << endl;
        xmlFree(pcCurValue);
    }
    else
    {
        pstNode = pstRootNode->xmlChildrenNode;
        if (iDASIDIn != 0)
        {
            /* the user has specified a non-zero DAS ID, which could only mean
               that parameter to be updated is DAS liveness */
            while (pstNode != NULL)
            {
                if (0 == xmlStrcmp(pstNode->name, (const xmlChar *) pcNodeName))
                {
                    pcCurValue = xmlGetProp(pstNode, (const xmlChar *) "id");
                    iDASID = atoi((const char *) pcCurValue);
                    xmlFree(pcCurValue);
                    if (iDASIDIn == iDASID)
                    {
                        pcCurValue = xmlGetProp(pstNode,
                                                 (const xmlChar *) pcAttrName);
                        cout << "Old " << pcAttrName << " of " << pcNodeName
                             << " is "
                             << pcCurValue
                             << endl;
                        xmlFree(pcCurValue);
                        (void) xmlSetProp(pstNode,
                                          (const xmlChar *) pcAttrName,
                                          (const xmlChar *) pcValue);
                        pcCurValue = xmlGetProp(pstNode, (const xmlChar *) pcAttrName);
                        cout << "New " << pcAttrName << " of " << pcNodeName << " is "
                             << pcCurValue
                             << endl;
                        xmlFree(pcCurValue);
                        iFlagMatch = MBR_TRUE;
                        break;
                    }
                }
                pstNode = pstNode->next;
            }
        }
        else
        {
            while (pstNode != NULL)
            {
                if (0 == xmlStrcmp(pstNode->name, (const xmlChar *) pcNodeName))
                {
                    pcCurValue = xmlGetProp(pstNode, (const xmlChar *) pcAttrName);
                    cout << "Old " << pcAttrName << " of " << pcNodeName << " is "
                         << pcCurValue
                         << endl;
                    xmlFree(pcCurValue);
                    (void) xmlSetProp(pstNode,
                                      (const xmlChar *) pcAttrName,
                                      (const xmlChar *) pcValue);
                    pcCurValue = xmlGetProp(pstNode, (const xmlChar *) pcAttrName);
                    cout << "New " << pcAttrName << " of " << pcNodeName << " is "
                         << pcCurValue
                         << endl;
                    xmlFree(pcCurValue);
                    iFlagMatch = MBR_TRUE;
                    break;
                }
                pstNode = pstNode->next;
            }
        }

        if (iFlagMatch != MBR_TRUE)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "Invalid node name " << pcNodeName
                     << endl;
            cerr << "ERROR: Invalid node name!" << endl;
            xmlFreeDoc(pstDoc);
            return MBR_RET_ERROR;
        }
    }

    /* allocate memory for, and build the validation command string */
    pcValidateCmd = (char *) malloc(strlen(MBR_CMD_VALIDATE)
                                    + strlen(pcConfigFile)
                                    + 1);   /* for "\0" */
    if (NULL == pcValidateCmd)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "malloc() failed, "
                 << "errno set to " << errno << " with error: "
                 << strerror(errno)
                 << endl;
        cerr << "ERROR: Memory allocation failure!" << endl;
        return errno;
    }

    (void) sprintf(pcValidateCmd,
                   MBR_CMD_VALIDATE "%s",
                   pcConfigFile);

    /* run xmllint, the validation program */
    iRet = system(pcValidateCmd);
    if (!(WIFEXITED(iRet)))
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "system(" << pcValidateCmd << ") returned "
                 << WEXITSTATUS(iRet)
                 << endl;
        cerr << "ERROR: Config file validation failed" << endl;
        return iRet;
     }

    /* save the file */
    iRet = xmlSaveFormatFile(pcConfigFile, pstDoc, 1);
    if (MBR_RET_ERROR == iRet)  /* for success, returns number of bytes */
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "xmlSaveFormatFile(" << pcConfigFile << ") returned "
                 << iRet
                 << endl;
        cerr << "ERROR: Saving config file failed!" << endl;
        return MBR_RET_ERROR;
    }

    /* clean up */
    free(pcValidateCmd);

    return MBR_RET_SUCCESS;
}

int MBR_ParseDoc(const char *pcConfigFile,
                 const char *pcNodeName,
                 const char *pcAttrName,
                 int iDASID,
                 xmlChar *pcAttrValueIn)
{
    xmlDocPtr pstDoc = NULL;
    xmlNodePtr pstRootNode = NULL;
    int iRet = MBR_RET_SUCCESS;

    pstDoc = xmlParseFile(pcConfigFile);
    if (NULL == pstDoc)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "xmlParseFile(" << pcConfigFile << ") returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Parsing configuration file failed!" << endl;
        return MBR_RET_ERROR;
    }

    pstRootNode = xmlDocGetRootElement(pstDoc);
    if (NULL == pstRootNode)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "xmlDocGetRootElement(" << pcConfigFile << ") returned "
                 << "NULL"
                 << endl;
        cerr << "ERROR: Getting document root element failed!" << endl;
        xmlFreeDoc(pstDoc);
        return MBR_RET_ERROR;
    }

    if (strstr(pcConfigFile, MBR_PATH_XML_MC) != NULL)
    {
        if (xmlStrcmp(pstRootNode->name, MBR_NODE_ROOT_MC) != 0)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "xmlStrcmp() returned non-zero, mismatch between "
                     << pstRootNode->name << " and " << MBR_NODE_ROOT_MC
                     << endl;
            cerr << "ERROR: Root node name mismatch!" << endl;
            xmlFreeDoc(pstDoc);
            return MBR_RET_ERROR;
        }
    }
    else
    {
        if (xmlStrcmp(pstRootNode->name, MBR_NODE_ROOT_DAS) != 0)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "xmlStrcmp() returned non-zero, mismatch between "
                     << pstRootNode->name << " and " << MBR_NODE_ROOT_DAS
                     << endl;
            cerr << "ERROR: Root node name mismatch!" << endl;
            xmlFreeDoc(pstDoc);
            return MBR_RET_ERROR;
        }
    }

    iRet = MBR_GetAttribute(pstDoc,
                            pstRootNode,
                            pcNodeName,
                            pcAttrName,
                            pcAttrValueIn,
                            iDASID);
    if (iRet != MBR_RET_SUCCESS)
    {
        g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                 << "Invalid node name " << pcNodeName
                 << endl;
        cerr << "ERROR: Invalid node name!" << endl;
        xmlFreeDoc(pstDoc);
        return MBR_RET_ERROR;
    }

    /* clean up */
    xmlFreeDoc(pstDoc);

    return MBR_RET_SUCCESS;
}

int MBR_GetAttribute(xmlDocPtr pstDoc,
                     xmlNodePtr pstNode,
                     const char *pcNodeName,
                     const char *pcAttrName,
                     xmlChar *pcAttrValueIn,
                     int iDASIDIn)
{
    xmlChar *pcAttrValue = NULL;
    bool bIsNoMatch = true;
    int iDASID = 0;

    if (0 == xmlStrcmp(pstNode->name, (const xmlChar *) pcNodeName))
    {
        pcAttrValue = xmlGetProp(pstNode, (const xmlChar *) pcAttrName);
        (void) strcpy((char *) pcAttrValueIn, (char *) pcAttrValue);
        xmlFree(pcAttrValue);
    }
    else
    {
        pstNode = pstNode->xmlChildrenNode;
        if (iDASIDIn != 0)
        {
            while (pstNode != NULL)
            {
                if (0 == xmlStrcmp(pstNode->name, MBR_NODE_ROOT_DAS))
                {
                    pcAttrValue = xmlGetProp(pstNode, (const xmlChar *) "id");
                    iDASID = atoi((const char *) pcAttrValue);
                    xmlFree(pcAttrValue);
                    if (iDASIDIn == iDASID)
                    {
                        pcAttrValue = xmlGetProp(pstNode,
                                                 (const xmlChar *) "live");
                        (void) strcpy((char *) pcAttrValueIn,
                                      (char *) pcAttrValue);
                        xmlFree(pcAttrValue);
                        bIsNoMatch = false;
                        break;
                    }
                }
                pstNode = pstNode->next;
            }
        }
        else
        {
            while (pstNode != NULL)
            {
                if (0 == xmlStrcmp(pstNode->name, (const xmlChar *) pcNodeName))
                {
                    pcAttrValue = xmlGetProp(pstNode,
                                             (const xmlChar *) pcAttrName);
                    (void) strcpy((char *) pcAttrValueIn, (char *) pcAttrValue);
                    xmlFree(pcAttrValue);
                    bIsNoMatch = false;
                    break;
                }
                pstNode = pstNode->next;
            }
        }

        if (bIsNoMatch)
        {
            g_ErrLog << "[" << MBR_GetTimestamp() << "] "
                     << "Invalid node name " << pcNodeName
                     << endl;
            cerr << "ERROR: Invalid node name!" << endl;
            return MBR_RET_ERROR;
        }
    }

    return MBR_RET_SUCCESS;
}

