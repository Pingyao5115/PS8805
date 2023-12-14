#include <myDP8051XP.H>
#include "global.h"
#include "PD.h"
#include "registers_map.h"

/*********************************************************************************************/
/*  Name:			ext1_INT
/*	Description:	Interrupt Service Routine for INT2
/*  				when an interrupt request comes, send a command to low priority command
/*					queue.
/*					clear the interrupt request
/*					if command queue is full, discard the event.
/********************************************************************************************/

void ext1_INT(void) interrupt 2
{
//	unsigned char xdata Rd = 0;
//	unsigned char xdata Ra = 0;

/*	if( ALERT_STATUS_1 & 0x02 & (ALERT_MASK_LOW) )	// Power status changed
	{
		if ( ( GPIO_RD_BACK & 0x40 ) == 0 )
		{
			g_vucxReg5[0xF2]++;
	
			if ( POWER_STATUS & 0x18 & POWER_STATUS_MASK )
			{
				DISABLE_SOURCE_VBUS;//turn off VBUS
				ALERT_STATUS_2 |= 0x02;//ALERT.Fault
#ifdef VBUS_OCP
				FAULT_STATUS |= 0x08;//Internal or External OCP VBUS Over Current Protection Fault
#else
//				FAULT_STATUS |= 0x04;//Internal or External OVP VBUS Over Voltage Protection Fault
#endif
			}
			ALERT_STATUS_1 = ALERT_STATUS_1 & (0x02);
		}
	}*/
/*	if( ALERT_STATUS_1 & 0x01 & (ALERT_MASK_LOW) )	// CC status changed
	{
		if ( PDC_STAT_31_24 & 0x01 )//DRP
		{
			g_vucxReg5[0xF1]++;

			ALERT_MASK_LOW &= 0xFE;
			ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
		}
	}*/
					
	{
	
		//CC1,CC2:10mV;VBUS:100mV;VCONN:25mV			
#ifdef TCPM_DEBOUNCE
//		if( CC_DET_IRQ_STATUS0 & 0x18 & (~REG_CC_DET_INT_MASK0) )	// CC1_CONN_FILT_STATUS,CC2_CONN_FILT_STATUS
		if( CC_DET_IRQ_INT0 & 0x18 )	// CC1_CONN_FILT_STATUS,CC2_CONN_FILT_STATUS
#else
//		if( CC_DET_IRQ_STATUS0 & 0x03 & (~REG_CC_DET_INT_MASK0) )	// CC1_CONN_DEB_STATUS,CC2_CONN_DEB_STATUS
		if( CC_DET_IRQ_INT0 & 0x03 )	// CC1_CONN_DEB_STATUS,CC2_CONN_DEB_STATUS
#endif
		{
//			REG_CC_DET_INT_MASK = 0xFC;

/*			REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
			REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
			REG_DET_CTRL1 |= 0x10;
			REG_DET_CTRL1 &= 0xEF;*/
#ifdef TCPM_DEBOUNCE
//g_vucxReg5[0x30] = PDC_STAT_23_16;
//g_vucxReg5[0x31] = ROLE_CONTROL;
//g_vucxReg5[0x32] = CC_STATUS;
//g_vucxReg5[0x01] = 1;
//			g_vucxReg5[0xA1]++;
			REG_IRQ_SRC_CTL |= 0x01;
#if 0
			if( CC_DET_IRQ_STATUS0 & 0x08 )	// CC1_CONN_FILT_STATUS
			{																										  
	REG_GPIOP_OUT |= GPIO7;
				g_vucxReg5[0xA1]++;
#if 0
/*				if ( ( ( ucxCCState != CC1_RA_CC2_OPEN ) && ( ucxCCState != CC1_OPEN_CC2_RA ) ) || ( ( PDC_STAT_23_16 & 0x60 ) == 0x60 ) )
				{
					g_vucxReg5[0xB1]++;
					ALERT_MASK_LOW |= 0x01;
				}*/
				if ( ( ( ucxCCState == CC1_RA_CC2_OPEN ) || ( ucxCCState == CC1_OPEN_CC2_RA ) ) && ( ( PDC_STAT_23_16 & 0x60 ) != 0x60 ) )
				{
					g_vucxReg5[0xB1]++;
				}
				else
				{
					g_vucxReg5[0xC1]++;
					ALERT_MASK_LOW |= 0x01;
				}
#endif
			}
			if( CC_DET_IRQ_STATUS0 & 0x10 )	// CC2_CONN_FILT_STATUS
			{
				g_vucxReg5[0xA2]++;
#if 0
/*				if ( ( ( ucxCCState != CC1_RA_CC2_OPEN ) && ( ucxCCState != CC1_OPEN_CC2_RA ) ) || ( ( PDC_STAT_23_16 & 0x60 ) == 0x60 ) )
				{
					g_vucxReg5[0xB2]++;
					ALERT_MASK_LOW |= 0x01;
				}*/
				if ( ( ( ucxCCState == CC1_RA_CC2_OPEN ) || ( ucxCCState == CC1_OPEN_CC2_RA ) ) && ( ( PDC_STAT_23_16 & 0x60 ) != 0x60 ) )
				{
					g_vucxReg5[0xB2]++;
				}
				else
				{
					g_vucxReg5[0xC2]++;
					ALERT_MASK_LOW |= 0x01;
				}
#endif
			}
#endif
#else//TCPM_DEBOUNCE
			if( CC_DET_IRQ_STATUS0 & 0x01 )	// CC1_CONN_DEB_STATUS
			{
				g_vucxReg5[0xA1]++;
//				ALERT_MASK_LOW |= 0x01;
				if ( ( ( ROLE_CONTROL & 0x4F ) == 0x0A ) || ( ( ( ROLE_CONTROL & 0x40 ) == 0x40 ) && ( ( CC_STATUS & 0x10 ) == 0x10 ) ) )
				{
					g_vucxReg5[0xB1]++;

					ALERT_MASK_LOW |= 0x01;
//					ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
//					ALERT_STATUS_1 |= 0x01;
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01; 
					REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
					REG_DET_CTRL1 |= 0x10;
					REG_DET_CTRL1 &= 0xEF;
					ucxCCState = CC1_RP_CC2_OPEN;
				}
				if ( ( ( ROLE_CONTROL & 0x4F ) == 0x05 ) || ( ( ( ROLE_CONTROL & 0x40 ) == 0x40 ) && ( ( CC_STATUS & 0x10 ) == 0x00 ) ) )
				{
					g_vucxReg5[0xC1]++;

					if ( ( ucxCCState != CC1_RA_CC2_OPEN ) && ( ucxCCState != CC1_OPEN_CC2_RA ) )
					{
						g_vucxReg5[0xD1]++;

						ALERT_MASK_LOW |= 0x01;
//						ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
//						ALERT_STATUS_1 |= 0x01;
/*						REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_RD_CC2_OPEN;*/
					}
					else
					{
//						return;
					}
				}
			}
			if( CC_DET_IRQ_STATUS0 & 0x02 )	// CC2_CONN_DEB_STATUS
			{
				g_vucxReg5[0xA2]++;
//				ALERT_MASK_LOW |= 0x01;
				if ( ( ( ROLE_CONTROL & 0x4F ) == 0x0A ) || ( ( ( ROLE_CONTROL & 0x40 ) == 0x40 ) && ( ( CC_STATUS & 0x10 ) == 0x10 ) ) )
				{
					g_vucxReg5[0xB2]++;

					ALERT_MASK_LOW |= 0x01;
//					ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
//					ALERT_STATUS_1 |= 0x01;
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04; 
					REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
					REG_DET_CTRL1 |= 0x10;
					REG_DET_CTRL1 &= 0xEF;
					ucxCCState = CC1_OPEN_CC2_RP;
				}
				if ( ( ( ROLE_CONTROL & 0x4F ) == 0x05 ) || ( ( ( ROLE_CONTROL & 0x40 ) == 0x40 ) && ( ( CC_STATUS & 0x10 ) == 0x00 ) ) )
				{
					g_vucxReg5[0xC2]++;

					if ( ( ucxCCState != CC1_RA_CC2_OPEN ) && ( ucxCCState != CC1_OPEN_CC2_RA ) )
					{
						g_vucxReg5[0xD2]++;

						ALERT_MASK_LOW |= 0x01;
//						ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
//						ALERT_STATUS_1 |= 0x01;
/*						REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_OPEN_CC2_RD;*/
					}
					else
					{
//						return;
					}
				}
			}
#endif//TCPM_DEBOUNCE
			g_vucxReg5[0x90] |= 0x01;
			g_vucxReg5[0x91] = 0;
			g_vucxReg5[0x92] = 0;
			g_vucxReg5[0x93] = 0;
			g_vucxReg5[0x94] = 0;
			g_vucxReg5[0x95] = 0;
			g_vucxReg5[0x96] = 0;
			g_vucxReg5[0x8F] = 0;
			g_vucxReg5[0x20] = 0;
			g_vucxReg5[0x21] = 0;

#ifdef COMPARATOR
			if ( ( ROLE_CONTROL & 0x40 ) == 0x40 )//DRP
			{
				g_vucxReg5[0x91] |= 0x01;
				
				if ( ( CC_STATUS & 0x30 ) == 0x00 )//TCPC is presenting Rp
				{
					g_vucxReg5[0x92] |= 0x01;

					//source
					if ( ( PDC_STAT_23_16 & 0x60 ) == 0x20 )//CC2_CONN
					{
						g_vucxReg5[0x93] |= 0x01;

						if ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 )
						{
							g_vucxReg5[0x94] = 0x01;
							g_vucxReg5[0x8F] = 0x51;

/*							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
*/
							ucxCCState = CC1_OPEN_CC2_RA;
						}
						else
						{
							g_vucxReg5[0x94] = 0x02;
							g_vucxReg5[0x8F] = 0x01;
							
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_OPEN_CC2_RD;
						}
					}
					else if ( ( PDC_STAT_23_16 & 0x60 ) == 0x40 )//CC1_CONN
					{
						g_vucxReg5[0x93] |= 0x02;

						if ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 )
						{
							g_vucxReg5[0x94] = 0x01;
							g_vucxReg5[0x8F] = 0x54;

/*							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
*/
							ucxCCState = CC1_RA_CC2_OPEN;
						}
						else
						{
							g_vucxReg5[0x94] = 0x02;
							g_vucxReg5[0x8F] = 0x04;
							
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RD_CC2_OPEN;
						}
					}
					else if ( ( PDC_STAT_23_16 & 0x60 ) == 0x60 )//CC1_CONN,CC2_CONN
					{
						g_vucxReg5[0x93] |= 0x04;

						if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) )//port partner is CC1:Rd,CC2:Ra
						{
							g_vucxReg5[0x94] = 0x01;
							g_vucxReg5[0x8F] = 0x11;//
	
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x06; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RD_CC2_RA;
						}
						else if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) )//port partner is CC1:Ra,CC2:Rd
						{
							g_vucxReg5[0x94] = 0x02;
							g_vucxReg5[0x8F] = 0x12;//
	
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x09; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RA_CC2_RD;
						}
						else if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) )
						{
							g_vucxReg5[0x94] = 0x03;
							g_vucxReg5[0x8F] = 0x21;
	
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x05;
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RA_CC2_RA;
						}
						else if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) )
						{
							g_vucxReg5[0x94] = 0x04;
							g_vucxReg5[0x8F] = 0x31;
	
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0A; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RD_CC2_RD;
						}
					}
				}
				else if ( ( CC_STATUS & 0x30 ) == 0x10 )//TCPC is presenting Rd
				{
					g_vucxReg5[0x92] |= 0x02;
	
					//sink
					if ( ( PDC_STAT_23_16 & 0x60 ) == 0x40 )//CC1_CONN
					{
						g_vucxReg5[0x93] |= 0x01;
						g_vucxReg5[0x8F] = 0x41;//
						
						if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) )//port partner is CC1:Rp:3A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x03;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x03;
							g_ucxRpVal = RP_3_0_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC1:Rp:1.5A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x02;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02;
							g_ucxRpVal = RP_1_5_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC1:Rp:0.9A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x01;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01;
							g_ucxRpVal = RP_0_9_A;
						}

						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_RP_CC2_OPEN;
					}
					if ( ( PDC_STAT_23_16 & 0x60 ) == 0x40 )//CC2_CONN
					{
						g_vucxReg5[0x93] |= 0x02;
						g_vucxReg5[0x8F] = 0x42;//
						
						if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) )//port partner is CC2:Rp:3A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x03;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0C;
							g_ucxRpVal = RP_3_0_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC2:Rp:1.5A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x02;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08;
							g_ucxRpVal = RP_1_5_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC2:Rp:0.9A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x01;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04;
							g_ucxRpVal = RP_0_9_A;
						}

						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_OPEN_CC2_RP;
					}
				}
			}
			else
			{
				g_vucxReg5[0x91] |= 0x02;

				if ( ( ROLE_CONTROL & 0x0F ) == 0x05 )//TCPC is Rp
				{
					g_vucxReg5[0x92] |= 0x01;
		
					//source
					if ( ( PDC_STAT_23_16 & 0x60 ) == 0x20 )//CC2_CONN
					{
						g_vucxReg5[0x93] |= 0x01;

						if ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 )
						{
							g_vucxReg5[0x94] = 0x01;
							g_vucxReg5[0x8F] = 0x57;

/*							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
*/
							ucxCCState = CC1_OPEN_CC2_RA;
						}
						else
						{
							g_vucxReg5[0x94] = 0x02;

							g_vucxReg5[0x8F] = 0x07;//
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_OPEN_CC2_RD;
						}
					}
					else if ( ( PDC_STAT_23_16 & 0x60 ) == 0x40 )//CC1_CONN
					{
						g_vucxReg5[0x93] |= 0x02;

						if ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 )
						{
							g_vucxReg5[0x94] = 0x01;
							g_vucxReg5[0x8F] = 0x5A;

/*							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
*/
							ucxCCState = CC1_RA_CC2_OPEN;
						}
						else
						{
							g_vucxReg5[0x94] = 0x02;

							g_vucxReg5[0x8F] = 0x0A;//
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RD_CC2_OPEN;
						}
					}
					else if ( ( PDC_STAT_23_16 & 0x60 ) == 0x60 )//CC1_CONN,CC2_CONN
					{
						g_vucxReg5[0x93] |= 0x04;

						if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) )//port partner is CC1:Rd,CC2:Ra
						{
							g_vucxReg5[0x94] = 0x01;
							g_vucxReg5[0x8F] = 0x13;//

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x06; 
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RD_CC2_RA;
						}
						else if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) )//port partner is CC1:Ra,CC2:Rd
						{
							g_vucxReg5[0x94] = 0x02;
							g_vucxReg5[0x8F] = 0x14;//

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x09; 
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RA_CC2_RD;
						}
						else if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) )
						{
							g_vucxReg5[0x94] = 0x03;
							g_vucxReg5[0x8F] = 0x23;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x05; 
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RA_CC2_RA;
						}
						else if ( ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) )
						{
							g_vucxReg5[0x94] = 0x04;
							g_vucxReg5[0x8F] = 0x33;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0A;
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RD_CC2_RD;
						}
					}
				}	
				else if ( ( ROLE_CONTROL & 0x0F ) == 0x0A )//TCPC is Rd
				{
					g_vucxReg5[0x92] |= 0x02;

					//sink
					if ( ( PDC_STAT_23_16 & 0x60 ) == 0x40 )//CC1_CONN
					{
						g_vucxReg5[0x93] |= 0x01;
						g_vucxReg5[0x8F] = 0x43;//
						
						if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) )//port partner is CC1:Rp:3A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x03;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x03;
							g_ucxRpVal = RP_3_0_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC1:Rp:1.5A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x02;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02;
							g_ucxRpVal = RP_1_5_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC1:Rp:0.9A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x01;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01;
							g_ucxRpVal = RP_0_9_A;
						}

						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_RP_CC2_OPEN;
					}
					if ( ( PDC_STAT_23_16 & 0x60 ) == 0x40 )//CC2_CONN
					{
						g_vucxReg5[0x93] |= 0x02;
						g_vucxReg5[0x8F] = 0x44;//
						
						if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) )//port partner is CC2:Rp:3A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x03;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0C;
							g_ucxRpVal = RP_3_0_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC2:Rp:1.5A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x02;
			
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08;
							g_ucxRpVal = RP_1_5_A;
						}
						else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//port partner is CC2:Rp:0.9A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x01;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04;
							g_ucxRpVal = RP_0_9_A;
						}

						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_OPEN_CC2_RP;
					}
				}
			}
