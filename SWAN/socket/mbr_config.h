/*
 * mbr_config.h
 * MBR configuration file management module header file
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_CONFIG_H__
#define __MBR_CONFIG_H__

#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define MBR_NODE_TEXT       ((const xmlChar *) "#text")
#define MBR_NODE_ROOT_DAS   ((const xmlChar *) "das")
#define MBR_NODE_ROOT_MC    ((const xmlChar *) "mc")
#define MBR_PATH_XML_DAS    "/config/mbr_das.xml"
#define MBR_PATH_XML_MC     "/config/mbr_mc.xml"
#define MBR_CMD_VALIDATE    "xmllint --valid --noout "

int MBR_ConfigEntry(int iAction,
                    int iCfgFile,
                    const char *pcNodeName,
                    const char *pcAttrName,
                    int iDASID,
                    char *pcAttrValue);
int UpdateConfigFile(const char *pcConfigFile,
                     const char *pcNodeName,
                     const char *pcAttrName,
                     int iDASIDIn,
                     const char *pcValue);
int MBR_ParseDoc(const char *pcConfigFile,
                  const char *pcNodeName,
                  const char *pcAttrName,
                  int iDASID,
                  xmlChar *pcAttrValueIn);
int MBR_GetAttribute(xmlDocPtr pstDoc,
                     xmlNodePtr pstNode,
                     const char *pcNodeName,
                     const char *pcAttrName,
                     xmlChar *pcAttrValueIn,
                     int iDASIDIn);
#endif  /* __MBR_CONFIG_H__ */

