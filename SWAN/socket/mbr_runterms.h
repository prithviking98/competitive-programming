/*
 * mbr_runterms.h
 * Header file for mbr_runterms
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Jayanth Chennamangalam
 *  Yogesh Maan
 */

#ifndef __MBR_RUNTERMS_H__
#define __MBR_RUNTERMS_H__

#define MBR_NUM_ROW             2
#define MBR_NUM_COL             5

/* 17" 4:3 without command line */
#define MBR_SIZE_4_3_X          37
#define MBR_SIZE_4_3_Y          34

/* 17" 4:3 with command line */
#define MBR_SIZE_4_3_MON_X      40
#define MBR_SIZE_4_3_MON_Y      28

/* 17" 4:3 command line */
#define MBR_SIZE_4_3_CL_X       211
#define MBR_SIZE_4_3_CL_Y       11

/* 17" 16:9 without command line */
#define MBR_SIZE_16_9_X         43
#define MBR_SIZE_16_9_Y         25

/* 17" 16:9 with command line */
#define MBR_SIZE_16_9_MON_X     43
#define MBR_SIZE_16_9_MON_Y     18

/* 17" 16:9 command line */
#define MBR_SIZE_16_9_CL_X      225
#define MBR_SIZE_16_9_CL_Y      11

/* height of a character in pixels, at default resolution */
#if 0
/* 17" 4:3 */
#define MBR_CHARHEIGHT_IN_PX    16
#endif

/* 17" 16:9 */
#define MBR_CHARHEIGHT_IN_PX    12

#define MBR_LEN_COUNT           2

#define MBR_LEN_EXECVPARRAY     10

#define MBR_MAX_DAS             10

#define MBR_EXE_XTERM           (char *) "xterm"

#define MBR_PATH_TERMDISP       "/home/das/scripts/mbr_termdisp.sh"

void MBR_FormatDASID(int iCount, char acCount[]);
void MBR_PrintUsage(const char *pcProgName);

#endif  /* __MBR_RUNTERMS_H__ */

