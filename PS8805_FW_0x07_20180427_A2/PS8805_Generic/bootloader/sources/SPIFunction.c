#include "include/SPIFunctions.h"

t_FlashType code g_FlashType[] =
{	
   	{/*"EON", 	 "EN25F20",*/   0x1C, 0x11, 0x1C, 0x31, 0x12, 0x04, 0x20, 0xC7, 0x06, 0x00, 0x08, 0x04, 0x9C, /*0x01, 0x01,*/  }, 
   	{/*"Winbond", "W25Q20CL",*/ 0xEF, 0x11, 0xEF, 0x40, 0x12, 0x04, 0x20, 0xC7, 0x06, 0x00, 0x08, 0x04, 0x8C, /*0x01, 0x01,*/  }, 
   	{/*"Winbond", "W25X20",*/   0xEF, 0x11, 0xEF, 0x30, 0x12, 0x04, 0x20, 0xC7, 0x06, 0x00, 0x08, 0x04, 0x8C, /*0x01, 0x01,*/  }, 
   	{/*"UNKNOW",  "UNKNOW",*/   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, /*0xff, 0xff*/  }
};


// bit to check if we are busy in Aux Update operation.
extern bit b_CheckBusyStatus;

unsigned char  MPU_SPI_DetectRomType( void )
{
	unsigned char data uciIndex = 0;
	
	SPI_WDATA 	=   0x9f;	 		// RDID command
	SPI_LEN		= 	0x20;			// read 3 bytes
	SPICTL		= 	0x01;			// trigger read

	while((SPICTL & 0x01 ));	   // wait until write is done

//	while((SPISTATUS & 0x03 ));	   // wait until write is done
	
	while( g_FlashType[uciIndex].ucVendorID != 0xff )
	{
		SPICTL	= 0x02;
		while((SPICTL & 0x02 ));	   // wait until FIFO pointer is cleared

		if( SPI_RDATA == g_FlashType[uciIndex].ucJMID )
		{
			if( SPI_RDATA == g_FlashType[uciIndex].ucJDID )
			{
				if( SPI_RDATA == g_FlashType[uciIndex].ucJCID )
				{
					return uciIndex;
				}
			}
		}
		uciIndex++;
	}

	if( g_FlashType[uciIndex].ucVendorID == 0xff )	
	{
		uciIndex   = 0;

		SPI_WDATA 	=   0x90;	 		// RDID command
		SPI_WDATA 	=   0x00;	 		
		SPI_WDATA 	=   0x00;	 		
		SPI_WDATA 	=   0x00;	 		
		SPI_LEN		= 	0x43;			// write 4 bytes read 5 bytes
		SPICTL		= 	0x01;			// trigger read

		while((SPICTL & 0x01 ));	   // wait until write is done

		while( g_FlashType[uciIndex].ucVendorID != 0xff )
		{
			SPICTL	= 0x02;
			while((SPICTL & 0x01 ));	   // wait until FIFO pointer is cleared

			if( SPI_RDATA == g_FlashType[uciIndex].ucVendorID )
			{
				if( SPI_RDATA == g_FlashType[uciIndex].ucDeviceID )
				{
					return uciIndex;
				}
			}
			uciIndex++;
		}
	}
	
	return uciIndex;
}


/*****************************************************************************/
/* Function Name:	MPU_TriggerWriteInCache
/*  Description:	Trigger SPI write command, polling until the SPI ROM ready
/*                  Please notices, the code itself must be load into the cache 
/*					line before execution.
/* Input parameter:	None
/* Output paramter:	None
/*****************************************************************************/
#if 0
void MPU_SPITriggerWrite(void)
{
	SPICTL = 0x05;// trigger Write

	//Wait SPI interface ready
	while(SPICTL&0x01);

	//Polling the SPI ROM status register to see
	//if it is not busy.
Polling:
	//SPICTL		= 0x02;	//Clear Command queue
	SPI_WDATA	= 0x05;	// RDSR
	SPI_LEN		= 0x00;
	SPICTL		= 0x01;	// read
	
	//Wait SPI interface ready	
	while(SPICTL&0x01);
	
	//If SPI ROM is busy	
	if((SPI_RDATA&0x01) == 0x01)
		goto Polling;
}
#endif

//
//#define DELAYINITTIMESHORT	0xffdf0000L				// about 1 second
//#define DELAYINITTIMELONG	0xffb00000L				// about 2 second
// (0xb00000 - 0xdf0000)/4 = 0xbc000 : about 0.25 or 250ms duration
//  it will be 0x100000 - 0xbc000 = 0x44000
//#define BUSYWAITTIME_250MS	0xfff44000
//#define BUSYWAITTIME	0xfffffb00//0xffffb000//0xfff4b000
#define BUSYWAITTIME	0xfb00//0xffffb000//0xfff4b000

