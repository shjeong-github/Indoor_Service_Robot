/*
 * led.h
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#ifndef __LED_H_
#define __LED_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"

#define LED1_Port						GPIOB
#define LED1_Pin						GPIO_PIN_0

#define LED2_Port						GPIOB
#define LED2_Pin						GPIO_PIN_1

#define LED3_Port						GPIOB
#define LED3_Pin						GPIO_PIN_2

#define LED4_Port						GPIOB
#define LED4_Pin						GPIO_PIN_5

#define	LED_ON		0
#define	LED_OFF		1

typedef struct{
	GPIO_TypeDef * Port;
	uint16_t Pin;
}LED_PortDef;


//LED Setting
void LED_Init(void);
//LED bit control
void LED_On(uint8_t Data);
//LED Position Control
void LED_On_Unit(uint8_t Position,uint8_t OnOff);








#ifdef __cplusplus
 extern "C" {
#endif


#endif /* __LED_H_ */
