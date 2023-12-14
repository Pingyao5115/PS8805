2017/06/22	0x01	initial version, based on A1 chip

2017/09/15	0x02	verified with reef board replace PS8751

2017/09/19	0x03	enable VBUS monitor

2017/09/22	0x04	for A1A, disable I2C last timer

2017/10/31	0x05	(1)adjust threshold of detecting Rp;
			(2)add code to detect different Rp value on CC1&CC2 to support debug 				accessory
					
2018/03/08	0x06	for A2,
			(1)The Rx message alert is asserted after GoodCRC is sent;
			(2)adjust receiver's hysteresis control to 300mV;
			(3)adjust GCRC bus idle timer;
			(4)change default EQ;
			(5)change Rd/Ra detection ADC difference from 5 to 10;
					
2018/04/27	0x07	(1)fix a bug of reporting wrong cc status when Rp value change,
			(2)set HPD Toggle time 1.2ms,
			(3)set to one pattern error allowed for SOP,
			(4)remove some EQ settings.
					
2018/08/10	0x08	(1)unmask FAULT_STATUS;
			(2)enable GPIO for VBUS source, sink and discharge;
			(3)change DRP toggle condition to both CC are Rd or Rp;
			(4)add BIST mode;
			(5)add COMMAND function.
					
2018/09/04	0x09	fix a bug of detecting debug accessory;
			support Rp/Rp TS.
					
2018/10/19	0x0A	(1)mask/unmask cc status change IRQ when TCPM write role control;
			(2)unmask cc status change IRQ before update CC_STATUS;
			(3)remove mask cc status change IRQ when TCPM write look for 
			   connection.
					
2018/10/23	0x0B	move clear IRQ registers code to first power on to fix a Zinger charger not 
			detected issue.

2018/10/26	0x0C	change receiver's hysteresis control to 300mV to fix a Apple charger issue 
			which sending 140mv noise when bus idle.

2019/06/18	0x0D	(1)clear CC disconnetion status when CC connection;
			(2)clear CC status seperately when CC disconnetion.

2019/06/20	0x0E	add a condition of checking VConn status to fix a debug accessory issue.

2020/01/19	0x0F	(1)Random Jitter optimized:
			   p1.63=0x24
			   p1.64=0x2a
			(2)restrict CC detection to support detection of Ra changed to 20K after 
			    VCONN SWAP
			(3)fix a bug of wrong ADDRCFG0 value caused I2C disable access function 
			   failure
			(4)AOI_REG_PDC_15_8 = 0x00;//CC Debounce Assert 40us
			(5)AOI_REG_PDC_23_16 |= 0x02;//<1> select debounce signalㄩRa only 
			   will sleep
			(6)clear CC status seperately in Rp change IRQ
					
2020/05/15	0x10	(1)clear another CC status when disconnection, if its disconnection because 
                                        of VCONN on clear corresponding cc status when VCONN on	
			    set P3.18[0] to indicate unflip/flip 
			(2)remove P3.1F
			(3)add SendFRSwapSignal by COMMAND of 0xCC
			(4)set FRS signal pulse width to 120us
			(5)stop send message when detected FRS
					
2020/05/29	0x11	(1)change revision to 1.2
			(2)add Detect RpRp Change function	
			(3)add FRS function

2020/06/18	0x12	change version number

2020/10/26	0x13	(1)P6.0B[7]=1:LOOK4CONN_CLR_MASK
			(2)generate VBUS present when TCPC is source
			(3)Auto DCI mode disable
			(4)move Rp/Rp change switch to P3.E7
			(5)add FRS switch to P3.E6
			(6)clear Looking4Connection if CC connected when TCPM writing 
			   COMMAND = 0x99
			(7)change BCDDEVICE to 0x04
			(8)P1.01[7]=1: controlled sample switch always on

2021/03/05	0x14	(1)P3.AA = 0x96:workaround for abnormal end of GOODCRC with an 
			   abnormal dongle
			(2)use P1.E4[6:5] as CC open condition to avoid GRL tester pull about 100K 
			   to GND issue
			(3)set P2.0B[7] CC VREF for Comparator to 0(2.6V) when Rp 3.0A and 
			   1(1.6V) when Rp 0.9 & 1.5A		
			(4)remove Rp change status register clear when Rp detected
			(5)enable Rp change detection
			(6)fix wrong CC_STATUS issue caused by abnormal CC voltage when 
			    dongle unplug

2021/06/03	0x15	workaround to update CC status after device glitch

2021/07/15	0x16	update BCDDEVICE to 0x02 for A3 chip

for A2:
2021/07/22	0x17	fix BIST Test mode

2021/08/11 	0x18     modify the string in the code to match the real firmware version

2023/02/08 	0x19	remove the USB mux switch during RpRp detection, and add it back after 
			the CC status RpRp is detected

for A3:
2021/07/22	0x20	fix BIST Test mode

2021/08/11	0x21 	modify the string in the code to match the real firmware version

2023/02/02 	0x22	remove the USB mux switch during RpRp detection, and add it back after 
			the CC status RpRp is detected

2023/06/01	0x23	(1)add a condition of Role_Crontrol is 2A in the firmware patch for glitch 
			   issue
			(2)workaround for no IRQ event when cc changes from 1.5A to 3A.
	 		(3)the alert of CC_DET_IRQ_STATUS1 is not cleared that cause PS8805 
			   doesn't send IRQ. Firmware writes register to clear cc status.
					
/////////////////////////////////////////////////////////////////////////////////////////////////////////////					
for A4 chip,
			P3.D5[2] = 1:NON_EXPECTED_GOODCRC_EN
			add FRS switch on/off code when TCPM write P3.1C[7]
			update P3.E6 control code for FRS	
