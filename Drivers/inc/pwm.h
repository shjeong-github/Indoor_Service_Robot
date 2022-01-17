/*
 * pwm.h
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#ifndef __PWM_H_
#define __PWM_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"


 // ----------------------------------------
#define PWM1_TIM					TIM4
#define PWM1_TIM_IRQn				TIM4_IRQn
#define PWM1_TIM_Prescaler			24					//84       Scaler*Period = T
#define PWM1_TIM_Period_Default		999				//1000-1   Resolution

#define PWM2_TIM					TIM2
#define PWM2_TIM_IRQn				TIM2_IRQn
#define PWM2_TIM_Prescaler			24
#define PWM2_TIM_Period_Default		999




// PWM_TIM1 port and pin
#define PWM1_1_Port			GPIOB
#define PWM1_1_Pin			GPIO_PIN_6


#define PWM1_2_Port			GPIOB
#define PWM1_2_Pin			GPIO_PIN_7


#define PWM1_3_Port			GPIOB
#define PWM1_3_Pin			GPIO_PIN_8


#define PWM1_4_Port			GPIOB
#define PWM1_4_Pin			GPIO_PIN_9


// #define PWM_GND_Port		GPIOA
// #define PWM_GND_Pin		GPIO_PIN_9

// PWM_TIM2 port and pin

#define PWM2_1_Port			GPIOA
#define PWM2_1_Pin			GPIO_PIN_0


#define PWM2_2_Port			GPIOA
#define PWM2_2_Pin			GPIO_PIN_1


#define PWM_DIR1_Port		GPIOC
#define PWM_DIR1_Pin		GPIO_PIN_4


#define PWM_DIR2_Port		GPIOC
#define PWM_DIR2_Pin		GPIO_PIN_5


 //------------------------------------------





 typedef enum{
 	PWM1_1,
 	PWM1_2,
 	PWM1_3,
 	PWM1_4,
 	PWM2_1,
	PWM2_2,
 }PWM;

 typedef struct{
 	GPIO_TypeDef * Port;
 	uint16_t Pin;
 }DIR_PortDef;


TIM_HandleTypeDef htimpwm1;
TIM_HandleTypeDef htimpwm2;




//PWM Setting
void PWM_Init(uint16_t msPeriod1, uint16_t msPeriod2);
//PWM Enable
void PWM_Open(PWM Pwm, float Percent);
//PWM Disable
void PWM_Close(PWM Pwm);
//PWM Duty Change
void PWM_Duty_Set(PWM Pwm,uint8_t Data_num, float Data_value);
//PWM error handler
void Error_PWM_Handler(void);
uint16_t Duty_calculate(float Persent);
//PWM DIR Change
void DIR_Change(uint8_t Dirnum, uint8_t Direction);
// PWM 서보모터 및 DC모터  기본 값 설정
void Angle_Value_Set(float inclination_value, float bias_value, float angle_min_value, float angle_max_value);
// 서보모터 각도 계산
float Angle_duty_cal(float angle);
// DC모터 스피드 계산
float Speed_duty_cal(float speed);



#ifdef __cplusplus
}
#endif

#endif /* __PWM_H_ */