#else

CC_SAMPLE:
			if ( REG_DET_CTRL2 & 0x40 )//ADC is sampling VBUS
			{
				REG_DET_CTRL2 &= 0x9B;//stop
				REG_DLPF_CTRL0 |= 0x80;//Software reset for low pass filter
				REG_DLPF_CTRL0 &= 0x7F;
				g_ucxExitSample = 1;
			}

//g_vucxReg5[0x9B] = CC_DET_IRQ_INT0;
//g_vucxReg5[0x9C] = CC_DET_IRQ_STATUS0;
//g_vucxReg5[0x9D] = PDC_STAT_23_16;

//	ADDRCFG0 = 0x15;//enable I2C access	******this line should be removed, otherwise monitor will be failed****
//g_vucxReg5[0x33] = CC_STATUS;
//REG_GPIOP_OUT = REG_GPIOP_OUT | (GPIO6);
			REG_DET_CTRL0 &= 0xB4;//stop
			CC_DET_IRQ_STATUS2 = 0x04;
			REG_DET_CTRL2 &= 0x9B;
//			if( CC_DET_IRQ_INT0 & 0x08 )	// CC1_CONN_FILT_STATUS
			{
				REG_DET_CTRL0 |= 0x01;//SW_ADC_CC1_EN
				REG_DET_CTRL0 |= 0x40;//SW_DLPF_START
				while ( (!(CC_DET_IRQ_STATUS2 & 0x04)) /*&& ( REG_DET_CTRL0 & 0x40 )*/ )
				{
					g_vucxReg5[0x82]++;
				}
				CC_DET_IRQ_STATUS2 = 0x04;
				REG_DET_CTRL0 &= 0xB4;//stop
				g_vucxReg5[0x20] = REG_CC1_DCC;
			}
//			if ( ( REG_CC1_DCC >= 0xD0 ) && ( REG_CC1_DCC <= 0xF0 ) )
			{
//				REG_GPIOP_OUT |= GPIO7;
			}
//g_vucxReg5[0x34] = CC_STATUS;

