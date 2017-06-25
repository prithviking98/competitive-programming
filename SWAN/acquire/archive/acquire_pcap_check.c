/*
 * acquire_pcap_check.c
 * Program to check the status of the FPGA transmitter by sniffing packets
 * and checking if they contain data.
 *
 * Usage: acquire_pcap_check <dev_name>
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
#define SIZE_FULL_PACKET    (SIZE_PACKET + 42)
#define MAX_NUM_PKTSPERFILE 100
#define TIMEOUT             1000
#define MODE_PROMISC        1
#define LEN_DATAHEADER      28
#define MAX_NUM_SLIPS       2000
#define MAX_NUM_INFOITEMS   3
#define POS_PREV            0
#define POS_CURRENT         1
#define POS_PKTCOUNT        2
#define MBR_PCAP_USER           ((unsigned char *) "das01")

typedef unsigned char BYTE;

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket);

int g_iPacketCount = 0;
int g_iCurrentMarker = 0;
int g_iPrevMarker = 0;
int g_iSlipCount = 0;
int g_aiSlips[MAX_NUM_SLIPS][MAX_NUM_INFOITEMS] = {{0}};
pcap_t *g_pstHandle = NULL;

int main(int argc, char *argv[])
{
    char acErrBuf[PCAP_ERRBUF_SIZE] = {0};
    char *pcDevice = NULL;
    int iRet = 0;

    pcDevice = argv[1];

    g_pstHandle = pcap_open_live(pcDevice,
                                SIZE_FULL_PACKET,
                                MODE_PROMISC,
                                TIMEOUT,
                                acErrBuf);
    if (NULL == g_pstHandle)
    {
        fprintf(stderr, "%s\n", acErrBuf);

        return -1;
    }

    iRet = pcap_loop(g_pstHandle, -1, ProcessPacket, MBR_PCAP_USER);
    if (-1 == iRet)
    {
        fprintf(stderr, "ERROR: pcap_loop() failed!\n");

        /* clean up */
        pcap_close(g_pstHandle);

        return -1;
    }
    else if (-2 == iRet)
    {
        /* pcap_breakloop() encountered, so continue */
    }

    /* clean up */
    pcap_close(g_pstHandle);

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
    BYTE *pbMarkerPos = NULL;
    int i = 0;

    assert(pcUser != NULL);
    assert(pstPacketHeader != NULL);
    assert(pbPacket != NULL);

    stHeaderEth = (struct ether_header*) pbPacket;
    stHeaderIP  = (struct iphdr*) (pbPacket + sizeof(struct ether_header));
    stHeaderUDP = (struct udphdr*) (((BYTE *) stHeaderIP)
                                    + sizeof (struct iphdr));
    pbData = (BYTE *) (((BYTE *) stHeaderUDP) + sizeof (struct udphdr));

    pbMarkerPos = pbData + LEN_DATAHEADER; 
    g_iCurrentMarker = (unsigned int) ntohl((*(unsigned int *)pbMarkerPos));
    if (g_iPacketCount != 0)
    {
        /* this is not the first packet */
        if (g_iCurrentMarker != (g_iPrevMarker + 1))
        {
            g_aiSlips[g_iSlipCount][POS_PREV] = g_iPrevMarker;
            g_aiSlips[g_iSlipCount][POS_CURRENT] = g_iCurrentMarker;
            g_aiSlips[g_iSlipCount][POS_PKTCOUNT] = g_iPacketCount;
            ++g_iSlipCount;
            if (MAX_NUM_SLIPS == g_iSlipCount)
            {
                printf("Slip count exceeded limit! Wrapping around!\n");
                g_iSlipCount = 0;
            }
        }
    }
    g_iPrevMarker = g_iCurrentMarker;

    /* increment the packet count and check the limit */
    ++g_iPacketCount;
    if (MAX_NUM_PKTSPERFILE == g_iPacketCount)
    {
        printf("%d slips detected!\n", g_iSlipCount);

        for (i = 0; i < g_iSlipCount; ++i)
        {
            printf("Slip detected! ");
            printf("Previous = %x, current = %x, diff = %d, "
                   "packet count = %d\n",
                   g_aiSlips[i][POS_PREV],
                   g_aiSlips[i][POS_CURRENT],
                   (g_aiSlips[i][POS_CURRENT] - g_aiSlips[i][POS_PREV]),
                   g_aiSlips[i][POS_PKTCOUNT]);
        }
        printf("%d packets processed.\n", g_iPacketCount);
        pcap_breakloop(g_pstHandle);
        return;
    }

    return;
}

