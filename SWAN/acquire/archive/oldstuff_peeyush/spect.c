/* Program to display the spectrum of 2 channel raw data acquired in windowed 
   sampling mode using the bf536 card. Samples are 4 bits, 2 channels assumed
 peeyush, 11/07/07
*/

#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include <sys/time.h>
#include <cpgplot.h>
#include <string.h>
#include <stdlib.h>

float Plxmin=1, Plxmax=20000000, Plymin=20, Plymax=600,First=1;
enum {AvgSet=30, FoldPeriod=4092, Span=124*3, Taps=4096, SampClk=40920019, 
      BinBw=SampClk/Taps, Recs2Sec=330};

typedef struct
{ int seq;
  unsigned char folded[FoldPeriod];
}FoldType;

double pwr(fftw_complex *z)
{ return (z[0][0]*z[0][0] + z[1][1]*z[1][1]); }

double logpwr(fftw_complex *z)
{ return 10*log10 (z[0][0]*z[0][0] + z[1][1]*z[1][1]); }

int plot_init()
{ if(cpgopen("/xwindow") < 1)
  { fprintf(stderr,"No plotting facility!\n"); return -1;}
  cpgask (0);
  cpgsubp (2,1);
  cpgsci (5);
  cpgenv (Plxmin,Plxmax,Plymin,Plymax,0,-2);
  cpgsci (14);
  cpgbox ("G",0,0,"G",0,0);
  cpgsci (5);
  cpgbox ("ABCTSVN",(Plxmax-Plxmin)/5.0,10,"ABCTSN",(Plymax-Plymin)/2,10);
  cpgsci (8);
  cpglab ("Freq (KHz)","Power (dB)","Ch-A");

  // cpgenv (1,20000000,10,50,0,-2);
  cpgenv (Plxmin,Plxmax,Plymin,Plymax,0,-2);
  cpgsci (14);
  cpgbox ("G",0,0,"G",0,0);
  cpgsci (5);
  // cpgbox ("ABCTSVN",5000000.0,5,"ABCTSN",10,2);
  cpgbox ("ABCTSVN",(Plxmax-Plxmin)/5.0,10,"ABCTSN",(Plymax-Plymin)/2,10);
  cpgsci (8);
  cpglab ("Freq (KHz)","Power (dB)","Ch-B");
  return 0;
}

int datastats (FoldType *rec, float *mean, float *var, int *h)
{ int i=0;
  int s=0,x=0,x2=0;
  float m=0, v=0;

  if (rec == NULL || h == NULL) return -1;

  for (i=0; i<Taps; i++)
  { s = (rec->folded[i]>>4)&15; // NOTE: assuming data in msb
    x += s;
    x2 += s*s;
    h[s]++;
  }
  m = (float)x/Taps;
  v = (float)x2/Taps- m*m;

  *mean = m;
  *var = v;
  return 0;
}

