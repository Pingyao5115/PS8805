#include <myDP8051XP.H>
#include "global.h"
//#include "cl_Functions.h"
#include "MPU_Functions.h"
//#include "MPU_SPIFunction.h"
#include "registers_map.h"


void ll_MPUInit(void)
{
	MPU_Init();
}

void ll_SetVerNum( void )
{
	MPU_SetVerNum( 0, 1, 0, 0 );
}
