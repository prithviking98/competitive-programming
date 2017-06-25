/* extract for chk_n_rmmark.c for just locating the markers */

/*  This version is for use on LINUX  */
/*  But has notes on how to covert to DOS or ALPHA/LINUX version & vice versa */
/*  now caters for extended header for upto 2 rf channels --desh 09-FEB-2002 */
/*  Also, does the splitting for 1-bit data from 2 channels
    in addition to that for 2-bit data of two channels */

/*   chk_n_rmmark_lin.c   major modification from chk_n_rmmark_ws.c
     1) Now reads the header 
     2) Writes out now even the last incomplete data block.
     3) Provision to split files in the 2-channel (4-bit) mode
     4) Notes the number of markers found
 
	      --desh 18-JAN-2002


     It expects the full path for the input file and creates the
     output data file in the current directory with a _fixed tag.

     This program is to find out whether any data bytes are missing 
     because some timing mismatch in the FIFO read/write timing
     And to correct such slips & output the data without the markers

     Now you can output only a part of the data to the _fixed file
	   -- desh 25-Jun-97

     1.    whether at every " Nth " word increments by ONE
		" N "  user selectable
	  EPLD programmed is " new24.pof 24/6 : 3:16  " 
					  .pof : Chksum : 1500c7
     2. The starategy is as follows:
	----------------------------

	a.  Look for the mark +1 at the specified location;
	b.  IF not found look for " 00 " in the consecutive
	    locations then read the next Byte , which the NEXT
	    " mark " available, then continue the same way

       c.  NO assumption is made like there must exist a mark
	   within a Block; It may or may NOT be true     

  ------------------------------------------------------- */


/*  Important pts : short int  2 bytes, int : 4 bytes */

/* use the following include statements for ALPHA/LINUX instead of the set further below */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"


/* Added by Jayanth Chennamangalam --> */
#include <arpa/inet.h>
/* <-- Added by Jayanth Chennamangalam */


/* use the following include statements for DOS instead of the above */
/*
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <math.h>
#include <sys/stat.h>
*/




int handle,clstat;          /* used for files */
FILE * handle_o1;

long int i;
long int j,kk,k,l,m;


/* Added by Jayanth Chennamangalam --> */
double jtest = 0;
unsigned int jwrapover = 0xFFFFFFFF;
unsigned int jntohs = 0;
unsigned char *jcuraddr = NULL;
/* <-- Added by Jayanth Chennamangalam */

unsigned int mark, n1, n2, nargs;
unsigned int want_output,temp1,temp2,split_file,max_miss;
unsigned int byte_split[256];
long int file_size,file_cnt;
char datafile[60] = "obs.dat";

char in_path[60] = "test.gbd";
char extra_strg0[8] = "_fixed";
char extra_strg1[8] = "1_fixed";
char extra_strg2[8] = "2_fixed";

struct stat stbuf;
/* int stat(char *, struct stat *); */  /* uncomment this for DOS; else comment it out */

/*  ================  declarations of subroutines   =====================*/
    void file_open();
    void file_close();
    void read_n_write_frame();

/*  ================  Start of the main routine   =====================*/
	

main(int argc, char *argv[]) 
/* void main(int argc, char *argv[]) */
		      /* should be ...    void main() for DOS
			 and just         main() for ALPHA */
    {
	nargs = 3;
	if(argc<nargs)
	  {printf("usage....\n");
	   printf("chkrmrk1 <infile> <nslip_blocks_allowed>\n");
	   printf("want to continue with default parameters ? enter 1 if yes; else 0:");
	   scanf("%d",&nargs);
	   if(nargs > 0)
	     {split_file = 0;
	      max_miss = 1;
	     }
	   else
	     {exit(0);}
	  }
	else
	  {sscanf(argv[1],"%su",in_path);
	   sscanf(argv[2],"%du",&max_miss);
	  }
     file_open();
     read_n_write_frame();
     file_close();
    }
/*  ================  end of main routine  ==============================*/