//			REG_DET_CTRL2 &= 0x9B;
//			if( CC_DET_IRQ_INT0 & 0x10 )	// CC2_CONN_FILT_STATUS
			{
				REG_DET_CTRL0 |= 0x02;//SW_ADC_CC2_EN
				REG_DET_CTRL0 |= 0x40;//SW_DLPF_START
				while ( (!(CC_DET_IRQ_STATUS2 & 0x04)) /*&& ( REG_DET_CTRL0 & 0x40 )*/ )
				{
					g_vucxReg5[0x83]++;
				}
				CC_DET_IRQ_STATUS2 = 0x04;
				REG_DET_CTRL0 &= 0xB4;//stop
				g_vucxReg5[0x21] = REG_CC2_DCC;
			}
#if 1
			//re-sample CC1 in case glitch when sampling CC1
//			if( CC_DET_IRQ_INT0 & 0x08 )	// CC1_CONN_FILT_STATUS
			{
				REG_DET_CTRL0 |= 0x01;//SW_ADC_CC1_EN
				REG_DET_CTRL0 |= 0x40;//SW_DLPF_START
				while ( (!(CC_DET_IRQ_STATUS2 & 0x04)) /*&& ( REG_DET_CTRL0 & 0x40 )*/ )
				{
					g_vucxReg5[0x84]++;
				}
				CC_DET_IRQ_STATUS2 = 0x04;
				REG_DET_CTRL0 &= 0xB4;//stop
				g_vucxReg5[0x22] = REG_CC1_DCC;
			}
//			if( CC_DET_IRQ_INT0 & 0x10 )	// CC2_CONN_FILT_STATUS
			{
				REG_DET_CTRL0 |= 0x02;//SW_ADC_CC2_EN
				REG_DET_CTRL0 |= 0x40;//SW_DLPF_START
				while ( (!(CC_DET_IRQ_STATUS2 & 0x04)) /*&& ( REG_DET_CTRL0 & 0x40 )*/ )
				{
					g_vucxReg5[0x85]++;
				}
				CC_DET_IRQ_STATUS2 = 0x04;
				REG_DET_CTRL0 &= 0xB4;//stop
				g_vucxReg5[0x23] = REG_CC2_DCC;
			}
#endif
	ADDRCFG0 = 0x10;//enable I2C access
			if ( ( REG_CC1_DCC <= 5 ) && ( REG_CC2_DCC <= 5 ) && ( ( PDC_STAT_23_16 & 0x60 ) == 0x00 ) )
			{
				g_vucxReg5[0x60]++;
				CC_DET_IRQ_STATUS0 = 0xDB;
				return;
			}

//REG_GPIOP_OUT = REG_GPIOP_OUT & (~GPIO6);
//g_vucxReg5[0x35] = CC_STATUS;

//	ADDRCFG0 = 0x10;//enable I2C access
			if ( ( ROLE_CONTROL & 0x40 ) == 0x40 )//DRP
			{
				g_vucxReg5[0x91] |= 0x01;
				
//				if ( ( ROLE_CONTROL & 0xC0 ) == 0x40 )//DRP
//				{
//					REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
//g_vucxReg5[0x36] = CC_STATUS;
//g_vucxReg5[0x01] = 0;
//g_vucxReg5[0x37] = COMMAND;
					if ( ( CC_STATUS & 0x10 ) == 0x00 )//TCPC is presenting Rp
					{
						g_vucxReg5[0x92] |= 0x01;

						//source
						if ( REG_CC1_DCC == 0xFF )
						{
							g_vucxReg5[0x93] |= 0x01;

							if ( ( ROLE_CONTROL & 0x30 ) == 0x00 )//TCPC Rp is 0.9A
							{
								if ( REG_CC2_DCC < 20 )
								{
									g_vucxReg5[0x94] = 0x01;
									g_vucxReg5[0x8F] = 0x51;

/*									if ( ucxCCState != CC1_OPEN_CC2_RA )
									{
										REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
									}*/
									ucxCCState = CC1_OPEN_CC2_RA;
								}
								else if ( REG_CC2_DCC <= 165 )
								{
									g_vucxReg5[0x94] = 0x02;

									g_vucxReg5[0x8F] = 0x01;
									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_OPEN_CC2_RD;
								}
							}
							else if	( ( ROLE_CONTROL & 0x30 ) == 0x10 )//TCPC Rp is 1.5A
							{
								if ( REG_CC2_DCC < 40 )
								{
									g_vucxReg5[0x94] = 0x03;
									g_vucxReg5[0x8F] = 0x52;

/*									if ( ucxCCState != CC1_OPEN_CC2_RA )
									{
										REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
									}*/
									ucxCCState = CC1_OPEN_CC2_RA;
								}
								else if ( REG_CC2_DCC <= 165 )
								{
									g_vucxReg5[0x94] = 0x04;

									g_vucxReg5[0x8F] = 0x02;
									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_OPEN_CC2_RD;
								}
							}
							else if	( ( ROLE_CONTROL & 0x30 ) == 0x20 )//TCPC Rp is 3A
							{
								if ( REG_CC2_DCC < 80 )
								{
									g_vucxReg5[0x94] = 0x05;
									g_vucxReg5[0x8F] = 0x53;//pass

/*									if ( ucxCCState != CC1_OPEN_CC2_RA )
									{
										REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
									}*/
									ucxCCState = CC1_OPEN_CC2_RA;
								}
								else if ( REG_CC2_DCC <= 245 )
								{
									g_vucxReg5[0x94] = 0x06;

									g_vucxReg5[0x8F] = 0x03;//pass
									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_OPEN_CC2_RD;
								}
							}
						}
						else if ( REG_CC2_DCC == 0xFF )
						{
							g_vucxReg5[0x93] |= 0x02;
							if ( ( ROLE_CONTROL & 0x30 ) == 0x00 )//TCPC Rp is 0.9A
							{
								if ( REG_CC1_DCC < 20 )
								{
									g_vucxReg5[0x94] = 0x01;
									g_vucxReg5[0x8F] = 0x54;

/*									if ( ucxCCState != CC1_RA_CC2_OPEN )
									{
										REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
									}*/
									ucxCCState = CC1_RA_CC2_OPEN;
								}
								else if ( REG_CC1_DCC <= 165 )
								{
									g_vucxReg5[0x94] = 0x02;

									g_vucxReg5[0x8F] = 0x04;
									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RD_CC2_OPEN;
								}
							}
							else if	( ( ROLE_CONTROL & 0x30 ) == 0x10 )//TCPC Rp is 1.5A
							{
								if ( REG_CC1_DCC < 40 )
								{
									g_vucxReg5[0x94] = 0x03;
									g_vucxReg5[0x8F] = 0x55;

/*									if ( ucxCCState != CC1_RA_CC2_OPEN )
									{
										REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
									}*/
									ucxCCState = CC1_RA_CC2_OPEN;
								}
								else if ( REG_CC1_DCC <= 165 )
								{
									g_vucxReg5[0x94] = 0x04;

									g_vucxReg5[0x8F] = 0x05;
									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RD_CC2_OPEN;
								}
							}
							else if	( ( ROLE_CONTROL & 0x30 ) == 0x20 )//TCPC Rp is 3A
							{
								if ( REG_CC1_DCC < 80 )
								{
									g_vucxReg5[0x94] = 0x05;
									g_vucxReg5[0x8F] = 0x56;//pass

/*									if ( ucxCCState != CC1_RA_CC2_OPEN )
									{
										REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
									}*/
									ucxCCState = CC1_RA_CC2_OPEN;
								}
								else if ( REG_CC1_DCC <= 245 )
								{
									g_vucxReg5[0x94] = 0x06;

									g_vucxReg5[0x8F] = 0x06;//pass
									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RD_CC2_OPEN;
								}
							}
						}
						else
						{
							g_vucxReg5[0x93] |= 0x04;

//							if ( ( REG_CC1_DCC > REG_CC2_DCC ) && ( REG_CC1_DCC - REG_CC2_DCC > 5 ) )//port partner is CC1:Rd,CC2:Ra
							if ( ( REG_CC1_DCC > REG_CC2_DCC ) && ( REG_CC1_DCC - REG_CC2_DCC >= 10 ) )//port partner is CC1:Rd,CC2:Ra
							{
								{
									if ( REG_CC1_DCC <= 245 )
									{
										g_vucxReg5[0x94] = 0x01;
										g_vucxReg5[0x8F] = 0x11;//pass
	
										REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x06; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
										ucxCCState = CC1_RD_CC2_RA;
									}
								}
							}
//							else if ( ( REG_CC2_DCC > REG_CC1_DCC ) && ( REG_CC2_DCC - REG_CC1_DCC > 5 ) )//port partner is CC1:Ra,CC2:Rd
							else if ( ( REG_CC2_DCC > REG_CC1_DCC ) && ( REG_CC2_DCC - REG_CC1_DCC >= 10 ) )//port partner is CC1:Ra,CC2:Rd
							{
								{
									if ( REG_CC2_DCC <= 245 )
									{
										g_vucxReg5[0x94] = 0x02;
										g_vucxReg5[0x8F] = 0x12;//pass
	
										REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x09; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
										ucxCCState = CC1_RA_CC2_RD;
									}
								}
							}
							else//CC1 == CC2
							{
								if ( ( ( ROLE_CONTROL & 0x30 ) == 0x00 ) || ( ( ROLE_CONTROL & 0x30 ) == 0x10 ) )//TCPC Rp is 0.9A or 1.5A
								{
									if ( REG_CC1_DCC <= 40 )
									{
										g_vucxReg5[0x94] = 0x03;
										g_vucxReg5[0x8F] = 0x21;
	
										REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x05;
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
										ucxCCState = CC1_RA_CC2_RA;
									}
									else if ( REG_CC1_DCC <= 165 )
									{
										g_vucxReg5[0x94] = 0x04;
										g_vucxReg5[0x8F] = 0x31;
	
										REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0A; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
										ucxCCState = CC1_RD_CC2_RD;
									}
								}
								else if	( ( ROLE_CONTROL & 0x30 ) == 0x20 )//TCPC Rp is 3A
								{
									if ( REG_CC1_DCC <= 80 )
									{
										g_vucxReg5[0x94] = 0x05;
										g_vucxReg5[0x8F] = 0x22;//pass
	
										REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x05;
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
										ucxCCState = CC1_RA_CC2_RA;
									}
									else if ( REG_CC1_DCC <= 245 )
									{
										g_vucxReg5[0x94] = 0x06;
										g_vucxReg5[0x8F] = 0x32;//pass
	
										REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0A; 
										REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
										REG_DET_CTRL1 |= 0x10;
										REG_DET_CTRL1 &= 0xEF;
										ucxCCState = CC1_RD_CC2_RD;
									}
								}
							}
						}
					}
					else if ( ( CC_STATUS & 0x10 ) == 0x10 )//TCPC is presenting Rd
					{
						g_vucxReg5[0x92] |= 0x02;
	
						//sink
						if ( REG_CC2_DCC <= 20 )
						{
							g_vucxReg5[0x93] |= 0x01;

							g_vucxReg5[0x8F] = 0x41;//pass
							if ( ( REG_CC1_DCC >= 25 ) && ( REG_CC1_DCC <= 66 ) )//port partner is CC1:Rp:0.9A,CC2:Open
							{
								g_vucxReg5[0x94] = 0x01;

								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01;
							}
							else if ( ( REG_CC1_DCC > 66 ) && ( REG_CC1_DCC <= 123 ) )//port partner is CC1:Rp:1.5A,CC2:Open
							{
								g_vucxReg5[0x94] = 0x02;
			
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02;
							}
							else if ( ( REG_CC1_DCC > 123 ) && ( REG_CC1_DCC <= 204 ) )//port partner is CC1:Rp:3A,CC2:Open
							{
								g_vucxReg5[0x94] = 0x03;
			
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x03;
							}
							else if ( REG_CC1_DCC > 204 )//CC voltage abnormal
							{
								g_vucxReg5[0x97]++;
								g_vucxReg5[0x98] = REG_CC1_DCC;
	
								goto CC_SAMPLE;
							}
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RP_CC2_OPEN;
						}
						if ( REG_CC1_DCC <= 20 )
						{
							g_vucxReg5[0x93] |= 0x02;

							g_vucxReg5[0x8F] = 0x42;//pass
							if ( ( REG_CC2_DCC >= 25 ) && ( REG_CC2_DCC <= 66 ) )//port partner is CC2:Rp:0.9A,CC1:Open
							{
								g_vucxReg5[0x94] = 0x01;
			
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04;
							}
							else if ( ( REG_CC2_DCC > 66 ) && ( REG_CC2_DCC <= 123 ) )//port partner is CC2:Rp:1.5A,CC1:Open
							{
								g_vucxReg5[0x94] = 0x02;
			
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08;
							}
							else if ( ( REG_CC2_DCC > 123 ) && ( REG_CC2_DCC <= 204 ) )//port partner is CC2:Rp:3A,CC1:Open
							{
								g_vucxReg5[0x94] = 0x03;
			
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0C;
							}
							else if ( REG_CC2_DCC > 204 )//CC voltage abnormal
							{
								g_vucxReg5[0x97]++;
								g_vucxReg5[0x98] = REG_CC2_DCC;
	
								goto CC_SAMPLE;
							}
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_OPEN_CC2_RP;
						}
						if ( ( REG_CC1_DCC >= 25 ) && ( REG_CC2_DCC >= 25 ) )
						{
							g_vucxReg5[0x93] |= 0x04;
	
							if ( ( REG_CC1_DCC >= 25 ) && ( REG_CC1_DCC <= 66 ) )//port partner is CC1:Rp:0.9A,CC2:Open
							{
								g_vucxReg5[0x94] |= 0x01;
			
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xFC ) | 0x01;
							}
							else if ( ( REG_CC1_DCC > 66 ) && ( REG_CC1_DCC <= 123 ) )//port partner is CC1:Rp:1.5A,CC2:Open
							{
								g_vucxReg5[0x94] |= 0x02;
	
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xFC ) | 0x02; 
							}
							else if ( ( REG_CC1_DCC > 123 ) && ( REG_CC1_DCC <= 204 ) )//port partner is CC1:Rp:3A,CC2:Open
							{
								g_vucxReg5[0x94] |= 0x03;
	
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xFC ) | 0x03; 
							}
	
							if ( ( REG_CC2_DCC >= 25 ) && ( REG_CC2_DCC <= 66 ) )//port partner is CC2:Rp:0.9A,CC1:Open
							{
								g_vucxReg5[0x94] |= 0x10;
	
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF3 ) | 0x04;
							}
							else if ( ( REG_CC2_DCC > 66 ) && ( REG_CC2_DCC <= 123 ) )//port partner is CC2:Rp:1.5A,CC1:Open
							{
								g_vucxReg5[0x94] |= 0x20;
	
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF3 ) | 0x08; 
							}
							else if ( ( REG_CC2_DCC > 123 ) && ( REG_CC2_DCC <= 204 ) )//port partner is CC2:Rp:3A,CC1:Open
							{
								g_vucxReg5[0x94] |= 0x30;
	
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF3 ) | 0x0C; 
							}
							g_vucxReg5[0x8F] = 0x45;
							REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
							REG_DET_CTRL1 |= 0x10;
							REG_DET_CTRL1 &= 0xEF;
							ucxCCState = CC1_RP_CC2_RP;
						}
