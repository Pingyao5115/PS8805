#include <stdio.h>
#include <stdlib.h>
#include <intrins.h>
#include "include/type.h"
#include <include/myDP8051XP.H>
#include "include/registers_map.h"
#include "include/SPIFunctions.h"

#define BANK0_BACKUP_DATA_ADDR  		0x3000 // at 12K
#define BANK0_MID_DATA_OFFSET 	 		0x30;//at 12K //0x20; // At 8K 0x20 00


#define BANK0 0
#define BOOTLOADER_BANK 0x03 // default BL bank
#define NO_LONG

// bit to check if we are busy in Aux Update operation.
bit b_CheckBusyStatus = 0;

//
// Add CAPS for future usage
//
//----------------------------------------------------------//

#define		CHIPVERSION					0x00		

#define		CHIP_VERSION_NUM				0x10

#define		PASS						0
#define		FAIL						0xff

#define		BOOTLOADERSIZE			0x2000			// 8K Bytes; should be integer mutiple of sector size.
#define		BOOTLOADERSIZEH			0x20
#define		BOOTLOADERSIZEL			0x00

// application in bank 2 start address
#define		APP2STARTADDRESS			0x20000L

// application in bank 1 start address
#define		APP1STARTADDRESS			0x10000L

// default application in bank 3 start address
#define		DEFAULTSTARTADDRESS			(0x30000L + BOOTLOADERSIZE)

// system startup address
#define		BOOTLDSTARTADDRESS			0x30000L
#define		BOOTLDRADDRH				0X03
#define		BOOTLDRADDRM				0X00
#define		BOOTLDRADDRL				0X00

// bootloader data location

#define		BOOTLDDATAADDRESS		0x2000L  // at 8K 4-9
#define		BOOTLDDATAADDRH			0x00
#define		BOOTLDDATAADDRM			0x20
#define		BOOTLDDATAADDRL			0x00


#define		APPLICATIONSIZE				0x10000L

#define		DEFAULTAPPSIZE				0xE000L			// 0xf000L

#define		APPLICATIONSIZE_2			0xFFFD 			// 0x10000L-2

#define		DEFAULTAPPSIZE_2			0xDFFD			// 0xE000L-2 //0xf000L

#define		DEFAULT_BANK				0x03

unsigned char idata g_uciFlashType;

extern unsigned char code g_uccVersionNumMajor;
extern unsigned char code g_uccVersionNumMiddle;
extern unsigned char code g_uccVersionNumMinor;

void 		 (*g_DisableWriteProtection)(unsigned char ucIndex, unsigned char ucBank );
void 		 (*g_EnableWriteProtection)(unsigned char ucIndex);

volatile unsigned char xdata g_vucxVersion _at_ 0x505;

volatile unsigned char xdata g_vucxBootldVerH 	_at_ 0x506;
volatile unsigned char xdata g_vucxBootldVerL 	_at_ 0x507;
//volatile unsigned char xdata g_vucxChipVerL  	_at_ 0x508;
//volatile unsigned char xdata g_vucxChipVerH  	_at_ 0x509;
volatile unsigned char xdata g_vucxBootldStatus _at_ 0x50a;
volatile unsigned char xdata g_vucxBootImgInfo  _at_ 0x50b;


void SaveBootData( unsigned char ucBankNum );

unsigned char CheckApplication( unsigned char ucBankNum, unsigned short usSize );

void SetReadSPIAddr( unsigned char ucAddrE, unsigned char ucAddrH, unsigned char ucAddrL );


#define MPU_DISABLEINT	EA = 0


void SwitchToBootloader( void )
{
	SBANK = 0x03;

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	((void(*)(void))0x0000)( );

}


