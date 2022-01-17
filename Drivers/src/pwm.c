/*
 * pwm.c
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */


#include "pwm.h"

static void PWM_GPIO_Init(void);

// PWM Period change
uint16_t PWM1_TIM_Period = PWM1_TIM_Period_Default;
uint16_t PWM2_TIM_Period = PWM2_TIM_Period_Default;
DIR_PortDef DIR_PortTable[] = {{PWM_DIR1_Port,PWM_DIR1_Pin},{PWM_DIR2_Port,PWM_DIR2_Pin}};
float INCLINATION =0;
float BIAS=0;
float ANGLE_MIN=0;
float ANGLE_MAX=0;

void PWM_Init(uint16_t msPeriod1, uint16_t msPeriod2)
{
	//TIM Master configuration Structure
	TIM_MasterConfigTypeDef sMasterConfig1 = {0};
	TIM_MasterConfigTypeDef sMasterConfig2 = {0};
	//TIM Slave configuration structure
	TIM_ClockConfigTypeDef sClockSourceConfig1 = {0};
	TIM_ClockConfigTypeDef sClockSourceConfig2 = {0};
	//Time PWM structure
	TIM_OC_InitTypeDef sConfigOC1 = {0};
	TIM_OC_InitTypeDef sConfigOC2 = {0};
	//PWM pin setting
	__HAL_RCC_TIM4_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	PWM_GPIO_Init();
	// timer clock enable


	//PWM1 Init
	PWM1_TIM_Period = msPeriod1;
	htimpwm1.Instance = PWM1_TIM;
	htimpwm1.Init.Prescaler = PWM1_TIM_Prescaler-1;
	htimpwm1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimpwm1.Init.Period = msPeriod1-1;
	htimpwm1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htimpwm1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htimpwm1) != HAL_OK)
	{
		Error_PWM_Handler();
	}
	//PWM clock setting
	sClockSourceConfig1.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htimpwm1, &sClockSourceConfig1) != HAL_OK)
	{
		Error_PWM_Handler();
	}

	if (HAL_TIM_PWM_Init(&htimpwm1) != HAL_OK)
	{
		Error_PWM_Handler();
	}
	//Triger setting
	sMasterConfig1.MasterOutputTrigger = TIM_TRGO_RESET;
	//Slave setting
	sMasterConfig1.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	if (HAL_TIMEx_MasterConfigSynchronization(&htimpwm1, &sMasterConfig1) != HAL_OK)
	{
		Error_PWM_Handler();
	}

	sConfigOC1.OCMode = TIM_OCMODE_PWM1;
	sConfigOC1.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC1.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC1.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	//sConfigOC1.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	//sConfigOC1.OCIdleState  = TIM_OCIDLESTATE_RESET;
	sConfigOC1.Pulse =0;
	if (HAL_TIM_PWM_ConfigChannel(&htimpwm1, &sConfigOC1, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_PWM_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htimpwm1, &sConfigOC1, TIM_CHANNEL_2) != HAL_OK)
		{
			Error_PWM_Handler();
		}
	if (HAL_TIM_PWM_ConfigChannel(&htimpwm1, &sConfigOC1, TIM_CHANNEL_3) != HAL_OK)
		{
			Error_PWM_Handler();
		}
	if (HAL_TIM_PWM_ConfigChannel(&htimpwm1, &sConfigOC1, TIM_CHANNEL_4) != HAL_OK)
		{
			Error_PWM_Handler();
		}
	// PWM2 Init

	PWM2_TIM_Period = msPeriod2;
	htimpwm2.Instance = PWM2_TIM;
	htimpwm2.Init.Prescaler = PWM2_TIM_Prescaler-1;
	htimpwm2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimpwm2.Init.Period = msPeriod2-1;
	htimpwm2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htimpwm2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htimpwm2) != HAL_OK)
	{
		Error_PWM_Handler();
	}
	//PWM clock setting
	sClockSourceConfig2.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htimpwm2, &sClockSourceConfig2) != HAL_OK)
	{
		Error_PWM_Handler();
	}

	if (HAL_TIM_PWM_Init(&htimpwm2) != HAL_OK)
	{
		Error_PWM_Handler();
	}
	//Triger setting
	sMasterConfig2.MasterOutputTrigger = TIM_TRGO_RESET;
	//Slave setting
	sMasterConfig2.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	if (HAL_TIMEx_MasterConfigSynchronization(&htimpwm2, &sMasterConfig2) != HAL_OK)
	{
		Error_PWM_Handler();
	}

	sConfigOC2.OCMode = TIM_OCMODE_PWM1;
	sConfigOC2.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC2.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC2.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfigOC2.Pulse =0;
	if (HAL_TIM_PWM_ConfigChannel(&htimpwm2, &sConfigOC2, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_PWM_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htimpwm2, &sConfigOC2, TIM_CHANNEL_2) != HAL_OK)
	{
			Error_PWM_Handler();
	}

}


void PWM_Open(PWM Pwm, float Percent)
{
	//PWM buffer set
	uint16_t PWM_buffer;
	PWM_buffer = Duty_calculate(Percent);
	//Seclect Channel and Duty set
	switch(Pwm)
	{
		case PWM1_1:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_1 ,PWM_buffer); // PWM Input Duty
			HAL_TIM_PWM_Start(&htimpwm1, TIM_CHANNEL_1);
			break;
		case PWM1_2:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_2,PWM_buffer);
			HAL_TIM_PWM_Start(&htimpwm1, TIM_CHANNEL_2);
			break;
		case PWM1_3:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_3,PWM_buffer);
			HAL_TIM_PWM_Start(&htimpwm1, TIM_CHANNEL_3);
			break;
		case PWM1_4:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_4,PWM_buffer);
			HAL_TIM_PWM_Start(&htimpwm1, TIM_CHANNEL_4);
			break;
		case PWM2_1:
			__HAL_TIM_SET_COMPARE(&htimpwm2,TIM_CHANNEL_1,PWM_buffer); // PWM Input Duty
			HAL_TIM_PWM_Start(&htimpwm2, TIM_CHANNEL_1);
			break;
		case PWM2_2:
			__HAL_TIM_SET_COMPARE(&htimpwm2,TIM_CHANNEL_2,PWM_buffer); // PWM Input Duty
			HAL_TIM_PWM_Start(&htimpwm2, TIM_CHANNEL_2);
			break;
		default:
			break;
	}

}

