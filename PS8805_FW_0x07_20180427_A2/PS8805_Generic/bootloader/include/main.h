#define PAGE0(a)	0+a
#define PAGE1(a)	0x100+a
#define PAGE2(a)	0x200+a
#define PAGE3(a)	0x300+a
#define PAGE4(a)	0x400+a
#define PAGE5(a)    0x500+a
#define PAGE6(a)    0x600+a


#define REG(a,b)	volatile unsigned char xdata a _at_ b

#define		NEW_OPEN_LIVE_VIDEO_SEQUENCE

#define		OUI_0_APPLE				0x00
#define		OUI_1_APPLE				0x10
#define		OUI_2_APPLE				0xfa

#define		PASS 	1
#define		FAIL	0

#define		BLOCK0_3				0x8C
#define		BLOCK2_3				0x88
#define		BLOCK3					0x84

#define		ACTIVEIMAGEBLOCK		0x0L
#define		BOOTLOADERSIZE			0x2000L			// 8K Bytes; should be integer mutiple of sector size.
#define		APPSTARTADDRESS			BOOTLOADERSIZE

#define		VERSIONNUMBERBLOCK1		0x15000
#define		VERSIONNUMBERBLOCK2		0x25000

#define		BOOTLDRDATADDRESS		0x00000L
#define		APPBLOCK1ADDRESS		0x11000L
#define		APPBLOCK2ADDRESS		0x21000L
#define		DEFAULTADDRESS			0x31000L

unsigned char idata g_uciFlashType;
unsigned char idata g_uciActiveMark = 0;


extern unsigned char code g_uccVersionNumMinor;

void 		 (*g_DisableWriteProtection)(unsigned char ucIndex, unsigned char ucBlock);
void 		 (*g_EnableWriteProtection)(unsigned char ucIndex);

#if 0
PP_PANELPARAM_STRUCT code *	 spPanelInfo;

unsigned char code uccNoDisplay[270] = 
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x1c, 0x86, 0xa0, 0x08, 0x8a, 0x20, 0x09, 0xa2, 0x20, 0x0a, 0xc2, 0x70, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //N
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x84, 0x20, 0x10, 0x02, 0x21, 0x10, 0x02, 0x21, 0x10, 0x84, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //O
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //SPACE
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x84, 0x40, 0x10, 0x04, 0x41, 0x10, 0x04, 0x41, 0x10, 0x84, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //D
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x10, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //I
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0b, 0xc4, 0x40, 0x08, 0x04, 0x80, 0x07, 0x80, 0x40, 0x08, 0x8c, 0x40, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //S
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x08, 0x81, 0x10, 0x08, 0x81, 0x10, 0xf8, 0x80, 0x00, 0x08, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //P
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x08, 0x80, 0x00, 0x08, 0x80, 0x00, 0x08, 0x81, 0x10, 0x08, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //L
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x30, 0x80, 0x04, 0x48, 0x80, 0x04, 0xfc, 0x40, 0x08, 0x02, 0x71, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	 //A
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x1c, 0x82, 0x40, 0x04, 0x28, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	 //Y
};

unsigned char code uccDisplayRAM[32] = 
{
	0x80, 0x42, 0x81, 0x23, 0x82, 0x32, 0x83, 0x44, 0x84, 0x55, 0x85, 0x6a, 0x86, 0x7d, 0x87, 0x8e, 
	0x88, 0x9f, 0x89, 0x22, 0x8a, 0x65, 0x8b, 0x33, 0x8c, 0x47, 0x8d, 0x4d, 0x8e, 0x52, 0x8f, 0xb1,
};

unsigned char code uccLUTRAM[32] = 
{
	0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe, 
	0x00, 0x11, 0x22, 0x33, 0x09, 0x93, 0x30, 0x00, 0x00, 0x30, 0x93, 0x09, 0xFF, 0xFF, 0xFF, 0xFF,
};
#endif