/*						else
						{
							g_vucxReg0[0x5D]++;
							g_vucxReg5[0x99]++;
							g_vucxReg5[0x23] = REG_CC1_DCC;
							g_vucxReg5[0x24] = REG_CC2_DCC;
		
							goto CC_SAMPLE;
						}*/
					}
//				}
			}
			else
			{
				g_vucxReg5[0x91] |= 0x02;

				if ( ( ROLE_CONTROL & 0x03 ) == 0x01 )//TCPC is Rp
				{
					g_vucxReg5[0x92] |= 0x01;
		
					//source
					if ( REG_CC1_DCC == 0xFF )
					{
						g_vucxReg5[0x93] |= 0x01;

						if ( ( ROLE_CONTROL & 0x30 ) == 0x00 )//TCPC Rp is 0.9A
						{
							if ( REG_CC2_DCC < 20 )
							{
								g_vucxReg5[0x94] = 0x01;
								g_vucxReg5[0x8F] = 0x57;

/*								if ( ucxCCState != CC1_OPEN_CC2_RA )
								{
									REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
								}*/
								ucxCCState = CC1_OPEN_CC2_RA;
							}
							else if ( REG_CC2_DCC <= 165 )
							{
								g_vucxReg5[0x94] = 0x02;

								g_vucxReg5[0x8F] = 0x07;
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
								REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
								REG_DET_CTRL1 |= 0x10;
								REG_DET_CTRL1 &= 0xEF;
								ucxCCState = CC1_OPEN_CC2_RD;
							}
						}
						else if	( ( ROLE_CONTROL & 0x30 ) == 0x10 )//TCPC Rp is 1.5A
						{
							if ( REG_CC2_DCC < 40 )
							{
								g_vucxReg5[0x94] = 0x03;
								g_vucxReg5[0x8F] = 0x58;

/*								if ( ucxCCState != CC1_OPEN_CC2_RA )
								{
									REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
								}*/
								ucxCCState = CC1_OPEN_CC2_RA;
							}
							else if ( REG_CC2_DCC <= 165 )
							{
								g_vucxReg5[0x94] = 0x04;

								g_vucxReg5[0x8F] = 0x08;
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
								REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
								REG_DET_CTRL1 |= 0x10;
								REG_DET_CTRL1 &= 0xEF;
								ucxCCState = CC1_OPEN_CC2_RD;
							}
						}
						else if	( ( ROLE_CONTROL & 0x30 ) == 0x20 )//TCPC Rp is 3A
						{
							if ( REG_CC2_DCC < 80 )
							{
								g_vucxReg5[0x94] = 0x05;
								g_vucxReg5[0x8F] = 0x59;

/*								if ( ucxCCState != CC1_OPEN_CC2_RA )
								{
									REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
								}*/
								ucxCCState = CC1_OPEN_CC2_RA;
							}
							else if ( REG_CC2_DCC <= 245 )
							{
								g_vucxReg5[0x94] = 0x06;

								g_vucxReg5[0x8F] = 0x09;
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
								REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
								REG_DET_CTRL1 |= 0x10;
								REG_DET_CTRL1 &= 0xEF;
								ucxCCState = CC1_OPEN_CC2_RD;
							}
						}
					}
					else if ( REG_CC2_DCC == 0xFF )
					{
						g_vucxReg5[0x93] |= 0x02;

						if ( ( ROLE_CONTROL & 0x30 ) == 0x00 )//TCPC Rp is 0.9A
						{
							if ( REG_CC1_DCC < 20 )
							{
								g_vucxReg5[0x94] = 0x01;
								g_vucxReg5[0x8F] = 0x5A;

/*								if ( ucxCCState != CC1_RA_CC2_OPEN )
								{
									REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
								}*/
								ucxCCState = CC1_RA_CC2_OPEN;
							}
							else if ( REG_CC1_DCC <= 165 )
							{
								g_vucxReg5[0x94] = 0x02;

								g_vucxReg5[0x8F] = 0x0A;
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
								REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
								REG_DET_CTRL1 |= 0x10;
								REG_DET_CTRL1 &= 0xEF;
								ucxCCState = CC1_RD_CC2_OPEN;
							}
						}
						else if	( ( ROLE_CONTROL & 0x30 ) == 0x10 )//TCPC Rp is 1.5A
						{
							if ( REG_CC1_DCC < 40 )
							{
								g_vucxReg5[0x94] = 0x03;
								g_vucxReg5[0x8F] = 0x5B;

/*								if ( ucxCCState != CC1_RA_CC2_OPEN )
								{
									REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
								}*/
								ucxCCState = CC1_RA_CC2_OPEN;
							}
							else if ( REG_CC1_DCC <= 165 )
							{
								g_vucxReg5[0x94] = 0x04;

								g_vucxReg5[0x8F] = 0x0B;
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
								REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
								REG_DET_CTRL1 |= 0x10;
								REG_DET_CTRL1 &= 0xEF;
								ucxCCState = CC1_RD_CC2_OPEN;
							}
						}
						else if	( ( ROLE_CONTROL & 0x30 ) == 0x20 )//TCPC Rp is 3A
						{
							if ( REG_CC1_DCC < 80 )
							{
								g_vucxReg5[0x94] = 0x05;
								g_vucxReg5[0x8F] = 0x5C;

/*								if ( ucxCCState != CC1_RA_CC2_OPEN )
								{
									REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
								}*/
								ucxCCState = CC1_RA_CC2_OPEN;
							}
							else if ( REG_CC1_DCC <= 245 )
							{
								g_vucxReg5[0x94] = 0x06;

								g_vucxReg5[0x8F] = 0x0C;
								REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
								REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
								REG_DET_CTRL1 |= 0x10;
								REG_DET_CTRL1 &= 0xEF;
								ucxCCState = CC1_RD_CC2_OPEN;
							}
						}
					}
					else
					{
						g_vucxReg5[0x93] |= 0x04;

						if ( ( REG_CC1_DCC > REG_CC2_DCC ) && ( REG_CC1_DCC - REG_CC2_DCC >= 10 ) )//port partner is CC1:Rd,CC2:Ra
						{
							{
								if ( REG_CC1_DCC <= 245 )
								{
									g_vucxReg5[0x94] = 0x01;
									g_vucxReg5[0x8F] = 0x13;

									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x06; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RD_CC2_RA;
								}
							}
						}
						else if ( ( REG_CC2_DCC > REG_CC1_DCC ) && ( REG_CC2_DCC - REG_CC1_DCC >= 10 ) )//port partner is CC1:Ra,CC2:Rd
						{
							{
								if ( REG_CC2_DCC <= 245 )
								{
									g_vucxReg5[0x94] = 0x02;
									g_vucxReg5[0x8F] = 0x14;

									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x09; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RA_CC2_RD;
								}
							}
						}
						else//CC1 == CC2
						{
							if ( ( ( ROLE_CONTROL & 0x30 ) == 0x00 ) || ( ( ROLE_CONTROL & 0x30 ) == 0x10 ) )//TCPC Rp is 0.9A or 1.5A
							{
								if ( REG_CC1_DCC <= 40 )
								{
									g_vucxReg5[0x94] = 0x03;
									g_vucxReg5[0x8F] = 0x23;

									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x05; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RA_CC2_RA;
								}
								else if ( REG_CC1_DCC <= 165 )
								{
									g_vucxReg5[0x94] = 0x04;
									g_vucxReg5[0x8F] = 0x33;

									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0A;
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RD_CC2_RD;
								}
							}
							else if	( ( ROLE_CONTROL & 0x30 ) == 0x20 )//TCPC Rp is 3A
							{
								if ( REG_CC1_DCC <= 80 )
								{
									g_vucxReg5[0x94] = 0x05;
									g_vucxReg5[0x8F] = 0x24;

									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x05; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RA_CC2_RA;
								}
								else if ( REG_CC1_DCC <= 245 )
								{
									g_vucxReg5[0x94] = 0x06;
									g_vucxReg5[0x8F] = 0x34;

									REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0A; 
									REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
									REG_DET_CTRL1 |= 0x10;
									REG_DET_CTRL1 &= 0xEF;
									ucxCCState = CC1_RD_CC2_RD;
								}
							}
						}
					}
				}
				else if ( ( ROLE_CONTROL & 0x03 ) == 0x02 )//TCPC is Rd
				{
					g_vucxReg5[0x92] |= 0x02;

					//sink
					if ( REG_CC2_DCC <= 20 )
					{
//REG_GPIOP_OUT |= (GPIO6);
						g_vucxReg5[0x93] |= 0x01;

						if ( ( REG_CC1_DCC >= 25 ) && ( REG_CC1_DCC <= 66 ) )//port partner is CC1:Rp:0.9A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x01;
		
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01;
						}
						else if ( ( REG_CC1_DCC > 66 ) && ( REG_CC1_DCC <= 123 ) )//port partner is CC1:Rp:1.5A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x02;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
						}
						else if ( ( REG_CC1_DCC > 123 ) && ( REG_CC1_DCC <= 204 ) )//port partner is CC1:Rp:3A,CC2:Open
						{
							g_vucxReg5[0x94] = 0x03;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x03; 
						}
						else if ( REG_CC1_DCC > 204 )//CC voltage abnormal
						{
							g_vucxReg5[0x97]++;
							g_vucxReg5[0x98] = REG_CC1_DCC;

							goto CC_SAMPLE;
						}
						g_vucxReg5[0x8F] = 0x43;//pass
						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_RP_CC2_OPEN;
					}
					if ( REG_CC1_DCC <= 20 )
					{
						g_vucxReg5[0x93] |= 0x02;

						if ( ( REG_CC2_DCC >= 25 ) && ( REG_CC2_DCC <= 66 ) )//port partner is CC2:Rp:0.9A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x01;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04;
						}
						else if ( ( REG_CC2_DCC > 66 ) && ( REG_CC2_DCC <= 123 ) )//port partner is CC2:Rp:1.5A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x02;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
						}
						else if ( ( REG_CC2_DCC > 123 ) && ( REG_CC2_DCC <= 204 ) )//port partner is CC2:Rp:3A,CC1:Open
						{
							g_vucxReg5[0x94] = 0x03;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0C; 
						}
						else if ( REG_CC2_DCC > 204 )//CC voltage abnormal
						{
							g_vucxReg5[0x97]++;
							g_vucxReg5[0x98] = REG_CC2_DCC;

							goto CC_SAMPLE;
						}
						g_vucxReg5[0x8F] = 0x44;
						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_OPEN_CC2_RP;
					}
					if ( ( REG_CC1_DCC >= 25 ) && ( REG_CC2_DCC >= 25 ) )
					{
						g_vucxReg5[0x93] |= 0x04;

						if ( ( REG_CC1_DCC >= 25 ) && ( REG_CC1_DCC <= 66 ) )//port partner is CC1:Rp:0.9A,CC2:Open
						{
							g_vucxReg5[0x94] |= 0x01;
		
							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xFC ) | 0x01;
						}
						else if ( ( REG_CC1_DCC > 66 ) && ( REG_CC1_DCC <= 123 ) )//port partner is CC1:Rp:1.5A,CC2:Open
						{
							g_vucxReg5[0x94] |= 0x02;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xFC ) | 0x02; 
						}
						else if ( ( REG_CC1_DCC > 123 ) && ( REG_CC1_DCC <= 204 ) )//port partner is CC1:Rp:3A,CC2:Open
						{
							g_vucxReg5[0x94] |= 0x03;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xFC ) | 0x03; 
						}

						if ( ( REG_CC2_DCC >= 25 ) && ( REG_CC2_DCC <= 66 ) )//port partner is CC2:Rp:0.9A,CC1:Open
						{
							g_vucxReg5[0x94] |= 0x10;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF3 ) | 0x04;
						}
						else if ( ( REG_CC2_DCC > 66 ) && ( REG_CC2_DCC <= 123 ) )//port partner is CC2:Rp:1.5A,CC1:Open
						{
							g_vucxReg5[0x94] |= 0x20;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF3 ) | 0x08; 
						}
						else if ( ( REG_CC2_DCC > 123 ) && ( REG_CC2_DCC <= 204 ) )//port partner is CC2:Rp:3A,CC1:Open
						{
							g_vucxReg5[0x94] |= 0x30;

							REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF3 ) | 0x0C; 
						}
						g_vucxReg5[0x8F] = 0x45;
						REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
						REG_DET_CTRL1 |= 0x10;
						REG_DET_CTRL1 &= 0xEF;
						ucxCCState = CC1_RP_CC2_RP;
					} 
