#ifndef _REGISTERS_MAP_INC_
#define _REGISTERS_MAP_INC_
//#include "spiregdef.h"
#include "include/type.h"
#include "include/registers_map.h"

#if 0
#define PAGE0(a)	0+a
#define PAGE1(a)	0x100+a
#define PAGE2(a)	0x200+a
#define PAGE3(a)	0x300+a
#define PAGE4(a)	0x400+a
#define PAGE5(a)    0x500+a
#define PAGE6(a)    0x600+a


#define REG(a,b)	volatile unsigned char xdata a _at_ b
#define REGDEF(a,b) volatile a##_STRUCT xdata a _at_ b


// This definition will generate dozens of warning 'memory space overlap' for there are
// already individual register definitions in page1.
// this definition is to save time when doing DPCD addressing mapping during DP SW training

//volatile unsigned char xdata g_vucxReg1[0xff] _at_ 0x100;
//volatile unsigned char xdata g_vucxReg5[0xff] _at_ 0x500;


// TOP CONTROL
REG(ROMADDR_BYTE1,PAGE2(0x8e));
REG(ROMADDR_BYTE2,PAGE2(0x8f));

REG(GPIO_OUT0,PAGE2(0xa6));
REG(GPIO_OUT1,PAGE2(0xa7));
REG(GPIO_OEB0,PAGE2(0xa8));
REG(GPIO_OEB1,PAGE2(0xa9));

// SPI interface
REG(SPICFG1,PAGE2(0X80));
REG(SPICFG2,PAGE2(0X81));
REG(SPICFG3,PAGE2(0X82));
REG(SPICFG4,PAGE2(0X83));

REG(SPI_WDATA,PAGE2(0x90));
REG(SPI_RDATA,PAGE2(0x91));
REG(SPI_LEN,PAGE2(0x92));
REG(SPICTL,PAGE2(0x93));
REG(SPISTATUS,PAGE2(0x9e));

REG(READSPI_ADDRL,PAGE2(0xc9));
REG(READSPI_ADDRH,PAGE2(0xca));
REG(READSPI_ADDRE,PAGE2(0xcb));
REG(READSPI_READY,PAGE2(0xcc));
REG(READSPI_DATA,PAGE2(0xcd));

#endif



#endif