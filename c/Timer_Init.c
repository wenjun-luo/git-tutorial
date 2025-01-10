#include "project.h"
uint8_t  g_flag_1ms = 0;
uint8_t  g_flag_200ms = 0;
uint8_t  g_flag_ms = 0;
uint32_t g_1ms_cnt = 0;
uint32_t l_1ms_cnt = 0;
void Timer_Init(void);

/*****************************************************
 *�������ƣ�void Timer_Test(void);
 *�������ܣ�T0/T1/T2����
 *��ڲ�����void
 *���ڲ�����void
 *****************************************************/
void Timer_Test(void)
{
	Timer_Init();
}
/*****************************************************
 *�������ƣ�void Timer_Init(void)
 *�������ܣ�T0/T1/T2��ʼ��    ĿǰT0�Ķ�ʱ����Ϊ1ms��������ֵΪ41536��
 *��ڲ�����void
 *���ڲ�����void
 *****************************************************/
void Timer_Init(void)
{
	TMCON = 0X07; //------111 ;Timer0��Tiemr1��Tiemr2ѡ��ʱ��Fsys

	// T0����
	TMOD |= 0x01;				 // 0000 0001;Timer0���ù�����ʽ1
	TL0 = (65536 - 12000) % 256; // ���ʱ�䣺ʱ��ΪFsys����12000*��1/Fsys��=1ms;
	TH0 = (65536 - 12000) / 256;
	TR0 = 0;
	ET0 = 1; // ��ʱ��0����
	TR0 = 1; // �򿪶�ʱ��0
	
	// T1����
//	TMOD |= 0x20;	 // 0010 0000;Timer1���ù�����ʽ2
//	TL1 = 256 - 120; // ���ʱ�䣺ʱ��ΪFsys����120*��1/Fsys��=10us;
//	TH1 = 256 - 120;
//	TR1 = 0;
//	ET1 = 1; // ��ʱ��1����
//	TR1 = 1; // �򿪶�ʱ��1


	// T2����
	T2MOD = 0x00;
	T2CON = 0x00;					// ����Ϊ16λ���ؼĴ���
	RCAP2H = (65536 - 12000) / 256; // ���ʱ�䣺ʱ��ΪFsys����12000*��1/Fsys��=1ms;
	RCAP2L = (65536 - 12000) % 256;
	TR2 = 0;
	ET2 = 1; // ��ʱ��2����
	TR2 = 1; // �򿪶�ʱ��2

	/*
	//Timer2������
	T2CON = 0X09; //ʹ��EXT2��16λ����ģʽ
	T2MOD = 0X00;
	TH2 = 0X00;
	TL2 = 0X00;
	RCAP2H = 0X00;
	RCAP2L = 0X00;
	TR2 = 0;
	ET2 = 1;//��ʱ��2����
	TR2 = 1;//�򿪶�ʱ��2
	*/

	EA = 1;
}

uint32_t get_tick_count()
{
	return g_1ms_cnt;
}

//ms�Ƿ񵽴����������������ۼ�
uint8_t is_1ms_tick(uint8_t clear)
{
	if (g_flag_1ms)
	{
		if(clear)
			g_flag_1ms = 0;
		return 1;
	}
	return 0;
}

/**************************************************
 *�������ƣ�void timer0/1/2() interrupt 1/3/5
 *�������ܣ���ʱ���жϲ�������
 *��ڲ�����void
 *���ڲ�����void
 **************************************************/
void timer0() interrupt 1
{
	static u16 cnt_1ms = 0;
	TL0 = (65536 - 12000) % 256;   //1200���Ϊ��Ƶֵ
	TH0 = (65536 - 12000) / 256;
	g_1ms_cnt++;
	if (++cnt_1ms > STEPVALUE )    //STEPVALUE����PWMDTY1_Set2() 
	{
		cnt_1ms = 0;
		g_flag_1ms = 1;
	}
}


void timer1() interrupt 3
{
	TF1 = 0;//�������
}

 
//200ms�Ƿ񵽴����������������ۼ�
uint8_t is_200ms_tick(uint8_t clear)
{
	if (g_flag_200ms)
	{
		if(clear)
			g_flag_200ms = 0;
		return 1;
	}
	return 0;
}
//ms��������������������ۼ�
uint8_t is_ms_tick(uint8_t clear)
{
	if (g_flag_ms)
	{
		if(clear)
			g_flag_ms = 0;
		return 1;
	}
	return 0;
}

void Timer2Int(void) interrupt 5
{  
	static u16 cnt = 0;
	static u16 cnt_ms = 0;
	TF2 = 0; // �������
	l_1ms_cnt++;	
    if (++cnt > 199 )
	{
		cnt = 0;
		g_flag_200ms = 1;
	}
	if (++cnt_ms > Uart1_RxData[5] )
	{
		cnt_ms = 0;
		g_flag_ms = 1;
	}

}

