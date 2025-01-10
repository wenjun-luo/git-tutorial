#include "project.h"

extern TagRingBuffer g_comunicate_rb;
uint32_t  exKeyValueFlag;
uint8_t Uart1_RxData[UART_RECV_TOTALLEN] = {0};   //������������
bit ChangeFlag = 0;    
bit BreatheLED = 0;   //�����Ʊ�־λ


//�������� ����LED״̬
uint8_t handle_tft2mcu_data(uint8_t *buf) {

    if ((buf[4] & 0x0F) == 0x00) {
        PWMDTY1 = 0x00;  //ȫ��
		BreatheLED = 0;
    } else if ((buf[4] & 0x0F) == 0x01) {
        PWMDTY1 = 0x64;  //ȫ��
		BreatheLED = 0;
    } else if ((buf[4] & 0x0F) == 0x02) {
        BreatheLED = 1;   //�����Ʊ�־λ
    }  
	
    return 0;
}
//��������֡�����봦��
u8 handle_mcu2tft_data(uint8_t *buf, int len)
{
    u8 i, sum = 0;

    for (i = 1; i < len - 1 ; i++)
    {
        sum += buf[i];
    }
    return (0x100 - sum ); //����У��ֵ
         
}
//��������֡У���봦��
u8 handle_tft2mcu_datacheck(uint8_t *buf, int len)
{
    u8 i, sum = 0;

    for (i = 1; i < len - 1 ; i++)
    {
        sum += buf[i];
    }
    return ((0x200 - sum) & 0xFF); //����У��ֵ
         
}

uint8_t Uart1_TxData[UART_SEND_TOTALLEN] = {0xAA,0x88,0x07}; //Ҫ���͵�����֡
uint8_t SwitchFlag = 0;                     //�����������
uint8_t RadarFlag = 0;                      //�״��������
//��������֡����
void loop_write_comunicate_data(void)
{
    Uart1_TxData[UART_SEND_BYTE0] = SEND_HANDER1;
	Uart1_TxData[UART_SEND_BYTE1] = SEND_HANDER2;
	Uart1_TxData[UART_SEND_BYTE2] = UART_SEND_TOTALLEN;
	Uart1_TxData[UART_SEND_BYTE3] =  ((Uart1_TxData[UART_SEND_BYTE3] &0xfe)| RadarFlag);
	Uart1_TxData[UART_SEND_BYTE4] =  ((Uart1_TxData[UART_SEND_BYTE4] &0xfe)| SwitchFlag);
	Uart1_TxData[UART_SEND_CHECK] =  handle_mcu2tft_data(Uart1_TxData,Uart1_TxData[UART_SEND_BYTE2]);
      
}

//��������֡����
void loop_recv_comunicate_data(uint8_t *com_data)
{
    static uint8_t byte_index = 0;
    while (ringBuffer_pop(&g_comunicate_rb, com_data+byte_index))
    {	        
        //com_data[byte_index] = ch;
        switch (byte_index){
        case 0:
			if (com_data[byte_index] == RECV_HANDER1){				
                byte_index++;				
            }else{   
				byte_index = 0;
			}
            break;
		case 1:
			if (com_data[byte_index] == RECV_HANDER2){            
                byte_index++;
            }else{    				
				byte_index = 0;
			}
			break;
        case 2:
			if (com_data[byte_index] == UART_RECV_TOTALLEN){             
                byte_index++;			
            }else{    
				byte_index = 0;
			}
            break;
        default:
            byte_index++;
            if (byte_index >= com_data[UART_RECV_BYTE2] || byte_index > UART_RECV_TOTALLEN){   			
               // handle_tft2mcu_data(com_data,byte_index); // �����������
				if(handle_tft2mcu_datacheck(com_data,com_data[UART_RECV_BYTE2]) == com_data[byte_index - 1]){
					handle_tft2mcu_data(com_data);  //��������
				}
                byte_index = 0;
            }
            break;
        }
    }
}

//�״���
void Radar_work(void)
{
		RadarFlag = Radar_Ischeck();
		if( RadarFlag)
		{
			RadarFlag = 0x01;
		}
		else
			RadarFlag = 0x00;
}

void project(void)
{        
	    
	     if(SOCAPI_TouchKeyStatus & 0x80)
        {
            SOCAPI_TouchKeyStatus &= 0x7f;
            exKeyValueFlag = TouchKeyScan();
			if(exKeyValueFlag & (1L << 0))
            {            
				ChangeFlag = 1;
            }
			else
			{
				if(ChangeFlag == 1)
			   {
					ChangeFlag = 0;
					SwitchFlag = (SwitchFlag == 0x01) ? 0x00 : 0x01;
			   }

			}
			loop_write_comunicate_data();         //д������
			loop_recv_comunicate_data(Uart1_RxData); //��������
			Radar_work();                         //�״���
			if(is_200ms_tick(1))
			{
				UART_Sendstring(Uart1_TxData);   //��������
			}
			//������		
			if(BreatheLED)
				PWMDTY1_Set();
            TouchKeyRestart();		
			
        }
}
