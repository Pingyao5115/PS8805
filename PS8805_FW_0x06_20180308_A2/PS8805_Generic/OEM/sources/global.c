/*******************************************************************************/
/********		Parade	Technologies,Inc.          *****************************/
/*******************************************************************************/

/*******************************************************************************/
/* File name:			global.inc							
/* Description:			global variables
/*******************************************************************************/

// naming regulation
// global variable:			g_
// unsigned char:			uc
// unsigned char far:		ucf
// unsigned char code:		ucc
// unsigned int:			ui
// bit:						b
// union:					un
// struct:					s
// volatile:				v
// xdata:					x



#include "global.h"

unsigned char xdata g_ucTick = 0;
unsigned char xdata g_ucTicks = 0;

volatile unsigned char xdata g_vucxVersion _at_ 0x382;
volatile unsigned char xdata g_vucxProjectID _at_ 0x064;

unsigned char xdata g_ucxDisConnIgnore = 0;
unsigned char xdata ucxCCState = 0;
unsigned char xdata g_ucxRole_Control;
unsigned short xdata usxDelay;

unsigned short xdata g_usx_VBUS_SINK_DISCONNECT;
unsigned short xdata g_usx_VBUS_STOP_DISCHARGE;
unsigned short xdata g_usx_VBUS_VOLTAGE_ALARM_HI;
unsigned short xdata g_usx_VBUS_VOLTAGE_ALARM_LO;

unsigned char xdata g_ucxRaDisconnCnt = 0;
unsigned char xdata g_ucxRpVal = 0;
//unsigned char xdata g_ucxVBUS_Discharge = 0;
unsigned char xdata g_ucxVBUS_Force_Discharge = 0;
unsigned char xdata g_ucxExitSample = 0;
