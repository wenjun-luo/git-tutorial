#include "project.h"
void main(void)
{  
	// WDTCON |= 0x10;		    //�忴�Ź�
    IO_Init();
    Timer_Test();
	PWM_Init();
	Radar_init();
    TouchKeyInit();
	UART1_Init(12,9600);
    while(1)
    {
		//���������
         project();   
				
    }
    
}
