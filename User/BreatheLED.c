#include "BreatheLED.h"
#include "project.h"
uint8_t pwm1_duty = 0x64;  //LED ��pwm��״̬
bit flag = 0;


// ����PWMռ�ձ�    Uart1_RxData[5]ֵԽ�󣬺���Ƶ��Խ��
void PWMDTY1_Set(void) 
{
    if (is_ms_tick(1)) 
	{  // ����Ƿ񵽴�ms
        if (flag == 0) 
		{
            PWMDTY1 = pwm1_duty;  // ����PWMռ�ձ�
            pwm1_duty -= 1;  // ����ռ�ձ�
            if (pwm1_duty == 0) 
			{
                flag = 1;  // �ı䷽��
            }
        }
		else 
		{
            PWMDTY1 = pwm1_duty;  // ����PWMռ�ձ�
            pwm1_duty += 1;  // ����ռ�ձ�
            if (pwm1_duty > 0x64) 
			{
                flag = 0;  // �ı䷽��
            }
        }
    }
}
/*
// ����PWMռ�ձ�    Uart1_RxData[5]ֵԽ�󣬺���Ƶ��Խ��
void PWMDTY1_Set2(void) 
{
    if (is_1ms_tick(1)) 
	{  // ����Ƿ񵽴�ms
        if (flag == 0) 
		{
            PWMDTY1 = pwm1_duty;  // ����PWMռ�ձ�
            pwm1_duty -= 1;  // ����ռ�ձ�
            if (pwm1_duty == 0) 
			{
                flag = 1;  // �ı䷽��
            }
        }
		else 
		{
            PWMDTY1 = pwm1_duty;  // ����PWMռ�ձ�
            pwm1_duty += 1;  // ����ռ�ձ�
            if (pwm1_duty == 0x64) 
			{
                flag = 0;  // �ı䷽��
            }
        }
    }
}
*/