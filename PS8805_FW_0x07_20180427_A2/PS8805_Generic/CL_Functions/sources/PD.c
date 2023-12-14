/**
  ******************************************************************************
  * @file  PD.c 
  * @author Jingbo.Li 
  * @version V1.0.0
  * @date    10/30/2015
  * @brief   
  ******************************************************************************
  */ 

#include <myDP8051XP.H>
#include "registers_map.h"
#include "PD.h"
#include "global.h"

void Physical_Layer_Init(void)
{
//	unsigned short xdata usxDelay = 150;
//	unsigned char idata uciData;

	AOI_REG_ANATOP_15_8 |= 0x10;//Disable I2C LAST
//	AOI_REG_ANATOP_63_56 = 0x25;//<7:5> I2C_ACTIVE_LAST:001:75mS

//	AOI_REG_PDC_39_32 = 0x40;//<6> Enable CC R/I select

//	ADDRCFG0 = 0x17;//disable I2C access
//	ADDRCFG4 = 0x8B;//[7]TESTI2CEN,[6:0]slave address[7:1]
//	MPU_HOLD_MODE = 0x07;//[2]MPU_HOLD_MODE  enable, [1]WR_HOLD, [0]RD_HLD
	REG_IRQ_SRC_CTL = 0x81;//[0]enable ALERT to TCPM[6]disable ALERT to MPU
//	REG_IRQ_SRC_CTL = 0xC1;//[0]enable ALERT to TCPM[6]enable ALERT to MPU
	FUNC_IRQ_MASK = 0xBF;//page3 write remapping
	FAULT_STATUS_MASK = 0x00;//0b: Interrupt masked

//	CTL_DEBUG_SEL = 0x20;//get I2C slave address
//	DEBUG_IN;//01:0x10;13:0x30;25:0x50;39:0x90

	REG_STRETCH |= 0x60;//read page 3 from control I2c to wakeup
	REG_DLPF_CTRL0 |= 0x60;//sample 64 times for average
	REG_DET_CTRL1 = 0x64;
	REG_DET_CTRL2 = 0x10;//[4:3]VBUS_CAL_SEL:100mv
	REG_DET_CTRL3 = 0x50;//REG_VSAFE0V = 0.8V,[6]VCONNEN_CLR_MASK
/*
#ifdef TCPM_DEBOUNCE
	REG_CC_DET_INT_MASK0 = 0xC7;//CC1_CONN_FILT_INT_MASK,CC2_CONN_FILT_INT_MASK,VBUS_CONN_FILT_INT_MASK
	REG_CC_DET_INT_MASK1 = 0xC7;//CC1_DISCONN_FILT_INT_MASK,CC2_DISCONN_FILT_INT_MASK,VBUS_DISCONN_FILT_INT_MASK
#else
	REG_DEBOUNCE_CTRL0 = 0x00;//CC attach debounce 10ms
	REG_DEBOUNCE_CTRL1 = 0x02;//CC detach debounce 3ms
//	REG_DEBOUNCE_CTRL1 |= 0x40;//FILT_SEL enable	
	REG_CC_DET_INT_MASK0 = 0xF8;//CC1_CONN_DEB_INT_MASK,CC2_CONN_DEB_INT_MASK,VBUS_CONN_DEB_INT_MASK
	REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
#endif
*/
	REG_DEBOUNCE_CTRL0 = 0x00;//CC attach debounce 10ms
	REG_DEBOUNCE_CTRL1 = 0x02;//CC detach debounce 3ms
	REG_DEBOUNCE_CTRL3 = 0x00;//vbus attach debounce 10ms
	REG_DEBOUNCE_CTRL4 = 0x82;//vbus detach debounce 3ms

//	CC_DET_IRQ_STATUS2 = 0xFF;
//	CC_DET_IRQ_STATUS4 = 0xFF;
	REG_CC_DET_INT_MASK2 = 0x87;
	REG_CC_DET_INT_MASK4 = 0xBE;//[6]PC_VCONN_EN_CHG_INT_MASK,[0]PC_FCDICHAR_CHG_INT_MASK
	AOI_REG_PDC_95_88 &= 0x3F;
	REGHPD |= 0x02;//[1] TCPC_EN for analog
	REG_HPD_TOG = 0x02;//Toggle time 1.2ms

	REG_GPIO_OEB = 0;//GPIO output
	REG_GPIOP_OEB = 0;//GPIO output
//	ENABLE_DISCHARGE_VBUS;
	REG_GPIO_SEL = REG_GPIO_SEL | GPIO5;
	REG_GPIO_OUT = REG_GPIO_OUT & (~GPIO5);
//	REG_GPIOP_SEL = REG_GPIOP_SEL | GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7;
//	REG_GPIOP_OUT = REG_GPIOP_OUT & (~GPIO0) & (~GPIO1) & (~GPIO2) & (~GPIO3) & (~GPIO4) & (~GPIO5) & (~GPIO6) & (~GPIO7);

//	REG_WID_SEL |= 0x08;//I2C R/W IRQ EN

//	C2SS_WU1_REG = 0xE0;//Port1 signal detector threshold adjust	

	REG_OPTION_CTR = 0x58;// Bit[4]:  1: The Rx message alert is asserted after GoodCRC is sent.
             						//0: The Rx message alert is asserted before GoodCRC is sent.

	AOP_REG_PDC_63_56 = 0x02;//<1:0>receiver's hysteresis control:10:300mV
	GOODCRC_BUS_IDLE_TIMER_BYTE_0 = 0xE6;//200.2us good
	GOODCRC_BUS_IDLE_TIMER_BYTE_1 = 0x0A;   // GCRC bus idle timer, it is setting into 195 us now (15MHz)

/*	BMC_PHY_CTR0 = 0x31;
	BMC_PHY_CTR1 = 0x53;
	BMC_PHY_CTR2 = 0x03;
	BMC_PHY_CTR3 = 0x06;
	BMC_PHY_CTR4 = 0x84;
	BMC_PHY_CTR5 = 0x00;
	BMC_PHY_CTR6 = 0x00;
	BMC_PHY_CTR7 = 0x00;
	BMC_PHY_CTR8 = 15 * 5;
	BMC_PHY_CTR9 = 0x96;

	REG_WID_SEL = 0x07;

	REG_OPTION_CTR_1 = 0x07;//HW control GOODCRC header info

	GOODCRC_BUS_IDLE_TIMER_BYTE_0 = 0x8B;
	GOODCRC_BUS_IDLE_TIMER_BYTE_1 = 0x0B;   // GCRC bus idle timer, it is setting into 195 us now (15MHz)
	GDCRC_TIMER_BYTE0 = 0x7C;
	GDCRC_TIMER_BYTE1 = 0x01; // RX GCRC sending timer, it is setting into 25 us now
	GOODCRC_RECEIVE_TIMER_BYTE0 = 0x98;
	GOODCRC_RECEIVE_TIMER_BYTE1 = 0x3A;

	VENDOR_ID_L = USB_Vendor_ID & 0xFF;
	VENDOR_ID_H = USB_Vendor_ID >> 8;
	PRODUCT_ID_L = USB_Product_ID & 0xFF;
	PRODUCT_ID_H = USB_Product_ID >> 8;
	DEVICE_ID_L = BCDDEVICE & 0xFF;
	DEVICE_ID_H = BCDDEVICE >> 8;
	USBTYPEC_REV_L = 0x10;
	USBTYPEC_REV_H = 0;
	USBPD_REV_VER_L = 0x12;
	USBPD_REV_VER_H = 0x20;
	PD_INTERFACE_REV_L = 0x11;
	PD_INTERFACE_REV_H = 0x10;*/

	BMC_PHY_CTR4 = 0xC4;
	BMC_PHY_CTR11 = 0x04;
	MESSAGE_HEADER_INFO = 0x02;

	PRODUCT_ID_L = USB_Product_ID & 0xFF;
	DEVICE_CAPABILITIES_1 = ROLES_SUPPORTED | SOPP_DBG_OR_SOPDP_DBG_SUPPORT | SOURCE_VCONN/* | SINK_VBUS | SOURCE_HIGH_VOLTAGE_VBUS | SOURCE_VBUS*/;//0xB8;
	DEVICE_CAPABILITIES_2 = /* BLEED_DISCHARGE |*/ FORCE_DISCHARGE | VBUS_MEASUREMENT_AND_ALARM_CAPABLE | SOURCE_RESISTOR_SUPPORTED;//0x0E;
#ifdef VBUS_OCP
//	DEVICE_CAPABILITIES_2 |= VBUS_OCP_REPORTING;
//	REG_DEBOUNCE_CTRL3 |= VBUS_OCP_GPIO;//[7:5]SW_ANA_OCP_SEL
#else
//	DEVICE_CAPABILITIES_2 |= VBUS_OVP_REPORTING;
#endif
	DEVICE_CAPABILITIES_3 = /*SINK_DISCONNECT_DETECTION |*/ STOP_DISCHARGE_THRESHOLD | VBUS_VOLTAGE_ALARM_LSB | VCONN_POWER_SUPPORTED/* | VCONN_OVERCURRENT_FAULT_CAPABLE*/;//0x62
	DEVICE_CAPABILITIES_4 = 0x00; 
	STANDARD_INPUT_CAPABILITIES = 0;//VBUS_EXTERNAL_OVER_CURRENT_FAULT;// | FORCE_OFF_VBUS;//0x03;
	STANDARD_OUTPUT_CAPABILITIES = MUX_CONFIGURATION_CONTROL | CONNECTION_PRESENT | CONNECTOR_ORIENTATION | VBUS_PRESENT_MONITOR;//0x27;

	VBUS_SINK_DISCONNECT_THRESHOLD_L = 200;
	VBUS_SINK_DISCONNECT_THRESHOLD_H = 0x00;
	VBUS_STOP_DISCHARGE_THRESHOLD_L = 0x20;
	VBUS_STOP_DISCHARGE_THRESHOLD_H = 0x00;
	VBUS_VOLTAGE_ALARM_HI_CFG_L = 240;
	VBUS_VOLTAGE_ALARM_HI_CFG_H = 0x00;
	VBUS_VOLTAGE_ALARM_LO_CFG_L = 0x00;
	VBUS_VOLTAGE_ALARM_LO_CFG_H = 0x00;

	AOP_REG_PDC_63_56 = 0x01;//receiver's hysteresis control
	AOP_REG_PDC_79_72 = 0x03;//SST Driver output peak value tuning -8.34%
	AOI_REG_PDC_15_8 = 0xC0;//wake up 160us
//	AOI_REG_PDC_23_16 |= 0x01;//<0>Select Rp initial toggle when CC1 & CC2 is open, 0: Rd, 1: Rp
	AOI_REG_PDC_31_24 |= 0x10;//<4> select DRP toggle condition
							  //0: both of CC are RD or Rp
							  //1: both of CC are open
//	AOI_REG_PDC_23_16 |= 0x02;//<1> select debounce signal
							 //0: Ra only will keep wake up
							 //1: Ra only will sleep
	REGDD &= 0xBF;//[6]0:don't change status when masked
	REGDD |= 0x20;//GoodCrc header byte is set to specification revision
#if 0//debug
	REG_VENDOR_CTRL2 |= 0x10;//not clear RECEIVE_BYTE_COUNT when alert is cleared
	REG_VENDOR_CTRL2 |= 0x04;//not clear RECEIVE_BYTE_COUNT when received hardreset
	REG_VENDOR_CTRL3 |= 0x02;//not clear RECEIVE_BYTE_COUNT when send hardreset
#endif
	REG_VENDOR_CTRL4 |= 0x80;//[7]FRS_DET_DIG_MASK
							 //Mask function of stopping transmitting CC message when detecting fast_role_swap signal
							 //1:enable,0:disable
	REG_POWER_STATUS |= 0x08;//POWER_STATUS: [3]VBUS Present Detection Enabled
	POWER_CONTROL &= 0xBF;//[6]VBUS_VOLTAGE Monitoring is enabled

//	OTHER_CTRL3 &= 0xDF;//[5]CC_CONN_ENWIN_MASK

	ADDRCFG0 = 0x10;//enable I2C access
//	ADDRCFG0 = 0x17;//enable I2C access
//REG_GPIOP_OUT = REG_GPIOP_OUT | GPIO6;

/*	REG_RUSB_DRV_7_0 = 0x03;//set swing to decrease by 3 levels
	REG_RUSB_DRV_15_8 = 0x04;//set preshoot on for rx as lvl 4
	REG_RUSB_DRV_23_16 = 0x16;//set de-emphasis on for rx as lvl 6
	//SIGNALDET rising and falling edge timing
	REG_EQTX_31_24 = 0x09;//TUSB SD falling edge timing and rising edge timing, 20180131
	REG_EQRX_23_16 = 0x40;//RUSB SD rising edge timing, 20180131
	REG_EQRX_31_24 = 0x02;//RUSB SD falling edge timing, 20180131
	//TX De-emphasis and Preshoot settings
	REG_TUSB_DRV_15_8 = 0x8b;//set de-emphasis (lvl 3) on and preshoot(lvl 1)  on for tx,20180118
*/
	if ( ( POWER_ON_RESET & 0x01 ) == 0 )//POWER_ON_RESET: 0:power on reset;1:wake up
	{
/*		//CEQ
		AOI_REG_ANATOP_47_40 = 0x1E;
		AOI_REG_ANATOP_39_32 = 0x07;//db
		//SSEQ
		AOI_REG_ANATOP_31_24 = 0x1E;
*/
		POWER_ON_RESET |= 0x01;
g_vucxReg0[0x5C]++;
		ALERT_MASK_LOW	= 0xFE;	//0b: Interrupt masked,1b: Interrupt unmasked
		ALERT_MASK_HIGH	= 0x01;	
		POWER_STATUS_MASK = 0x04;//[2]VBUS Present Status Interrupt UnMask	
	
#ifdef ENABLE_AUTO_POWER_DOWN
/*		AOI_REG_ANATOP_15_8 |= 0x80;//FIRMCMD_AUTOPD_EN
		usxDelay = 30;
		while ( usxDelay-- );
		AOP_REG_ANATOP_7_0 |= 0x10; //sleep,auto clear when wakeup*/
		AOI_REG_ANATOP_15_8 &= 0x7F;//disable FIRMCMD_AUTOPD_EN
#endif

#ifdef HW_MODE
		REG_DET_CTRL0 = 0x04;//HW MODE
#else
		REG_DET_CTRL0 = 0x84;//SW MODE
#endif
		g_vucxReg2[0x30] = REG_DET_CTRL0;
	}
	else
	{
		REGDD |= 0x10;//set POWER_STATUS change alert
		if ( STA_P2_75 & 0x30 )//WK_I2C_STAT or WK_PLUG_STAT
		{
			//clear WK_I2C_STAT & WK_PLUG_STAT
			REG_MI2C_MODE |= 0x10;
			REG_MI2C_MODE &= 0xEF;
		}
	}

	REG_DET_CTRL0 = g_vucxReg2[0x30];

	ALERT_STATUS_1 = 0xFF;
	ALERT_STATUS_2 = 0xFF;
#ifdef TCPM_DEBOUNCE
//	CC_DET_IRQ_STATUS0 = 0xFF;
	REG_CC_DET_INT_MASK0 = 0xC7;//CC1_CONN_FILT_INT_MASK,CC2_CONN_FILT_INT_MASK,VBUS_CONN_FILT_INT_MASK
#else
//	CC_DET_IRQ_STATUS0 = 0xFF;
	REG_CC_DET_INT_MASK0 = 0xF8;//CC1_CONN_DEB_INT_MASK,CC2_CONN_DEB_INT_MASK,VBUS_CONN_DEB_INT_MASK
#endif
//	CC_DET_IRQ_STATUS1 = 0xFF;
	REG_CC_DET_INT_MASK1 = 0xF8;//CC1_DISCONN_DEB_INT_MASK,CC2_DISCONN_DEB_INT_MASK,VBUS_DISCONN_DEB_INT_MASK
//	ALERT_STATUS_2 = 0x02;//[1]ALERT_REGISTER.Fault

#if 0
	g_vucxReg6[0x3E] = 0x44;
	g_vucxReg2[0x4F] = 0x03;
	g_vucxReg2[0x25] = 0x00;
	g_vucxReg2[0x2A] |= 0x20;
#endif

/*	//transmit message successful signal on GPIOP2
	g_vucxReg3[0xc0] = 0x5;
	g_vucxReg2[0x4f] = 0x1;
	g_vucxReg2[0x25] = 0x0;
	g_vucxReg2[0x2a] = 0x20;*/
}

