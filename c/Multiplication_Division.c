#include "H/Function_Init.H"

u32 product = 0;//�˻�
u32 quotient= 0;//��
u16 remainder = 0;//����
Result_union result;


void Multiplier_Divider_Test(void)   //�˳���
{
	while(1)
	{
		OPERCON &= ~0x40;
		//�˳�����
		Multiplication(0x55AA, 0xAA55);  //�˷�����
		if(product == 0x38ff5572)        //�жϻ�
		{
			P20 = 0;
		}
		
		Division(0xFFAA5500,0xAA55);     //��������
		if(quotient == 0x18040&&remainder == 0x3FC0)  //�ж��̺�����
		{
			P20 = 1;
		}
	}		
}	
/****************************************************
*�������ƣ�Multiplication(u16 faciend, u16 Multiplier)
*�������ܣ��˷�����
*��ڲ�����faciend��Multiplier
*���ڲ�������
****************************************************/
void Multiplication(u16 faciend, u16 Multiplier)
{
	EXA0 = faciend;
	EXA1 = faciend>>8;
	EXBL = Multiplier;
	EXBH = Multiplier>>8;

	OPERCON |= 0x80;      //��ʼ����
	while(OPERCON & 0x80);

	result.reg.a0 = EXA0;
	result.reg.a1 = EXA1;
	result.reg.a2 = EXA2;
	result.reg.a3 = EXA3;

	product = result.Result;
}	

/****************************************************
*�������ƣ�Division(u32 dividend,u16 divisor)
*�������ܣ���������
*��ڲ�����dividend��divisor
*���ڲ�������
****************************************************/
void Division(u32 dividend,u16 divisor)
{
	Result_union temp;
	temp.Result = dividend;

	EXA0 = temp.reg.a0;
	EXA1 = temp.reg.a1;
	EXA2 = temp.reg.a2;
	EXA3 = temp.reg.a3;

	EXBL = divisor;
	EXBH = divisor>>8;

	OPERCON |= 0xC0;
	while(OPERCON & 0x80);

	result.reg.a0 = EXA0;
	result.reg.a1 = EXA1;
	result.reg.a2 = EXA2;
	result.reg.a3 = EXA3;

	remainder = EXBH*256+ EXBL;
	quotient  = result.Result;
}

