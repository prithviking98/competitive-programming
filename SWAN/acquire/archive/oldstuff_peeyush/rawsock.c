 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netinet/ip.h>
 #include <netinet/tcp.h>
 #include <unistd.h>

 enum {BufSize = 8192};
 int main (int argc, char* argvp[])
 { int fd = socket (PF_INET, SOCK_RAW, IPPROTO_UDP);
   char *buf = NULL;
   FILE *frawpkt = NULL;
   struct ip *iphead;
   struct tcphdr *tcphead;
   int got = 0, pkt, npkts = 10;

  frawpkt = fopen ("rawpkt.dat", "wb");
  if (frawpkt == NULL) { perror ("fopen"); return -1; }

   buf = (char*) malloc (BufSize*sizeof (char));
   iphead = (struct ip*) buf;
   tcphead = (struct tcphdr*) (buf + sizeof (struct ip));

   pkt = 0;
   while (pkt < npkts)
   // while (read (fd, buf, BufSize) > 0)
   { got = read (fd, buf, 256);
     if (got < 0) break ;
      fprintf (stderr, "src: 0x%x, dest: 0x%x\n", iphead->ip_src,
     iphead->ip_dst);
     fwrite (buf, BufSize, 1, frawpkt);
     pkt++;
     fprintf (stderr, ".");
   }
   return 0;
}
   