// Dumpy function to mark C lib end.
void C_LIB_End(void)
{
}
/*****************************************************************************/
/* Function Name:	MPU_TriggerWriteInCache
/*  Description:	To assume that the code will be resident in cache before 
/*                  execution, we need first load the code into the cache line 
/*					manually then run it.
/* Input parameter:	None
/* Output paramter:	None
/*****************************************************************************/
void MPU_TriggerWriteInCache(void)
{
	unsigned char data uciPageCount = 0;
	unsigned char code* data cptr;
	unsigned int data uiiCounter;
	unsigned int data uiiCodeLength;
	unsigned char bDone=0;
	unsigned int data uiiBusyCounter=BUSYWAITTIME; 

	uiiCodeLength = (((unsigned int ) C_LIB_End - (unsigned int ) MPU_TriggerWriteInCache)+0x1F)&0xFFF0;
		
    cptr = (unsigned char code*)MPU_TriggerWriteInCache; // load code into cache

	for( uiiCounter = 0; uiiCounter < uiiCodeLength; uiiCounter++ )
	{
	    uciPageCount = *( cptr + uiiCounter );
	}
	//4-14:cptr = (unsigned char code*)0;

//	MPU_SPITriggerWrite();			  
	SPICTL = 0x05;// trigger Write

	//Wait SPI interface ready
	//while(SPICTL&0x01);
	while(SPICTL&0x01)
	{
		if(b_CheckBusyStatus)
		{
			uiiBusyCounter++;
			if(!uiiBusyCounter)
			{
				uiiBusyCounter = BUSYWAITTIME;
			}
		}
	}
	//Polling the SPI ROM status register to see
	//if it is not busy.

	//uliBusyCounter=BUSYWAITTIME_250MS;
	do
	{
		SPI_WDATA	= 0x05;	// RDSR
		SPI_LEN		= 0x00;
		SPICTL		= 0x01;	// read
	
		//Wait SPI interface ready	
		//while(SPICTL&0x01);
		while(SPICTL&0x01)
		{
			if(b_CheckBusyStatus)
			{
				uiiBusyCounter++;
				if(!uiiBusyCounter)
				{
					uiiBusyCounter = BUSYWAITTIME;
				}
			}
		}
		//g_vucxReg5[0x14]= g_vucxReg5[0x14]+1;	
		//If SPI ROM is busy
		if( (SPI_RDATA & 0x01) == 0x01 )
		{
	 		if(b_CheckBusyStatus)
			{
				uiiBusyCounter++;
				if(!uiiBusyCounter)
				{
					uiiBusyCounter = BUSYWAITTIME;
				}
			}
		}
		 else
		 {
		 	bDone=1;
		 }


	//}while( (SPI_RDATA & 0x01) == 0x01 );
	}while( !bDone );

	//4-14:while (*cptr!=0x02);


}

void MPU_SPI_EnableWriteProtection( unsigned char ucIndex )
{

	//unsigned char idata uciPageCount = 0;
	
    //unsigned char code* idata cptr;
    //unsigned int idata uiiCounter;

	//cptr = (unsigned char code*)MPU_SPI_WriteDisable;						 // load code into cache
    //for( uiiCounter = 0; uiiCounter < 0x80; uiiCounter++ )
    //{
        //uciPageCount = *( cptr + uiiCounter );
    //}

//	SPICFG3 	= 0x08;		
	SPICTL		= 0x06;				// clear the command queue

	SPI_WDATA   = g_FlashType[ucIndex].ucEWSRCmd;	//0x06;
	SPI_LEN		= 0x00;				// len
	MPU_TriggerWriteInCache();
	//SPICTL		= 0x05;			// write
	
	SPICTL		= 0x06;			   // clear the command queue
	SPI_WDATA	= 0x01;				// WRSR
//	SPI_WDATA	= 0x0c;				// value
	SPI_WDATA	= g_FlashType[ucIndex].ucDWEFlag;//0x8c;				// value	// bpl, bp0, bp1 = 1 to protect flash rom
	SPI_LEN		= 0x01;				// len
	MPU_TriggerWriteInCache();
	//SPICTL		= 0x05;			// write
	
//	SPICFG3 	= 0x00;		

}

/****************************************************************************************/
/*	Function Name:	 MPU_SPI_EWSRandWSR
/*  Description:	 write EWSR and WSR to SPI control registers
/*					 According to flash's datasheet, WSR should be immediately after EWSR.
/*					 If there is any read action immediately after EWSR, the data read out
/*					 are wrong. As the instruction bytes number between two SPICTL is larger
/*					 than 16( a cache line), there must be a read action after EWSR. So we call
/*					 this function twice to make sure that the function code is in cache. 
/*					 The first call doesn't trigger the write.
/* Input parameter:		i		:	0:indicate the first run
/*									1:indicate the second run, actural write
/* Output paramter:		none
/* Modified by Priscilla 2008/02/26 load code into cache before execute, so need to call twice
/****************************************************************************************/
void MPU_SPI_DisableWriteProtection( unsigned char ucIndex, unsigned char ucBank )
{
	unsigned char data uciStatusReg;

//	SPICFG3 = 0x08;
	if(ucBank==3)
		uciStatusReg = g_FlashType[ucIndex].ucWEFlag;// 0x0 unprotect all
	else
		uciStatusReg = ( ucBank == 2 ) ? g_FlashType[ucIndex].ucFlagApp2 : g_FlashType[ucIndex].ucFlagApp1;

	SPICTL		= 0x06;				// clear the command queue
	SPI_WDATA	= g_FlashType[ucIndex].ucEWSRCmd;	// 0x06;				// EWSR
	SPI_LEN		= 0x00;				// len
	MPU_TriggerWriteInCache();

	SPICTL		= 0x06;			   // clear the command queue
	SPI_WDATA	= 0x01;				// WRSR
	SPI_WDATA	= uciStatusReg; // g_FlashType[ucIndex].ucWEFlag;				// value
	SPI_LEN		= 0x01;				// len

	MPU_TriggerWriteInCache();
}

