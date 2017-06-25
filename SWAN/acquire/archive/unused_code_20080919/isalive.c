/* isalive.c
 * Libpcap program to check if packets are coming on the wire. If packets are
 *     being received, periods ('.') are printed, else nothing is printed.
 *     TODO: Add timeout.
 *
 *  Usage: isalive <dev_name>
 * 
 * Created by Jayanth Chennamangalam
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

