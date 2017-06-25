/*
 * mbr_runterms.cpp
 * Program to create multiple terminals that open ssh sessions to the DAS
 * machines, and based on the input flags, either gives the user a terminal,
 * or runs the mbrdasd terminal monitoring script.
 *
 * Usage: mbrrunterms [options]
 *     -h  --help                 Display this usage information
 *     -d  --das <das_id>         Select the DAS machine.
 *                                (0 for all; 1 - 10 for individuals)
 *     -m  --monitor              Run in monitoring mode.
 *     -s  --size <AxB>           Size of the terminal screen
 *                                (A is the horizontal size in characters,
 *                                 B is the vertical size in lines)
 *     -n  --nonwide              Display terminals for 4:3 aspect ratio
 *                                monitors
 *     -v  --version              Display the version
 *
 * Authors:
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Jayanth Chennamangalam
 *  Yogesh Maan
 */

#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
/* for getopt_long() and related stuff */
/* unlike what the man page for getopt_long() suggests, #define _GNU_SOURCE is
   not needed because the gcc compiler has the definition somewhere in one of
   its header files - and from the GNU mailing list, it seems to be the case
   that even the GCC developers are not sure what to do about it */
#include <getopt.h>

#include "mbr_runterms.h"
#include "mbr_common.h"

extern const char *g_pcVersion;

