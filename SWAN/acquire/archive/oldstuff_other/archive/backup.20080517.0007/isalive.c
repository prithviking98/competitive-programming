/* acquire_1056_check.c
 * Program to read raw socket packets using the pcap library and write them to 
 * file.
 * Compile: gcc -o rawpcap rawpcap.c -Wall -lpcap
 * pep/10apr08
 * Modified by Jayanth Chennamangalam on 2008.04.23
 * desh: bytes to be written changed to 1030 instead of 1024   2008.04.24; 17:27
 * Modified by Jayanth Chennamangalam on 2008.04.26 - writing to multiple files
 *     and cosmetic changes, also changed filename from rawpcap.c to acquire.c
 * desh: bytes to be written changed to 1056 instead of 1030, as marker bytes are increased to 26; 2008.05.01; 18:22
 * the 26 bytes of Marker may contain some FFFFFs and 00000s, followed by a name of the DAS etc.
 * the GPS 1-sec pulse count then follows with 2 bytes, and then a 4-byte packet counter value.
 * Thus 32 total bytes preceed 1024 bytes of data.. making the (non-udp) packet size of interest as 1056
 * Modified by Jayanth Chennamangalam on 2008.05.07 - this program reads the
 * captured packets and checks for marker sequentiality
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pcap.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define SIZE_PACKET         1056
#define MAX_SIZE_FILE       (100 * SIZE_PACKET)
#define SIZE_FULL_PACKET    (SIZE_PACKET + 42)
#define MAX_NUM_PKTSPERFILE (MAX_SIZE_FILE/SIZE_PACKET)
#define TIMEOUT             1000
#define MODE_PROMISC        1

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket);

int g_iPacketCount = 0;
pcap_t *g_stHandle = NULL;

int main(int argc, char *argv[])
{
    char acErrBuf[PCAP_ERRBUF_SIZE] = {0};
    char *pcDevice = NULL;
    int iRet = 0;

    pcDevice = argv[1];

    g_stHandle = pcap_open_live(pcDevice,
                                SIZE_FULL_PACKET,
                                MODE_PROMISC,
                                TIMEOUT,
                                acErrBuf);
    if (NULL == g_stHandle)
    {
        fprintf(stderr, "%s\n", acErrBuf);

        return -1;
    }

    iRet = pcap_loop(g_stHandle, -1, ProcessPacket, 0);
    if (-1 == iRet)
    {
        fprintf(stderr, "ERROR: pcap_loop() failed!\n");

        /* clean up */
        pcap_close(g_stHandle);

        return -1;
    }
    else if (-2 == iRet)
    {
        /* pcap_breakloop() encountered, so continue */
    }

    /* clean up */
    pcap_close(g_stHandle);

    return 0;
}

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket)
{
    //assert(pcUser != NULL);
    assert(pstPacketHeader != NULL);
    assert(pbPacket != NULL);

    printf(".");
    fflush(stdout);

    /* increment the packet count and check the limit */
    ++g_iPacketCount;
    if (MAX_NUM_PKTSPERFILE == g_iPacketCount)
    {
        printf("%d packets processed.\n", g_iPacketCount);
        pcap_breakloop(g_stHandle);
        return;
    }

    return;
}

