#ifndef _TYPE_H_
#define _TYPE_H_

typedef union
{
	long			S32;
	unsigned long	U32;
}ALONG;

typedef struct
{
	unsigned short usReg;
	unsigned char ucValue;
}	REGTAB_STRUCT, *P_REGTAB_STRUCT;

//Get a byte from long value
#define LSBOFLONG(l)	(*(((unsigned char *)&((unsigned long)(l))) + 3 ))
#define LSBHOFLONG(l)	(*(((unsigned char *)&((unsigned long)(l))) + 2 ))
#define MSBLOFLONG(l)	(*(((unsigned char *)&((unsigned long)(l))) + 1 ))
#define MSBOFLONG(l)	(*(((unsigned char *)&((unsigned long)(l)))))
//Get a word from long value
#define LSWOFLONG(l)	(*(((unsigned short *)&((unsigned long)(l))) + 1 ))
#define MSWOFLONG(l)	(*(((unsigned short *)&((unsigned long)(l)))))
//Get a byte from short value
#define LSBOFSHORT(s)	(*(((unsigned char *)&((unsigned short)(s))) + 1 ))
#define MSBOFSHORT(s)	(*(((unsigned char *)&((unsigned short)(s)))))

#endif