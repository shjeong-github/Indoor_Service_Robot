/*
 * led.c
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */


#include "led.h"

const LED_PortDef LED_PortTable[] = {{LED1_Port, LED1_Pin},	{LED2_Port, LED2_Pin}, {LED3_Port, LED3_Pin}, {LED4_Port, LED4_Pin}};

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : PE0,1,2,5  */
	GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(GPIOE, LED4_Pin,GPIO_PIN_SET);  // 1 ->4 로 수정 PE10번 핀

}


void LED_On(uint8_t Data)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		if(Data & (1 << i))
		{
			HAL_GPIO_WritePin(LED_PortTable[i].Port, LED_PortTable[i].Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(LED_PortTable[i].Port, LED_PortTable[i].Pin, GPIO_PIN_RESET);
		}
	}
}

void LED_On_Unit(uint8_t Position, uint8_t OnOff)
{
	if(OnOff)
		HAL_GPIO_WritePin(LED_PortTable[Position-1].Port, LED_PortTable[Position-1].Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LED_PortTable[Position-1].Port, LED_PortTable[Position-1].Pin, GPIO_PIN_RESET);
}