/*					else
					{
						g_vucxReg5[0x99]++;
						g_vucxReg5[0x23] = REG_CC1_DCC;
						g_vucxReg5[0x24] = REG_CC2_DCC;
	
						goto CC_SAMPLE;
					}*/
				}
			}
#endif//COMPARATOR

			if ( ( ucxCCState == CC1_RD_CC2_OPEN ) || ( ucxCCState == CC1_RD_CC2_RA ) )
			{
//				REG_GPIOP_OUT &= (~GPIO7);
				ALERT_MASK_LOW |= 0x01;
				g_vucxReg5[0x95] |= 0x01;
				g_vucxReg5[0x96] = 0x01;

				DISABLE_DISCHARGE_VBUS;
				REG_DET_CTRL0 &= 0xDF;//SW_CC2_DISABLE
				REG_DET_CTRL0 |= 0x10;//SW_CC1_EN
				g_vucxReg2[0x30] = REG_DET_CTRL0;
				REG_CC_DET_INT_MASK5 |= 0x20;//[5]RPCUR_DEB_CHG_INT_MASK
				AOP_REG_ANATOP_7_0 &= 0xDF;//unflip
				REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
			}
			else if ( ( ucxCCState == CC1_OPEN_CC2_RD ) || ( ucxCCState == CC1_RA_CC2_RD ) )
			{
//				REG_GPIOP_OUT &= (~GPIO7);
				ALERT_MASK_LOW |= 0x01;
				g_vucxReg5[0x95] |= 0x02;
				g_vucxReg5[0x96] = 0x02;

				DISABLE_DISCHARGE_VBUS;
				REG_DET_CTRL0 &= 0xEF;//SW_CC1_DISABLE
				REG_DET_CTRL0 |= 0x20;//SW_CC2_EN
				g_vucxReg2[0x30] = REG_DET_CTRL0;
				REG_CC_DET_INT_MASK5 |= 0x20;//[5]RPCUR_DEB_CHG_INT_MASK
				AOP_REG_ANATOP_7_0 |= 0x20;//flip
				REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
			}
			else if ( ( ucxCCState == CC1_RP_CC2_OPEN )/* || ( ucxCCState == CC1_RP_CC2_RA )*/ )
			{
//				REG_GPIOP_OUT &= (~GPIO7);
				ALERT_MASK_LOW |= 0x01;
				g_vucxReg5[0x95] |= 0x04;
				g_vucxReg5[0x96] = 0x04;

				DISABLE_DISCHARGE_VBUS;
				REG_DET_CTRL0 &= 0xDF;//SW_CC2_DISABLE
				REG_DET_CTRL0 |= 0x10;//SW_CC1_EN
				g_vucxReg2[0x30] = REG_DET_CTRL0;
				REG_CC_DET_INT_MASK5 = 0xDF;//[5]RPCUR_DEB_CHG_INT_MASK
				AOP_REG_ANATOP_7_0 &= 0xDF;//unflip
//				CC_DET_IRQ_STATUS1 = 0x12;
				CC_DET_IRQ_STATUS1 = 0x92;
				REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
			}
			else if ( ( ucxCCState == CC1_OPEN_CC2_RP )/* || ( ucxCCState == CC1_RA_CC2_RP )*/ )
			{
//				REG_GPIOP_OUT &= (~GPIO7);
				ALERT_MASK_LOW |= 0x01;
				g_vucxReg5[0x95] |= 0x08;
				g_vucxReg5[0x96] = 0x08;

				DISABLE_DISCHARGE_VBUS;
				REG_DET_CTRL0 &= 0xEF;//SW_CC1_DISABLE
				REG_DET_CTRL0 |= 0x20;//SW_CC2_EN
				g_vucxReg2[0x30] = REG_DET_CTRL0;
				REG_CC_DET_INT_MASK5 = 0xDF;//[5]RPCUR_DEB_CHG_INT_MASK
				AOP_REG_ANATOP_7_0 |= 0x20;//flip
//				CC_DET_IRQ_STATUS1 = 0x09;
				CC_DET_IRQ_STATUS1 = 0x49;
				REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
			}
			else if ( ucxCCState == CC1_OPEN_CC2_RA )
			{
				g_vucxReg5[0x95] |= 0x10;
				g_vucxReg5[0x96] = 0x10;
//				g_vucxReg5[0x84]++;

				if ( ( ROLE_CONTROL & 0x40 ) == 0x40 )//DRP
				{
					ALERT_MASK_LOW &= 0xFE;
//					OTHER_CTRL3 |= 0x20;//[5]CC_CONN_ENWIN_MASK
					REG_CC_DET_INT_MASK1 = 0xFF;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
					REG_CC_DET_INT_MASK5 &= 0x7F;//[7]RADISCONN_CC2_INT_MASK
					AOI_REG_PDC_95_88 |= 0x80;//continue to toggle when detecting Ra on CC2
/*
#ifdef TCPM_DEBOUNCE
					REG_CC_DET_INT_MASK0 = 0xC7;//CC1_CONN_FILT_INT_MASK,CC2_CONN_FILT_INT_MASK,VBUS_CONN_FILT_INT_MASK
					REG_CC_DET_INT_MASK1 = 0xC7;//CC1_DISCONN_FILT_INT_MASK,CC2_DISCONN_FILT_INT_MASK,VBUS_DISCONN_FILT_INT_MASK
#else
					REG_CC_DET_INT_MASK0 = 0xF8;//CC1_CONN_DEB_INT_MASK,CC2_CONN_DEB_INT_MASK,VBUS_CONN_DEB_INT_MASK
					REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
#endif
*/
//					g_ucxRaDisconnCnt = 0;
				}
			}
			else if ( ucxCCState == CC1_RA_CC2_OPEN )
			{
				g_vucxReg5[0x95] |= 0x20;
				g_vucxReg5[0x96] = 0x20;
//				g_vucxReg5[0x85]++;

				if ( ( ROLE_CONTROL & 0x40 ) == 0x40 )//DRP
				{
					ALERT_MASK_LOW &= 0xFE;
//					OTHER_CTRL3 |= 0x20;//[5]CC_CONN_ENWIN_MASK
					REG_CC_DET_INT_MASK1 = 0xFF;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
					REG_CC_DET_INT_MASK5 &= 0xBF;//[6]RADISCONN_CC1_INT_MASK
					AOI_REG_PDC_95_88 |= 0x40;//continue to toggle when detecting Ra on CC1
/*
#ifdef TCPM_DEBOUNCE
					REG_CC_DET_INT_MASK0 = 0xC7;//CC1_CONN_FILT_INT_MASK,CC2_CONN_FILT_INT_MASK,VBUS_CONN_FILT_INT_MASK
					REG_CC_DET_INT_MASK1 = 0xC7;//CC1_DISCONN_FILT_INT_MASK,CC2_DISCONN_FILT_INT_MASK,VBUS_DISCONN_FILT_INT_MASK
#else
					REG_CC_DET_INT_MASK0 = 0xF8;//CC1_CONN_DEB_INT_MASK,CC2_CONN_DEB_INT_MASK,VBUS_CONN_DEB_INT_MASK
					REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
#endif
*/
//					g_ucxRaDisconnCnt = 0;
				}
			}
