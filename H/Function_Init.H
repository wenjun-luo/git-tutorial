#ifndef _Function_Init_H_
#define _Function_Init_H_

#include "SC92F841x_C.H"
#include "intrins.H"
#include "Multiplication_Division.H"
#define uchar unsigned char
#define uint unsigned int
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           long uint32_t;
#define IapROM  0x00	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
#define IapEPPROM  0x02	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作

typedef enum
{
  ADC_SamplesNum_SixTimes = 0x06,				//采样次数为6次
  ADC_SamplesNum_EightTimes = 0x08,			//采样次数为8次
  ADC_SamplesNum_TenTimes = 0x0A,				//采样次数为10次
	ADC_SamplesNum_TwelveTimes = 0x0C,    //采样次数为12次
	ADC_SamplesNum_FourteenTimes = 0x0E,    //采样次数为14次
	ADC_SamplesNum_SixteenTimes = 0x10,    //采样次数为16次
} ADC_SamplesNum_TypeDef;

extern void IO_Init(void);
extern void BTM_Test(void);
extern void EXTI_Test(void);
extern void Timer_Test(void);
extern void LCD_Test(void);
extern void PWM_Test(void);
extern void Uart0_Test(void);
extern void SSI_Test(void);
extern void ADC_Test(void);
extern void IAP_Test(uint Address,uchar IAPArea);
extern void Multiplier_Divider_Test();
/*****************************************
说明：选择测试IC
*****************************************/
#define SC92F8413  0
#define SC92F8412  1
#define SC92F8411  2

#define IC_MODEL  SC92F8411

#endif