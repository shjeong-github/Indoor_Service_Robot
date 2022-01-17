/*
 * qep.h
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#ifndef __QEP_H_
#define __QEP_H_

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f1xx.h"

//Define Timer Setting
#define QEP_TIM				TIM1
#define QEP_GPIO_AF			GPIO_AF_TIM1
#define QEP_TIM_Prescaler	1
#define QEP_TIM_Period		0xffff

//Define pin
//CH A output
#define QEP_OUTA_Port					GPIOA
#define QEP_OUTA_Pin					GPIO_Pin_8

//CH B output
#define QEP_OUTB_Port					GPIOA
#define QEP_OUTB_Pin					GPIO_Pin_9

//CH Z output
#define QEP_OUTZ_Port					GPIOA
#define QEP_OUTZ_Pin					GPIO_Pin_10

// TIM_HandleTypeDef Structure
TIM_HandleTypeDef htim1;


//encoder data read
void QEP_Read(void);
//encoder reset
void QEP_Reset(void);
// encoder data get
int16_t QEP_Get(void);
// encoder init
void QEP_Init(void);
void Error_qep_Handler(void);
// 엔코더의 기본 세팅 함수
void Encoder_value_Set(uint16_t Encoder_count_value,uint8_t multiple_value,float Time_value);
// 엔코더 각속도 계산 함수
uint16_t Encoder_angular_velocity(void);
// 엔코더 속도 게산 함수
uint16_t Encoder_speed(void);


#endif /* __QEP_H_ */
