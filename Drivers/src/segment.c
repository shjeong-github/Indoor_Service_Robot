/*
 * segment.c
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#include "segment.h"

static uint8_t Segment_Pin_Open[]={63,6,91,79,102,109,125,7,127,103,119,124,57,94,121,113}; // 0~9 sevensegnum
static uint16_t u16_segmentvalue;

Segment_PORT_Def Segment_PortTable[] =
	   {{Segment1_Port,Segment1_Pin},
		{Segment2_Port,Segment2_Pin},
		{Segment3_Port,Segment3_Pin},
		{Segment4_Port,Segment4_Pin},
		{Segment5_Port,Segment5_Pin},
		{Segment6_Port,Segment6_Pin},
		{Segment7_Port,Segment7_Pin},
		{Segment8_Port,Segment8_Pin}};

Segment_PORT_Def Segment_EnableTable[] =
	   {{SegmentA_Port,SegmentA_Pin},
	    {SegmentB_Port,SegmentB_Pin},
	    {SegmentC_Port,SegmentC_Pin}};


void Segment_Init(void)
{
	//GPOI Init structure
	GPIO_InitTypeDef GPIO_InitStruct_SEG = {0};
	GPIO_InitTypeDef GPIO_InitStruct_ENB = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 세그먼트 핀 기본 설정
	HAL_GPIO_WritePin(Segment1_Port, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin|Segment8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SegmentA_Port, SegmentA_Pin|SegmentB_Pin|SegmentC_Pin,GPIO_PIN_RESET);
	// 세그먼트 기능 설정
	GPIO_InitStruct_SEG.Pin = Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin|Segment8_Pin;
	GPIO_InitStruct_SEG.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_SEG.Pull = GPIO_NOPULL;
	GPIO_InitStruct_SEG.Speed = GPIO_SPEED_FREQ_LOW;

	GPIO_InitStruct_ENB.Pin = SegmentA_Pin|SegmentB_Pin|SegmentC_Pin;
	GPIO_InitStruct_ENB.Mode= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_ENB.Pull= GPIO_NOPULL;
	GPIO_InitStruct_ENB.Speed= GPIO_SPEED_FREQ_LOW;

	// 세그먼트 핀 정보 입력
	HAL_GPIO_Init(Segment1_Port, &GPIO_InitStruct_SEG);
	HAL_GPIO_Init(SegmentA_Port, &GPIO_InitStruct_ENB);
	// 세그먼트 핀 작동 시작
	HAL_GPIO_WritePin(Segment1_Port, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin|Segment8_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SegmentA_Port, SegmentA_Pin|SegmentB_Pin|SegmentC_Pin,GPIO_PIN_SET);
	// 초기값 설정
	Segment_Set_Value(0);
}


void Segment_On(uint8_t u8_segnum)
{
	for(uint8_t i = 0; i < NUM_LED; i++)
	{
		// 세그먼트 비트 ON,OFF 유무 확인
		if((u8_segnum) & 1U)
		{
			// 1인 비트 ON
			HAL_GPIO_WritePin(Segment1_Port,Segment_PortTable[i].pin,SEGMENT_ON);
		}
		else
		{
			// 0인 비트 OFF
			HAL_GPIO_WritePin(Segment1_Port,Segment_PortTable[i].pin,SEGMENT_OFF);
		}
		//다음 비트 넘거가기
		u8_segnum = u8_segnum >> 1;
	}
}

uint16_t Segment_Get_Value(void)
{
	// 입력받은 세그먼트 값
	return u16_segmentvalue;
}

void Segment_Set_Value(uint16_t u16_input_segmentvalue)
{
	// 세그먼트 숫자정보 값 할당
	u16_segmentvalue = u16_input_segmentvalue;
}

void Segment_Power_ON(void)
{
	// 세그먼트 전원 플레그
   static uint8_t flag_segment =0;
   // 16비트 세그먼트 1000이하  숫자정보값 할당
   u16_segmentvalue = u16_segmentvalue%1000;
      if(flag_segment ==0)
      {
         HAL_GPIO_WritePin(SegmentA_Port, SegmentA_Pin, GPIO_PIN_SET);
         HAL_GPIO_WritePin(SegmentB_Port, SegmentB_Pin, GPIO_PIN_RESET);
         HAL_GPIO_WritePin(SegmentC_Port, SegmentC_Pin, GPIO_PIN_RESET);
         Segment_On(Segment_Pin_Open[u16_segmentvalue%10]);
         flag_segment =1;
      }
      else if(flag_segment ==1)
      {
		 HAL_GPIO_WritePin(SegmentA_Port, SegmentA_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(SegmentB_Port, SegmentB_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(SegmentC_Port, SegmentC_Pin, GPIO_PIN_RESET);
         Segment_On(Segment_Pin_Open[u16_segmentvalue/10%10]);
         flag_segment = 2;
      }
      else
      {
    	 HAL_GPIO_WritePin(SegmentA_Port, SegmentA_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(SegmentB_Port, SegmentB_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(SegmentC_Port, SegmentC_Pin, GPIO_PIN_SET);
         Segment_On(Segment_Pin_Open[u16_segmentvalue/100%10]);
         flag_segment = 0;
      }
}

void Segment_Power_OFF(void)
{
	 HAL_GPIO_WritePin(SegmentA_Port, SegmentA_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(SegmentB_Port, SegmentB_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(SegmentC_Port, SegmentC_Pin, GPIO_PIN_RESET);
}



