#ifndef _TYPE_H_
#define _TYPE_H_


typedef union
{
	long			S32;
	unsigned long	U32;
}ALONG;


typedef union
{
	int				S16;
	unsigned int	U16;
}AINT;


typedef union
{
	char			S8;
	unsigned char 	U8;
}ABYTE;


typedef struct
{
    ABYTE           B1;
    ABYTE           B2;
}WD;


typedef union
{
	AINT			I16;
    WD              W16;
}NINT;


typedef struct
{
    NINT            NI1;
    NINT            NI2;
} DD;


typedef union
{
	ALONG			L32;
    DD              DD32;
}NLONG;

typedef union _U48
{	
	
	unsigned char byte[6];
	struct
	{
		unsigned short usDummy;
		unsigned long ulong;
	}sData;
	

} _U48;


typedef union _U24
{	
	unsigned char byte[4];
	unsigned long ulong;
} _U24;


typedef struct
{
 	unsigned char	ucCommandType;
	unsigned char	ucCommandParam1;
	unsigned char	ucCommandParam2;
}t_command;

typedef struct
{
	unsigned char ucHigh;
	unsigned char ucLow;

}t_uint16;


typedef struct{
	unsigned char ucAddr;
	unsigned char ucValue;
}t_Reg;


typedef struct
{
	unsigned char ucPage;
	unsigned char ucOffset;
	unsigned char ucBit;
	unsigned char ucMaskOffset;
	unsigned char ucMaskBit;
	unsigned char *ucInfo;
}t_INT;


typedef struct
{

	unsigned char ucPage;
	unsigned char ucOffset;
	unsigned char ucValue;

}t_INTMASK;

typedef enum 
{ 
  NO = 0, 
  YES = !NO
} StatusYesOrNo;

// command type,  no more than 0xff
enum COMMANDTYPENUM
{

	COMMAND_EMPTY	=	0,
	UART_COMMAND,
	PDTIMER_EVENT,

};
#endif