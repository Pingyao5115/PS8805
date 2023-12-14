/*	version number					 				*/
/*	should be set every time check in				*/
/*													*/
/*													*/
#include "global.h"

typedef struct
{
	unsigned char ucHeader[3];	//0x55, 0xaa, 0x01
	unsigned char ucLength;		//length of product ID structure 
	unsigned char ucProductID[20];	// eg 'MON27a'
	unsigned char ucVendorID[3];//OEM key
	unsigned char ucProjectID;//Project ID
	unsigned char ucVerNum;//version number
//	unsigned char ucChecksum;	//checksum making sum of this structure to be 0
} t_PRODUCT_ID_STRUCT;

t_PRODUCT_ID_STRUCT code g_sProductID = 
{
	{ 0x55, 0xaa, 0x01 },
	0x1E,
	{ "Google" },
	{ "INT" },
	PROJECT_ID,
	OEM_PARADE_VERSION_NUM,
//	0x96,

};

unsigned char code g_uccVersionNumMajor  = 1;
unsigned char code g_uccVersionNumMiddle = 0;
unsigned char code g_uccVersionNumMinor  = 0;

unsigned char code g_uccVersionDescription[250]="PS8805FW Google 0x06 for A2, 20180308";
unsigned char code g_uccBootloaderString[64] = "No Bootloader";