#ifdef ENABLE_AUTO_POWER_DOWN
			AOI_REG_ANATOP_15_8 &= 0x7F;//disable FIRMCMD_AUTOPD_EN
#endif

/*
#ifdef TCPM_DEBOUNCE
			CC_DET_IRQ_STATUS0 = 0x18;
#else
			CC_DET_IRQ_STATUS0 = 0x03;
#endif
*/
//			CC_DET_IRQ_STATUS0 = 0x1B;
			CC_DET_IRQ_STATUS0 = 0xDB;
		}

#ifdef TCPM_DEBOUNCE
//		if( CC_DET_IRQ_STATUS0 & 0x20 (~REG_CC_DET_INT_MASK0) )	// VBUS_CONN_FILT_STATUS
		if( CC_DET_IRQ_INT0 & 0x20 )	// VBUS_CONN_FILT_STATUS
#else
//		if( ( CC_DET_IRQ_STATUS0 & 0x04 ) && ( ( REG_CC_DET_INT_MASK & 0x01 ) != 0x01 ) )	// VBUS_CONN_DEB_STATUS
//		if( CC_DET_IRQ_STATUS0 & 0x04 (~REG_CC_DET_INT_MASK0) )	// VBUS_CONN_DEB_STATUS
		if( CC_DET_IRQ_INT0 & 0x04 )	// VBUS_CONN_DEB_STATUS
#endif
		{
			if ( ( POWER_CONTROL & 0x40 ) == 0 )
			{
				if ( REG_DET_CTRL2 & 0x40 )//ADC is sampling VBUS
				{
					REG_DET_CTRL2 &= 0x9B;//stop
					REG_DLPF_CTRL0 |= 0x80;//Software reset for low pass filter
					REG_DLPF_CTRL0 &= 0x7F;
					g_ucxExitSample = 1;
				}
				REG_DET_CTRL2 &= 0x9B;//stop
				CC_DET_IRQ_STATUS2 = 0x04;
				REG_DET_CTRL2 |= 0x20;//SW_ADC_VBUS_EN
				REG_DET_CTRL2 |= 0x40;//SW_DLPF_START
				while ( (!(CC_DET_IRQ_STATUS2 & 0x04)) /*&& ( REG_DET_CTRL2 & 0x40 )*/ )
				{
					g_vucxReg5[0x86]++;
				}
				CC_DET_IRQ_STATUS2 = 0x04;
				REG_DET_CTRL2 &= 0x9B;//stop
				REG_DET_CTRL2 |= 0x04;//[2]SW_ADC_DET_DONE_VBUS
				REG_DET_CTRL2 &= 0xFB;

				ET1 = 1;
				TR1	= 1;
			}
			g_vucxReg5[0xA3]++;
/*
#ifdef TCPM_DEBOUNCE
			CC_DET_IRQ_STATUS0 = 0x20;
#else
			CC_DET_IRQ_STATUS0 = 0x04;
#endif
*/
			CC_DET_IRQ_STATUS0 = 0x24;
		}
