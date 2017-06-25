/* acquire_rawsock_check.c
 * Raw socket program to check incoming packets for slips.
 *
 * Usage: acquire_rawsock_check <dev_name>
 *
 * Older programs modified by Jayanth Chennamangalam for raw socket acquisition
 *     instead of libpcap-based acquisition
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

#include "das.h"
#include "das_shm.h"

#define MAX_SIZE_FILE       (99 * DAS_SIZE_SHM_DATA)
#define SIZE_PACKET         1056
#define SIZE_FULL_PACKET    (SIZE_PACKET + 42)
#define MAX_NUM_PKTSPERFILE (MAX_SIZE_FILE/SIZE_PACKET)
#define LEN_DATAHEADER      28
#define MAX_NUM_SLIPS       2000
#define MAX_NUM_INFOITEMS   3
#define POS_PREV            0
#define POS_CURRENT         1
#define POS_PKTCOUNT        2
/* this should be an integral multiple of SIZE_FULL_PACKET */
/* WARNING: Keep it equal to SIZE_FULL_PACKET! */
#define SIZE_PKTBUFFER      SIZE_FULL_PACKET
#define NUM_PKTSPERBUFFER   (SIZE_PKTBUFFER/SIZE_FULL_PACKET)

int main(int argc, char *argv[])
{
    int iRet = 0;
    DAS_BLOCK_S *pstBlock = NULL;
    int iBlockID = DAS_BLOCKID_START;   /* first block */
    struct ether_header *stHeaderEth = NULL;
    struct iphdr *stHeaderIP = NULL;
    struct udphdr *stHeaderUDP = NULL;
    DAS_BYTE *pbData = NULL;
    DAS_BYTE *pbMarkerPos = NULL;
    int iPacketCount = 0;
    int iCurrentMarker = 0;
    int iPrevMarker = 0;
    int iSlipCount = 0;
    int iBuffer = 0;
    int aiSlips[MAX_NUM_SLIPS][MAX_NUM_INFOITEMS] = {{0}};
    int iBufferChange = 0;
    DAS_BLOCKADDS_S stBlockAdds[DAS_NUM_BUFS] = {{0}};
    DAS_SHM_DATATYPE *pBufBase[DAS_NUM_BUFS] = {NULL};
    DAS_SHM_DATATYPE *pBasePointer = NULL;
    DAS_SHM_DATATYPE *pWritePointer = NULL;
    DAS_SHMINFO_S *pstShmInfo = NULL;
    DAS_BYTE abPacketBuffer[SIZE_PKTBUFFER] = {0};
    struct ifreq stIFReq = {{{0}}};
    int iSocket = 0;
    int i = 0;

    /* CASE 1: SOCK_RAW gives the whole packet, including the Ethernet header */
    iSocket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    /* CASE 2: SOCK_DGRAM gives the packet starting from the IP header */
    #if 0
    iSocket = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
    #endif
    if (-1 == iSocket)
    {
        perror("socket");
        return -1;
    }

    (void) strncpy(stIFReq.ifr_name, argv[1], IFNAMSIZ);

    iRet = ioctl(iSocket, SIOCGIFINDEX, &stIFReq);
    if (-1 == iRet)
    {
        perror("ioctl, SIOCGIFINDEX");
        return -1;
    }

    /* get socket configuration flags */
    iRet = ioctl(iSocket, SIOCGIFFLAGS, &stIFReq);
    if (-1 == iRet)
    {
        perror("ioctl, SIOCGIFFLAGS");
        return -1;
    }

    /* add IFF_PROMISC to socket configuration flags */
    stIFReq.ifr_ifru.ifru_flags |= IFF_PROMISC;
    iRet = ioctl(iSocket, SIOCSIFFLAGS, &stIFReq);
    if (-1 == iRet)
    {
        perror("ioctl, SIOCSIFFLAGS");
        return -1;
    }

    printf("Grabbing packets and checking them for slips...\n");
    while (DAS_TRUE)
    {
        (void) read(iSocket, abPacketBuffer, SIZE_PKTBUFFER);

        stHeaderEth = (struct ether_header *) abPacketBuffer;
        stHeaderIP  = (struct iphdr *) (abPacketBuffer
                                        + sizeof(struct ether_header));
        /* uncomment this for CASE 2 */
        #if 0
        stHeaderIP  = (struct iphdr *) abPacketBuffer;
        #endif
        stHeaderUDP = (struct udphdr *) (((DAS_BYTE *) stHeaderIP)
                                         + sizeof (struct iphdr));
        pbData = (DAS_BYTE *) (((DAS_BYTE *) stHeaderUDP)
                               + sizeof (struct udphdr));

        pbMarkerPos = pbData + LEN_DATAHEADER;
        iCurrentMarker = (unsigned int) ntohl((*(unsigned int *) pbMarkerPos));

        if (iPacketCount != 0)
        {
            /* this is not the first packet */

            if (iCurrentMarker != (iPrevMarker + NUM_PKTSPERBUFFER))
            {
                aiSlips[iSlipCount][POS_PREV] = iPrevMarker;
                aiSlips[iSlipCount][POS_CURRENT] = iCurrentMarker;
                aiSlips[iSlipCount][POS_PKTCOUNT] = iPacketCount;
                ++iSlipCount;
                if (MAX_NUM_SLIPS == iSlipCount)
                {
                    printf("Slip count exceeded limit! Wrapping around!\n");
                    iSlipCount = 0;
                }
            }
        }
        iPrevMarker = iCurrentMarker;

        /* increment the packet count, check the limit, and set the current file
           pointer if necessary */
        ++iPacketCount;
        if (MAX_NUM_PKTSPERFILE == iPacketCount)
        {
            printf("Stopping data acquisition...\n");
            printf("%d slips detected!\n", iSlipCount);

            for (i = 0; i < iSlipCount; ++i)
            {
                printf("Slip detected! ");
                printf("Previous = %X, current = %X, diff = %d\n",
                       aiSlips[i][POS_PREV],
                       aiSlips[i][POS_CURRENT],
                       (aiSlips[i][POS_CURRENT] - aiSlips[i][POS_PREV]));
            }
            printf("%d packets processed.\n", iPacketCount);
            printf("%d buffer changes.\n", iBufferChange);
            break;
        }
    }

    (void) close(iSocket);

    return 0;
}