/*****************************************************************************/
/* Function Name:		MPU_SPI_ReadAByteFromRom
/* Description:			read a byte from flash
/* Input parameter:		addr		:	the address to be read
/*						
/* Output parameter:	ucDataPtr	:	the place to save the read data
/* revision history:	
/*
/*
/*****************************************************************************/
/*void MPU_SPI_ReadAByteFromRom( ALONG addr, unsigned char * ucDataPtr )
{
	 	SPI_WDATA 	=   0x0B;	 		// read data command
		SPI_WDATA	=	*(((unsigned char*)(&addr))+1);		// address hi
		SPI_WDATA	=   *(((unsigned char*)(&addr))+2);		// address middle
		SPI_WDATA	=	*(((unsigned char*)(&addr))+3);		// address low
		SPI_WDATA	=	0x00;			// dummy
		SPI_LEN		= 	0x04;			// write 4 byte
		SPICTL		= 	0x01;			// trigger read

	 	while(SPICTL&0x01);				// wait until data is available

		*ucDataPtr = SPI_RDATA;

}
*/
void MPU_SPI_WriteEnable( void )
{
	/* 4-14-09
	    	unsigned char code* idata cptr;
		unsigned char idata ucdummy,ucdummy1;
		cptr = (unsigned char code *) MPU_SPI_WriteEnable;
		for (ucdummy=0;ucdummy<0x4e;ucdummy++)
			ucdummy1=*cptr++;
	*/		
		SPI_WDATA	= 0x06;				// WE
		SPI_LEN		= 0x00;				// len
		
		SPICTL		= 0x05;				// write

		while(SPICTL&0x01);
}

void MPU_SPI_EraseSector( unsigned char ucHigh, unsigned char ucMid )
{
	//unsigned char idata uciPageCount = 0;
	
    //unsigned char code* idata cptr;
    //unsigned int idata uiiCounter;

	//cptr = (unsigned char code*)MPU_SPI_EraseSector;						 // load code into cache
    //for( uiiCounter = 0; uiiCounter < 0x80; uiiCounter++ )
    //{
        //uciPageCount = *( cptr + uiiCounter );
    //}

	//4-6
	//SPICTL =0x02;
	//while(SPICTL &0x02);

	//-4-6

	SPI_WDATA	= 0x20;				// erase sector
	SPI_WDATA	=	ucHigh;	// address hi
	SPI_WDATA	=   ucMid;	// address middle
	SPI_WDATA	= 0;

	SPI_LEN		= 0x03;				// len
	//SPICTL		= 0x05;				// write
	MPU_TriggerWriteInCache();

//	while((SPISTATUS & 0x0c ));		// wait until erase section is done

}
/*
void MPU_SPI_EraseBank( unsigned char ucHigh )
{
//	MPU_SPI_WriteEnable( );

	SPI_WDATA	= 0xD8;				// erase bank
	SPI_WDATA	=	ucHigh;	// address hi
	SPI_WDATA	=   0;	// address middle
	SPI_WDATA	=	0;	// address low
	SPI_LEN		= 0x03;				// len
	//SPICTL		= 0x05;				// write
	MPU_TriggerWriteInCache();

//	while((SPISTATUS & 0x0c ));		// wait until erase section is done
}
*/
void MPU_SPI_WriteAByte( unsigned char addrH, unsigned char addrM, unsigned char addrL, unsigned char value )
{
	SPI_WDATA 	=   0x02;	 		// write data command
	SPI_WDATA	=	addrH;	// address hi
	SPI_WDATA	=   addrM;	// address middle
	SPI_WDATA	=	addrL;	// address low
	SPI_WDATA	=	value;			// data
	SPI_LEN		= 	0x04;			// write 4 byte
	//SPICTL		= 	0x05;			// trigger 
	MPU_TriggerWriteInCache();
}

unsigned char MPU_SPI_ReadStatusRegister( void )
{
	SPI_WDATA	= 0x05;				// RDSR
	SPI_LEN		= 0x00;				// Write 1 byte and read 1 byte
	SPICTL		= 0x01;				// read
	
	while(SPICTL&0x01);
	
	return SPI_RDATA;
}
