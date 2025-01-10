#ifndef __PROJECT__
#define __PROJECT__

#include "Radar.h"
#include "BreatheLED.h"
#include "H/Function_Init.H"
#include "..\TKDriver\H\TKDriver.h" 
#include "H/RingBuffer_C51.H"


#define SEND_HANDER1 0xAA
#define SEND_HANDER2 0x88

#define RECV_HANDER1 0xAA
#define RECV_HANDER2 0x55


enum SEND_DATA_ENUM
{
	UART_SEND_BYTE0 = 0,
	UART_SEND_BYTE1,
	UART_SEND_BYTE2,
	UART_SEND_BYTE3,
	UART_SEND_BYTE4,
	UART_SEND_BYTE5,
	UART_SEND_CHECK,
	
	UART_SEND_TOTALLEN,
};

enum RECEIVE_DATA_ENUM
{
	UART_RECV_BYTE0 = 0,
	UART_RECV_BYTE1,
	UART_RECV_BYTE2,
	UART_RECV_BYTE3,
	UART_RECV_BYTE4,
	UART_RECV_BYTE5,
	UART_RECV_CHECK,
	
	UART_RECV_TOTALLEN,
};


u8 handle_tft2mcu_data(uint8_t *buf);
u8 handle_mcu2tft_data(uint8_t *buf, int len);
u8 handle_tft2mcu_datacheck(uint8_t *buf, int len);
void loop_recv_comunicate_data(uint8_t *com_data);
void loop_write_comunicate_data(void);
void Radar_work(void);
void project(void);
extern uint8_t is_200ms_tick(uint8_t clear);
extern uint8_t is_100us_tick(uint8_t clear);
extern uint8_t is_ms_tick(uint8_t clear);
extern void PWMDTY1_Set(void);
extern void PWM_Init(void);
extern void UART_Sendstring(u8 *str);
extern void UART1_Init(uint Freq,unsigned long int baud);

extern bit BreatheLED;
extern uint8_t RadarFlag;
extern uint8_t Uart1_RxData[UART_RECV_TOTALLEN];

#define STEPVALUE (Uart1_RxData[UART_RECV_BYTE5] + (0xFF - Uart1_RxData[UART_RECV_BYTE5]) * 2 - 0xFF)

#endif 