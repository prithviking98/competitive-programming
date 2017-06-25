/*
 * sendpacket.c
 * Sends a UDP packet containing some data to the DAS machine
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

#define SIZE_PACKET     1098
#define IP              "10.10.10.1"
#define PORT            4950

int main(int argc, char *argv[])
{
    struct sockaddr_in stDASSockAddr = {0};
    int iSocket = 0;
    int iPacketCount = 0;
    int iRet = 0;
    FILE *pfPacketFile = NULL;
    unsigned char aucPacket[SIZE_PACKET] = {0};
    int iFlagSockType = SOCK_RAW;

    if (0 == strcmp(argv[1], "raw"))
    {
        iFlagSockType = SOCK_RAW;
        //iSocket = socket(PF_PACKET, iFlagSockType, htons(ETH_P_ALL));
        iSocket = socket(PF_PACKET, iFlagSockType, htons(ETH_P_ALL));
        if (-1 == iSocket)
        {
            perror("socket");
            return -1;
        }

        stDASSockAddr.sin_family = PF_PACKET;
        stDASSockAddr.sin_port = htons(PORT);
        stDASSockAddr.sin_addr.s_addr = inet_addr(IP);
        (void) memset(stDASSockAddr.sin_zero, '\0', sizeof(stDASSockAddr.sin_zero));
    }
    else if (0 == strcmp(argv[1], "udp"))
    {
        iFlagSockType = SOCK_DGRAM;
        iSocket = socket(PF_INET, iFlagSockType, IPPROTO_UDP);
        if (-1 == iSocket)
        {
            perror("socket");
            return -1;
        }

        stDASSockAddr.sin_family = PF_INET;
        stDASSockAddr.sin_port = htons(PORT);
        stDASSockAddr.sin_addr.s_addr = inet_addr(IP);
        (void) memset(stDASSockAddr.sin_zero, '\0', sizeof(stDASSockAddr.sin_zero));
    }
    else
    {
        fprintf(stderr, "ERROR: Invalid user input!\n");
        return -1;
    }

    pfPacketFile = fopen("packet", "r");
    if (NULL == pfPacketFile)
    {
        perror("fopen");
        return -1;
    }

    (void) fread(aucPacket, sizeof(unsigned char), SIZE_PACKET, pfPacketFile);

    if (SOCK_DGRAM == iFlagSockType)
    {
        while (1)
        {
            printf("Sending packet %d...\n", iPacketCount);
            iRet = sendto(iSocket,
                          (aucPacket + 42),
                          (SIZE_PACKET - 42),
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
        }
    }
    else if (SOCK_RAW == iFlagSockType)
    {
        while (1)
        {
            printf("Sending packet %d...\n", iPacketCount);
            iRet = write(iSocket, aucPacket, SIZE_PACKET);
            #if 0
            iRet = sendto(iSocket,
                          aucPacket,
                          SIZE_PACKET,
                          0,
                          (struct sockaddr *) &stDASSockAddr,
                          sizeof(stDASSockAddr));
            #endif
            if (-1 == iRet)
            {
                perror("write");
                //perror("sendto");
                (void) fclose(pfPacketFile);
                (void) close(iSocket);
                return -1;
            }
            ++iPacketCount;
        }
    }

    printf("%d bytes sent.\n", iRet);

    (void) fclose(pfPacketFile);
    (void) close(iSocket);

    return 0;
}

