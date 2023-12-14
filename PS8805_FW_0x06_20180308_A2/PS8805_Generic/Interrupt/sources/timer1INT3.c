#include <myDP8051XP.H>
#include "global.h"
#include "PD.h"
#include "registers_map.h"

void timer1_INT(void) interrupt 3
{
    TF1 = 0;

    TR1 = 0;

	g_ucTicks++;
	g_vucxReg5[0xFD] = g_ucTicks;

    //60MHz
    TH1         =   0X3C;	 //10ms
    TL1         =   0XB0;

	if ( g_ucTicks == 50 )
    {
//		EA = 0;
		REG_DET_CTRL2 &= 0x9B;//stop
		CC_DET_IRQ_STATUS2 = 0x04;
		REG_DET_CTRL2 |= 0x20;//SW_ADC_VBUS_EN
		REG_DET_CTRL2 |= 0x40;//SW_DLPF_START
		while ( (!(CC_DET_IRQ_STATUS2 & 0x04)) /*&& ( REG_DET_CTRL2 & 0x40 )*/ )
		{
			g_vucxReg5[0x87]++;
		}
		CC_DET_IRQ_STATUS2 = 0x04;
		REG_DET_CTRL2 &= 0x9B;//stop
		REG_DET_CTRL2 |= 0x04;//[2]SW_ADC_DET_DONE_VBUS
		REG_DET_CTRL2 &= 0xFB;
//		EA = 1;
//		VBUS_VOLTAGE = ( (unsigned short)REG_VBUS_DCC << 2 ) | 0x0800;//REG_VBUS_DCC:100mV per bit;VBUS_VOLTAGE:25mV per bit

        g_ucTicks = 0;

		g_vucxReg5[0xFE]++;
    }

    TR1 = 1;
}