void    file_open()
{

/* These 5 lines are for ALPHA/LINUX runs ... comment for DOS runs */
/*   printf(" input file path ?  ");
   scanf("%s",in_path);
   printf(" File name ?  (with out the path)   ");
   scanf("%s",datafile);
   strcat(in_path,datafile);
*/
/*       if((handle = open(in_path, O_CREAT | O_RDWR | O_BINARY, S_IWRITE)) == -1) */ /* for DOS */
/*       if((handle = open(in_path, O_RDONLY , S_IWRITE)) == -1)  */ /* for ALPHA or LINUX */
         if((handle = open(in_path, O_RDONLY , S_IWRITE)) == -1)   /* for ALPHA or LINUX */

	  {
	   perror("Error in opening the in-put file  :");
	   exit(0);
	  }
	 stat(in_path,&stbuf);
	 file_size = stbuf.st_size;
	 i =i+1;


    /* Added by Jayanth Chennamangalam --> */
    printf("File %s opened for checking\n", in_path);
    /* <-- Added by Jayanth Chennamangalam */


}

void file_close()
	{
	  int clstat;

	  if(clstat = ((close(handle))==-1))
	    {printf("Error closing the input file");}
	  if(want_output)
	     {if(clstat = ((fclose(handle_o1))==0))
	       {printf(" Output now available in:    %s\n ",datafile);}
	      else
	       {printf("Error closing the output file");}
	     }
	}


