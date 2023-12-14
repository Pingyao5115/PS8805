#ifndef _MPU_FUNCTIONS_
#define _MPU_FUNCTIONS_
//#include "MPU_Serial.h"

void MPU_Init(void);
void MPU_DisableINT(void);
void MPU_EnableINT(void);
//void MPU_OpenTimer0INT(void);
void MPU_SetINTMask0(void);
void MPU_SetINTMask1(void);
//void MPU_ClearINTMask0(void);
//void MPU_ClearINTMask1(void);
void MPU_EnableINT0(void);
void MPU_EnableINT1(void);

void MPU_SetVerNum( unsigned char ucOEM, unsigned char ucMajor, unsigned char ucMiddle, unsigned char ucMinor );

#endif
