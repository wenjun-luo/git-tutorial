#include "H/Function_Init.H"

void ADC_Init(uint Channel,uchar ADCFreq);
uint ADC_GetAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum);
unsigned int ADCValue = 0x0000;
bit AdcFlag = 0;
/***********ADC����Ƶ��ѡ��*************/
enum ADCFreq {F32=0,F24,F16,F12,F8,F6,F4,F3};

/***********ADC������ѡ��*************/
#if (IC_MODEL == SC92F8413)
enum Channel {AIN0=0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,VDD4=31};
#endif

#if (IC_MODEL == SC92F8412)
enum Channel {AIN2=2,AIN3,AIN4,AIN5,AIN8=8,AIN9,VDD4=31};
#endif

#if (IC_MODEL == SC92F8411)
enum Channel {AIN2=2,AIN3,AIN4,AIN8=8,AIN9,VDD4=31};
#endif

/*****************************************************
*�������ƣ�void ADC_Test(void)
*�������ܣ�ADC����
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void ADC_Test(void)
{
	ADC_Init(AIN2,F8);
	while(1)
	{
		ADCValue = ADC_GetAverageValue(ADC_SamplesNum_SixteenTimes);
	}
}
/*****************************************************
*�������ƣ�void ADC_Init(uint Channel,uchar ADCFreq)
*�������ܣ�ADC��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void ADC_Init(uint Channel,uchar ADCFreq)
{
	ADCCON = 0X80|Channel;		//����ADC��ADC����Ƶ��Ϊ3M ,ѡ��ChannelλADC������
	if(Channel<8)
	{
		ADCCFG0 = 1<<Channel;   //����Channel��Ϊ������
	}
	else
	{
		ADCCFG1 = 1<<(Channel-8);   //����Channel��Ϊ������
	}
	ADCCFG2 = ADCFreq;
	IE |= 0X40;        //����ADC�ж�
	EA = 1;
}

/*****************************************************
*�������ƣ�uint ADC_GetAverageValue(uint Channel,ADC_SamplesNum_TypeDef ADC_SamplesNum)
*�������ܣ�ADC����ȡƽ��ֵ
*��ڲ�����
ADC_SamplesNum_TypeDef ADC_SamplesNum:��������
*���ڲ�����
uint:��β���ƽ��ֵ
*****************************************************/
uint ADC_GetAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum)
{
	uchar tmpCnt;
	uint tmpValueSum = 0, tmpValue;
  uint tmpValue_Max = 0, tmpValue_Min = 0xFFFF;
 
	for(tmpCnt = 0; tmpCnt < ADC_SamplesNum; tmpCnt ++)
  {
		EA = 0;
		OPINX = 0xC1;
	  OPREG |= 0x10;      //�л�������Ƶ		
		EA = 1;		
		ADCCON |= 0X40;             //��ʼһ��ADCת��
	  while(!AdcFlag);	  //�ȴ�ADCת�����	
		EA = 0;
		OPINX = 0xC1;
	  OPREG &= 0xCF;      //������һ��Ƶ
		EA = 1;	
		
		AdcFlag = 0;             
	  tmpValue=(ADCVH<<4)+(ADCVL>>4);     //��ȡ����ת��ֵ
		   
    if(tmpValue > tmpValue_Max)   //��ȡ���ת��ֵ�е����ֵ
      tmpValue_Max = tmpValue;   
    if(tmpValue < tmpValue_Min)   //��ȡ���ת��ֵ�е���Сֵ
      tmpValue_Min = tmpValue;		
    tmpValueSum += tmpValue;   //�ۼӶ��ת��ֵ�ĺ�
  }

	/* ͨ��Ӳ���˳�����������ƽ��ֵ */
  {
    OPERCON |= 0X40;
    /* ������Ϊ16λ���� */
    tmpValueSum -= (tmpValue_Max + tmpValue_Min);
    EXA0 = tmpValueSum;
    EXA1 = tmpValueSum >> 8;
    EXBL = ADC_SamplesNum - 2;			//����Ϊ8λ����

    OPERCON |= 0x80;				//��ʼ��������
    while(OPERCON & 0x80);			//�ȴ��������

    //��ȡ��
    tmpValue = (uint)EXA0;
    tmpValue |= EXA1 << 8;
  }
    return tmpValue;			//����ƽ��ֵ
}

void ADC_Interrupt(void) interrupt 6
{
	ADCCON&=~(0X20);  //���жϱ�־λ
	AdcFlag = 1;
}