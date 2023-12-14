#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "type.h"
#include "PD.h"
	

#define		PASS					0x00
#define		FAIL					0xff

#define		FALSE					0x00
#define		TRUE					0x01

#define		OEM_PARADE_VERSION_NUM		0x06	// increase 1 every release version
#define		PROJECT_ID					0x01	// Google

//#define		CHIP_VERSION_NUM		0x00	// 0x00 for A0

#define		VBUS_OCP
//#define		VBUS_OVP

enum CC_STATE
{
	CC1_RD = 0x01,
	CC2_RD = 0x10,
	CC1_RA = 0x02,
	CC2_RA = 0x20,
	CC1_RP = 0x04,
	CC2_RP = 0x40,
	CC1_OPEN_CC2_OPEN = 0x00,
	CC1_RD_CC2_OPEN = 0x01,
	CC1_OPEN_CC2_RD = 0x10,
	CC1_OPEN_CC2_RA = 0x20,
	CC1_RA_CC2_OPEN = 0x02,
	CC1_RD_CC2_RA = 0x21,
	CC1_RA_CC2_RD = 0x12,
	CC1_RD_CC2_RD = 0x11,
	CC1_RA_CC2_RA = 0x22,
	CC1_RP_CC2_OPEN = 0x04,
	CC1_OPEN_CC2_RP = 0x40,
	CC1_RP_CC2_RD = 0x14,
	CC1_RD_CC2_RP = 0x41,
	CC1_RP_CC2_RP = 0x44,
	CC1_RA_CC2_RP = 0x42,
	CC1_RP_CC2_RA = 0x24,
};

#define DEBUG_ACCESSORY_MODE	0x11	
#define AUDIO_ACCESSORY_MODE	0x22

extern unsigned char xdata g_ucTick;
extern unsigned char xdata g_ucTicks;

extern volatile unsigned char xdata g_vucxVersion;
extern volatile unsigned char xdata g_vucxProjectID;

extern unsigned char xdata g_ucxDisConnIgnore;
extern unsigned char xdata ucxCCState;
extern unsigned char xdata g_ucxRole_Control;
extern unsigned short xdata usxDelay;

extern unsigned short xdata g_usx_VBUS_SINK_DISCONNECT;
extern unsigned short xdata g_usx_VBUS_STOP_DISCHARGE;
extern unsigned short xdata g_usx_VBUS_VOLTAGE_ALARM_HI;
extern unsigned short xdata g_usx_VBUS_VOLTAGE_ALARM_LO;

extern unsigned char xdata g_ucxRaDisconnCnt;
extern unsigned char xdata g_ucxRpVal;
//extern unsigned char xdata g_ucxVBUS_Discharge;
extern unsigned char xdata g_ucxVBUS_Force_Discharge;
extern unsigned char xdata g_ucxExitSample;
#endif
