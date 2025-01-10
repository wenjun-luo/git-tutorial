#include "H/Function_Init.H"

void ADC_Init(uint Channel,uchar ADCFreq);
uint ADC_GetAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum);
unsigned int ADCValue = 0x0000;
bit AdcFlag = 0;
/***********ADC采样频率选择*************/
enum ADCFreq {F32=0,F24,F16,F12,F8,F6,F4,F3};

/***********ADC采样口选择*************/
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
*函数名称：void ADC_Test(void)
*函数功能：ADC测试
*入口参数：void
*出口参数：void
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
*函数名称：void ADC_Init(uint Channel,uchar ADCFreq)
*函数功能：ADC初始化
*入口参数：void
*出口参数：void
*****************************************************/
void ADC_Init(uint Channel,uchar ADCFreq)
{
	ADCCON = 0X80|Channel;		//开启ADC，ADC采样频率为3M ,选择Channel位ADC采样口
	if(Channel<8)
	{
		ADCCFG0 = 1<<Channel;   //设置Channel作为采样口
	}
	else
	{
		ADCCFG1 = 1<<(Channel-8);   //设置Channel作为采样口
	}
	ADCCFG2 = ADCFreq;
	IE |= 0X40;        //开启ADC中断
	EA = 1;
}

/*****************************************************
*函数名称：uint ADC_GetAverageValue(uint Channel,ADC_SamplesNum_TypeDef ADC_SamplesNum)
*函数功能：ADC采样取平均值
*入口参数：
ADC_SamplesNum_TypeDef ADC_SamplesNum:采样次数
*出口参数：
uint:多次采样平均值
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
	  OPREG |= 0x10;      //切换至二分频		
		EA = 1;		
		ADCCON |= 0X40;             //开始一次ADC转换
	  while(!AdcFlag);	  //等待ADC转换完成	
		EA = 0;
		OPINX = 0xC1;
	  OPREG &= 0xCF;      //返回至一分频
		EA = 1;	
		
		AdcFlag = 0;             
	  tmpValue=(ADCVH<<4)+(ADCVL>>4);     //获取单次转换值
		   
    if(tmpValue > tmpValue_Max)   //获取多次转换值中的最大值
      tmpValue_Max = tmpValue;   
    if(tmpValue < tmpValue_Min)   //获取多次转换值中的最小值
      tmpValue_Min = tmpValue;		
    tmpValueSum += tmpValue;   //累加多次转换值的和
  }

	/* 通过硬件乘除法器来计算平均值 */
  {
    OPERCON |= 0X40;
    /* 被除数为16位数据 */
    tmpValueSum -= (tmpValue_Max + tmpValue_Min);
    EXA0 = tmpValueSum;
    EXA1 = tmpValueSum >> 8;
    EXBL = ADC_SamplesNum - 2;			//除数为8位数据

    OPERCON |= 0x80;				//开始除法计算
    while(OPERCON & 0x80);			//等待计算完毕

    //获取商
    tmpValue = (uint)EXA0;
    tmpValue |= EXA1 << 8;
  }
    return tmpValue;			//返回平均值
}

void ADC_Interrupt(void) interrupt 6
{
	ADCCON&=~(0X20);  //清中断标志位
	AdcFlag = 1;
}