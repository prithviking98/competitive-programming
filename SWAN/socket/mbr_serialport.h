/*
 * mbr_serialport.h
 * Header file for serial port interfacing functions
 *
 * Authors:
 *  G. Gurushanth (2003.07.23)
 *  Salna Viswanathan
 *  Deepa Dhamnekar
 *  Harshad Sahasrabudhe
 *  Madhura Murthy
 *  Pavithra Kurapati
 *  Jayanth Chennamangalam
 */

#ifndef __MBR_SERIALPORT_H__
#define __MBR_SERIALPORT_H__

//#ifdef MBR_LOCAL

#include <fcntl.h>
#include <termios.h>
#include <fstream>

#define MBR_DEV_SERIALPORT      "/dev/ttyS0"    /* the serial port device */
#define MBR_SIZE_WRITE          1               /* bytes to write at a time */
#define MBR_NUM_BIT             23

/* 8255 I/O modes */
#define MBR_8255MODE_ALLOUT     0x80        /* mode 0: A-out: B-out: C-out: */
/* the following port I/O modes are not used */
#define MBR_8255MODE_AIBOCO     0x90        /* mode 0: A-in : B-out: C-out: */
#define MBR_8255MODE_AOBICO     0x82        /* mode 0: A-out: B-in : C-out: */
#define MBR_8255MODE_AIBICO     0x92        /* mode 0: A-in : B-in : C-out: */
#define MBR_8255MODE_AOBOCI     0x89        /* mode 0: A-out: B-out: C-in : */
#define MBR_8255MODE_AIBOCI     0x99        /* mode 0: A-in : B-out: C-in : */
#define MBR_8255MODE_AOBICI     0x8b        /* mode 0: A-out: B-in : C-in : */
#define MBR_8255MODE_AIBICI     0x9b        /* mode 0: A-in : B-in : C-in : */

/* 8255 port and control word addresses */
#define MBR_8255CW_1            0x31
#define MBR_8255PORT_A1         0x32
#define MBR_8255PORT_B1         0x33
#define MBR_8255PORT_C1         0x34
#define MBR_8255CW_2            0x35
#define MBR_8255PORT_A2         0x36
#define MBR_8255PORT_B2         0x37
#define MBR_8255PORT_C2         0x38
/* the following ports are not used */
#define MBR_8255INPORT_A1       0x62
#define MBR_8255INPORT_B1       0x63
#define MBR_8255INPORT_C1       0x64
#define MBR_8255INPORT_A2       0x66
#define MBR_8255INPORT_B2       0x67
#define MBR_8255INPORT_C2       0x68

#define MBR_BITPOS_ATTENLATCH   6

/* paths */
#define MBR_FILE_DAS_BITMAP     "/config/bitmap"
#define MBR_FILE_DAS_LOOKUP     "/config/devlookup.newcon"

//values required to initialize the synthesizer
#define MBR_CLK_HIGH            1
#define MBR_CLK_LOW             0
#define MBR_LE_HIGH             1
#define MBR_LE_LOW              0
#define IL                      0x59c693
#define FL                      0x59c692
#define R                       0x100028
#define AB_BASE                 0x200001

//number of bits for passing the device values
#define MBR_NUM_BITS_ATTENUATOR 7
#define MBR_NUM_BITS_LOFREQ     3

//values required to set the frequency(fvco)
#define P                       16

typedef struct DeviceLookUp
{
    char acDevice[MBR_MAX_LEN_GENSTRING];
    int iStart;
    int iStop;
} MBR_LookUp;

//#endif  /* MBR_LOCAL */

int MBR_Download(const char *pcParam, const char *pcValue);
int MBR_SerialPortInit(void);
int MBR_FreqSynthInit( int iStartBit, int iStopBit);
int MBR_AttenuatorInit(int iDevID, long long *pllBitmap);
int MBR_CreateDeviceLookup(void);
int MBR_WriteBitmap(long long llBitmap);
int MBR_SetBits(int iStartBit, int iStopBit, int iValue, long long *pllBitmap);
int MBR_GetBits(char *pcDevice, char *pcBits);
int MBR_DevWrite(int iAddress, int iVal);
int MBR_Freq2AB(const char *pcFreq);
long long MBR_Bitmap2LongLong(const char* pcVal);
void MBR_LongLong2Bitmap(long long llnum, char acBitmap[]);
float MBR_GetAttnFromBitmap(const char* pcVal);
void MBR_DevClose();

#endif  /* __MBR_SERIALPORT_H__ */

