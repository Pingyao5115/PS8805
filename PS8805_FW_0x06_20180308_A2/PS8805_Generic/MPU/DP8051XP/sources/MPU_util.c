#include <intrins.h>
#include <myDP8051XP.H>
//#include <string.h>
//#include "mpu_serial.h"
#include "global.h"
//#include <absacc.h>
#include "registers_map.h"
//#include "MPU_command.h"
//#include "MPU_SPIFunction.h"
#include "MPU_Functions.h"
//#include "cl_Functions.h"

t_INTMASK code s_cIntMask0[] = 
{
	{ 0x02, 0x9c, 0xff },
	{ 0x02, 0xe6, 0xff },
	{ 0x02, 0xd8, 0x05 },
	{ 0x02, 0x41, 0x05 },

	{ 0xff, 0xff, 0xff },		// last
};

t_INTMASK code s_cIntMask1[] = 
{
	{ 0xff, 0xff, 0xff },		// last
};

//extern MPU_COMM_STATUS MPU_SendSerialPtr(char code * messageptr, unsigned char size);


void MPU_SetINTMask0(void)
{
	unsigned char idata uciIndex = 0;

	while ( s_cIntMask0[uciIndex].ucPage != 0xff )
	{
		g_vucxReg[ s_cIntMask0[uciIndex].ucPage * 256 + s_cIntMask0[uciIndex].ucOffset ] |= 
		   s_cIntMask0[uciIndex].ucValue;
		
		uciIndex++;
	}
}
/*
void MPU_ClearINTMask0(void)
{
	unsigned char idata uciIndex = 0;

	while ( s_cIntMask0[uciIndex].ucPage != 0xff )
	{
		g_vucxReg[ s_cIntMask0[uciIndex].ucPage * 256 + s_cIntMask0[uciIndex].ucOffset ] &= 
		   ~s_cIntMask0[uciIndex].ucValue;
		
		uciIndex++;
	}
} */

void MPU_SetINTMask1(void)
{
	unsigned char idata uciIndex = 0;

	while ( s_cIntMask1[uciIndex].ucPage != 0xff )
	{
		g_vucxReg[ s_cIntMask1[uciIndex].ucPage * 256 + s_cIntMask1[uciIndex].ucOffset ] |= 
		   s_cIntMask1[uciIndex].ucValue;
		
		uciIndex++;
	}
}
/*
void MPU_ClearINTMask1(void)
{
	unsigned char idata uciIndex = 0;

	while ( s_cIntMask1[uciIndex].ucPage != 0xff )
	{
		g_vucxReg[ s_cIntMask1[uciIndex].ucPage * 256 + s_cIntMask1[uciIndex].ucOffset ] &= 
		   ~s_cIntMask1[uciIndex].ucValue;
		
		uciIndex++;
	}
}*/

void MPU_EnableINT0( void )
{
//	CTLIRQ_CTL = 0xF3;//enable [3]WAIT_IRQ_MASK & [2]READ_WAIT_IRQ
}

void MPU_EnableINT1( void )
{
//	ALERT_MASK_LOW	= 0x00;	//0b: Interrupt masked,1b: Interrupt unmasked
//	ALERT_MASK_HIGH	= 0x00;	

}


/*****************************************************************************/
/* Function Name:		MPU_DisableINT
/* Description:			disable INT request to protect shared global variables
/* Input parameter:		none
/* Output parameter:	None
/* revision history:	
/*
/*
/*****************************************************************************/
void MPU_DisableINT(void)
{
	EA = 0;
	ES = 0;
	ET1 = 0;
	EX0 = 0;
	EX1 = 0;
    ET0 = 0;
}

/*
void MPU_OpenTimer0INT(void)
{
	EA = 1;
	ES = 0;
	ET1 = 0;
	EX0 = 0;
	EX1 = 0;
    ET0 = 1;
}
*/
/*****************************************************************************/
/* Function Name:		MPU_EnableINT
/* Description:			enable INT request after shared global variables processed
/* Input parameter:		none
/* Output parameter:	None
/* revision history:	
/*
/*
/*****************************************************************************/
void MPU_EnableINT(void)
{
	ET1 = 0;
    ET0 = 0;
//    ES = 1;
	EX0 = 1;
	EX1 = 1;
    EA = 1;
}

/**************************************************************************************************/
/*	Function Name:		MPU_SetVerNum
/*	Description:		set version number shown in debug utility by I2C
/* Input parameter:		none
/* Output parameter:	None
/* revision history:	
/*
/*
/*****************************************************************************/
void MPU_SetVerNum( unsigned char ucOEM, unsigned char ucMajor, unsigned char ucMiddle, unsigned char ucMinor )
{
	ucOEM = ucOEM;
//	FW_VER_MAJOR  	= ucMajor; 
//	FW_VER_MIDDLE  	= ucMiddle;
//	FW_VER_MINOR  	= ucMinor;
	g_vucxVersion	= OEM_PARADE_VERSION_NUM;
	g_vucxProjectID = PROJECT_ID;
}