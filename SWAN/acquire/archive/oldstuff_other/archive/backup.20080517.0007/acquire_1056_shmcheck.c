/* acquire_1056_shm.c
 * Program to read raw socket packets using the libpcap library and
 *     write them to shared memory.
 *
 * Compile: gcc acquire_1056_shm.c -lpcap -o acquire_1056_shm
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
#include <pcap.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#include "das.h"
#include "das_shm.h"

//#define MAX_SIZE_FILE       ((unsigned int) 2048 * 1024 * 1024)
#define MAX_SIZE_FILE       (99 * DAS_SIZE_SHM_DATA)
#define SIZE_PACKET         1056
#define SIZE_FULL_PACKET    (SIZE_PACKET + 42)
#define MAX_NUM_PKTSPERFILE (MAX_SIZE_FILE/SIZE_PACKET)
#define TIMEOUT             1000
#define MODE_PROMISC        1
#define LEN_DATAHEADER      28
#define MAX_NUM_SLIPS       2000
#define MAX_NUM_INFOITEMS   3
#define POS_PREV            0
#define POS_CURRENT         1
#define POS_PKTCOUNT        2
#define PCAP_USER           ((unsigned char *) "das1")
#define SIZE_PKTBUFFER      105600

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket);

int g_iPacketCount = 0;
int g_iCurrentMarker = 0;
int g_iPrevMarker = 0;
int g_iSlipCount = 0;
int g_iBuffer = 0;
int g_aiSlips[MAX_NUM_SLIPS][MAX_NUM_INFOITEMS] = {{0}};
int g_iFirstIter = DAS_TRUE;
int g_iBufferChange = 0;
pcap_t *g_stHandle = NULL;
DAS_BLOCKADDS_S g_stBlockAdds[DAS_NUM_BUFS] = {{0}};
DAS_SHM_DATATYPE *g_pBufBase[DAS_NUM_BUFS] = {NULL};
DAS_SHM_DATATYPE *g_pBasePointer = NULL;
DAS_SHM_DATATYPE *g_pWritePointer = NULL;
DAS_SHMINFO_S *g_pstShmInfo = NULL;

int main(int argc, char *argv[])
{
    char acErrBuf[PCAP_ERRBUF_SIZE] = {0};
    char *pcDevice = NULL;
    int iRet = 0;
    DAS_BLOCK_S *pstBlock = NULL;
    int iBlockID = DAS_BLOCKID_START;   /* first block */
    int i = 0;

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

    /* create the shminfo data structure in shared memory */
    printf("Creating shminfo...");
    fflush(stdout);
    g_pstShmInfo = DAS_CreateShmInfo(DAS_KEY_FL_OUT, DAS_PID_FL);
    if (NULL == g_pstShmInfo)
    {
        printf("ERROR in ShmAlloc() for g_pstShmInfo\n");

        /* clean up */
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        pcap_close(g_stHandle);

        return -1;
    }
    printf("DONE\n");

    /* create buffers */
    for (i = 0; i < DAS_NUM_BUFS; ++i)
    {
        printf("Creating block %d...", iBlockID);
        fflush(stdout);
        g_stBlockAdds[i] = DAS_CreateBlock(iBlockID,
                                           DAS_KEY_FL_OUT,
                                           g_pstShmInfo,
                                           DAS_PID_FL);
        pstBlock = g_stBlockAdds[i].pstBlock;
        if (NULL == pstBlock)
        {
            printf("ERROR in DAS_CreateBlock() for block %d\n", iBlockID);

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            pcap_close(g_stHandle);

            return -1;
        }
        g_pBufBase[i] = g_stBlockAdds[i].pData;
        /* initially, set the data flag to DAS_STATUS_NOP */
        g_stBlockAdds[i].pstBlock->iFlagData = DAS_STATUS_NOP;
        printf("DONE\n");
        ++iBlockID;
    }

    /* the first buffer will be written to now, so set the data flag
       to DAS_STATUS_FRESH */
    g_stBlockAdds[0].pstBlock->iFlagData = DAS_STATUS_FRESH;

    /* set the base and write pointers to the first buffer */
    g_iBuffer = 0;
    g_pBasePointer = g_stBlockAdds[0].pData;
    g_pWritePointer = g_stBlockAdds[0].pData;

    /* set the status flag to DAS_STATUS_WRITESTART */
    g_pstShmInfo->iStatus = DAS_STATUS_WRITESTART;

    iRet = pcap_loop(g_stHandle, -1, ProcessPacket, PCAP_USER);
    if (-1 == iRet)
    {
        fprintf(stderr, "ERROR: pcap_loop() failed!\n");

        /* clean up */
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        pcap_close(g_stHandle);

        return -1;
    }
    else if (-2 == iRet)
    {
        /* pcap_breakloop() encountered, so continue */
    }

    /* set the status flag to DAS_STATUS_WRITEDONE */
    g_pstShmInfo->iStatus = DAS_STATUS_WRITEDONE;

    /* clean up */
    /* delete buffers */    
    iBlockID = DAS_BLOCKID_START;
    for (i = 0; i < DAS_NUM_BUFS; ++i)
    {
        iRet = shmdt(g_stBlockAdds[i].pData);
        if (iRet != 0)
        {
            printf("ERROR in shmdt() for data in block %d: ", iBlockID);
            fflush(stdout);
            perror("");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            pcap_close(g_stHandle);

            return -1;
        }
        iRet = shmdt(g_stBlockAdds[i].pstBlock);
        if (iRet != 0)
        {
            printf("ERROR in shmdt() for block %d: ", iBlockID);
            fflush(stdout);
            perror("");

            /* clean up */
            DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
            pcap_close(g_stHandle);
    
            return -1;
        }
        ++iBlockID;
    }

    iRet = shmdt(g_pstShmInfo);
    if (iRet != 0)
    {
        perror("ERROR in shmdt() for g_pstShmInfo");

        /* clean up */
        DAS_CleanUp(DAS_KEY_FL_OUT, DAS_PID_FL);
        pcap_close(g_stHandle);

        return -1;
    }

    pcap_close(g_stHandle);

    return 0;
}

