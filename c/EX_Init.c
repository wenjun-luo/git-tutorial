#include "H/Function_Init.H"

void EX_Init(void);
uchar INT1_flag = 0x00;
/*****************************************************
*函数名称：void EXTI_Test(void)
*函数功能：外部中断测试
*入口参数：void
*出口参数：void
*****************************************************/
void EXTI_Test(void)
{
	EX_Init();
	while(1)
	{					
	}
}
/*****************************************************
*函数名称：void EX_Init(void)
*函数功能：外部中断初始化
*入口参数：void
*出口参数：void
*****************************************************/
void EX_Init(void)
{	
	//配置中断口INT03(P13)、INT12/13(P16/17)、INT24/25(P20/21)
	P1CON &= 0X37;     //中断IO口设置为高阻输入
	P1PH  |= 0xC8;     //中断IO口设置为高阻带上拉
	P2CON &= 0XFC;     //中断IO口设置为高阻输入
	P2PH  |= 0x03;     //中断IO口设置为高阻带上拉
 
	//配置INT03上升沿中断、INT12/13下降沿中断、INT24/25双沿中断
  //下降沿设置	
	INT0F = 0X00 ;    //xxxx 0000  0关闭 1使能
	INT1F = 0X0C ;    //xxxx xxxx  0关闭 1使能
  INT2F = 0X30 ;    //0000 xxxx  0关闭 1使能
  //上升沿设置	
	INT0R = 0X08 ;    //xxxx 0000  0关闭 1使能 
	INT1R = 0X00 ;    //xxxx xxxx  0关闭 1使能
	INT2R = 0X30 ;    //0000 xxxx  0关闭 1使能	
	
	//外部中断优先级设置
	IE  |= 0x05;	    //0000 0x0x
	IE1 |= 0x08;	    //0000 x000  INT2使能
	IP  |= 0X00;
	IP1 |= 0X00;
	EA = 1;
}

/*****************************************************
*函数名称：void EX0/1/2() interrupt	0/2/10
*函数功能：外部中断函数
*入口参数：void
*出口参数：void
*****************************************************/
void EX0() interrupt	0
{
    P00 = ~P00;
}

void EX1() interrupt	2
{
    P01= ~P01;
	if(P16 == 0)
	{
		INT1_flag = 0x10; //INT12产生中断
	}
	if(P17 == 0)
	{
		INT1_flag = 0x20; //INT13产生中断
	}
}

void EX2() interrupt	10
{
    P05 = ~P05;
}
