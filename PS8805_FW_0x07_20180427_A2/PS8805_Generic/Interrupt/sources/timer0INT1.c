#include <myDP8051XP.H>
#include "global.h"
#include "registers_map.h"


void timer0_IT(void) interrupt 1
{
    TF0 = 0;

    TR0 = 0;

	g_ucTick++;
	g_vucxReg5[0xFB]++;

    //60MHz
    TH0         =   0X9E;	 //5ms
    TL0         =   0X58;
//    TH0         =   0X3C;	 //10ms
//    TL0         =   0XB0;

	if ( g_ucTick == 10 )
    {
        g_ucTick = 0;
    }

    TR0 = 1;
}
