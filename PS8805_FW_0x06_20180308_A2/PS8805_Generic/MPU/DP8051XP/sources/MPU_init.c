#include <myDP8051XP.H>
#include "registers_map.h"

/*****************************************************************************/
/* Function Name:		MPU_Init
/* Description:			Initialize timer0, timer1, UART
/* Input parameter:		None
/* Output parameter:	None
/* revision history:	
/*
/*
/*****************************************************************************/

void MPU_Init(void)
{
	SCON	=	0X50;		   // 8 bit UART, baud rate can be set. enable receive
//	TMOD	=	TMOD | 0X20;   // Timer1 works at Mode2, load TL1 from TH1 automaticly
//	TMOD	=	TMOD | 0X10;   // Timer1 works at Mode1, 16bit counter
//	PCON	|=	0X80;		   // SMOD0=1, baud rate is 1/16 of overflow frequency of Timer1 
							   // 152542.3/16=9533.90			 76923 / 16 = 4807
    
	//PCON    |=  0X10;       //Make XDATA writable
    //60Mhz
	TH0         =   0X9E;			   	// 65536 - 0x9E58 = 25000, 60MHz/12=5MHz, that's 1/200s.
    TL0         =   0X58;			  	// so in ISR for Timer0, count to 200, add 1s.

    TH1         =   0X3C;	 //10ms
    TL1         =   0XB0;

	TMOD	    =	TMOD | 0x11;	   	// Timer0,1 works at Mode 1, 16bit counter

//	TR1		=	1;		  // start Timer1
//  TR0     =   1;		  // start Timer0


//	PX0         =   1;          //0: low priority     1: high priority
//	PX1         =   1;          //0: low priority     1: high priority
    IT0         =   0;          //0: level trigger   1: edge trigger
    IT1         =   0;          //0: level trigger   1: edge trigger

#ifdef ENABLE_MPU_RESET_COUNTER
	OTHER_CTRL1 = 0x10;  		//[7]STUCK_RST_IGNORE
                              	//[6]FW_CNT_CLR(0->1 toggle)
                              	//[5:4]TIMEOUT_SEL, 00:250ms, 01:500ms, 10:750ms, 11:1000ms
#else
	OTHER_CTRL1 = 0x90;
#endif

/*	// 2 seconds		   
	ECNT0  = 0x00;
	ECNT1  = 0x0E;
	ECNT2  = 0x27;
	ECNT3  = 0x07;
	ECNT4  = 0x00;
*/
//	EIE |= 0x03;		// enable 40bit counter 1,2 interrupt
//	EIE |= 0x01;		// enable 40bit counter 1 interrupt
}