int main(int argc,char *argv[])
{ FILE *fraw = NULL, *fout=NULL, *fcomp=NULL;
  int rec=0,i,k,set=0, file=0;
  fftw_complex *in1 = NULL, *out1 = NULL;
  fftw_complex *in2 = NULL, *out2 = NULL;
  fftw_plan p1,p2;
  FoldType raw;
  float x[Taps],ch1[Taps],ch2[Taps],oldch1[Taps],oldch2[Taps];
  float m,v;
  int hist[16], comp = 0,samp = 0;
  
  if((in1  = (fftw_complex*)fftw_malloc (sizeof (fftw_complex)*Taps))==NULL)
  { perror ("malloc"); return -1;}
  if((out1 = (fftw_complex*)fftw_malloc (sizeof (fftw_complex)*Taps))==NULL)
  { perror ("malloc"); return -1;}
  p1 = fftw_plan_dft_1d(Taps,in1,out1,FFTW_FORWARD,FFTW_ESTIMATE);
  if((in2  = (fftw_complex*)fftw_malloc (sizeof (fftw_complex)*Taps))==NULL)
  { perror ("malloc"); return -1;}
  if((out2 = (fftw_complex*)fftw_malloc (sizeof (fftw_complex)*Taps))==NULL)
  { perror ("malloc"); return -1;}
  p2 = fftw_plan_dft_1d (Taps,in2,out2,FFTW_FORWARD,FFTW_ESTIMATE);
  
  if ((fraw = fopen (argv[1],"rb")) == NULL)
  { perror ("fopen"); return -1;}

  if ((fcomp = fopen ("comp.dat","w")) == NULL)
  { perror ("fopen"); return -1;}

  if ((fout = fopen ("spect.out","w")) == NULL)
  { perror ("fopen"); return -1;}

  // if (!file) plot_init ();
  // calibrate 
  set = 0;
  while (set++ <= AvgSet)
  { fread (&raw, sizeof (FoldType), 1, fraw);
    datastats (&raw, &m, &v, hist);
    for (i=0; i<FoldPeriod/Span; i++)
    { memset (in1, 0, 2*Taps*sizeof (fftw_complex));
      for (k=0; k<Span; k++)
        in1[k][0] += ((raw.folded[i*Span+k]>>4) - m); // remaining are set to 0
      fftw_execute (p1);
      for (k=1; k<Taps; k++)
       ch1[k] += logpwr(out1+k); 
    }
  }
  for (k=1; k<Taps; k++) { ch1[k] /= AvgSet; ch2[k] /= AvgSet; }
  ch1[0] = ch1[1]; ch2[0] = ch2[1]; // for better plotting
  { float min=99999, max= -99999;
    int m;
    for (i=1; i<Taps/2; i++)
    { if (min > ch1[i]) min = ch1[i];
      if (max < ch1[i]) { max = ch1[i]; m=i; }
    }
    Plymin = min -50; Plymax = max + 50;
    fprintf (stderr, "Plymax: %f, ind=%d, freq: %8d\n",Plymax,m,m*BinBw);
    comp = m;
    plot_init();
  }
  
  set = 0;
  rewind (fraw);
  memset (ch1, 0, Taps*sizeof(float));

  for (i=0; i<Taps; i++)
  { x[i] = BinBw*i; ch1[i] = 0; ch2[i] = 0;}

  while (fread (&raw, sizeof (FoldType), 1, fraw))
  { datastats (&raw, &m, &v, hist);
    // each raw block is 33 ms worth
    for (i=0; i<FoldPeriod/Span; i++)
    { memset (in1, 0, 2*Taps*sizeof (fftw_complex));
      for (k=0; k<Span; k++)
        in1[k][0] += ((raw.folded[i*Span+k]>>4) - m); // remaining are set to 0
      fftw_execute (p1);
      fprintf(fcomp,"%8d %10.5lf %10.5lf\n",samp++,out1[comp][0],out1[comp][1]);
      for (k=1; k<Taps; k++)
       ch1[k] += logpwr(out1+k); 
    }

    if(set++ >= AvgSet)
    { for (k=1; k<Taps; k++) { ch1[k] /= AvgSet; ch2[k] /= AvgSet; }
      ch1[0] = ch1[1]; ch2[0] = ch2[1]; // for better plotting
      if (!file)
      { cpgpanl (1,1);
        cpgsci (0);
        cpgline (Taps,x,oldch1);
        cpgsci (6);
        cpgline (Taps,x,ch1);

        cpgpanl (2,1);
        cpgsci (0);
        cpgline (Taps,x,oldch2);
        cpgsci (6);
        cpgline (Taps,x,ch2);
      }
      else
      { for (i=1; i<Taps/2; i++)
        {  fprintf (fout, "%15.3lf %8.3lf %8.3lf\n", x[i], ch1[i], ch2[i]);
        }
        fprintf (fout, "\n\n");
      }
      memcpy (oldch1, ch1, sizeof (float)*Taps);
      memset (ch1, 0, sizeof (float)*Taps);
      memcpy (oldch2, ch2, sizeof (float)*Taps);
      memset (ch2, 0, sizeof (float)*Taps);
      set = 0;
    }
    if (rec++ % Recs2Sec == 0) fprintf (stderr, ".");
  }

  getchar ();
  fftw_destroy_plan (p1); fftw_free (in1); fftw_free (out1);
  fftw_destroy_plan (p2); fftw_free (in2); fftw_free (out2);
  return 0;
}