void ProcessPacket(u_char *pcUser,
                   const struct pcap_pkthdr *pstPacketHeader,
                   const u_char *pbPacket)
{
    struct ether_header *stHeaderEth = NULL;
    struct iphdr *stHeaderIP = NULL;
    struct udphdr *stHeaderUDP = NULL;
    DAS_BYTE *pbData = NULL;
    DAS_BYTE *pbMarkerPos = NULL;
    int i = 0;

    assert(pcUser != NULL);
    assert(pstPacketHeader != NULL);
    assert(pbPacket != NULL);

    stHeaderEth = (struct ether_header *) pbPacket;
    stHeaderIP  = (struct iphdr *) (pbPacket + sizeof(struct ether_header));
    stHeaderUDP = (struct udphdr *) (((DAS_BYTE *) stHeaderIP)
                                     + sizeof (struct iphdr));
    pbData = (DAS_BYTE *) (((DAS_BYTE *) stHeaderUDP) + sizeof (struct udphdr));

    pbMarkerPos = pbData + LEN_DATAHEADER;
    g_iCurrentMarker = (unsigned int) ntohl((*(unsigned int *) pbMarkerPos));

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

    /* if the end of the buffer is reached, reset the write pointer to the base
       pointer of the next buffer */
    if ((g_pWritePointer - g_pBasePointer) == DAS_SIZE_SHM_DATA)
    {
        ++g_iBufferChange;
        if (g_iBuffer != (DAS_NUM_BUFS - 1))    /* not the last buffer */
        {
            ++g_iBuffer;
        }
        else    /* the current buffer is the last buffer */
        {
            g_iBuffer = 0;
        }

        #if 0
        if ((DAS_STATUS_FRESH == g_stBlockAdds[g_iBuffer].pstBlock->iFlagData))
        {
            printf("ERROR: Overwriting buffer %d at packet number %d!\n",
                   g_iBuffer,
                   g_iPacketCount);
            printf("Stopping data acquisition...\n");
            printf("%d slips detected!\n", g_iSlipCount);

            for (i = 0; i < g_iSlipCount; ++i)
            {
                printf("Slip detected! ");
                #if 0
                printf("Previous = %X, current = %X, diff = %d, "
                       "packet count = %d\n",
                       g_aiSlips[i][POS_PREV],
                       g_aiSlips[i][POS_CURRENT],
                       (g_aiSlips[i][POS_CURRENT] - g_aiSlips[i][POS_PREV]),
                       g_aiSlips[i][POS_PKTCOUNT]);
                #else
                printf("Previous = %X, current = %X, diff = %d\n",
                       g_aiSlips[i][POS_PREV],
                       g_aiSlips[i][POS_CURRENT],
                       (g_aiSlips[i][POS_CURRENT] - g_aiSlips[i][POS_PREV]));
                #endif
            }
            printf("%d packets processed.\n", g_iPacketCount);
            printf("%d buffer changes.\n", g_iBufferChange);
            pcap_breakloop(g_stHandle);
            return;

        }
        #endif
        g_stBlockAdds[g_iBuffer].pstBlock->iFlagData = DAS_STATUS_FRESH;
        g_pBasePointer = g_stBlockAdds[g_iBuffer].pData;
        g_pWritePointer = g_stBlockAdds[g_iBuffer].pData;
    }

    /* write to shared memory */
    (void) memcpy(g_pWritePointer, pbData, SIZE_PACKET);
    g_pWritePointer += SIZE_PACKET;
    g_pstShmInfo->iWrittenData += SIZE_PACKET;

    /* increment the packet count, check the limit, and set the current file
       pointer if necessary */
    ++g_iPacketCount;
    if (MAX_NUM_PKTSPERFILE == g_iPacketCount)
    {
        printf("Stopping data acquisition...\n");
        printf("%d slips detected!\n", g_iSlipCount);

        for (i = 0; i < g_iSlipCount; ++i)
        {
            printf("Slip detected! ");
            #if 0
            printf("Previous = %X, current = %X, diff = %d, "
                   "packet count = %d\n",
                   g_aiSlips[i][POS_PREV],
                   g_aiSlips[i][POS_CURRENT],
                   (g_aiSlips[i][POS_CURRENT] - g_aiSlips[i][POS_PREV]),
                   g_aiSlips[i][POS_PKTCOUNT]);
            #else
            printf("Previous = %X, current = %X, diff = %d\n",
                   g_aiSlips[i][POS_PREV],
                   g_aiSlips[i][POS_CURRENT],
                   (g_aiSlips[i][POS_CURRENT] - g_aiSlips[i][POS_PREV]));
            #endif
        }
        printf("%d packets processed.\n", g_iPacketCount);
        printf("%d buffer changes.\n", g_iBufferChange);
        pcap_breakloop(g_stHandle);
        return;
    }

    return;
}

