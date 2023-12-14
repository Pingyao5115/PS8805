/////////////////////////////////////////////////
//	LL function for MPU
/////////////////////////////////////////////////
#include <myDP8051XP.H>
#include "global.h"
//#include "cl_Functions.h"
#include "mpu_functions.h"
//#include "llfnEnum.h"

void ll_MPU_DisableINT(void)
{
	MPU_DisableINT();
}

void ll_MPU_EnableINT(void)
{
	MPU_EnableINT();
}

void ll_MPU_SetINTMask(void)
{
	MPU_SetINTMask0();
	MPU_SetINTMask1();

	MPU_EnableINT0();
	MPU_EnableINT1();
}

