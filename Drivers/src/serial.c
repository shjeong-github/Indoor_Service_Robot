/*
 * serial.c
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#include "serial.h"
#include "stdio.h"

static void USART2_GPIO_Init(void);
static void USART3_GPIO_Init(void);
static void USART3_HALF_DUFLEX_GPIO_Init(void);

uint8_t Rx1_buffer;
uint8_t Rx2_buffer;
uint8_t Rx3_buffer;
uint8_t Rx4_buffer;


// Global Variable

SERIAL_CALLBACK SerialCallbackTable[SERIAL_PORT_MAX] = {(void *)0, };
const uint8_t *HexaString = "0123456789ABCDEF";

uint8_t uart2_tx[10] = "123456";

void Serial1_Init(void)
{
	//시리얼 GPIO INIT
	USART2_GPIO_Init();
	// 시리얼 INIT
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Serial_Handler();
	}
}
void Serial2_Init(void)
{
	//시리얼 GPIO INIT
	USART3_GPIO_Init();

	// 시리얼 INIT
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Serial_Handler();
	}
}





void Serial_Open(SERIAL_PORT Port, uint32_t Baudrate, SERIAL_CALLBACK Callback)  //SERIAL_CALLBACK Callback
{
	// 시리얼 포트 확인
	if(Port == SERIAL_PORT1)
	{
		// 시리얼 보드레이트
		huart2.Init.BaudRate = Baudrate;
		if (HAL_UART_Init(&huart2) != HAL_OK)
		{
			Error_Serial_Handler();
		}
		// 시리얼 인터럽드 순위 설정
		HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
		// 시리얼 인터럽트 활성화
		HAL_NVIC_EnableIRQ(USART2_IRQn);
		// 시리얼 수신 인터럽트 활성화
		HAL_UART_Receive_IT(&huart2, &Rx1_buffer, 1);
	}
	else if(Port == SERIAL_PORT2)
	{
		huart3.Init.BaudRate = Baudrate;
		if (HAL_UART_Init(&huart3) != HAL_OK)
		{
			Error_Serial_Handler();
		}
		HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
		HAL_UART_Receive_IT(&huart3, &Rx2_buffer, 1);
	}


	SerialCallbackTable[Port] = Callback;
}

void Serial_Close(SERIAL_PORT Port)
{

	switch(Port)
	{
		case SERIAL_PORT1 :
			HAL_NVIC_DisableIRQ(USART2_IRQn);
			break;
		case SERIAL_PORT2 :
			HAL_NVIC_DisableIRQ(USART3_IRQn);
			break;
		/*case SERIAL_PORT3 :
			HAL_NVIC_DisableIRQ(USART3_IRQn);*/
		default :
			break;
	}
	//callback close
	SerialCallbackTable[Port] = (void *)0;
}


void Serial_WriteByte(SERIAL_PORT Port, uint8_t Data)
{
	USART_TypeDef *USART_Port;
	UART_HandleTypeDef USART;

	switch(Port)
	{
		case SERIAL_PORT1:
			USART_Port = USART2;
			break;
		case SERIAL_PORT2 :
			USART_Port = USART3;
			break;
		default :
			return;
	}

}

void Serial_WriteHexa(SERIAL_PORT Port, uint32_t Data)
{
	uint8_t Temp , i;

	//Serial_WriteByte(Port, '0');
	//Serial_WriteByte(Port, 'x');

	for(i = 0;i < 8; i++)
	{
		Temp = (Data >> (28 - 4*i))& 0x0F;
		Temp = HexaString[Temp];
		//Serial_WriteByte(Port, Temp);
	}
}

void Serial_WriteString(SERIAL_PORT Port, uint8_t* String)
{
	while(*String != 0)
	{
		Serial_WriteByte(Port, *String);
		String++;
	}
}

