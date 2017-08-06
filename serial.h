#ifndef _SERIAL_H
#define _SERIAL_H 1

typedef int     INT32;
typedef short   INT16;
typedef char    INT8;
typedef unsigned int UNIT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;

/* serial.c */
INT32 OpenComPort (INT32 ComPort, INT32 baudrate, INT32 databit,
										const char *stopbit, char parity);
void CloseComPort (void);

INT32 ReadComPort (void *data, INT32 datalength);
INT32 WriteComPort (UINT8 * data, INT32 datalength);

/**
 * export serial fd to other program to perform
 * directly read, write to serial.
 * 
 * @return serial's file description 
 */
int getPortFd();

#endif /* serial.c */