void SwitchToApp( unsigned char ucBankNum )
{

	SBANK = ucBankNum;

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	_nop_();
	_nop_();
	_nop_();
	_nop_();

	((void(*)(void))(void far *)0x2000)( ); 		// 8K


}
/*
void ProtectROM( void )
{
	ENCTLSPI_WR		   = 0x00;	// disable writing to flash by writing to page7 through I2C
	ENMPU_WR		   = 0x00;	// disable writing to flash by writing to page7 through MPU
	ROMADDR_BYTE1	   = 0xf0;	// protect upper space in case 
								// there is some writing action to page 7 
								// when flash write protection is disabled
	ROMADDR_BYTE2      = 0x00;

	REG_IOMODE_CTL	&= 0xEF;				// enable to set WP 
	g_EnableWriteProtection( g_uciFlashType );
	REG_IOMODE_CTL	|= 0x10;				// disable to set WP 
}
*/
unsigned char CheckBootData( void )
{
	unsigned char data ucDummy = 0;
	unsigned char data ucCheckSum = 0;
	unsigned char data ucBootData[4];
	unsigned char data ucCtr;

	SetReadSPIAddr( BOOTLDDATAADDRH, BOOTLDDATAADDRM, BOOTLDDATAADDRL );

	for ( ucCtr = 0; ucCtr < 4; ucCtr++ )
	{
		while(  (READSPI_READY & 0x01) != 0x01 );
	
		ucBootData[ucCtr] = READSPI_DATA;
		ucCheckSum += ucBootData[ucCtr];
	}
	
	if (   ( ucBootData[0] == 0x55 )
	    && ( ucBootData[1] == 0xaa ) 
		&& ( ( ucBootData[2] == 0x01 ) || ( ucBootData[2] == 0x02 ) ) 
		&& ( ucCheckSum == 0x00 )
	   )
	{
		return PASS;
	}
	else
	{
		return FAIL;
	}
}

void SaveBootData( unsigned char ucBankNum )
{
	unsigned char data ucCtr;
	unsigned char data ucData[4];
	unsigned char data ucDstAddrL = BOOTLDDATAADDRL;
	
	REG_IOMODE_CTL &= 0xEF;//unprotect
	g_DisableWriteProtection( g_uciFlashType, 1 );	
	g_DisableWriteProtection( g_uciFlashType, 1 );		
	REG_IOMODE_CTL |= 0x10;//protect
	
	MPU_SPI_WriteEnable();

	MPU_SPI_EraseSector( 0x00, BOOTLDDATAADDRM ); 
	
	ucData[0] = 0x55;	   			//signature
	ucData[1] = 0xaa;				//signature
	ucData[2] = ucBankNum;			//active bank
	ucData[3] = 0x01 - ucBankNum;	//checksum
	
	for ( ucCtr = 0; ucCtr < 4; ucCtr++ )
	{
		MPU_SPI_WriteEnable( );	
		MPU_SPI_WriteAByte( BOOTLDDATAADDRH, BOOTLDDATAADDRM, ucDstAddrL++, ucData[ucCtr] );
	}

	REG_IOMODE_CTL &= 0xEF;//unprotect
	g_EnableWriteProtection( g_uciFlashType );
	REG_IOMODE_CTL |= 0x10;//protect
}

void SetReadSPIAddr(unsigned char ucAddrE, unsigned char ucAddrH, unsigned char ucAddrL)
{
	READSPI_ADDRE = 0x80;		// reset
	READSPI_ADDRE = ucAddrE;
	READSPI_ADDRH = ucAddrH;
	READSPI_ADDRL = ucAddrL;
	
	while(  (READSPI_READY & 0x01) != 0x01 );
}

//#define BATCHSIZE			15			//The maximum is 15 because the first byte return from FASTREAD is dummy byte 
//#define FASTREAD			0x0B

