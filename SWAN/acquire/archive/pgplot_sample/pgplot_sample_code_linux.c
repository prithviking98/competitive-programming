#include <stdio.h>
#include <math.h>
/* #include <maxdimc.h> */
/* #include <nr.h> */
/* #include <nrutil.h> */
#include <cpgplot.h>

#define PI 3.14159265

  double temp_real,temp_imag;
  double fresnel_scale,lambda,max_delay,edge_y_val;
  double xbc,ybc,zbc,xint,yint,zint;
  double xpb1,ypb1,zpb1,xpb2,ypb2,zpb2;
  double xfsur,yfsur,zfsur,xprad,yprad,zprad;
  double cone_angle_cos;
  double rel_phase_const;
  double apilum_array[2000];
  double xy_array[2000];
  float x11[150],y11[150];
  int nx,ny;
  int nprofile;
  int first_time;

MAIN__()
{
  char inbuf[32];
  int i,j,ii,jj;
  int option,max_rings,nring,nrim_now;
  int npoint,nrim,nrim_max,want_diffraction;
  double tmp1,tmp2,tmp12;
  float temp_float,period;
  /* plot variables */
  int nplot,symbol_1=17,symbol_2=2,symbol_3=21;
  float xmin,xmax,ymin,ymax,ymin0,ymax0;
  float xarray[300];
  float yarray_i[300],yarray_q[300],yarray_u[300],yarray_v[300];
  float yarray_xx[300],yarray_yy[300],yarray_xy[300],yarray_yx[300];
  float yarray_i_p[300],yarray_q_p[300],yarray_u_p[300],yarray_v_p[300];
  float yarray_xx_p[300],yarray_yy_p[300],yarray_xy_p[300],yarray_yx_p[300];

  first_time = 1;

/* sample inputs  */
  nplot = 300;
  period = (float)nplot;


  xmin=0.0;
  xmax=0.0;
  ymin=0.0;
  ymax=0.0;
  for(j=0;j<nplot;++j)
    {
      xarray[j]=(float)j;  
      yarray_i[j] = cos(2.*PI*(float)j/period);
      yarray_q[j] = sin(2.*PI*(float)j/period);
      if(xmin > xarray[j]) xmin = xarray[j];
      if(xmax < xarray[j]) xmax = xarray[j];
      if(ymin > yarray_i[j]) ymin = yarray_i[j];
      if(ymax < yarray_i[j]) ymax = yarray_i[j];
      if(ymin > yarray_q[j]) ymin = yarray_q[j];
      if(ymax < yarray_q[j]) ymax = yarray_q[j];
      yarray_xx[j] = yarray_i[j];
      yarray_yy[j] = yarray_q[j];
      yarray_xy[j] = yarray_i[j];
      yarray_yx[j] = yarray_q[j];

      yarray_i_p[j] = 100.*cos(4.*PI*(float)j/period);
      yarray_q_p[j] = 100.*sin(4.*PI*(float)j/period);
      yarray_xx_p[j] = yarray_i_p[j];
      yarray_yy_p[j] = yarray_q_p[j];
      yarray_xy_p[j] = yarray_i_p[j];
      yarray_yx_p[j] = yarray_q_p[j];
    }
 /* find our xmin,xmax,ymin,ymax as we will need them below.*/ 
  ymin0 = ymin;
  ymax0 = ymax;

for(i=0;i<2;i++)
 {cpgbeg(0,"?",1,1);

  ymax=ymax0;ymin=ymin0;
  cpgsvp(0.1,0.5,0.6,0.9);
  cpgswin(xmin,xmax,ymin,ymax);
  cpgbox("BCNST",0.0,0,"BCNST",0.0,0);
  cpglab("ant_front_az offset (arcmin)",
		      "correlated amp","I,Q,U,V");
  cpgline(nplot,xarray,yarray_i);
  cpgpt(nplot,xarray,yarray_q,symbol_1);
/*  cpgpt(nplot,xarray,yarray_u,symbol_2);
  cpgpt(nplot,xarray,yarray_v,symbol_3);
*/
  cpgsvp(0.55,0.95,0.6,0.9);
  cpgswin(xmin,xmax,ymin,ymax);
  cpgbox("BCNST",0.0,0,"BCNST",0.0,0);
  cpglab("ant_front_az offset (arcmin)",
		      " ","XX,YY,XY,YX");
  cpgline(nplot,xarray,yarray_xx);
  cpgpt(nplot,xarray,yarray_yy,symbol_1);
  cpgpt(nplot,xarray,yarray_xy,symbol_2);
  cpgpt(nplot,xarray,yarray_yx,symbol_3);

  cpgsvp(0.1,0.5,0.1,0.4);
  ymax=200;ymin=-200;
  cpgswin(xmin,xmax,ymin,ymax);
  cpgbox("BCNST",0.0,0,"BCNST",0.0,0);
  cpglab("ant_front_az offset (arcmin)",
		      "correlated phase"," ");
  cpgline(nplot,xarray,yarray_i_p);
  cpgpt(nplot,xarray,yarray_q_p,symbol_1);
/*  cpgpt(nplot,xarray,yarray_u_p,symbol_2);
  cpgpt(nplot,xarray,yarray_v_p,symbol_3);
*/
  cpgsvp(0.55,0.95,0.1,0.4);
  cpgswin(xmin,xmax,ymin,ymax);
  cpgbox("BCNST",0.0,0,"BCNST",0.0,0);
  cpglab("ant_front_az offset (arcmin)",
		      " "," ");
  cpgline(nplot,xarray,yarray_xx_p);
  cpgpt(nplot,xarray,yarray_yy_p,symbol_1);
  cpgpt(nplot,xarray,yarray_xy_p,symbol_2);
  cpgpt(nplot,xarray,yarray_yx_p,symbol_3);

  cpgend();
 }
}
