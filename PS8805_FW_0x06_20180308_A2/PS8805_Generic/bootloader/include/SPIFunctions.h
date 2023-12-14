#include "type.h"
#include "include/registers_map.h"



typedef struct{
	//unsigned char ucVendor[10];
	//unsigned char ucPartNum[10];
	unsigned char ucVendorID;
	unsigned char ucDeviceID;
	unsigned char ucJMID;		// JEDEC manufacturer ID
	unsigned char ucJDID;		// JEDEC device ID
	unsigned char ucJCID;		// JEDEC capacity ID
	unsigned char ucMinSecSize;
	unsigned char ucSecEraseCmd;
	unsigned char ucChipEraseCmd;
	unsigned char ucEWSRCmd;
	unsigned char ucWEFlag;		// the status register value with chip protection disabled
	unsigned char ucFlagApp1;	// status register value when writing bank1
	unsigned char ucFlagApp2;	// status register value when writing bank2
	unsigned char ucDWEFlag;	// the status register value with chip protection enabled

	//unsigned char ucFastWFlag;	// whether support fast write;
	//unsigned char ucPageWFlag;	// whether support page write

//	void 		 (*DisableWriteProtection)(unsigned char ucIndex);
//	void 		 (*EnableWriteProtection)(unsigned char ucIndex);

}t_FlashType;

extern t_FlashType code g_FlashType[];

unsigned char  MPU_SPI_DetectRomType( void );

void MPU_SPI_DisableWriteProtection( unsigned char ucIndex, unsigned char ucBank );
void MPU_SPI_EnableWriteProtection( unsigned char ucIndex );

void MPU_SPI_WriteDisable( void );

//void MPU_SPITriggerWrite(void);

//void MPU_TriggerWriteInCache(void);

//void MPU_SPI_EWSRandWSR( unsigned char ucStatus );


void MPU_SPI_WriteEnable( void );

void MPU_SPI_WriteAByte( unsigned char addrH, unsigned char addrM, unsigned char addrL, unsigned char value );
void MPU_SPI_EraseSector( unsigned char ucHigh, unsigned char ucMid );
void MPU_SPI_EraseBank( unsigned char ucHigh );

unsigned char MPU_SPI_ReadStatusRegister( void );