/*
#ifdef TCPM_DEBOUNCE
//		if( CC_DET_IRQ_STATUS1 & 0x08 & (~REG_CC_DET_INT_MASK1) )	// CC1_DISCONN_FILT_STATUS
		if( CC_DET_IRQ_INT1 & 0x08 )	// CC1_DISCONN_FILT_STATUS
#else
//		if( CC_DET_IRQ_STATUS1 & 0x01 & (~REG_CC_DET_INT_MASK1) )	// CC1_DISCONN_DEB_STATUS
		if( CC_DET_IRQ_INT1 & 0x01 )	// CC1_DISCONN_DEB_STATUS
#endif
*/
		if( CC_DET_IRQ_INT1 & 0x01 )	// CC1_DISCONN_DEB_STATUS
		{
//				REG_GPIOP_OUT &= (~GPIO6);
			if ( ucxCCState == CC1_RA_CC2_OPEN )
			{
//				CC_DET_IRQ_STATUS1 = 0x09;
				CC_DET_IRQ_STATUS1 = 0x49;
				return;
			}
/*			if ( ( PDC_STAT_23_16 & 0x60 ) != 0 )//cc connection
			{
				g_vucxReg5[0x61]++;
				CC_DET_IRQ_STATUS1 = 0x49;
				return;
			}*/

			if( ( CC_DET_IRQ_STATUS4 & 0x40 ) && ( POWER_CONTROL & 0x01 ) && ( REG_DET_CTRL0 & 0x20 ) ) 	// PC_VCONN_EN_CHG_STATUS
			{
				g_vucxReg5[0xB4]++;
		
//				CC_DET_IRQ_STATUS1 = 0x09;
				CC_DET_IRQ_STATUS1 = 0x49;
				CC_DET_IRQ_STATUS4 = 0x40;

				return;
			}
//REG_GPIOP_OUT &= (~GPIO7);
			g_vucxReg5[0xA4]++;
			{
				REG_CC_DET_INT_MASK5 |= 0x20;//[5]RPCUR_DEB_CHG_INT_MASK
				REG_CC_DET_INT_MASK5 |= 0x40;//[6]RADISCONN_CC1_INT_MASK
				ucxCCState = 0;
//				REG_CC_DET_INT_MASK = 0xFF;
//				REG_DET_CTRL0 &= 0xEF;//SW_CC1_DISABLE
//				ENABLE_DISCHARGE_VBUS;
	//			REG_CC_DET_INT_MASK = 0xFE;
				AOI_REG_PDC_95_88 &= 0x3F;
				g_vucxReg5[0x90] = 0;
				g_vucxReg5[0x91] = 0;
				g_vucxReg5[0x92] = 0;
				g_vucxReg5[0x93] = 0;
				g_vucxReg5[0x94] = 0;
				g_vucxReg5[0x95] = 0;
				g_vucxReg5[0x96] = 0;
				g_vucxReg5[0x8F] = 0;

				ALERT_MASK_LOW |= 0x01;
				REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
				REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
				REG_DET_CTRL1 |= 0x10;
				REG_DET_CTRL1 &= 0xEF;
/*
#ifdef ENABLE_AUTO_POWER_DOWN
				AOI_REG_ANATOP_15_8 |= 0x80;//FIRMCMD_AUTOPD_EN
				usxDelay = 30;
				while ( usxDelay-- );
				AOP_REG_ANATOP_7_0 |= 0x10; //sleep,auto clear when wakeup
#endif
*/
			}
/*
#ifdef TCPM_DEBOUNCE
			CC_DET_IRQ_STATUS1 = 0x08;
#else
			CC_DET_IRQ_STATUS1 = 0x01;
#endif
*/
//			CC_DET_IRQ_STATUS1 = 0x09;
			CC_DET_IRQ_STATUS1 = 0x49;
		}
/*
#ifdef TCPM_DEBOUNCE
//		if( CC_DET_IRQ_STATUS1 & 0x10 & (~REG_CC_DET_INT_MASK1) )	// CC2_DISCONN_FILT_STATUS
		if( CC_DET_IRQ_INT1 & 0x10 )	// CC2_DISCONN_FILT_STATUS
#else
//		if( CC_DET_IRQ_STATUS1 & 0x02 & (~REG_CC_DET_INT_MASK1) )	// CC2_DISCONN_DEB_STATUS
		if( CC_DET_IRQ_INT1 & 0x02 )	// CC2_DISCONN_DEB_STATUS
#endif
*/
		if( CC_DET_IRQ_INT1 & 0x02 )	// CC2_DISCONN_DEB_STATUS
		{
//				REG_GPIOP_OUT &= (~GPIO6);
			if ( ucxCCState == CC1_OPEN_CC2_RA )
			{
//				CC_DET_IRQ_STATUS1 = 0x12;
				CC_DET_IRQ_STATUS1 = 0x92;
				return;
			}
/*			if ( ( PDC_STAT_23_16 & 0x60 ) != 0 )//cc connection
			{
				g_vucxReg5[0x62]++;
				CC_DET_IRQ_STATUS1 = 0x92;
				return;
			}*/

			if( ( CC_DET_IRQ_STATUS4 & 0x40 ) && ( POWER_CONTROL & 0x01 ) && ( REG_DET_CTRL0 & 0x10 ) ) 	// PC_VCONN_EN_CHG_STATUS
			{
				g_vucxReg5[0xB5]++;
		
//				CC_DET_IRQ_STATUS1 = 0x12;
				CC_DET_IRQ_STATUS1 = 0x92;
				CC_DET_IRQ_STATUS4 = 0x40;

				return;
			}
//REG_GPIOP_OUT &= (~GPIO7);
			g_vucxReg5[0xA5]++;
			{
				REG_CC_DET_INT_MASK5 |= 0x20;//[5]RPCUR_DEB_CHG_INT_MASK
				REG_CC_DET_INT_MASK5 |= 0x80;//[7]RADISCONN_CC2_INT_MASK
				ucxCCState = 0;
//				REG_CC_DET_INT_MASK = 0xFF;
//				REG_DET_CTRL0 &= 0xDF;//SW_CC2_DISABLE
//				ENABLE_DISCHARGE_VBUS;
	//			REG_CC_DET_INT_MASK = 0xFE;
				AOI_REG_PDC_95_88 &= 0x3F;
				g_vucxReg5[0x90] = 0;
				g_vucxReg5[0x91] = 0;
				g_vucxReg5[0x92] = 0;
				g_vucxReg5[0x93] = 0;
				g_vucxReg5[0x94] = 0;
				g_vucxReg5[0x95] = 0;
				g_vucxReg5[0x96] = 0;
				g_vucxReg5[0x8F] = 0;

				ALERT_MASK_LOW |= 0x01;
				REG_DET_CTRL4 = REG_DET_CTRL4 & 0xF0; 
				REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
				REG_DET_CTRL1 |= 0x10;
				REG_DET_CTRL1 &= 0xEF;
/*
#ifdef ENABLE_AUTO_POWER_DOWN
				AOI_REG_ANATOP_15_8 |= 0x80;//FIRMCMD_AUTOPD_EN
				usxDelay = 30;
				while ( usxDelay-- );
				AOP_REG_ANATOP_7_0 |= 0x10; //sleep,auto clear when wakeup
#endif
*/
			}
/*
#ifdef TCPM_DEBOUNCE
			CC_DET_IRQ_STATUS1 = 0x10;
#else
			CC_DET_IRQ_STATUS1 = 0x02;
#endif
*/
//			CC_DET_IRQ_STATUS1 = 0x12;
			CC_DET_IRQ_STATUS1 = 0x92;
		}
/*
#ifdef TCPM_DEBOUNCE
//		if( CC_DET_IRQ_STATUS1 & 0x20 & (~REG_CC_DET_INT_MASK1) )	// VBUS_DISCONN_FILT_STATUS
		if( CC_DET_IRQ_INT1 & 0x20 )	// VBUS_DISCONN_FILT_STATUS
#else
//		if( CC_DET_IRQ_STATUS1 & 0x04 & (~REG_CC_DET_INT_MASK1) )	// VBUS_DISCONN_DEB_STATUS
		if( CC_DET_IRQ_INT1 & 0x04 )	// VBUS_DISCONN_DEB_STATUS
#endif
*/
		if( CC_DET_IRQ_INT1 & 0x04 )	// VBUS_DISCONN_DEB_STATUS
		{
			ET1 = 0;
			TR1	= 0;

			g_vucxReg5[0xA6]++;

			CC_DET_IRQ_STATUS1 = 0x24;
		}

/*		if( CC_DET_IRQ_STATUS4 & 0x40 )	// ENABLE_VCONN_CHG_STATUS
		{
			CC_DET_IRQ_STATUS4 = 0x40;
		}*/
		if( CC_DET_IRQ_INT4 & 0x01 )	// PC_FCDICHAR_CHG_STATUS
		{
			g_vucxReg5[0xA7]++;

			if ( POWER_CONTROL & 0x04 )
			{
				ENABLE_DISCHARGE_VBUS;
				g_ucxVBUS_Force_Discharge = 1;
			}
			else
			{
				g_ucxVBUS_Force_Discharge = 0;
			}

			CC_DET_IRQ_STATUS4 = 0x01;
		}

