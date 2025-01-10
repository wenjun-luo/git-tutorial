#include "Radar.h"
#include "project.h"
extern uint32_t l_1ms_cnt;
//开启雷达
void Radar_open(void)
{
    P1CON &= 0xEF;
    P1PH |= 0x02; 	
	P11 = 1;
	//l_1ms_cnt = 0;
}
//雷达自检
void Radar_check(void)
{
	while(P14 == 1); //等待自检输出低电平
	l_1ms_cnt = 0;
    while(l_1ms_cnt <= 1000)
	{
		continue;
		if(l_1ms_cnt == 1000)
			break;
	}
//	if(P14 == 0)
//		return 1;
//	else
//		return 0;
    	
}
//判断雷达输出
unsigned char Radar_Ischeck(void)
{

	if(P14 == 1)
		return 1;
	else
		return 0;

}
//雷达初始化
void Radar_init(void)
{
	Radar_open();
	Radar_check();
}