unsigned char CheckApplication( unsigned char ucBankNum, unsigned short usSize )
{
//	unsigned char ucCalAddCS = 0;
//	unsigned char ucCalXorCS = 0;
//	unsigned char ucThisBatchSize;
//	unsigned char ucNextBatchSize;
//	unsigned char ucTemp;
//	unsigned char ucSPILen;
//	unsigned short u_Addr = 0;
//	unsigned short usByteLeft;
//	unsigned char ucByteInBuffer = 0;
//	unsigned char ucByteToCalChecksum = 0;
//	unsigned char ucBuffer[BATCHSIZE + 1];
	unsigned char ucBuffer[2];

	SPICRC_ADDR_H = ucBankNum;
	SPICRC_ADDR_M = BOOTLOADERSIZEH;
	SPICRC_ADDR_L = BOOTLOADERSIZEL;

	SPICRC_LEN_H = 0x00;
	SPICRC_LEN_M = usSize >> 8;
	SPICRC_LEN_L = usSize & 0xFF;

	CRCSPICFG0_REG |= 0x01;

	SetReadSPIAddr( ucBankNum, 0xFF, 0xFE );

	while(  (READSPI_READY & 0x01) != 0x01 );
	ucBuffer[0] = READSPI_DATA;
	while(  (READSPI_READY & 0x01) != 0x01 );
	ucBuffer[1] = READSPI_DATA;
/*
	bit bCS = 0;

	if ( ucBankNum == DEFAULT_BANK )
	{
		MSBOFSHORT( u_Addr ) = BOOTLOADERSIZEH;
	}

	usByteLeft = usSize;
	ucThisBatchSize = ( usByteLeft > BATCHSIZE ) ? BATCHSIZE : (unsigned char) usByteLeft;
	ucSPILen = ( ( ( ucThisBatchSize  ) * 16 ) + 3 ); 

	while ( ucThisBatchSize )
	{
		{
			SPI_WDATA = FASTREAD;
			SPI_WDATA = ucBankNum;

			SPI_WDATA = MSBOFSHORT( u_Addr );
			SPI_WDATA = LSBOFSHORT( u_Addr );


			SPI_LEN = ucSPILen;
			SPICTL	  = 0X01; 	
			usByteLeft -= ucThisBatchSize;

			u_Addr += ucThisBatchSize;

			ucSPILen = ( ( ( ucThisBatchSize  ) * 16 ) + 3 ); 
			ucNextBatchSize = ( usByteLeft > BATCHSIZE ) ? BATCHSIZE : (unsigned char) usByteLeft;
			if ( ( ucNextBatchSize == 0 ) && ( bCS == 0 ) )
			{
				bCS = 1;
				ucNextBatchSize = 2;
				usByteLeft = 2;
			} 
		}

		while ( ucByteInBuffer-- )
		{
			ucTemp = ucBuffer[ucByteInBuffer];
			ucCalAddCS += (unsigned char) ucTemp;
			ucCalXorCS ^= ucTemp;	
		}


		{
			if ( ( bCS ) && ( ucNextBatchSize == 0 ) )
			{
				ucThisBatchSize = 2;
			}
			ucByteInBuffer = ucThisBatchSize;

			while ( SPICTL & 0x01 );
			ucTemp = SPI_RDATA;

			while ( ucThisBatchSize-- )
			{
				ucBuffer[ucThisBatchSize] = SPI_RDATA;
			}
		}

		ucThisBatchSize = ucNextBatchSize;
	}
*/
	if ( ( ucBuffer[1] == SPICRC_XOR ) && ( ucBuffer[0] == SPICRC_AND ) )
	{
		return PASS;
	}
	else
	{
		return FAIL;
	}
}