void VBUS_Force_Discharge(void)
{
	REG_DET_CTRL2 &= 0x9B;//stop
	REG_DET_CTRL2 |= 0x20;//SW_ADC_VBUS_EN
	REG_DET_CTRL2 |= 0x40;//SW_DLPF_START
//REG_GPIOP_OUT = REG_GPIOP_OUT | (GPIO7);
	while ( (!(CC_DET_IRQ_STATUS2 & 0x04)) /*&& ( REG_DET_CTRL2 & 0x40 )*/ )
	{
		if ( g_ucxExitSample )
		{
			g_ucxExitSample = 0;
//			g_ucxVBUS_Force_Discharge = 0;//?
			return;
		}
		g_vucxReg5[0x81]++;
	}
	CC_DET_IRQ_STATUS2 = 0x04;
	REG_DET_CTRL2 &= 0x9B;//stop
	REG_DET_CTRL2 |= 0x04;//[2]SW_ADC_DET_DONE_VBUS
	REG_DET_CTRL2 &= 0xFB;
//REG_GPIOP_OUT = REG_GPIOP_OUT & (~GPIO7);
//	VBUS_VOLTAGE = ( (unsigned short)REG_VBUS_DCC << 2 ) | 0x0800;//REG_VBUS_DCC:100mV per bit;VBUS_VOLTAGE:25mV per bit
	g_usx_VBUS_STOP_DISCHARGE = (unsigned short)REG_VBUS_DCC << 2;//convert to 25mV per bit
	if ( g_usx_VBUS_STOP_DISCHARGE < VBUS_STOP_DISCHARGE_THRESHOLD_L + VBUS_STOP_DISCHARGE_THRESHOLD_H * 256 )//stop discharge
	{
		DISABLE_DISCHARGE_VBUS;
//		g_ucxVBUS_Discharge = 0;//?
		g_ucxVBUS_Force_Discharge = 0;//?
		POWER_CONTROL &= 0xFB;
//		g_vucxReg5[0x10]= g_usx_VBUS_STOP_DISCHARGE & 0xFF;
//		g_vucxReg5[0x11]= g_usx_VBUS_STOP_DISCHARGE >> 8;
//		g_vucxReg5[0x12]= REG_VBUS_DCC;
	}
}
/*
void Sink_Auto_Discharge(void)
{
	REG_DET_CTRL0 &= 0xB4;//stop
	REG_DET_CTRL2 &= 0x9B;//stop
	REG_DET_CTRL2 |= 0x20;//SW_ADC_VBUS_EN
	REG_DET_CTRL2 |= 0x40;//SW_DLPF_START
	while ( !(CC_DET_IRQ_STATUS2 & 0x04) );
	CC_DET_IRQ_STATUS2 = 0x04;
	REG_DET_CTRL2 &= 0x9B;//stop
//	REG_DET_CTRL2 |= 0x04;//[2]SW_ADC_DET_DONE_VBUS
//	REG_DET_CTRL2 &= 0xFB;
//	VBUS_VOLTAGE = ( REG_VBUS_DCC << 2 ) | 0x0800;//REG_VBUS_DCC:100mV per bit;VBUS_VOLTAGE:25mV per bit
	g_usx_VBUS_SINK_DISCONNECT = ( (unsigned short)REG_VBUS_DCC ) << 2;//convert to 25mV per bit
	if ( g_usx_VBUS_SINK_DISCONNECT < VBUS_SINK_DISCONNECT_THRESHOLD_L + VBUS_SINK_DISCONNECT_THRESHOLD_H * 256 )//start to discharge
	{
		ENABLE_DISCHARGE_VBUS;
	}
}*/

void Delay( unsigned char ucMilliSec )
{
	unsigned char idata i;

	for ( i = 0; i < ucMilliSec; i++ )
	{
		usxDelay = 375;
		while ( usxDelay-- );
	}
}