void Serial_WriteInt(SERIAL_PORT Port, uint16_t Data)
{
	Serial_Send(Port,'0'+Data/10000   ,1);
	Serial_Send(Port,'0'+Data/ 1000%10,1);
	Serial_Send(Port,'0'+Data/  100%10,1);
	Serial_Send(Port,'0'+Data/   10%10,1);
	Serial_Send(Port,'0'+Data      %10,1);

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		// 시리얼 CR1 레지스터 RXNEIE(RX NOT ENABLE INTERRUPT) 비활성화 확인 ,데이터 1개를 수신하면 인터럽트를 발생시킨다.
		if((USART2->CR1 & USART_CR1_RXNEIE) == RESET )
		{
				// 콜백 함수 유무 확인
				if(SerialCallbackTable[SERIAL_PORT1] != (void *)0)
				{
					// 콜백함수 실행
					SerialCallbackTable[SERIAL_PORT1]();
				}
		}
	}
	if (huart->Instance == USART3) {
		if((USART3->CR1 & USART_CR1_RXNEIE) == RESET )
		{
			// 콜백 함수 유무 확인
			if(SerialCallbackTable[SERIAL_PORT2] != (void *)0)
				{
					// 콜백함수 실행
					SerialCallbackTable[SERIAL_PORT2]();
				}
		}

	}
}


void USART2_IRQHandler(void)
{
	// USART2 인터럽트 작동
	HAL_UART_IRQHandler(&huart2);

	// 인터럽트 종료후 수신 대기 인터럽드 작동
	HAL_UART_Receive_IT(&huart2,&Rx1_buffer, 1);

}


void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */
  HAL_UART_Receive_IT(&huart3,&Rx2_buffer, 1);
  /* USER CODE END USART3_IRQn 1 */
}

uint8_t Serial_Data_GET(SERIAL_PORT Port)
{
	// 시리얼 데이터 리턴
	switch(Port)
	{	case SERIAL_PORT1:
		return Rx1_buffer;
		case SERIAL_PORT2:
		return Rx2_buffer;
		case SERIAL_PORT3:
		return Rx3_buffer;
		case SERIAL_PORT4:
		return Rx4_buffer;
		default:
		break;
	}

}

void Serial_Send(SERIAL_PORT Port , uint8_t *Data, uint16_t Size)
{
	// 시리얼 데이터 전송
	if(Port ==0)
	HAL_UART_Transmit(&huart2, Data, Size,100);
	else
	HAL_UART_Transmit(&huart3, Data, Size, 100);
}





static void USART2_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_usart2_tx = {0};
	GPIO_InitTypeDef GPIO_InitStruct_usart2_rx = {0};

	/* Peripheral clock enable */
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**USART2 GPIO Configuration
	PA2     ------> USART2_TX
	PA3     ------> USART2_RX
	*/
	GPIO_InitStruct_usart2_tx.Pin = GPIO_PIN_2;
	GPIO_InitStruct_usart2_tx.Mode = GPIO_MODE_AF_PP;  //GPIO_MODE_AF_PP
	GPIO_InitStruct_usart2_tx.Speed = GPIO_SPEED_FREQ_HIGH; //GPIO_SPEED_FREQ_MEDIUM GPIO_SPEED_FREQ_HIGH
	GPIO_InitStruct_usart2_tx.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_usart2_tx);

	GPIO_InitStruct_usart2_rx.Pin = GPIO_PIN_3;
	GPIO_InitStruct_usart2_rx.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct_usart2_rx.Pull = GPIO_PULLUP;
	GPIO_InitStruct_usart2_rx.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_usart2_rx);

}
static void USART3_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_usart3_tx = {0};
	GPIO_InitTypeDef GPIO_InitStruct_usart3_rx = {0};

	__HAL_RCC_USART3_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/**USART3 GPIO Configuration
	PB10     ------> USART3_TX
	PB11     ------> USART3_RX
	*/
	GPIO_InitStruct_usart3_tx.Pin = GPIO_PIN_10;
	GPIO_InitStruct_usart3_tx.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct_usart3_tx.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct_usart3_tx.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_usart3_tx);

	GPIO_InitStruct_usart3_rx.Pin = GPIO_PIN_11;
	GPIO_InitStruct_usart3_rx.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct_usart3_rx.Pull = GPIO_PULLUP;
	GPIO_InitStruct_usart3_rx.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_usart3_rx);


}





void Error_Serial_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
