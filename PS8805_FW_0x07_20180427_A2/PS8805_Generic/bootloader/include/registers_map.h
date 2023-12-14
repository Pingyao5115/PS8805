#ifndef _REGISTERS_MAP_H_
#define _REGISTERS_MAP_H_
//#include "spiregdef.h"

#if 0
extern volatile unsigned char xdata g_vucxReg0[0xff] ;
extern volatile unsigned char xdata g_vucxReg1[0xff] ;
extern volatile unsigned char xdata g_vucxReg2[0xff] ;
extern volatile unsigned char xdata g_vucxReg3[0xff] ;
extern volatile unsigned char xdata g_vucxReg4[0xff] ;
extern volatile unsigned char xdata g_vucxReg5[0xff] ;
#endif


#ifndef FARRAY
	#define FARRAY(object, base) ((object volatile xdata *) (base))
#endif

#define g_vucxReg1 FARRAY(unsigned char, 0x100)

#define g_vucxReg5 FARRAY(unsigned char, 0x500)
#define g_vucxReg6 FARRAY(unsigned char, 0x600)

//extern volatile unsigned char xdata g_vucxReg1[0xff] ;
//extern volatile unsigned char xdata g_vucxReg5[0xff] ;

#define XBase(object, base) ((object volatile xdata *) (base))

#define REGPAGE0	 	XBase(unsigned char, 0x0) 
#define REGPAGE1		XBase(unsigned char, 0x100)
#define REGPAGE2		XBase(unsigned char, 0x200)
#define REGPAGE3		XBase(unsigned char, 0x300)
#define REGPAGE4		XBase(unsigned char, 0x400)
#define REGPAGE5    	XBase(unsigned char, 0x500)
#define REGPAGE6	    XBase(unsigned char, 0x600)
#define REGPAGE7	    XBase(unsigned char, 0x700)
#define REGPAGE8	    XBase(unsigned char, 0x800)
#define REGPAGE9	    XBase(unsigned char, 0x900)

#define PAGE0(a)	REGPAGE0[a] 
#define PAGE1(a)	REGPAGE1[a]
#define PAGE2(a)	REGPAGE2[a]
#define PAGE3(a)	REGPAGE3[a]
#define PAGE4(a)	REGPAGE4[a]
#define PAGE5(a)    REGPAGE5[a]
#define PAGE6(a)    REGPAGE6[a]
#define PAGE7(a)    REGPAGE7[a]
#define PAGE8(a)    REGPAGE8[a]
#define PAGE9(a)    REGPAGE9[a]

//page 2
#define REG_IOMODE_CTL PAGE2(0x2A)


// SPI interface
#define SPICFG1 PAGE2(0X80)
#define SPICFG2 PAGE2(0X81)
#define SPICFG3 PAGE2(0X82)
#define SPICFG4 PAGE2(0X83)


// TOP CONTROL
#define ROMADDR_BYTE1 PAGE2(0x8e)
#define ROMADDR_BYTE2 PAGE2(0x8f)

#define SPI_WDATA PAGE2(0x90)
#define SPI_RDATA PAGE2(0x91)
#define SPI_LEN PAGE2(0x92)
#define SPICTL PAGE2(0x93)
#define CTLIRQ_CTL PAGE2(0x9c)
#define CTL_IRQ PAGE2(0x9d)
#define SPISTATUS PAGE2(0x9e)

#define CRCSPICFG0_REG PAGE2(0xa0)
#define SPICRC_ADDR_L PAGE2(0xa1)
#define SPICRC_ADDR_M PAGE2(0xa2)
#define SPICRC_ADDR_H PAGE2(0xa3)
#define SPICRC_LEN_L PAGE2(0xa4)
#define SPICRC_LEN_M PAGE2(0xa5)
#define SPICRC_LEN_H PAGE2(0xa6)

#define SPICRC_XOR PAGE2(0xa9)
#define SPICRC_AND PAGE2(0xaa)

#define READSPI_ADDRL PAGE2(0xc9)
#define READSPI_ADDRH PAGE2(0xca)
#define READSPI_ADDRE PAGE2(0xcb)
#define READSPI_READY PAGE2(0xcc)
#define READSPI_DATA PAGE2(0xcd)

#define ENCTLSPI_WR PAGE2(0xda)
#define ENMPU_WR PAGE2(0xdb)

#endif