/*
 * timer.h
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include "segment.h"
#include "qep.h"


 // Timer Define
#define BASE_TIM				TIM3
#define BAES_TIM_IRQn			TIM3_IRQn
#define BASE_TIM_Prescaler		64  // 36
#define BASE_TIM_Period			999

// Timer IT Define
#define BAES_TIM_IT_PreemptionPriority 	2
#define BAES_TIM_IT_SubPriority 	0

// Timer IT register
typedef enum{
	ALARM0,
	ALARM1,
	ALARM2,
	ALARM3,
	ALARM4,
	ALARM5,
	ALARM6,
	ALARM_MAX
}ALARM;

TIM_HandleTypeDef htim3;

// Timer IT callback function
typedef void (*ALARM_CALLBACK)(void);

// Timer Setting
void Timer_Init(void);

// Regist Timer IT
void Alarm_Open(ALARM Alarm, uint16_t msPeriod, ALARM_CALLBACK Callback);

// Delete Timer IT
void Alarm_Close(ALARM Alarm);



// Error
void Error_Timer_Handler(void);

#ifdef __cplusplus
}
#endif


#endif /* __TIMER_H_ */
