#include <myDP8051XP.H>
#include "global.h"
#include "registers_map.inc"
#include "PD.h"
//#include "debug.h"
#include "ll_MPU.h"
#include "ll_functions.h"


main()
{
//	ADDRCFG0 = 0x15;//disable I2C access
	FAULT_STATUS = 0x80;//[7]FAULT_STATUS.reset_to_default

	ll_MPU_DisableINT();

	ll_MPU_SetINTMask();

	ll_MPUInit();				//Initialize MPU

    ll_MPU_EnableINT( );
	
	Physical_Layer_Init();

	ll_SetVerNum( );

	while(1)
	{
#ifdef ENABLE_MPU_RESET_COUNTER
		//[6]FW_CNT_CLR(0->1 toggle)
		OTHER_CTRL1 &= 0xBF;  	
		OTHER_CTRL1 |= 0x40;  	
#endif

		g_vucxReg5[0x00]++;
		REG_GPIOP_OUT ^= GPIO6;//toggle period is 2.3us

/*		if ( PDC_STAT_31_24 & 0x01 )//DRP
		{
			ALERT_MASK_LOW &= 0xFE;
			ALERT_STATUS_1 = ALERT_STATUS_1 & (0x01);
//			ALERT_STATUS_1 |= 0x01;
		}*/
		if ( g_ucxVBUS_Force_Discharge && ( DEVICE_CAPABILITIES_3 & 0x40 ) && ( ( CC_DET_IRQ_STATUS0 & 0x18 ) == 0 ) )
		{
//		g_vucxReg5[0x01]++;
			VBUS_Force_Discharge();
		}
/*//		if ( ( g_ucxPortPowerRole == PORT_POWER_ROLE_SINK ) && ( DEVICE_CAPABILITIES_3 & 0x80 ) )
		if ( ( ROLE_CONTROL == POWER_ROLE_SINK ) && ( DEVICE_CAPABILITIES_3 & 0x80 ) )
		{
//			Sink_Auto_Discharge();
		}*/
	}
}