void read_n_write_frame()
{  
/*   this function reads the DAS data file       */
/*   Check whteher after every N words, the count (lower 8 bits of a marker word) is incremented by 1 */
/************************************************************/

       long int res,data_first;       /* 4 bytes */
       unsigned short int a[8192],a_out[8193]; /* 2 bytes */
       unsigned int research,st_wrd = 0,ofset_wrd = 0,missed_cnt; 
       unsigned short int b[1024];
       unsigned short int noise[4096];
       long int no_of_8kbytes,left_bytes,left_words,Word_Count,percent;
       float per_ge,bytes_comp;
       long int this_word,wraps_so_far,missed_so_far,slip_size;
       long int blk_size,nblk_out,nmax_out,start_out,stop_out;
       int i_out, temp_byte[2], nbytes_got;
       long int mark_locn[10],missed_samps[10],n_mark,last_mark;
       short int *out_pointer[2];
       long int out_due[2],out_due_set,out_size,actual_out,out_size_now;
       unsigned int has_header,first_time;
       long int total_markers;
       char psrname[32];
       char data_file[32];
       char site_name[32];
       char observer[32] = "Unknown";
       int hr,mt,sec,dd,mm,yy;
       float  f_0,f_1,dm;
       long int invert,invert1,nbits,n_rfch;
       double bw,bw1;
       long int mark_gap;

       double *dh;
       float *fh;
       long int *ih; /* "long int" for DOS; else "int".. should be 4-bytes */
       char *ph;

// jayanth
        unsigned int jcounterval = 0;



/*       int  rand; */

       i_out = 0;
       actual_out = 0;
       nblk_out =0;
       nmax_out = 8192;    /* block size used for  output array is 8192 words */
       out_size = nmax_out/2; 

       out_due[0] = (nmax_out/4)*3;
       out_due[1] = (nmax_out/4);
       out_due_set = 0;
       out_pointer[0] = (short int *)a_out;
       out_pointer[1] = out_pointer[0] + out_size;
       missed_so_far = 0;
       blk_size = 4096;    /* each block read is of 4096 words */

/*       printf(" does this file contain header ? type 1 if yes; else 0 \n");
       scanf("%d",&has_header);*/


        /* Modified by Jayanth Chennamangalam --> */
#if 0
       has_header=1;
#endif
       has_header=0;
        /* <-- Modified by Jayanth Chennamangalam */


       if(has_header == 1)
	   {file_size = file_size - 2048;}

       no_of_8kbytes = (file_size)/(2*blk_size);
       printf(" file_size (bytes): %ld\n",file_size);
       printf("no.of 8kb blocks  : %ld\n",no_of_8kbytes);
       left_bytes    = (file_size - (no_of_8kbytes * 8192));
       printf("left_bytes        : %ld\n",left_bytes);

       lseek(handle,0,SEEK_SET);

/* read the header bytes (2048) if has_header == 1 */
       if(has_header == 1)
	  {if((res = read(handle,b,2048)) != 2048)
				      /* reading  8k bytes at one time */
	    {
	     printf("\n\nErr. reading the obs.dat file.. hit any key to Quit\n");
	     getchar();        /* To skip, look for any key typed from KBD */
	     printf(" no. of markers found : %ld\n",total_markers);
	     printf(" no. of slip events : %d\n",missed_cnt);
	     exit(0);
	    }

	     printf(" Header block summary : \n");
	     printf(" ===================================\n");
	     /* interprete the header info */
	     fh = (float *) b ;
	     dh = (double *) b ;
	     ih = (long int *) b ;       /* "long int" for DOS; else "int".. should be 4-bytes */
	     ph = (char *)b ;
	     printf("%lf %f %f %d %d %d %d %d %d %d\n",dh[0],fh[2],fh[3],ih[4],ih[5],ih[6],ih[7],ih[8],ih[9],ih[10]);

	     bw = dh[0];
	     printf(" bandwidth of obs.n : %f kHz \n",bw);

	     f_0 = fh[2];
	     printf(" Centred at : %f MHz \n",f_0);

	     dm = fh[3];
	     printf(" DM : %f pc/cc \n",dm);

	     mark_gap = ih[4];
	     printf(" marker_interval in header : %d words \n",mark_gap);
	     if(mark_gap>8192)mark_gap = 4096;
	     if(mark_gap<2048)mark_gap = 4096;
	     printf(" marker_interval to be used : %d words \n",mark_gap);
	     ofset_wrd = mark_gap + 1;

	     dd = ih[5];
	     mm = ih[6];
	     yy = ih[7];
	     printf(" date : %d-%d-%d \n",dd,mm,yy);

	     hr = ih[8];
	     mt = ih[9];
	     sec = ih[10];

	     printf(" IST at start : %d:%d:%d \n",hr,mt,sec);

	     memcpy(psrname, ph+44, 32);
	     printf(" Field_name %s \n",psrname);

	     memcpy(data_file, ph+76, 32);
	     printf(" original_data_file_name %s \n",data_file);

	     memcpy(site_name, ph+108, 32);
	     printf(" Telescope site_code %s \n",site_name);

	     /* header extention  begins here */           
	     n_rfch = ih[35]; 
	     if(n_rfch > 0 && n_rfch < 3)
	       {
		nbits = ih[36];
		f_1 = fh[37];
		bw1 = dh[19];
		memcpy(observer, ph+160, 32);   /* ih[40] */
		printf(" Observer %s \n",observer);
		printf(" ===================================\n");
		/* next usable: ih[48] or fh[48] or dh[24] or ph+192  */
	       }
	     else
	       {
		nbits = 2;
		n_rfch = 1;
		bw1 = bw;
		f_1 = f_0;
		printf("Observer Unknown (due to old header)\n");
		ih[35] = n_rfch; 
		ih[36] = nbits;
		fh[37] = f_1;
		dh[19] = bw1;
		memcpy(ph+160, observer, 32);   /* ih[40] */
	       }
	     printf(" %ld channel data; %ld-bits per sample\n",n_rfch,nbits);
	     if(n_rfch > 1)
	       {
		printf(" ===================================\n");
		printf(" bandwidth of 2nd channel : %f kHz \n",bw1);
		printf(" Centred at : %f MHz \n",f_1);
	       }
	     printf(" ===================================\n");
	   
	  }
       else        /* no header */
	  {
	   lseek(handle,0,SEEK_SET);   /* rewind to the beginning */


        /* Modified by Jayanth Chennamangalam --> */
#if 0
	   printf(" Enter the number of words between markers\n");
	   scanf("%d",&ofset_wrd);
#endif
        ofset_wrd = 515;
#if 0
	    ofset_wrd = ofset_wrd + 1;
#endif
        /* <-- Modified by Jayanth Chennamangalam */


	  }


/*     printf(" want output (_fixed) file ? 1 : if yes; 0 : else \n");
       scanf("%d",&want_output); */
       want_output=0;  /* only test ; no output required */
       if(want_output == 1)
	 {if(n_rfch > 1)
	    { /* printf(" want the split_file (parts 1 or 2) ? Enter 1 or 2 : if yes; 0 : else \n");
	      scanf("%d",&split_file);  */
	      printf(" requested split_file_code is %d\n",split_file);
	    } 
	  else
	    { split_file = 0;
	    }
   /*  commented for DOS runs; uncomment these for ALPHA/LINUX runs */
            if(split_file == 0)
	      {strcat(datafile,extra_strg0);}
	    if(split_file == 1)
	      {strcat(datafile,extra_strg1);}
	    if(split_file == 2)
	      {strcat(datafile,extra_strg2);}
   

	  printf(" Output File name will be :    %s ",datafile);
	  handle_o1 = fopen(datafile,"w");  /* open the output file */
	  printf(" in the local directory !\n ");
	     if(has_header == 1)
	       {
		if(split_file > 1)   /* interchange the chnnels related info */
		   { fh[2] = f_1;
		     dh[0] = bw1;
		     fh[37] = f_0;
		     dh[19] = bw;
		   }
		fwrite(b,sizeof(short int),1024,handle_o1); 
	       }
	 
	 }
       else
	 { printf("  NO output  File opened !\n ");
	 }
       if(want_output)
	 {/*printf(" enter start and end block no.s for output\n");
	  scanf("%ld %ld",&start_out,&stop_out); */
	  /* force to default values */
	  start_out = 1;
	  stop_out = 500;  /* no_of_8kbytes; */        /* =no_of_8kbytes; for ALPHA/LINUX runs, and =500; for DOS runs */
	  if(split_file > 0)
	    {start_out = start_out/2 + 1;
	     stop_out = stop_out/2;
	    }
	  if(start_out<= 0)
	    {start_out = 1;}
	  if(stop_out> no_of_8kbytes)
	    {stop_out = no_of_8kbytes;}

	  i = stop_out - start_out + 1;
	  printf("%ld blocks from %ld will be output\n",i,start_out);
	  stop_out = stop_out - 1;           /* as our counting starts with 0 */
	  start_out = start_out - 1;
	 }

       if(split_file > 0)
	   /* generate a look-up for splitting bytes depending
	      on the no. of bits per sample and channels to be
	      ouput 
	   */
	 {if(nbits >1)
	    {for (j = 0; j < 256; j = j+1)
	       {
		/* pick the ls-bits 1-2 & 5-6  if split_file eq. 1
		   or pick the ls-bits 3-4 & 7-8 if split_file eq. 2
		   and pack them compactly*/

		n1 = 1;
		if(split_file>1)n1 = 4;

		k = j;
		temp1 = ((k/n1) & (0x03));
		byte_split[j] = temp1;
		n2 = n1 * 16;
		temp1 = ((k/n2) & (0x03));
		byte_split[j] += temp1*4;
	   /*     printf("%d %04x\n ",j,byte_split[j]); */

	       }                                        /* "j" loop ends */
	    }
	  else        /* 1-bit data */
	    { printf("Generated codes for splitting 1-bit data\n");
	      for (j = 0; j < 256; j = j+1)
	       {
		/* pick the ls-bits 1,3,5 & 7  if split_file eq. 1
		   or pick the ls-bits 2,4,6 & 8 if split_file eq. 2
		   and pack them compactly*/

		n1 = 1;
		if(split_file>1)n1 = 2;

		k = j;
		temp1 = ((k/n1) & (0x01));
		byte_split[j] = temp1;
		
		n2 = n1 * 4;
		temp1 = ((k/n2) & (0x01));
		byte_split[j] += temp1*2;
		
		n2 = n1 * 16;
		temp1 = ((k/n2) & (0x01));
		byte_split[j] += temp1*4;
		
		n2 = n1 * 64;
		temp1 = ((k/n2) & (0x01));
		byte_split[j] += temp1*8;
	   /*     printf("%d %04x\n ",j,byte_split[j]); */

	       }                                        /* "j" loop ends */
	    }
	 }
/* now, we can proceed to read the data */
       first_time = 1;


       total_markers = 0;
       i = 1;
       research = 0;    /* let us not search to begin with */
       l = 0;
       bytes_comp = 0;

/*       printf(" Enter the max. no. of missing blocks (>0) allowed at a time \n");
       printf("  2 would be a reasonable choice \n");
       scanf("%d",&max_miss);
*/
	 printf(" max allowed block misses is %d\n",max_miss);
/*       max_miss = 1;*/
       if(max_miss<=0)
	 {max_miss = 1;}

       nbytes_got = 0;
       missed_cnt = 0;
       k = 0;    /* IMPORTANT */

     /* To find out the first encountered COUNTER value */
       mark = 0;           /* 8 bit counter value */
       last_mark = 0;
       while (i <= no_of_8kbytes)
	 { 
	  if((res = read(handle,a,8192)) != 8192) 
				      /* reading  8k bytes at one time */
	    {
	     printf("\n\nErr. reading the obs.dat file.. hit any key to Quit\n");
	     getchar();        /* To skip, look for any key typed from KBD */
	     printf(" no. of markers found : %ld\n",total_markers);
	     printf(" no. of slip events : %d\n",missed_cnt);
	     exit(0);
	    }
//TEST_BLOCK            
    for(l=0;l<blk_size;l++)
	{
        last_mark++;


        /* Modified by Jayanth Chennamangalam --> */
#if 0
		 j = a[l]/256;
#endif
        jntohs = (unsigned int) ntohs(a[l]);
		jtest = (double) jntohs/ jwrapover;
#if 0
        if(j==0)
#endif
		if(jtest==((double) 0xFFFF/(unsigned int)0xFFFFFFFF))
        {
            if(last_mark >= ofset_wrd) 
		    {
#if 0
                mark = a[l];
#endif
                jcuraddr = (unsigned char *) &a[l];
                mark = (unsigned int) ntohl((*(unsigned int *) (jcuraddr+2)));
                //printf("c = %x, m = %x, i = %d, lm = %d\n", jcounterval, mark, i, last_mark);
                //fflush(stdout);
                if (mark != (jcounterval + 1))
                {
                    //fprintf(stderr, "slip!\n");
                    printf("slip!");
                    printf("c = %x, m = %x, i = %d, lm = %d\n", jcounterval, mark, i, last_mark);
                    fflush(stdout);
                    printf (" block no, mark,gap    : %ld %x %d %d\n",i,mark,last_mark,ofset_wrd); 
                    missed_cnt++;
                    last_mark = 0;
                    //getchar();
                }
                jcounterval = mark;
                //printf("a[l+1] = %x, mark = %x\n", (*(unsigned int *) jcuraddr+2), mark);
                //printf("found: ");
		        //printf (" block no, mark,gap,l    : %ld %x %d %d\n",i,mark,last_mark, l);
        /* <-- Modified by Jayanth Chennamangalam */

		        if(last_mark == ofset_wrd)
    			{
                    total_markers++;
                    last_mark = 0;
                }
		        else
			    {
                    if(last_mark>ofset_wrd)
                    {
                        missed_cnt++;
                        //fprintf(stderr, "missed:\n");
                        printf("missed:");
		                printf (" block no, mark,gap    : %ld %x %d %d\n",i,mark,last_mark,ofset_wrd); 
                        last_mark = 0;
                        //getchar();
                    }
		        }
		    }
		}
	}

	     n_mark = 0;
	     goto okay; 

	  if(i==1)    /* Note the data in the first record for use in filling the missing samples */
	    {for(l=0;l<blk_size;l++)
		{noise[l] = a[l];}
	    }
	  n_mark = 0;
/* define a psudo marker at sample no -1 */
	  mark_locn[n_mark] = -1; 
	  missed_samps[n_mark] = 0;
	  n_mark++;
	  l = 0;
adjust:   if(research == 1)
	    { /* printf("seraching for mark : %d\n", mark); */
	     for (kk = l; kk <blk_size ; kk = kk+1)  /* Checking each time 8k bytes */
			     /* 4k words the incrementing values */
		{                                  
		 j = a[kk]/256;    /* extract the upper byte */
		 if(j==0)  /*  && (a[kk]>=0)) */
				  /* looking for "00" in the upper byte */
				  /* and new mark >= 0 */
		   { 
		     slip_size = last_mark - a[kk];
		     if(slip_size < 0)slip_size = slip_size + 256;
		     if(slip_size > max_miss)goto hold_on;
		     mark = a[kk];
		     last_mark = mark;
 
		     
		     printf ("match(?) at block no, mark    : %ld %d \n",i,mark);
		     printf (" values around the mark -,+: %d %d \n",a[k-1],a[k+1]);  
//TEST                     this_word = (i-1)*(blk_size) + kk + 1 + missed_so_far;
//TEST                     wraps_so_far = this_word/(ofset_wrd*256); /* as the mark is modulo 256 */
//TEST                     slip_size = this_word - wraps_so_far*ofset_wrd*256 - (mark+1)*ofset_wrd; 
/* TEST                     this_word = (i-1)*(blk_size/256); 
/*                     wraps_so_far = this_word/(ofset_wrd); */ /* as the mark is modulo 256 */
/*                     slip_size = (this_word - wraps_so_far*ofset_wrd)*256 - (mark+1)*ofset_wrd + kk + 1 + missed_so_far;
		     if(slip_size > (ofset_wrd*256))                     
		       {slip_size = slip_size - ofset_wrd*256;}
		     if(slip_size < (-ofset_wrd*256))                     
		       {slip_size = slip_size + ofset_wrd*256;}
*/                     
	    /* make some sanity checks for the reasonableness of this marker */
		     if(slip_size<0)
		       {m = -slip_size;
//TEST                        if(m>(max_miss*ofset_wrd))goto hold_on;
		       }
		     if(slip_size>0)
		       {m = slip_size;
//TEST                        if(m>(nmax_out/4))goto hold_on;
		       }
	    /*                                                */
		     if(slip_size>0)
		       {printf ("\n Extra words at this slip : %ld \n",slip_size);}
		     else
		       {m = -slip_size;
			printf ("\n Missing words at this slip : %ld \n",m);}
		     research = 0;
		     k = kk + 1;
		     if(first_time > 0) 
		       {if(mark == 1)
			{ k = k + 1;
			 printf("first time : \n");
			 scanf("%d",&first_time);
			 first_time = 0;
			}
		       }
		     mark_locn[n_mark] = kk;
		     missed_samps[n_mark] = -slip_size;
		     total_markers++;
		     n_mark++;
		     missed_so_far = missed_so_far - slip_size;
		     if(missed_so_far > (ofset_wrd*256))                     
		       {missed_so_far = missed_so_far - ofset_wrd*256;}
		     if(missed_so_far < (-ofset_wrd*256))                     
		       {missed_so_far = missed_so_far + ofset_wrd*256;}


		     goto next;
hold_on:             printf("!");     
		   }
		}
	     printf("\n No match (mark,block): %d %ld\n", mark,i);
	     goto skip;
	    }
next:     j = ((blk_size-k)/ofset_wrd);  /* the no of markers ahead in this block */
	  if(j==0)
	    {
	     k =  k - blk_size;
	    }
	  if(j >= 1)               /* j markers expected in this block */
	    { 
	     research = 0;
	     m = 0;
	     while(research == 0 && m < j)
		  { m++;
		    k = k + ofset_wrd ;
		    if(k>blk_size)k = k-blk_size;
		    l = k -1;
		    mark = mark + 1;
		    if(mark==256) mark=0;
		    if (a[l] == mark)
		      { /* printf ("\n mark %d in block %ld\n",mark,i); */    /* : No missing of the counter val. */
			last_mark = mark;
			research = 0;
			mark_locn[n_mark] = l;
			missed_samps[n_mark] = 0;
			total_markers++;
			n_mark++;
		     if(first_time > 0) 
		       {if(mark == 1)
			{ k = k + 1;
			  printf(" at expected first time\n");
			  scanf("%d",&first_time);
			  first_time = 0;
			}
		       }

		      }
		    else
		      { research = 1;
			missed_cnt = missed_cnt + 1;
			printf ("\n SLIP DETECTED ! count: %d",missed_cnt);
			printf ("\n (e-mark,actual) at block : %d %d %ld\n", mark,a[l],i);
			l = k-ofset_wrd; 
			if(l<=-1) l = 0;
			goto adjust;
		      }
		   }    /* " while research && ... loop is over " */
     
/*  The fact that we are here means we have found all the markers at the expected places */
	     k = k - blk_size;
	    }    /* if j>= 1 condition */
	  goto okay;
skip:     printf(" \n search to continue (s,i,mark,last_mark) : %d %ld %d %d\n",research,i,mark,last_mark);

okay:     mark_locn[n_mark] = blk_size;
			       /* define a psudo marker at sample no -1 */
	  missed_samps[n_mark] = 0;
	  n_mark++;

	if(want_output)
	 {for(l=0;l<(n_mark-1);l++) /* deal with each region bounded by two markers */
	     {/* printf("block,n_marks,i_out,missed : %ld %ld %ld %ld\n",i,n_mark,i_out,missed_samps[l]); */
	      if(missed_samps[l]<0) 
		       /* allow overwritting for the extra samples */
	       { i_out = i_out + missed_samps[l];
		 if(i_out<0)i_out = i_out + nmax_out;
	       }
	      if(missed_samps[l]>0)  
			   /* we need to  fill in some missing samples */
		{kk = rand();
		 kk = kk - (kk/blk_size)*blk_size;
		 for(m=0;m<missed_samps[l];m++)
		    { kk = kk + 1; 
		      kk = kk - (kk/blk_size)*blk_size;
		      if(kk<0)kk=kk+blk_size; 
		      if(split_file > 0)
			{temp1 = noise[kk];
			 temp2 = temp1/256;
			 n1 = temp1 - temp2*256;
			 n2 = temp2;
			 if(nbytes_got < 1)
			   {temp1 = byte_split[n2]*16 + byte_split[n1];
			    a_out[i_out] = temp1;
			    nbytes_got = 1;}
			 else
			   {temp1 = (byte_split[n2]*16 + byte_split[n1])*256;
			    a_out[i_out] += temp1;
			    nbytes_got = 0;
			    i_out++;}
			}
		      else
			{a_out[i_out] = noise[kk];
			 i_out++;
			}

		      if(i_out==out_due[out_due_set])
			{ /* printf(" Output block %ld\n",nblk_out); */
			  if((nblk_out >= start_out) && (nblk_out<=stop_out))
			    {actual_out++;
			     fwrite(out_pointer[out_due_set],sizeof(short int),out_size,handle_o1);}
			  out_due_set++;
			  if(out_due_set>=2)out_due_set = 0;
			  nblk_out++;
			}
		      if(i_out>=nmax_out)i_out = i_out - nmax_out;
		    }
		} 

	      kk = mark_locn[l] + 1;
	      j = mark_locn[l+1];
	      if(j>kk)
		{ /* printf(" copying from index %d %d \n",kk,j); */
	       for(m=kk;m<j;m++)
		    {if(split_file > 0)
		       {temp1 = a[m];
			temp2 = temp1/256;
			n1 = temp1 - temp2*256;
			n2 = temp2;
			if(nbytes_got < 1)
			  {temp1 = byte_split[n2]*16 + byte_split[n1];
			   a_out[i_out] = temp1;
			   nbytes_got = 1;}
			else
			  {temp1 = (byte_split[n2]*16 + byte_split[n1])*256;
			   a_out[i_out] += temp1;
			   nbytes_got = 0;
		 /*        temp1 = a_out[i_out];
			   printf(" %04x ",temp1);  */
			   i_out++;}
		       }
		     else
		       {a_out[i_out] = a[m];
	     /*        temp1 = a_out[i_out];
		       printf(" %04x ",temp1);  */
			i_out++;
		       }

		      if(i_out==out_due[out_due_set])
			{ /* printf(" Output block %ld\n",nblk_out); */
			 if((nblk_out >= start_out) && (nblk_out<=stop_out))
			   {actual_out++;
			    fwrite(out_pointer[out_due_set],sizeof(short int),out_size,handle_o1);}
			  out_due_set++;
			  if(out_due_set>=2)out_due_set = 0;
			  nblk_out++;
			}
		      if(i_out>=nmax_out)i_out = i_out - nmax_out;
		    }
		}
	     }
	 }    
	 /*    printf(" input block %ld is used\n",i); */
	i++;          /* one more block read  */
      }      /* End of while loop */
      if(want_output)
	/*  see if any poits are yet to be written out */
	{j = i_out - out_due_set*out_size;
	 if(j<0)
	   { /* printf(" Output block %ld\n",nblk_out); */
	    if((nblk_out >= start_out) && (nblk_out<=stop_out))
	      {actual_out++;
	       fwrite(out_pointer[out_due_set],sizeof(short int),out_size,handle_o1);}
	     out_due_set++;
	     if(out_due_set>=2)out_due_set = 0;
	     nblk_out++;
	     j = i_out - out_due_set*out_size;
	   }
	 if(j>0)
	   { /* printf(" Output block %ld\n",nblk_out); */
	    if((nblk_out >= start_out) && (nblk_out<=stop_out))
	      {actual_out++;
	       fwrite(out_pointer[out_due_set],sizeof(short int),j,handle_o1);}
	     out_due_set++;
	     if(out_due_set>=2)out_due_set = 0;
	     nblk_out++;
	   }
	}
      printf(" no. of slip events : %d\n",missed_cnt);
      printf(" no. of markers found : %ld\n",total_markers);
//      printf(" no. of 4KWord blocks written out : %ld\n",actual_out);
 }        /*  End of function read_n_write_frame */


