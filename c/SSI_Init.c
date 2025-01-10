#include "H/Function_Init.H"
#include "H/RingBuffer_C51.H"
#include "H/Data_Type.h"
#include "project.h"

bit Uart1SendFlag = 0;            //Uart发送中断标志位
//bit Uart1ReceiveFlag = 0; 		  //Uart接收中断标志位
TagRingBuffer g_comunicate_rb;    //定义队列
static char g_rb_buffer[9]={0};   
//发送字符串
void UART_Sendstring(u8 *str)
{   
	u8 i;
	for(i = 0; i < 7 ; i++)
	{
		SSDAT  = str[i];
		while(!Uart1SendFlag);
		Uart1SendFlag = 0;
	}
}

/*****************************************************
*函数名称：void Uart1_Init(uint Freq,unsigned long int baud)
*函数功能：Uart1中断初始化
*入口参数：Freq-主频，baud-波特率
*出口参数：void
*****************************************************/
void UART1_Init(uint Freq,unsigned long int baud)
{
	P2CON &= 0xFC;   //TX/RX设置为输入带上拉
	P2PH  |= 0x03;
	
	OTCON |= 0xC0;    //串行接口SSI选择Uart1通信
	SSCON0 = 0x50;   //设置通信方式为模式一，允许接收
	SSCON1 = Freq*1000000/baud;   //波特率低位控制
	SSCON2 = (Freq*1000000/baud)>>8;   //波特率高位控制
	IE1 |= 0x01;      //开启SSI中断
    EA = 1;	
	ringBuffer_init(&g_comunicate_rb, sizeof(g_rb_buffer),g_rb_buffer);//初始化队列
	
}

/*****************************************************
*函数名称：void TWI/SPI/UART1_Int() interrupt 7
*函数功能：SSI中断函数
*入口参数：void
*出口参数：void
*****************************************************/
void Uart1_Int() interrupt 7   //Uart1中断函数
{
	
	if(SSCON0&0x02)    //发送标志位判断
	{
		SSCON0 &= 0xFD;
		Uart1SendFlag = 1;
	}
	if(SSCON0&0x01)  //接收标志位判断
	{
		SSCON0 &= 0xFE;
		//Uart1ReceiveFlag = 1;
		ringBuffer_push(&g_comunicate_rb, SSDAT); //队列接收数据
	}	
}