main( )
{
//	unsigned char data ucRomType = 0xff;
	unsigned char data ucActive = 0xff;
	unsigned char data ucNonActive = 0x02;
	unsigned char data ucRet = 0;
//	unsigned char data ucTag = 0;
//	unsigned char data ucDelay;

//	bit bBootTag = 0;		// 0: cold reset;   1: hot reset

	g_vucxBootldStatus = 0x10;
	g_vucxBootImgInfo  = 0x00;

	// protect ROM
	ENCTLSPI_WR		   = 0x00;	// disable writing to flash by writing to page7 through I2C
	ENMPU_WR		   = 0x00;	// disable writing to flash by writing to page7 through MPU
	ROMADDR_BYTE1	   = 0xf0;	// protect upper rom in case 
	ROMADDR_BYTE2	   = 0x00;	// there is some writing action to page 7 
								// when flash write protection is disabled
	MPU_DISABLEINT;

	// P5.0x06/0x07 = Use two byte to represent BL.
 	g_vucxBootldVerH = ( g_uccVersionNumMajor << 4 ) | ( g_uccVersionNumMiddle  & 0x0F );
 	g_vucxBootldVerL =  g_uccVersionNumMinor;//( g_uccVersionNumMinor  & 0x0F );
	
//	g_vucxChipVerH = 0x30;
//	g_vucxChipVerL = 0x00;

	g_uciFlashType = MPU_SPI_DetectRomType( );
	g_DisableWriteProtection = MPU_SPI_DisableWriteProtection;
	g_EnableWriteProtection = MPU_SPI_EnableWriteProtection;

	ucRet = MPU_SPI_ReadStatusRegister( );
	if( 
		( ( ucRet & g_FlashType[g_uciFlashType].ucDWEFlag ) != g_FlashType[g_uciFlashType].ucDWEFlag )
	 || ( ( ucRet & g_FlashType[g_uciFlashType].ucDWEFlag ) != 0x9c )
	  )
	{
		REG_IOMODE_CTL &= 0xEF;//unprotect
		g_EnableWriteProtection( g_uciFlashType );		// set status register of flash 0x8c and WP low
		REG_IOMODE_CTL |= 0x10;//protect
	}

	if ( CheckBootData( ) == PASS )
	{
		ucActive = 2;
		// get active image tag
		SetReadSPIAddr( BOOTLDDATAADDRH, BOOTLDDATAADDRM, (BOOTLDDATAADDRL + 0x02) );

		ucActive = READSPI_DATA;
		
		g_vucxBootImgInfo =  ucActive << 4;
		
		if ( CheckApplication( ucActive, APPLICATIONSIZE_2 ) == PASS )	// check current active image
		{
			g_vucxBootImgInfo = g_vucxBootImgInfo | ucActive;

		}
		else	// active img err
		{

			ucActive = ( ucActive == 2 ) ? 1 : 2;	

			if ( CheckApplication( ucActive, APPLICATIONSIZE_2 ) == PASS ) // check nonactive image
			{
				g_vucxBootImgInfo = g_vucxBootImgInfo | ucActive;
			}
			else
			{
				if ( CheckApplication( DEFAULT_BANK, DEFAULTAPPSIZE_2 ) == PASS )
				{
					ucActive = 3;
					g_vucxBootImgInfo = g_vucxBootImgInfo | ucActive;
				}
				else
				{
					ucActive = 1; 		// set active to 1 to tell update function to update bank 2
//					ucTag |= 0x02;		// all 3 images are not available, wait for update cmd from source
				}
			}
		}
	}
	else
	{
		ucActive = 3;
		if ( CheckApplication( 2, APPLICATIONSIZE_2 ) == PASS ) // bank 2 is high priority
		{
			SaveBootData( 2 );
			ucActive = 2;
			g_vucxBootImgInfo = 0x22;
		}
		else if ( CheckApplication( 1, APPLICATIONSIZE_2 ) == PASS )
		{
			SaveBootData( 1 );
			ucActive = 1;
			g_vucxBootImgInfo = 0x11;
		}
		else if ( CheckApplication( DEFAULT_BANK, DEFAULTAPPSIZE_2 ) == PASS )
		{
			SaveBootData( 2 );
			ucActive = 3;
			g_vucxBootImgInfo = 0x23;
		}
		else
		{
//			ucTag |= 0x02;		// all 3 images are not available, wait for update cmd from source
			ucActive = 1; 		// set active to 1 to tell update function to update bank 2
		}
	}	

	SwitchToApp( ucActive );
}

