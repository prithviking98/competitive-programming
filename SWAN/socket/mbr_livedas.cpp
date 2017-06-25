/*
 * mbr_livedas.cpp
 * Program to update the live status of DAS machines
 *
 * Usage: mbrlivedas [options]
 *     -h  --help                 Display this usage information
 *     -v  --version              Display the version
 *
 * Created by Jayanth Chennamangalam
 */

#include <iostream>
/* for getopt_long() and related stuff */
/* unlike what the man page for getopt_long() suggests, #define _GNU_SOURCE is
   not needed because the gcc compiler has the definition somewhere in one of
   its header files - and from the GNU mailing list, it seems to be the case
   that even the GCC developers are not sure what to do about it */
#include <getopt.h>

#include "mbr_common.h"
#include "mbr_config.h"

extern const char *g_pcVersion;

void MBR_PrintUsage(const char *pcProgName);

int main(int argc, char *argv[])
{
    int iRet = MBR_RET_SUCCESS;
    int iNumDownDAS = 0;
    int i = 0;
    int j = 0;
    bool bLiveDAS[MBR_MAX_DAS] = {0};
    int iDeadDAS[MBR_MAX_DAS] = {0};
    char acLive[MBR_MAX_LEN_GENSTRING] = {0};
    char *pcProgName = NULL;
    int iNextOpt = 0;
    /* valid short options */
    const char* const pcShortOpts = "hv";
    /* valid long options */
    const struct option stLongOpts[] = {
        { "help",       0, NULL, 'h' },
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

    /* initialise the live DAS array */
    for (i = 0; i < MBR_MAX_DAS; ++i)
    {
        bLiveDAS[i] = true;
    }

    cout << "This program will help you update the list of live DAS machines."
         << endl;

    cout << "How many DAS machines are down?"
         << endl;
    cin >> iNumDownDAS;
    /* validate user input */
    if ((iNumDownDAS < 0) || (iNumDownDAS > MBR_MAX_DAS))
    {
        cerr << "Invalid number of dead DAS machines!" << endl;
        return MBR_RET_ERROR;
    }

    if (MBR_MAX_DAS == iNumDownDAS)
    {
        for (i = 0; i < iNumDownDAS; ++i)
        {
            bLiveDAS[i] = false;
        }
    }
    else
    {
        cout << "Enter the IDs of the dead DAS machines, each followed by a return:"
             << endl;
        for (i = 0; i < iNumDownDAS; ++i)
        {
            cin >> iDeadDAS[i];
            /* validate user input */
            if ((iDeadDAS[i] <= 0) || (iDeadDAS[i] > MBR_MAX_DAS))
            {
                cerr << "Invalid DAS ID!" << endl;
                return MBR_RET_ERROR;
            }
            /* make sure that the user has not made a duplicate entry */
            for (j = 0; j < i; ++j)
            {
                if (iDeadDAS[i] == iDeadDAS[j])
                {
                    cerr << "Duplicate DAS ID! Enter DAS ID again:" << endl;
                    cin >> iDeadDAS[i];
                    /* make sure that the user has not repeated the entry */
                    j = 0;
                    continue;
                }
            }
            bLiveDAS[iDeadDAS[i]-1] = false;
        }
    }

    for (i = 0; i < MBR_MAX_DAS; ++i)
    {
        (void) strcpy(acLive,
                      (bLiveDAS[i] ? MBR_XML_LIVE_YES : MBR_XML_LIVE_NO));
        iRet = MBR_ConfigEntry(MBR_CONFIG_UPDATE,
                               MBR_CFG_MC,
                               MBR_XML_ENT_DAS,
                               MBR_XML_ATT_LIVE,
                               (i + 1),
                               (char *) acLive);
        if (iRet != MBR_RET_SUCCESS)
        {
            cerr << "ERROR: Configuration file update failed!" << endl;
            return iRet;
        }
    }

    return MBR_RET_SUCCESS;
}

void MBR_PrintUsage(const char *pcProgName)
{
    cout << "Usage: " << pcProgName << " [options]" << endl;
    cout << "    -h  --help                 Display this usage information"
         << endl;
    cout << "    -v  --version              Display the version"
         << endl;

    return;
}

