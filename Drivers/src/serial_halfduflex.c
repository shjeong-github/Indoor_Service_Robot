/*
 * serial_halfduflex.c
 *
 *  Created on: Jan 28, 2022
 *      Author: JeongSeongHo
 */

#include "serial_halfduflex.h"
#include "stdio.h"

SERIAL_HALFDUFLEX_CALLBACK Serial_HalfDuflex_CallbackTable[SERIAL_HALFDUFLEX_PORT_MAX] = {(void *)0, };
static void USART3_HALF_DUFLEX_GPIO_Init(void);


void Serial_HalfDuflex_Init(void)
{
	USART3_HALF_DUFLEX_GPIO_Init();

	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_HalfDuplex_Init(&huart3) != HAL_OK)
	{
		Error_Serial_HALF_DUFLEX_Handler();
	}


}

void Serial_HalfDuflex_Open(SERIAL_HALFDUFLEX_PORT Port, uint32_t Baudrate, SERIAL_HALFDUFLEX_CALLBACK Callback)
{
	// 시리얼 포트 확인

	if(Port == SERIAL_HALFDUFLEX_PORT1)
	{
		huart3.Init.BaudRate = Baudrate;
		if (HAL_HalfDuplex_Init(&huart3) != HAL_OK)
		{
			Error_Serial_HALF_DUFLEX_Handler();
		}
		HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);

	}

	Serial_HalfDuflex_CallbackTable[Port] = Callback;
}

void Serial_HalfDuflex_Close(SERIAL_HALFDUFLEX_PORT Port)
{

	switch(Port)
	{
		case SERIAL_HALFDUFLEX_PORT1 :
			HAL_NVIC_DisableIRQ(USART3_IRQn);
			break;
		default :
			break;
	}
	//callback close
	Serial_HalfDuflex_CallbackTable[Port] = (void *)0;
}


static void USART3_HALF_DUFLEX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_HD ={0};
	__HAL_RCC_USART3_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct_HD.Pin = GPIO_PIN_10;
	GPIO_InitStruct_HD.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct_HD.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_HD);


}













void Error_Serial_HALF_DUFLEX_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */



}



