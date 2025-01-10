#include "H/Function_Init.H"
#include "H/RingBuffer_C51.H"
#include "H/Data_Type.h"
#include "project.h"

bit Uart1SendFlag = 0;            //Uart�����жϱ�־λ
//bit Uart1ReceiveFlag = 0; 		  //Uart�����жϱ�־λ
TagRingBuffer g_comunicate_rb;    //�������
static char g_rb_buffer[9]={0};   
//�����ַ���
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
*�������ƣ�void Uart1_Init(uint Freq,unsigned long int baud)
*�������ܣ�Uart1�жϳ�ʼ��
*��ڲ�����Freq-��Ƶ��baud-������
*���ڲ�����void
*****************************************************/
void UART1_Init(uint Freq,unsigned long int baud)
{
	P2CON &= 0xFC;   //TX/RX����Ϊ���������
	P2PH  |= 0x03;
	
	OTCON |= 0xC0;    //���нӿ�SSIѡ��Uart1ͨ��
	SSCON0 = 0x50;   //����ͨ�ŷ�ʽΪģʽһ���������
	SSCON1 = Freq*1000000/baud;   //�����ʵ�λ����
	SSCON2 = (Freq*1000000/baud)>>8;   //�����ʸ�λ����
	IE1 |= 0x01;      //����SSI�ж�
    EA = 1;	
	ringBuffer_init(&g_comunicate_rb, sizeof(g_rb_buffer),g_rb_buffer);//��ʼ������
	
}

/*****************************************************
*�������ƣ�void TWI/SPI/UART1_Int() interrupt 7
*�������ܣ�SSI�жϺ���
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void Uart1_Int() interrupt 7   //Uart1�жϺ���
{
	
	if(SSCON0&0x02)    //���ͱ�־λ�ж�
	{
		SSCON0 &= 0xFD;
		Uart1SendFlag = 1;
	}
	if(SSCON0&0x01)  //���ձ�־λ�ж�
	{
		SSCON0 &= 0xFE;
		//Uart1ReceiveFlag = 1;
		ringBuffer_push(&g_comunicate_rb, SSDAT); //���н�������
	}	
}