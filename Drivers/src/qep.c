/*
 * qep.c
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */


#include "qep.h"
#include "segment.h"
//Global Variable
static volatile int16_t oldEncoder;
static volatile int16_t Encoder;
volatile int16_t Count;
volatile int16_t CountTotal;
static void QEP_GPIO_Init(void);
static void QEP_GPIO_DEInit(void);


float Time=0;
// 배수 전역변수
uint8_t multiple=0;
// 엔코더 카운트 값
uint16_t Encoder_count =0 ;
#define PI 3.1415926535897932384626433832795

void QEP_Read(void)
{
	//Save previous value
	oldEncoder = Encoder;
	//Save present value
	Encoder = TIM1->CNT;
}

void QEP_Reset(void)
{
	//Interrupt Cutoff
	 __disable_irq();
	//Reset Value
	oldEncoder = 0;
	CountTotal = 0;
	Encoder = 0;
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	//Interrupt On
	__enable_irq();
}

int16_t QEP_Get(void)
{
	// 현재 엔코더 카운트값
	return Encoder;
}

void QEP_Init(void)
{

	/* USER CODE BEGIN TIM1_Init 0 */

	  /* USER CODE END TIM1_Init 0 */
	  //TIM_Encoder_InitTypeDef	Structure
	  TIM_Encoder_InitTypeDef sConfig = {0};
	  //TIM_MasterConfigTypeDef	Structure
	  TIM_MasterConfigTypeDef sMasterConfig = {0};

	  QEP_GPIO_Init();
	  __HAL_RCC_TIM1_CLK_ENABLE();
	  /* USER CODE BEGIN TIM1_Init 1 */

	  /* USER CODE END TIM1_Init 1 */
	  htim1.Instance = TIM1;
	  htim1.Init.Prescaler = 0;
	  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim1.Init.Period = 65535;
	  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; //TIM_AUTORELOAD_PRELOAD_ENABLE
	  htim1.Init.RepetitionCounter = 0;

	  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
	  sConfig.IC1Polarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE; //TIM_INPUTCHANNELPOLARITY_BOTHEDGE
	  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	  sConfig.IC1Filter = 0;
	  sConfig.IC2Polarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
	  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	  sConfig.IC2Filter = 0;
	  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
	  {
	    Error_qep_Handler();
	  }
	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	  {
		 Error_qep_Handler();
	  }

	  // QEP Start max count set
	  __HAL_TIM_SET_AUTORELOAD(&htim1, 65535); //0xffff
	  //Encoder start
	  HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);

	  QEP_Reset();


}

static void QEP_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};



	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**TIM1 GPIO Configuration
	PA8     ------> TIM1_CH1
	PA9     ------> TIM1_CH2
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


static void QEP_GPIO_DeInit(void)
{
	/* Peripheral clock disable */
	__HAL_RCC_TIM1_CLK_DISABLE();

	/**TIM1 GPIO Configuration
	PA8     ------> TIM1_CH1
	PA9     ------> TIM1_CH2
	*/
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_9);
}




void Encoder_value_Set(uint16_t Encoder_count_value,uint8_t multiple_value,float Time_value)
{
	// 속도, 계산할때의 시간 기준 시간 값
	Time = Time_value / 1000;
	// 엔코더의 배수 값
	multiple=multiple_value;
	// 엔코더의 현재 카운트 된값
	Encoder_count =Encoder_count_value;
}


uint16_t Encoder_angular_velocity(void)
{
	static float Encoder_Param = 0;
	//엔코더의 카운트 변수
	uint16_t edge = 0;
	// 현제 엔코더가 측정한 각속도 변수
	uint16_t angular_velocity =0;
	//엔코더 각속도 계산1
	Encoder_Param =	2 * Encoder_count * multiple * PI / Time;
	// 엔코더 카운트값 받기
	edge = QEP_Get();
	// 엔코더 각속도 계산2
	angular_velocity = (uint16_t)(Encoder_Param*edge);
	return angular_velocity;
}


uint16_t Encoder_speed(void)
{
	//엔코더의 카운트 변수
	uint16_t edge =0;
	// 엔코더 스피드 변수
	uint16_t Encoder_Speed =0;
	// 엔코더 카운트값 받기
	edge = QEP_Get();
	// 엔코더 속도 계산
	Encoder_Speed = (uint16_t)((60*edge)/(Time*Encoder_count*multiple));
	return Encoder_Speed;


}





void Error_qep_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