//		if( CC_DET_IRQ_STATUS5 & 0x20 & (~REG_CC_DET_INT_MASK5) )	// RPCUR_DEB_CHG_INT_MASK
		if( CC_DET_IRQ_INT5 & 0x20 )	// RPCUR_DEB_CHG_INT_MASK
		{
			g_vucxReg5[0xA8]++;

			if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x01 ) )//Rp value of port partner is 3A
			{
//				if ( g_ucxRpVal != RP_3_0_A )
				if ( ( REG_DET_CTRL0 & 0x10 ) == 0x10 )//SW_CC1_EN
				{
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x03; 
				}
				else if ( ( REG_DET_CTRL0 & 0x20 ) == 0x20 )//SW_CC2_EN
				{
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x0C; 
				}
				REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
				REG_DET_CTRL1 |= 0x10;
				REG_DET_CTRL1 &= 0xEF;
			}
			else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x01 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//Rp value of port partner is 1.5A
			{
//				if ( g_ucxRpVal != RP_1_5_A )
				if ( ( REG_DET_CTRL0 & 0x10 ) == 0x10 )//SW_CC1_EN
				{
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x02; 
				}
				else if ( ( REG_DET_CTRL0 & 0x20 ) == 0x20 )//SW_CC2_EN
				{
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x08; 
				}
				REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
				REG_DET_CTRL1 |= 0x10;
				REG_DET_CTRL1 &= 0xEF;
			}
			else if ( ( ( PDC_STAT_7_0 & 0x01 ) == 0x00 ) && ( ( PDC_STAT_15_8 & 0x01 ) == 0x00 ) )//Rp value of port partner is 0.9A
			{
//				if ( g_ucxRpVal != RP_0_9_A )
				if ( ( REG_DET_CTRL0 & 0x10 ) == 0x10 )//SW_CC1_EN
				{
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x01; 
				}
				else if ( ( REG_DET_CTRL0 & 0x20 ) == 0x20 )//SW_CC2_EN
				{
					REG_DET_CTRL4 = ( REG_DET_CTRL4 & 0xF0 ) | 0x04; 
				}
				REG_SET_CLR |= 0x02;//CC_STATUS.Looking4Connection = 0
				REG_DET_CTRL1 |= 0x10;
				REG_DET_CTRL1 &= 0xEF;
			}

			CC_DET_IRQ_STATUS5 = 0x20;
		}

//		if( CC_DET_IRQ_STATUS5 & 0x40 & (~REG_CC_DET_INT_MASK5) )	// RADISCONN_CC1_STATUS
		if( CC_DET_IRQ_INT5 & 0x40 )	// RADISCONN_CC1_STATUS
		{
			g_vucxReg5[0xA9]++;

			REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
			REG_CC_DET_INT_MASK5 |= 0x40;//[6]RADISCONN_CC1_INT_MASK
			AOI_REG_PDC_95_88 &= 0x3F;
			ucxCCState = 0;
/*				
#ifdef TCPM_DEBOUNCE
			CC_DET_IRQ_STATUS0 = 0x38;
			CC_DET_IRQ_STATUS1 = 0x38;
			REG_CC_DET_INT_MASK0 = 0xC7;//CC1_CONN_FILT_INT_MASK,CC2_CONN_FILT_INT_MASK,VBUS_CONN_FILT_INT_MASK
			REG_CC_DET_INT_MASK1 = 0xC7;//CC1_DISCONN_FILT_INT_MASK,CC2_DISCONN_FILT_INT_MASK,VBUS_DISCONN_FILT_INT_MASK
#else
			CC_DET_IRQ_STATUS0 = 0x07;
			CC_DET_IRQ_STATUS1 = 0x07;
			REG_CC_DET_INT_MASK0 = 0xF8;//CC1_CONN_DEB_INT_MASK,CC2_CONN_DEB_INT_MASK,VBUS_CONN_DEB_INT_MASK
			REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
#endif
*/
#ifdef ENABLE_AUTO_POWER_DOWN
			AOI_REG_ANATOP_15_8 |= 0x80;//FIRMCMD_AUTOPD_EN
			usxDelay = 30;
			while ( usxDelay-- );
			AOP_REG_ANATOP_7_0 |= 0x10; //sleep,auto clear when wakeup
#endif

			CC_DET_IRQ_STATUS5 = 0x40;
		}

//		if( CC_DET_IRQ_STATUS5 & 0x80 & (~REG_CC_DET_INT_MASK5) )	// RADISCONN_CC2_STATUS
		if( CC_DET_IRQ_INT5 & 0x80 )	// RADISCONN_CC2_STATUS
		{
			g_vucxReg5[0xAA]++;

			REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
			REG_CC_DET_INT_MASK5 |= 0x80;//[7]RADISCONN_CC2_INT_MASK
			AOI_REG_PDC_95_88 &= 0x3F;
			ucxCCState = 0;
/*				
#ifdef TCPM_DEBOUNCE
			CC_DET_IRQ_STATUS0 = 0x38;
			CC_DET_IRQ_STATUS1 = 0x38;
			REG_CC_DET_INT_MASK0 = 0xC7;//CC1_CONN_FILT_INT_MASK,CC2_CONN_FILT_INT_MASK,VBUS_CONN_FILT_INT_MASK
			REG_CC_DET_INT_MASK1 = 0xC7;//CC1_DISCONN_FILT_INT_MASK,CC2_DISCONN_FILT_INT_MASK,VBUS_DISCONN_FILT_INT_MASK
#else
			CC_DET_IRQ_STATUS0 = 0x07;
			CC_DET_IRQ_STATUS1 = 0x07;
			REG_CC_DET_INT_MASK0 = 0xF8;//CC1_CONN_DEB_INT_MASK,CC2_CONN_DEB_INT_MASK,VBUS_CONN_DEB_INT_MASK
			REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
#endif
*/
#ifdef ENABLE_AUTO_POWER_DOWN
			AOI_REG_ANATOP_15_8 |= 0x80;//FIRMCMD_AUTOPD_EN
			usxDelay = 30;
			while ( usxDelay-- );
			AOP_REG_ANATOP_7_0 |= 0x10; //sleep,auto clear when wakeup
#endif

			CC_DET_IRQ_STATUS5 = 0x80;
		}
	}

//	if( CC_DET_IRQ_STATUS2 & 0x08 & (~REG_CC_DET_INT_MASK2) )	//CMD_WRITE_STATUS 
	if( CC_DET_IRQ_INT2 & 0x08 )	//CMD_WRITE_STATUS 
	{
		switch ( COMMAND )
		{
		case 0x99://Look4Connection.
			ALERT_MASK_LOW &= 0xFE;
//			ROLE_CONTROL = ( ROLE_CONTROL & 0x30 ) | 0x4A;
			ALERT_STATUS_1 |= 0x01;
//			ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
//			REG_IRQ_SRC_CTL &= 0xFE;
			break;
		case 0xFF://I2C Idle.
			if ( ( PDC_STAT_23_16 & 0x60 ) == 0 )//no cc connection
			{
#ifdef ENABLE_AUTO_POWER_DOWN
				AOI_REG_ANATOP_15_8 |= 0x80;//FIRMCMD_AUTOPD_EN
				usxDelay = 30;
				while ( usxDelay-- );
				AOP_REG_ANATOP_7_0 |= 0x10; //sleep,auto clear when wakeup 
//REG_GPIOP_OUT |= (GPIO7);
#endif
			}
			break;
		case 0x11://WakeI2C
			break;
		case 0x22://DisableVbusDetect.
			break;
		case 0x33://EnableVbusDetect.
			break;
		case 0x44://DisableSinkVbus.
			break;
		case 0x55://SinkVbus.
			DISABLE_DISCHARGE_VBUS;
			break;
		case 0x66://DisableSourceVbus.
			break;
		case 0x77://SourceVbusDefaultVoltage.
			DISABLE_DISCHARGE_VBUS;
			break;
		case 0x88://SourceVbusHighVoltage.
			break;
		case 0xAA://RxOneMore.
			break;
		default:
			break;
		}
		COMMAND = 0;

		CC_DET_IRQ_STATUS2 = 0x08;						   
	}

//	if( CC_DET_IRQ_STATUS2 & 0x10 & (~REG_CC_DET_INT_MASK2) )	//BELOW_DISCON_THRESH_INT 
	if( CC_DET_IRQ_INT2 & 0x10 )	//BELOW_DISCON_THRESH_INT 
	{
		g_vucxReg5[0xAB]++;

		DISABLE_DISCHARGE_VBUS;
		POWER_CONTROL &= 0xFB;//Disable forced discharge

		CC_DET_IRQ_STATUS2 = 0x10;						   
	}
//	if( CC_DET_IRQ_STATUS2 & 0x20 & (~REG_CC_DET_INT_MASK2) )	//BELOW_VSAFE0V_INT_MASK 
	if( CC_DET_IRQ_INT2 & 0x20 )	//BELOW_VSAFE0V_INT_MASK 
	{
		g_vucxReg5[0xAC]++;

		DISABLE_DISCHARGE_VBUS;
		POWER_CONTROL &= 0xFB;

		CC_DET_IRQ_STATUS2 = 0x20;						   
	}
//	if( CC_DET_IRQ_STATUS2 & 0x40 & (~REG_CC_DET_INT_MASK2) )	//BELOW_STOP_THRESH_INT_MASK 
	if( CC_DET_IRQ_INT2 & 0x40 )	//BELOW_STOP_THRESH_INT_MASK 
	{
		g_vucxReg5[0xAD]++;

		CC_DET_IRQ_STATUS2 = 0x40;						   
	}

#if 0
	if ( ( ECNTCON & 0x10 ) == 0x10 )  // 40bit counter 1
	{
		ECNTCON  = 0x10;		// clear INT, disable counter1
	}
#endif	

#if 0
	if ( ( ECNTCON2 & 0x10 ) == 0x10 )  // 40bit counter 2
	{				
		ECNTCON2  = 0x10;		// clear INT, disable counter2
	}
#endif
}