int main(int argc, char *argv[])
{
    Display *pstDisplay = NULL;
    char acDAS[MBR_MAX_LEN_GENSTRING] = {0};
    char acDASID[MBR_LEN_COUNT+1] = {0};
    int iWidth = 0;
    int iHeight = 0;
    int iScreen = 0;
    int iLeft = 0;
    int iTop = 0;
    int i = 0;
    int j = 0;
    int iDASID = 0;
    int iDASIDIn = 0;
    int iPID[MBR_MAX_DAS] = {0};
    int iPIDCL = 0;
    char *apcCommand[MBR_LEN_EXECVPARRAY] = {NULL};
    bool bMonitor = false;
    bool bWidescreen = true;
    int iSizeX = MBR_SIZE_16_9_X;
    int iSizeY = MBR_SIZE_16_9_Y;
    char *pcSize = NULL;
    char *pcProgName = NULL;
    int iNextOpt = 0;
    /* valid short options */
    const char* const pcShortOpts = "hd:ms:nv";
    /* valid long options */
    const struct option stLongOpts[] = {
        { "help",       0, NULL, 'h' },
        { "das",        1, NULL, 'd' },
        { "monitor",    0, NULL, 'm' },
        { "size",       1, NULL, 's' },
        { "nonwide",    0, NULL, 'n' },
        { "version",    0, NULL, 'v' },
        { NULL,         0, NULL, 0   }
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

            case 'd':   /* -d or --das */
                /* set the DAS ID to which the SSH session has to be opened */
                iDASIDIn = atoi(optarg);
                if ((iDASIDIn < 0) || (iDASIDIn > MBR_MAX_DAS))
                {
                    cerr << "ERROR: DAS ID should be between " << 0 << " and "
                         << MBR_MAX_DAS << "!" << endl;
                    MBR_PrintUsage(pcProgName);
                    return MBR_RET_ERROR;
                }
                break;

            case 'm':   /* -m or --monitor */
                /* run the program in monitoring mode */
                bMonitor = true;
                break;

            case 's':   /* -s or --size */
                /* let the user specify the size of the terminal window */
                pcSize = optarg;    /* size is of the format AxB, where A is the
                                       horizontal size in characters and B is
                                       the vertical size in lines */
                break;

            case 'n':   /* -n or --nonwide */
                /* the monitor aspect ratio is 4:3 */
                bWidescreen = false;
                iSizeX = MBR_SIZE_4_3_X;
                iSizeY = MBR_SIZE_4_3_Y;
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

    /* open the display and get info */
    pstDisplay = XOpenDisplay(NULL);
    iScreen = DefaultScreen(pstDisplay);
    iWidth = DisplayWidth(pstDisplay, iScreen);
    iHeight = DisplayHeight(pstDisplay, iScreen);

    /* allocate memory for the strings required by execvp() */
    for (i = 0; i < (MBR_LEN_EXECVPARRAY - 1); ++i) /* the last element needs
                                                       to be 'NULL' */
    {
        apcCommand[i] = (char *) malloc(sizeof(char) * MBR_MAX_LEN_GENSTRING);
        if (NULL == apcCommand[i])
        {
            cerr << "ERROR: malloc() failed!" << endl;
            for (j = 0; j < i; ++j)
            {
                (void) free(apcCommand[j]);
            }
            return MBR_RET_ERROR;
        }
    }

    if (bMonitor)
    {
        if (bWidescreen)
        {
            iSizeX = MBR_SIZE_16_9_MON_X;
            iSizeY = MBR_SIZE_16_9_MON_Y;
        }
        else
        {
            iSizeX = MBR_SIZE_4_3_MON_X;
            iSizeY = MBR_SIZE_4_3_MON_Y;
        }
    }

    for (i = 0; i < MBR_NUM_ROW; ++i)
    {
        if (bMonitor)
        {
            if (0 == i)     /* first row */
            {
                iTop = (iHeight / MBR_NUM_ROW) * i;
            }
            else            /* last row */
            {
                if (bWidescreen)
                {
                    iTop = ((iHeight / MBR_NUM_ROW) * i)
                           + (MBR_SIZE_16_9_CL_Y * MBR_CHARHEIGHT_IN_PX);
                }
                else
                {
                    iTop = ((iHeight / MBR_NUM_ROW) * i)
                           + (MBR_SIZE_4_3_CL_Y * MBR_CHARHEIGHT_IN_PX);
                }
            }
        }
        else
        {
            iTop = (iHeight / MBR_NUM_ROW) * i;
        }
        for (j = 0; j < MBR_NUM_COL; ++j)
        {
            iLeft = (iWidth / MBR_NUM_COL) * j;
            ++iDASID;
            if ((0 == iDASIDIn) || (iDASIDIn == iDASID))
            {
                MBR_FormatDASID(iDASID, acDASID);
                (void) sprintf(acDAS, "das%s", acDASID);

                (void) strcpy(apcCommand[0], "xterm");
                (void) strcpy(apcCommand[1], "-geometry");
                if (pcSize != NULL) /* user has specified the size */
                {
                    (void) sprintf(apcCommand[2],
                                   "%s+%d+%d",
                                   pcSize,
                                   iLeft,
                                   iTop);
                }
                else                /* use the default size */
                {
                    (void) sprintf(apcCommand[2],
                                   "%dx%d+%d+%d",
                                   iSizeX,
                                   iSizeY,
                                   iLeft,
                                   iTop);
                }
                (void) strcpy(apcCommand[3], "-title");
                (void) sprintf(apcCommand[4], "%s", acDAS);
                (void) strcpy(apcCommand[5], "-e");
                (void) strcpy(apcCommand[6], "ssh");
                if (true == bMonitor)
                {
                    (void) sprintf(apcCommand[7], "%s", acDAS);
                    (void) sprintf(apcCommand[8], "%s", MBR_PATH_TERMDISP);
                }
                else
                {
                    (void) strcpy(apcCommand[7], "-X");
                    (void) sprintf(apcCommand[8], "%s", acDAS);
                }

                iPID[iDASID-1] = fork();
                if (0 == iPID[iDASID-1])    /* child process */
                {
                    (void) execvp(MBR_EXE_XTERM, apcCommand);
                }
            }

            /* reset the acDASID string */
            (void) memset(acDASID, '\0', (MBR_LEN_COUNT + 1));
        }
    }

    if (0 == iDASIDIn)
    {
        if (bMonitor)
        {
            /* create the command line terminal */
            (void) strcpy(apcCommand[0], "xterm");
            (void) strcpy(apcCommand[1], "-geometry");
            if (bWidescreen)
            {
                (void) sprintf(apcCommand[2],
                               "%dx%d+%d+%d",
                               MBR_SIZE_16_9_CL_X,
                               MBR_SIZE_16_9_CL_Y,
                               (iWidth / MBR_NUM_COL),
                               ((iHeight / MBR_NUM_ROW)
                                - ((MBR_SIZE_16_9_CL_Y * MBR_CHARHEIGHT_IN_PX)
                                   / 2)));
            }
            else
            {
                (void) sprintf(apcCommand[2],
                               "%dx%d+%d+%d",
                               MBR_SIZE_4_3_CL_X,
                               MBR_SIZE_4_3_CL_Y,
                               (iWidth / MBR_NUM_COL),
                               ((iHeight / MBR_NUM_ROW)
                                - ((MBR_SIZE_4_3_CL_Y * MBR_CHARHEIGHT_IN_PX)
                                   / 2)));
            }
            (void) strcpy(apcCommand[3], "-title");
            (void) sprintf(apcCommand[4], "M&C");
            for (i = 5; i < (MBR_LEN_EXECVPARRAY - 1); ++i)
            {
                free(apcCommand[i]);
                apcCommand[i] = NULL;
            }

            iPIDCL = fork();
            if (0 == iPIDCL)
            {
                (void) execvp(MBR_EXE_XTERM, apcCommand);
            }

            /* clean up */
            for (i = 0; i < 5; ++i)
            {
                free(apcCommand[i]);
            }
        }
    }
    else
    {
        /* clean up */
        for (i = 0; i < (MBR_LEN_EXECVPARRAY - 1); ++i)
        {
            free(apcCommand[i]);
        }
    }

    /* close the display */
    (void) XCloseDisplay(pstDisplay);

    return MBR_RET_SUCCESS;
}

void MBR_FormatDASID(int iCount, char acCount[])
{
    char acTemp[2] = {0};
    int iDigits[MBR_LEN_COUNT] = {0};
    int iNumDigits = 0;
    int i = 0;

    /* convert iCount to acCount */
    for (i = 0; i < MBR_LEN_COUNT; ++i)
    {
        if (0 == (iCount / 10))
        {
            iDigits[i] = iCount % 10;
            iNumDigits = i + 1;
            break;
        }
        else
        {
            iDigits[i] = iCount % 10;
            iCount = iCount / 10;
        }
    }

    for (i = (MBR_LEN_COUNT - iNumDigits); i > 0; --i)
    {
        (void) strcat(acCount, "0");
    }

    for (i = iNumDigits; i > 0; --i)
    {
        (void) sprintf(acTemp, "%d", iDigits[i-1]);
        (void) strcat(acCount, acTemp);
    }

    return;
}

void MBR_PrintUsage(const char *pcProgName)
{
    cout << "Usage: " << pcProgName << " [options]" << endl;
    cout << "    -h  --help                 Display this usage information"
         << endl;
    cout << "    -d  --das <das_id>         Select the DAS machine"
         << endl;
    cout << "                               (0 for all; 1 - 10 for individuals)"
         << endl;
    cout << "    -m  --monitor              Run in monitoring mode"
         << endl;
    cout << "    -s  --size <AxB>           Size of the terminal screen"
         << endl;
    cout << "                               (A is the horizontal size in "
         << "characters," << endl;
    cout << "                                B is the vertical size in lines)"
         << endl;
    cout << "    -n  --nonwide              Display terminals for 4:3 aspect "
         << "ratio monitors"
         << endl;
    cout << "    -v  --version              Display the version"
         << endl;

    return;
}

