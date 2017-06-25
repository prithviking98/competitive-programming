/* acquire_rawsock_shm.c
 * Program to read raw socket packets and write them to shared memory.
 *
 * Compile: gcc acquire_rawsock_shm.c -lpcap -o acquire_rawsock_shm
 *
 * pep/10apr08
 * Modified by Jayanth Chennamangalam on 2008.04.23
 * desh: bytes to be written changed to 1030 instead of 1024   2008.04.24; 17:27
 * Modified by Jayanth Chennamangalam on 2008.04.26 - writing to multiple files
 *     and cosmetic changes, also changed filename from rawpcap.c to acquire.c
 * desh: bytes to be written changed to 1056 instead of 1030, as marker bytes
 *     are increased to 26; 2008.05.01; 18:22
 *     the 26 bytes of Marker may contain some FFFFFs and 00000s,
 *     followed by a name of the DAS etc.
 *     the GPS 1-sec pulse count then follows with 2 bytes, and then a
 *     4-byte packet counter value.
 *     Thus 32 total bytes preceed 1024 bytes of data.. making
 *     the (non-udp) packet size of interest as 1056
 * Modified by Jayanth Chennamangalam on 2008.05.07 - writing to shared memory
 *     segments instead of files, renamed file from acquire_1056bytes.c
 */

//TODO: adding header

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
#define SIZE_PKTBUFFER      1098
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

    iSocket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    //iSocket = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
    //iSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //iSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == iSocket)
    {
        perror("socket");
        return -1;
    }

#if 1
    (void) strncpy(stIFReq.ifr_name, argv[1], IFNAMSIZ);

    iRet = ioctl(iSocket, SIOCGIFINDEX, &stIFReq);
    if (-1 == iRet)
    {
        perror("ioctl, get");
        return -1;
    }
#endif

#if 1
    /* get socket configuration flags */
    iRet = ioctl(iSocket, SIOCGIFFLAGS, &stIFReq);
    if (-1 == iRet)
    {
        perror("ioctl, get");
        return -1;
    }

    /* add IFF_PROMISC to socket configuration flags */
    stIFReq.ifr_ifru.ifru_flags |= IFF_PROMISC;
    iRet = ioctl(iSocket, SIOCSIFFLAGS, &stIFReq);
    if (-1 == iRet)
    {
        perror("ioctl, set");
        return -1;
    }
#endif

    /* create the shminfo data structure in shared memory */
    printf("Creating shminfo...");
    fflush(stdout);
    pstShmInfo = DAS_CreateShmInfo(DAS_KEY_FL_OUT, DAS_PID_FL);
    if (NULL == pstShmInfo)
    {
        printf("ERROR in ShmAlloc() for pstShmInfo\n");

        /* clean up */
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        (void) close(iSocket);

        return -1;
    }
    printf("DONE\n");

    /* create buffers */
    for (i = 0; i < DAS_NUM_BUFS; ++i)
    {
        printf("Creating block %d...", iBlockID);
        fflush(stdout);
        stBlockAdds[i] = DAS_CreateBlock(iBlockID,
                                           DAS_KEY_FL_OUT,
                                           pstShmInfo,
                                           DAS_PID_FL);
        pstBlock = stBlockAdds[i].pstBlock;
        if (NULL == pstBlock)
        {
            printf("ERROR in DAS_CreateBlock() for block %d\n", iBlockID);

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            (void) close(iSocket);

            return -1;
        }
        pBufBase[i] = stBlockAdds[i].pData;
        /* initially, set the data flag to DAS_STATUS_NOP */
        stBlockAdds[i].pstBlock->iFlagData = DAS_STATUS_NOP;
        printf("DONE\n");
        ++iBlockID;
    }

    /* the first buffer will be written to now, so set the data flag
       to DAS_STATUS_FRESH */
    stBlockAdds[0].pstBlock->iFlagData = DAS_STATUS_FRESH;

    /* set the base and write pointers to the first buffer */
    iBuffer = 0;
    pBasePointer = stBlockAdds[0].pData;
    pWritePointer = stBlockAdds[0].pData;

    /* set the status flag to DAS_STATUS_WRITESTART */
    pstShmInfo->iStatus = DAS_STATUS_WRITESTART;

    while (DAS_TRUE)
    {
        (void) read(iSocket, abPacketBuffer, SIZE_PKTBUFFER);

        stHeaderEth = (struct ether_header *) abPacketBuffer;
        stHeaderIP  = (struct iphdr *) (abPacketBuffer
                                        + sizeof(struct ether_header));
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

        /* if the end of the buffer is reached, reset the write pointer
           to the base pointer of the next buffer */
        if ((pWritePointer - pBasePointer) == DAS_SIZE_SHM_DATA)
        {
            ++iBufferChange;
            if (iBuffer != (DAS_NUM_BUFS - 1))    /* not the last buffer */
            {
                ++iBuffer;
            }
            else    /* the current buffer is the last buffer */
            {
                iBuffer = 0;
            }
            if ((DAS_STATUS_FRESH == stBlockAdds[iBuffer].pstBlock->iFlagData))
            {
                printf("ERROR: Overwriting buffer %d at packet number %d!\n",
                       iBuffer,
                       iPacketCount);
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
            stBlockAdds[iBuffer].pstBlock->iFlagData = DAS_STATUS_FRESH;
            pBasePointer = stBlockAdds[iBuffer].pData;
            pWritePointer = stBlockAdds[iBuffer].pData;
        }

        /* write to shared memory */
        (void) memcpy(pWritePointer, pbData, SIZE_PACKET);
        pWritePointer += SIZE_PACKET;
        pstShmInfo->iWrittenData += SIZE_PACKET;

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

    /* set the status flag to DAS_STATUS_WRITEDONE */
    pstShmInfo->iStatus = DAS_STATUS_WRITEDONE;

    /* clean up */
    /* delete buffers */    
    iBlockID = DAS_BLOCKID_START;
    for (i = 0; i < DAS_NUM_BUFS; ++i)
    {
        iRet = shmdt(stBlockAdds[i].pData);
        if (iRet != 0)
        {
            printf("ERROR in shmdt() for data in block %d: ", iBlockID);
            fflush(stdout);
            perror("");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            (void) close(iSocket);

            return -1;
        }
        iRet = shmdt(stBlockAdds[i].pstBlock);
        if (iRet != 0)
        {
            printf("ERROR in shmdt() for block %d: ", iBlockID);
            fflush(stdout);
            perror("");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            (void) close(iSocket);
    
            return -1;
        }
        ++iBlockID;
    }

    iRet = shmdt(pstShmInfo);
    if (iRet != 0)
    {
        perror("ERROR in shmdt() for pstShmInfo");

        /* clean up */
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        (void) close(iSocket);

        return -1;
    }

    (void) close(iSocket);

    return 0;
}

