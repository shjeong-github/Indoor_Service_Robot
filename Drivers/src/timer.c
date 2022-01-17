/*
 * timer.c
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#include "timer.h"

static ALARM_CALLBACK AlarmCallbackTable[ALARM_MAX] = {(void *)0,};
static uint16_t AlarmPeriodTable[ALARM_MAX] = {0, };



void Timer_Init(void)
{
	//TIM_MasterConfigTypeDef structure
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	//Tim Init
	__HAL_RCC_TIM3_CLK_ENABLE();

	htim3.Instance = BASE_TIM;
	htim3.Init.Prescaler = BASE_TIM_Prescaler-1;   				//840-1
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = BASE_TIM_Period;		//100-1
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Timer_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Timer_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Timer_Handler();
	}

	// Timer Interrupt Enable
	HAL_NVIC_EnableIRQ(BAES_TIM_IRQn);
	HAL_NVIC_SetPriority(BAES_TIM_IRQn, BAES_TIM_IT_PreemptionPriority, BAES_TIM_IT_SubPriority);
	HAL_NVIC_GetActive(BAES_TIM_IRQn);

	//timer start
	HAL_TIM_Base_Start_IT(&htim3);
}


void Alarm_Open(ALARM Alarm, uint16_t msPeriod, ALARM_CALLBACK Callback)
{
	// 알람 Period 설정
	AlarmPeriodTable[Alarm] = msPeriod;
	// 알람 콜백 함수 저장
	AlarmCallbackTable[Alarm] = Callback;
}

void Alarm_Close(ALARM Alarm)
{
	//알람 함수 종료
	AlarmPeriodTable[Alarm] = 0;
	AlarmCallbackTable[Alarm] = (void *)0;
}


// 타이머 인터럽트 함수
void TIM3_IRQHandler(void)
{
	static uint32_t Time = 0;
	uint8_t i;
	Time++;

	// Clear the Timer Update pending bit
	HAL_TIM_IRQHandler(&htim3);

	for(i = 0;i < ALARM_MAX;i++)
	{
		// 알람 함수 유무 확인
		if(AlarmPeriodTable[i] != 0)
		{
			// 알람 번호 순차 실행 확인
			if((Time % AlarmPeriodTable[i]) == 0)
			{
				// 알람 배열안에 함수 유무 확인
				if(AlarmCallbackTable[i] != (void *)0)
				{
					// 함수 실행
					AlarmCallbackTable[i]();
				}
			}
		}
	}
}



void Error_Timer_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
