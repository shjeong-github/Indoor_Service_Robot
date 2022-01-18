/*
 * serial.h
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#ifndef __SERIAL_H_
#define __SERIAL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_it.h"
#include "stm32f1xx_hal.h"
//Define Pin
#define SERIAL1_Tx_PORT					GPIOA
#define SERIAL1_Tx_PIN					GPIO_PIN_2

#define SERIAL1_Rx_PORT					GPIOA
#define SERIAL1_Rx_PIN					GPIO_PIN_3



#define SERIAL2_Tx_PORT					GPIOB
#define SERIAL2_Tx_PIN					GPIO_PIN_10

#define SERIAL2_Rx_PORT					GPIOB
#define SERIAL2_Rx_PIN					GPIO_PIN_11




#define SERIAL_BUFFER_SIZE		16
#define DATA_Size_PC_COMM		10

UART_HandleTypeDef huartx;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

typedef enum{
	SERIAL_PORT1,
	SERIAL_PORT2,
	SERIAL_PORT3,
	SERIAL_PORT4,
	SERIAL_PORT_MAX
}SERIAL_PORT;

typedef void (*SERIAL_CALLBACK)(void);
// 시리얼 1번 INIT
void Serial1_Init(void);
// 시리얼 2번 INIT
void Serial2_Init(void);
// 시리얼 오픈
void Serial_Open(SERIAL_PORT Port, uint32_t Baudrate, SERIAL_CALLBACK Callback);  //SERIAL_CALLBACK Callback
// 시리얼 종료
void Serial_Close(SERIAL_PORT Port);

// 시리얼 바이트 변환
void Serial_WriteByte(SERIAL_PORT Port, uint8_t Data);
// 시리얼 헥스 변환
void Serial_WriteHexa(SERIAL_PORT Port, uint32_t Data);
// 시리얼 문자 변환
void Serial_WriteString(SERIAL_PORT Port, uint8_t* String);
// 시리얼 인트 변환
void Serial_WriteInt(SERIAL_PORT Port, uint16_t Data);
// 시리얼 에러 헨들러
void Error_Serial_Handler(void);
// 시리얼 데이터 전송
void Serial_Send(SERIAL_PORT Port , uint8_t *Data, uint16_t Size);
// 시리얼 데이터 확인
uint8_t Serial_Data_GET(SERIAL_PORT Port);


#ifdef __cplusplus
}
#endif

#endif /* __SERIAL_H_ */
