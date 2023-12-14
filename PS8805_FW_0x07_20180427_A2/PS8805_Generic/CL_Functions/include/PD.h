/**
  ******************************************************************************
  * @file  PD.h
  * @author  Jingbo.Li
  * @version V1.0.0
  * @date    04/23/2015
  * @brief   This file contains the PD source functions prototypes.
  ******************************************************************************
  */ 
  
#ifndef __PD_H
#define __PD_H


#define NULL    0

#define	USB_VID_PARADE          0x1DA0


#define ENABLE_AUTO_POWER_DOWN
//#define ENABLE_MPU_RESET_COUNTER

#define	USB_Vendor_ID		USB_VID_PARADE
#define	USB_Product_ID		0x8805
#define	BCDDEVICE			0x0001

#define	VBUS_OCP_GPIO	( 6	<< 5 )

#define	TCPM_DEBOUNCE
//#define	COMPARATOR

enum SOURCE_RESISTOR
{
	RP_DEFAULT_ONLY				= 0,
	RP_1_5A_AND_DEFAULT,					
	RP_3_0A_1_5A_AND_DEFAULT,		
};

enum ROLES
{               
	CONFIGURABLE				= 0,
	SOURCE_ONLY,					
	SINK_ONLY,					
	SINK_WITH_ACCESSORY_SUPPORT,
	DRP_ONLY,					
	ALL_SUPPORTED,				
	SOURCE_SINK_DRP,				
	NOT_VALID_SUPPORT,			
};

#define	VBUS_OCP_REPORTING					0x40
#define	VBUS_OVP_REPORTING					0x20
#define	BLEED_DISCHARGE						0x10
#define	FORCE_DISCHARGE						0x08
#define	VBUS_MEASUREMENT_AND_ALARM_CAPABLE	0x04
#define	SOURCE_RESISTOR_SUPPORTED			RP_3_0A_1_5A_AND_DEFAULT
#define	ROLES_SUPPORTED						( ALL_SUPPORTED << 5 )
#define	SOPP_DBG_OR_SOPDP_DBG_SUPPORT		0x10
#define	SOURCE_VCONN						0x08
#define	SINK_VBUS							0x04
#define	SOURCE_HIGH_VOLTAGE_VBUS			0x02
#define	SOURCE_VBUS							0x01

enum VCONN_POWER
{
	VCONN_POWER_1W        = 0,
	VCONN_POWER_1_5W,        
	VCONN_POWER_2W,          
	VCONN_POWER_3W,          
	VCONN_POWER_4W,          
	VCONN_POWER_5W,          
	VCONN_POWER_6W,
	VCONN_POWER_EXTERNAL,          
};

enum GPIO_SEL
{
	GPIO0	=	0x01,
	GPIO1	=	0x02,
	GPIO2	=	0x04,
	GPIO3	=	0x08,
	GPIO4	=	0x10,
	GPIO5	=	0x20,
	GPIO6	=	0x40,
	GPIO7	=	0x80,
};

#define	GPIO_SOURCE_VBUS		GPIO0
#define	GPIO_SINK_VBUS			GPIO1
#define	GPIO_DISCHARGE_VBUS		GPIO5

#define	ENABLE_SOURCE_VBUS		( REG_GPIO_OUT |= GPIO_SOURCE_VBUS )
#define	ENABLE_SINK_VBUS		( REG_GPIO_OUT |= GPIO_SINK_VBUS )
#define	ENABLE_DISCHARGE_VBUS	( REG_GPIO_OUT |= GPIO_DISCHARGE_VBUS )

#define	DISABLE_SOURCE_VBUS		( REG_GPIO_OUT &= (~GPIO_SOURCE_VBUS) )
#define	DISABLE_SINK_VBUS		( REG_GPIO_OUT &= (~GPIO_SINK_VBUS) )
#define	DISABLE_DISCHARGE_VBUS	( REG_GPIO_OUT &= (~GPIO_DISCHARGE_VBUS) )

#define	SINK_DISCONNECT_DETECTION	0x80
#define	STOP_DISCHARGE_THRESHOLD	0x40
#define	VBUS_VOLTAGE_ALARM_LSB		0x20 //TCPC has 100mV LSB for its voltage alarm and uses only 8 bits.
#define	VCONN_POWER_SUPPORTED		( VCONN_POWER_1_5W << 1 )
#define	VCONN_OVERCURRENT_FAULT_CAPABLE	0x01

enum STANDARD_INPUT
{               
	VBUS_EXTERNAL_OVER_VOLTAGE_FAULT				= 0x04,
	VBUS_EXTERNAL_OVER_CURRENT_FAULT				= 0x02,	
	FORCE_OFF_VBUS									= 0x01,
};

enum STANDARD_OUTPUT
{               
	DEBUG_ACCESSORY_INDICATOR				= 0x40,
	VBUS_PRESENT_MONITOR					= 0x20,
	AUDIO_ADAPTER_ACCESSORY_INDICATOR		= 0x10,			
	ACTIVE_CABLE_INDICATOR					= 0x08,
	MUX_CONFIGURATION_CONTROL			    = 0x04,		
	CONNECTION_PRESENT						= 0x02,
	CONNECTOR_ORIENTATION					= 0x01,
};

enum RP_VALUE
{               
	RP_0_9_A		= 0x01,
	RP_1_5_A		= 0x02,
	RP_3_0_A		= 0x03,
};

void Physical_Layer_Init(void);
void VBUS_Force_Discharge(void);
//void Sink_Auto_Discharge(void);
void Delay( unsigned char ucMilliSec );

#endif /* __PD_H */

