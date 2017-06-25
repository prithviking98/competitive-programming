/* acquire.c
 * Program to read raw socket packets using the pcap library and write them to 
 * file.
 * Compile: gcc -o rawpcap rawpcap.c -Wall -lpcap
 * pep/10apr08
 * Modified by Jayanth Chennamangalam on 2008.04.23
 * desh: bytes to be written changed to 1030 instead of 1024   2008.04.24; 17:27
 * Modified by Jayanth Chennamangalam on 2008.04.26 - writing to multiple files
 *     and cosmetic changes, also changed filename from rawpcap.c to acquire.c
 */

//TODO: filename in DASName+PulsarName+JD+DateTime format
//TODO: adding header

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pcap.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define MAX_LEN_FILENAME    32
#define MAX_SIZE_PACKET     65536
#define MAX_SIZE_FILE       ((unsigned int) 2048 * 1024 * 1024)
#define SIZE_PACKET         1030
#define MAX_NUM_PKTSPERFILE (MAX_SIZE_FILE/SIZE_PACKET)
#define MAX_NUM_FILES       100
#define FILENAME_PREFIX     "packet"
#define TIMEOUT             1000
#define MODE_PROMISC        1

typedef unsigned char BYTE;

int OpenFiles();
void CloseFiles();
void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket);

FILE *g_apfFiles[MAX_NUM_FILES] = {NULL};
FILE *g_pfCurrentFile = NULL;
int g_iNumFiles = 0;
int g_iCurrentFileIndex=0;
int g_iPacketCount = 0;
pcap_t *g_stHandle = NULL;

int main(int argc, char *argv[])
{
    char acErrBuf[PCAP_ERRBUF_SIZE] = {0};
    char *pcDevice = NULL;
    int iRet = 0;

    pcDevice = argv[1];
    g_iNumFiles = atoi(argv[2]);
    if ((g_iNumFiles < 1) || (g_iNumFiles > MAX_NUM_FILES))
    {
        printf("ERROR: Number of files should be at least 1 ");
        printf("and not more than %d!\n", MAX_NUM_FILES);
        return -1;
    }

    iRet = OpenFiles();
    if (iRet != 0)
    {
        printf("ERROR: Error opening files!\n");
        return -1;
    }

    g_stHandle = pcap_open_live(pcDevice,
                              MAX_SIZE_PACKET,
                              MODE_PROMISC,
                              TIMEOUT,
                              acErrBuf);
    if (NULL == g_stHandle)
    {
        fprintf(stderr, "%s\n", acErrBuf);

        /* clean up */
        CloseFiles();

        return -1;
    }

    iRet = pcap_loop(g_stHandle, -1, ProcessPacket, 0);
    if (-1 == iRet)
    {
        fprintf(stderr, "ERROR: pcap_loop() failed!\n");

        /* clean up */
        pcap_close(g_stHandle);
        CloseFiles();

        return -1;
    }
    else if (-2 == iRet)
    {
        /* pcap_breakloop() encountered, so continue */
    }

    /* clean up */
    pcap_close(g_stHandle);
    CloseFiles();

    return 0;
}

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket)
{
    struct ether_header *stHeaderEth = NULL;
    struct iphdr *stHeaderIP = NULL;
    struct udphdr *stHeaderUDP = NULL;
    BYTE *pbData = NULL;

    //assert(pcUser != NULL);
    assert(pstPacketHeader != NULL);
    assert(pbPacket != NULL);

    stHeaderEth = (struct ether_header*) pbPacket;
    stHeaderIP  = (struct iphdr*) (pbPacket + sizeof(struct ether_header));
    stHeaderUDP = (struct udphdr*) (((BYTE *) stHeaderIP)
                                    + sizeof (struct iphdr));
    pbData = (BYTE *) (((BYTE *) stHeaderUDP) + sizeof (struct udphdr));

    (void) fwrite(pbData, SIZE_PACKET, 1, g_pfCurrentFile);

    /* increment the packet count, check the limit, and set the current file
       pointer if necessary */
    ++g_iPacketCount;
    if (g_iPacketCount >= MAX_NUM_PKTSPERFILE)
    {
        ++g_iCurrentFileIndex;
        if (g_iCurrentFileIndex == g_iNumFiles)
        {
            printf("Stopping data acquisition...\n");
            pcap_breakloop(g_stHandle);
            return;
        }
        g_pfCurrentFile = g_apfFiles[g_iCurrentFileIndex];
        g_iPacketCount = 0;
        printf("Writing to file %s%d\n", FILENAME_PREFIX, g_iCurrentFileIndex);
    }

#if 0
    if (0 == (g_iPacketCount % 10))
    {
        printf(".");
        fflush(stdout);
    }
#endif

    return;
}

int OpenFiles()
{
    int i = 0;
    char acFilename[MAX_LEN_FILENAME] = {0};

    for (i = 0; i < g_iNumFiles; ++i)
    {
        (void) sprintf(acFilename, FILENAME_PREFIX "%d", i);
        g_apfFiles[i] = fopen(acFilename, "w");
        if (NULL == g_apfFiles[i])
        {
            perror("fopen");
            return -1;
        }
    }

    /* set the current file pointer to the first file pointer */
    g_pfCurrentFile = g_apfFiles[0];

    return 0;
}

void CloseFiles()
{
    int i = 0;

    for (i = 0; i < g_iNumFiles; ++i)
    {
        fclose(g_apfFiles[i]);
    }

    return;
}

