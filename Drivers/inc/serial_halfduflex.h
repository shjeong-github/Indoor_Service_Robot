/*
 * serial_halfduflex.h
 *
 *  Created on: Jan 28, 2022
 *      Author: JeongSeongHo
 */



#ifndef __SERIAL_HALFDUFLEX_H_
#define __SERIAL_HALFDUFLEX_H_

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


 UART_HandleTypeDef huart3;

 typedef enum{
	SERIAL_HALFDUFLEX_PORT1,
	SERIAL_HALFDUFLEX_PORT2,
	SERIAL_HALFDUFLEX_PORT3,
	SERIAL_HALFDUFLEX_PORT4,
	SERIAL_HALFDUFLEX_PORT_MAX
 }SERIAL_HALFDUFLEX_PORT;

 typedef void (*SERIAL_HALFDUFLEX_CALLBACK)(void);


 void Serial_HalfDuflex_Init(void);
 // 시리얼 에러 헨들러
 void Error_Serial_HALF_DUFLEX_Handler(void);


 void Serial_HalfDulex_Open(SERIAL_HALFDUFLEX_PORT Port, uint32_t Baudrate, SERIAL_HALFDUFLEX_CALLBACK Callback);
 void Serial_HalfDuflex_Close(SERIAL_HALFDUFLEX_PORT Port);






















#ifdef __cplusplus
}
#endif
#endif /* __SERIAL_HALFDUFLEX_H_ */
