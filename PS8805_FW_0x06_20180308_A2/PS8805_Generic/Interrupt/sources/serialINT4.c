#include <myDP8051XP.H>
#include "global.h"

unsigned char idata g_uciUARTInNum = 0;
bit g_bUARTBufIndex = 0;

void serial_INT(void) interrupt 4
{
	if ( RI == 1 )
	{
//		g_vucxReg15[0x0e]++;

		if( g_uciUARTInNum < UARTINBUFLENGTH - 1 )
		{
			if ( ( g_ucUARTBufInUse & ( 1 << (unsigned char)g_bUARTBufIndex ) ) == 0 )
			{
				g_uciUARTIn[g_bUARTBufIndex][g_uciUARTInNum] = SBUF;
//				g_vucxReg15[g_uciUARTInNum + (unsigned char )g_bUARTBufIndex * 16] = g_uciUARTIn[g_bUARTBufIndex][g_uciUARTInNum];
				if ( (g_uciUARTIn[g_bUARTBufIndex][g_uciUARTInNum] == 0x0d) || ( g_uciUARTInNum == UARTINBUFLENGTH - 2) )
				{
					g_uciUARTIn[g_bUARTBufIndex][g_uciUARTInNum + 1 ] = 0;
//					g_vucxReg15[g_uciUARTInNum+1 +(unsigned char )g_bUARTBufIndex * 16] = g_uciUARTIn[g_bUARTBufIndex][g_uciUARTInNum+1];

					if( g_sLowPrio_Command_Que[g_ucLowPrio_Command_WIdx].ucCommandType == COMMAND_EMPTY )
					{
						g_sLowPrio_Command_Que[g_ucLowPrio_Command_WIdx].ucCommandType = UART_COMMAND;
						g_sLowPrio_Command_Que[g_ucLowPrio_Command_WIdx].ucCommandParam1 = (unsigned char)g_bUARTBufIndex;

						g_ucUARTBufInUse |= ( 1 << (unsigned char)g_bUARTBufIndex );
					
						g_bUARTBufIndex ^= 1;
						g_uciUARTInNum = 0;

						g_ucLowPrio_Command_WIdx++;
						if( g_ucLowPrio_Command_WIdx == LOWPRIOCOMMANDLENGTH )
						{
							g_ucLowPrio_Command_WIdx = 0;
						}
						g_uciCmd = 0;
					}				
				}
				else
				{
					g_uciUARTInNum++;
					g_uciCmd = 0;

					if( g_uciUARTInNum == UARTINBUFLENGTH )
					{
						g_uciUARTInNum = 0;
						g_bUARTOverflow = 1;
					}
				}

			}
		}
		
		

		RI = 0;
	}
	else if( TI == 1 )
	{
//		g_vucxReg15[0x0d]++;
		TI = 0;
		
//		if( g_bSerialBusy )
		{
		g_puccSerialBuf++;
		if( *g_puccSerialBuf != '\0' )
		{
			SBUF = *g_puccSerialBuf;
		}
		else
		{
			g_bSerialBusy = 0;
		}
		}
	}
}
/*****************************************************************************/
/* Function Name:		CommInt
/* Description:			get a char from serial port or put char to serial if not all
/*						chars have been output
/* Input parameter:		none
/* Output parameter:	none
/* revision history:	
/*
/*
/*****************************************************************************/
#if 0
void CommInt(void)
{
	if (RI==1)
	{
		RI=0;
		if (g_bSend_Only == 0)
		{
			g_unCBuffer.send_data[g_unComm_Index.rec_index++] = SBUF;
			if(g_unComm_Index.rec_index>=8)
			{
				g_unComm_Index.rec_index = 0;		// in case of array overflow by Priscilla 2007/07/02
			}
			
			g_uiBreak_Counter = 0;		// reset break counter. it will increase every timer1 interrupt
										// it is a sign to show whether a sequence of chars make up a command
										// or several commands
			g_bStart_Wait_Counter = 0;
			g_bStart_Break_Counter = 1;
		}
        else if(g_unComm_Index.rec_index==0)
        {
            g_bSend_Only=0;
			g_unCBuffer.send_data[g_unComm_Index.rec_index++] = SBUF;
			g_uiBreak_Counter = 0;
			g_bStart_Wait_Counter = 0;
			g_bStart_Break_Counter = 1;
        }
	}
	else if (TI==1)
	{
		TI = 0;
		g_bStart_Break_Counter = 0;
		g_uiBreak_Counter = 0;
		if (g_ucNumber_Of_OutputChar>=1)
		{
			g_ucNumber_Of_OutputChar--;
			if (g_bUse_Buffer)
				SBUF = g_unCBuffer.send_data[g_unComm_Index.send_index++];
			else
				SBUF = *(++g_unCBuffer.Bufferptr.msgptr);
		}
		//else
		if (g_ucNumber_Of_OutputChar == 0)
		{
			g_bSend_Only = 0;
			g_unComm_Index.rec_index = 0;
			g_bStart_Wait_Counter = 1;
			//send_index = 0;
			g_ucNumber_Of_OutputChar = 0;
		}
	}
	else
	{
//		serial_counter++;	
	}

}




/*****************************************************************************/
/* Function Name:		serial_INT
/* Description:			interrupt service routine for UART
/* Input parameter:		none
/* Output parameter:	none
/* revision history:	
/*
/*
/*****************************************************************************/
void serial_INT(void) interrupt 4
{
	//CommInt();
}
#endif