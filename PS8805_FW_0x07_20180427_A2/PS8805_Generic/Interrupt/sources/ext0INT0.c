#include <myDP8051XP.H>
#include "global.h"
#include "registers_map.h"

void ext0_INT(void) interrupt 0
{
/*	if( CTL_IRQ & (~CTLIRQ_CTL) )
	{
		if( CTL_IRQ & 0x08 & (~CTLIRQ_CTL) )	// WRITE_WAIT_IRQ
		{
			CTL_IRQ = CTL_IRQ & 0x08;
		}

		if( CTL_IRQ & 0x04 & (~CTLIRQ_CTL) )	// READ_WAIT_IRQ
		{
			CTL_IRQ = CTL_IRQ & 0x04;
		}
	}
*/
	if( FUNC_IRQ_STATUS & 0x40 & (~FUNC_IRQ_MASK) )
	{
		switch ( I2C_OFFSET )
		{
/*		case 0x1A:
			if ( ( I2C_WRDATA & 0x40 ) == 0x40 )
			{
//				ALERT_MASK_LOW &= 0xFE;
				ROLE_CONTROL = ( ROLE_CONTROL & 0x30 ) | 0x4A;
//				COMMAND = 0x99;
			}
//			ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
//			ALERT_STATUS_1 |= 0x01;
			break;*/
		case 0xD0:
			REGHPD = ( REGHPD & 0xFE ) | ( I2C_WRDATA & 0x01 );
			if ( I2C_WRDATA & 0x02 )
			{
			  	REG_HPD_TOG |= 0x80;
			  	REG_HPD_TOG &= 0x7F;
			}
			break;
		case 0xA0:
			BMC_PHY_CTR0 = 0x31;
			ADDRCFG0 = 0x10;//enable I2C access
			break;
		}

		FUNC_IRQ_STATUS = FUNC_IRQ_STATUS & 0x40;
	}

/*	if( FUNC_IRQ_STATUS & 0x40 & (~FUNC_IRQ_MASK) )
	{
		MI2CSLV_ADDR = 0x98;
		MI2C_OFFSET = I2C_OFFSET;
		MI2C_WDATA = I2C_WRDATA;
		MI2C_LEN = 0;
		MI2C_CTL = 1;

		FUNC_IRQ_STATUS = FUNC_IRQ_STATUS & 0x40;
	}*/
}