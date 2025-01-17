#include "project.h"
uint8_t  g_flag_1ms = 0;
uint8_t  g_flag_200ms = 0;
uint8_t  g_flag_ms = 0;
uint32_t g_1ms_cnt = 0;
uint32_t l_1ms_cnt = 0;
void Timer_Init(void);

/*****************************************************
 *函数名称：void Timer_Test(void);
 *函数功能：T0/T1/T2测试
 *入口参数：void
 *出口参数：void
 *****************************************************/
void Timer_Test(void)
{
	Timer_Init();
}
/*****************************************************
 *函数名称：void Timer_Init(void)
 *函数功能：T0/T1/T2初始化    目前T0的定时周期为1ms，计数初值为41536，
 *入口参数：void
 *出口参数：void
 *****************************************************/
void Timer_Init(void)
{
	TMCON = 0X07; //------111 ;Timer0、Tiemr1和Tiemr2选择时钟Fsys

	// T0设置
	TMOD |= 0x01;				 // 0000 0001;Timer0设置工作方式1
	TL0 = (65536 - 12000) % 256; // 溢出时间：时钟为Fsys，则12000*（1/Fsys）=1ms;
	TH0 = (65536 - 12000) / 256;
	TR0 = 0;
	ET0 = 1; // 定时器0允许
	TR0 = 1; // 打开定时器0
	
	// T1设置
//	TMOD |= 0x20;	 // 0010 0000;Timer1设置工作方式2
//	TL1 = 256 - 120; // 溢出时间：时钟为Fsys，则120*（1/Fsys）=10us;
//	TH1 = 256 - 120;
//	TR1 = 0;
//	ET1 = 1; // 定时器1允许
//	TR1 = 1; // 打开定时器1


	// T2设置
	T2MOD = 0x00;
	T2CON = 0x00;					// 设置为16位重载寄存器
	RCAP2H = (65536 - 12000) / 256; // 溢出时间：时钟为Fsys，则12000*（1/Fsys）=1ms;
	RCAP2L = (65536 - 12000) % 256;
	TR2 = 0;
	ET2 = 1; // 定时器2允许
	TR2 = 1; // 打开定时器2

	/*
	//Timer2捕获功能
	T2CON = 0X09; //使能EXT2，16位捕获模式
	T2MOD = 0X00;
	TH2 = 0X00;
	TL2 = 0X00;
	RCAP2H = 0X00;
	RCAP2L = 0X00;
	TR2 = 0;
	ET2 = 1;//定时器2允许
	TR2 = 1;//打开定时器2
	*/

	EA = 1;
}

uint32_t get_tick_count()
{
	return g_1ms_cnt;
}

//ms是否到达，若到达则清空重新累计
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
 *函数名称：void timer0/1/2() interrupt 1/3/5
 *函数功能：定时器中断产生方波
 *入口参数：void
 *出口参数：void
 **************************************************/
void timer0() interrupt 1
{
	static u16 cnt_1ms = 0;
	TL0 = (65536 - 12000) % 256;   //1200理解为分频值
	TH0 = (65536 - 12000) / 256;
	g_1ms_cnt++;
	if (++cnt_1ms > STEPVALUE )    //STEPVALUE用于PWMDTY1_Set2() 
	{
		cnt_1ms = 0;
		g_flag_1ms = 1;
	}
}


void timer1() interrupt 3
{
	TF1 = 0;//溢出清零
}

 
//200ms是否到达，若到达则清空重新累计
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
//ms级别，若到达则清空重新累计
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
	TF2 = 0; // 溢出清零
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