void PWM_Close(PWM Pwm)
{
	//Select PWM Channel
	switch(Pwm)
	{
		case PWM1_1:
			HAL_TIM_PWM_Stop(&htimpwm1, TIM_CHANNEL_1);
			break;

		case PWM1_2:
			HAL_TIM_PWM_Stop(&htimpwm1, TIM_CHANNEL_2);
			break;

		case PWM1_3:
			HAL_TIM_PWM_Stop(&htimpwm1, TIM_CHANNEL_3);
			break;

		case PWM1_4:
			HAL_TIM_PWM_Stop(&htimpwm1, TIM_CHANNEL_4);
			break;
		case PWM2_1:
			HAL_TIM_PWM_Stop(&htimpwm2, TIM_CHANNEL_1);
			break;

		case PWM2_2:
			HAL_TIM_PWM_Stop(&htimpwm2, TIM_CHANNEL_2);
			break;

		default:
			break;
	}
}


static void PWM_GPIO_Init(void)
{
	// GPIO Structure
	GPIO_InitTypeDef GPIO_InitStruct1 = {0};
	GPIO_InitTypeDef GPIO_InitStruct2 = {0};
	GPIO_InitTypeDef GPIO_InitStruct3 = {0};
	//GPIO Clock Set
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	//GPIO Pin Reset
	HAL_GPIO_WritePin(GPIOB, PWM1_1_Pin|PWM1_2_Pin|PWM1_3_Pin|PWM1_4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, PWM2_1_Pin|PWM2_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, PWM_DIR1_Pin|PWM_DIR2_Pin, GPIO_PIN_RESET);

	//GPIO Init
	GPIO_InitStruct1.Pin = PWM1_1_Pin|PWM1_2_Pin|PWM1_3_Pin|PWM1_4_Pin;
	GPIO_InitStruct1.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct1.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct1);

	GPIO_InitStruct2.Pin = PWM2_1_Pin|PWM2_2_Pin;
	GPIO_InitStruct2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct2.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStruct2);

	//Dir PIN
	GPIO_InitStruct3.Pin = PWM_DIR1_Pin|PWM_DIR2_Pin;
	GPIO_InitStruct3.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct3.Pull = GPIO_NOPULL;
	GPIO_InitStruct3.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC,&GPIO_InitStruct3);

}

void PWM_Duty_Set(PWM Pwm,uint8_t Data_num, float Data_value)
{
	//Duty Change
	uint16_t PWM_buffer;
	// Calculate Duty
	float percent_duty_value =0;

	if(Data_num == 0)
		percent_duty_value = Angle_duty_cal(Data_value);
	else if(Data_num ==1)
		percent_duty_value = Speed_duty_cal(Data_value);
	else
		percent_duty_value = Data_value;

	PWM_buffer = Duty_calculate(percent_duty_value);
	//Select PWM Channel
	switch(Pwm)
	{
		case PWM1_1:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_1,PWM_buffer);
			break;
		case PWM1_2:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_2,PWM_buffer);
			break;
		case PWM1_3:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_3,PWM_buffer);
			break;
		case PWM1_4:
			__HAL_TIM_SET_COMPARE(&htimpwm1,TIM_CHANNEL_4,PWM_buffer);
			break;
		case PWM2_1:
			__HAL_TIM_SET_COMPARE(&htimpwm2,TIM_CHANNEL_1,PWM_buffer);
			break;
		case PWM2_2:
			__HAL_TIM_SET_COMPARE(&htimpwm2,TIM_CHANNEL_2,PWM_buffer);
			break;
		default:
			break;
	}
}




float Speed_duty_cal(float speed)
{


}
void Angle_Value_Set(float inclination_value, float bias_value, float angle_min_value, float angle_max_value)
{
	// 서보모터의 1도당 듀티 퍼센트값
	INCLINATION = inclination_value;
	// 초기 0도 값
	BIAS = bias_value;
	// 각도 MAX값
	ANGLE_MIN = angle_min_value;
	// 각도 MIN값
	ANGLE_MAX = angle_max_value;
}


float Angle_duty_cal(float angle)
{
	// 엥글 각도 범위 조정 최소값 최대값
	if( ANGLE_MIN <= angle <= ANGLE_MAX)
		//
	return (angle*INCLINATION)+BIAS;
}


uint16_t Duty_calculate(float Persent)
{
	//  펄스를 퍼센트 계산하여 듀터 퍼센트로 변환
	return (uint16_t)((PWM1_TIM_Period*Persent)/100)-1;
}


void DIR_Change(uint8_t Dirnum, uint8_t Direction)
{
	if(Direction)
	HAL_GPIO_WritePin(DIR_PortTable[Dirnum].Port, DIR_PortTable[Dirnum].Pin, GPIO_PIN_SET);
	else
	HAL_GPIO_WritePin(DIR_PortTable[Dirnum].Port, DIR_PortTable[Dirnum].Pin, GPIO_PIN_RESET);

}



void Error_PWM_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
