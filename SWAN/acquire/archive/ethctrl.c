/*
 * ethctrl.c
 * Sends a packet containing control information to the FPGA board through
 * the Ethernet interface
 *
 * Created by Jayanth Chennamangalam
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>

#define SIZE_PACKET     64
#define PORT            4950

int main(int argc, char *argv[])
{
    struct sockaddr_in stDASSockAddr = {0};
    int iSocket = 0;
    int iPacketCount = 0;
    int iRet = 0;
    FILE *pfPacketFile = NULL;
    unsigned char aucPacket[SIZE_PACKET] = {0};
    char *pcIP = NULL;
    struct ifreq stIfReq = {0};

    pcIP = argv[1];

    iSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (-1 == iSocket)
    {
        perror("socket");
        return -1;
    }

    (void) memset(&stIfReq, 0, sizeof(stIfReq));
    (void) strncpy(stIfReq.ifr_name, argv[2], sizeof(stIfReq.ifr_name));
    iRet = setsockopt(iSocket,
                      SOL_SOCKET,
                      SO_BINDTODEVICE,
                      (void *) &stIfReq,
                      sizeof(stIfReq));
    if (-1 == iRet)
    {
        perror("setsockopt");
        return -1;
    }

    stDASSockAddr.sin_family = AF_INET;
    stDASSockAddr.sin_port = htons(PORT);
    stDASSockAddr.sin_addr.s_addr = inet_addr(pcIP);
    (void) memset(stDASSockAddr.sin_zero, '\0', sizeof(stDASSockAddr.sin_zero));

    pfPacketFile = fopen("packet", "r");
    if (NULL == pfPacketFile)
    {
        perror("fopen");
        return -1;
    }

    (void) fread(aucPacket, sizeof(unsigned char), SIZE_PACKET, pfPacketFile);

    printf("Message: %s", aucPacket);

    printf("Sending packet %d...\n", iPacketCount);
    iRet = sendto(iSocket,
                  aucPacket,
                  SIZE_PACKET,
                  0,
                  (struct sockaddr *) &stDASSockAddr,
                  sizeof(stDASSockAddr));
    if (-1 == iRet)
    {
        perror("sendto");
        (void) fclose(pfPacketFile);
        (void) close(iSocket);
        return -1;
    }
    ++iPacketCount;

    printf("%d bytes sent.\n", iRet);

    (void) fclose(pfPacketFile);
    (void) close(iSocket);

    return 0;
}

