#include <myDP8051XP.H>
#include "global.h"

#if 0
/*****************************************************************************/
/* Function Name:		MPU_SendSerialPtr
/* Description:			send const strings to serial port
/* Input parameter:		messageptr	:	the pointer of the string which is to be output
/* 						size		:	number of chars of the string
/* Output parameter:	None
/* revision history:	
/*
/*
/*****************************************************************************/

MPU_COMM_STATUS MPU_SendSerialPtr(char code * messageptr, unsigned char size)
{

	return MPU_COMM_SUCCESS;
#if 0
 	if ((g_ucNumber_Of_OutputChar==0)&&(g_bStart_Wait_Counter==0)&&(g_bStart_Break_Counter==0))
	{
		ES = 0;
		g_bSend_Only = 1;
		g_unCBuffer.Bufferptr.msgptr = (char*)messageptr;
		g_ucNumber_Of_OutputChar = size-1;
		g_bUse_Buffer = 0;
		SBUF =*g_unCBuffer.Bufferptr.msgptr;		
		ES =1;
		return MPU_COMM_SUCCESS;
	}

	return MPU_COMM_OCCUPIED;
#endif
}

/*****************************************************************************/
/* Function Name:		MPU_SendSerialPtrVariable
/* Description:			send variable strings to serial port
/* Input parameter:		messageptr	:	the pointer of the string which is to be output
/* 						size		:	number of chars of the string
/* Output parameter:	None
/* revision history:	
/*
/*
/*****************************************************************************/

MPU_COMM_STATUS MPU_SendSerialPtrVariable(char idata * messageptr, unsigned char size)
{
 
 	return MPU_COMM_SUCCESS;
#if 0
 	if ((g_ucNumber_Of_OutputChar==0)&&(g_bStart_Wait_Counter==0)&&(g_bStart_Break_Counter==0))
	{
		ES = 0;
		g_bSend_Only = 1;
		g_unCBuffer.Bufferptr.msgptr = (char*)messageptr;
		g_ucNumber_Of_OutputChar = size-1;
		g_bUse_Buffer = 0;
		SBUF =*g_unCBuffer.Bufferptr.msgptr;		
		ES =1;
		return MPU_COMM_SUCCESS;
	}

	return MPU_COMM_OCCUPIED;
#endif
}

#endif