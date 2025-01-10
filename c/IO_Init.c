#include "H/Function_Init.H"
/*****************************************************
*�������ƣ�void IO_Init(void)
*�������ܣ�IO��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void IO_Init(void)
{
  #if (IC_MODEL == SC92F8413)  //SC92F8413�Ŷ���
	P0CON = 0xFF;  //����P0Ϊǿ����ģʽ
	P0PH  = 0x00;		
	P1CON = 0x00;  //����P1Ϊ���������ģʽ
	P1PH  = 0xFF;
	P2CON = 0xFF;  //����P2Ϊǿ����ģʽ
	P2PH  = 0x00;
	P5CON = 0x00;  //����P5Ϊ��������ģʽ
	P5PH  = 0x00;
	#endif
	
	#if (IC_MODEL == SC92F8412)  //SC92F8412�Ŷ���
	P0CON = 0xFF;  //����P0Ϊǿ����ģʽ
	P0PH  = 0x00;		
	P1CON = 0x00;  //����P1Ϊ���������ģʽ
	P1PH  = 0xFF;
	P2CON = 0xFF;  //����P2Ϊǿ����ģʽ
	P2PH  = 0x00;
	P5CON = 0x00;  //����P5Ϊ��������ģʽ
	P5PH  = 0x00;
	SC92F8412_NIO_Init(); //δ����IO������
	#endif

  #if (IC_MODEL == SC92F8411)  //SC92F8411�Ŷ���
	P0CON = 0xFF;  //����P0Ϊǿ����ģʽ
	P0PH  = 0x00;		
	P1CON = 0xFF;  //����P1Ϊ���������ģʽ
	P1PH  = 0x00;
	P2CON = 0xFF;  //����P2Ϊǿ����ģʽ
	P2PH  = 0x00;
	P5CON = 0xFF;  //����P5Ϊ��������ģʽ
	P5PH  = 0x00;
	SC92F8411_NIO_Init(); //δ����IO������
	#endif

}