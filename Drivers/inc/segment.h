/*
 * segment.h
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#ifndef __SEGMENT_H_
#define __SEGMENT_H_

#include "stm32f1xx.h"

#define Segment1_Port 				GPIOC
#define Segment1_Pin				GPIO_PIN_9

#define Segment2_Port 				GPIOC
#define Segment2_Pin				GPIO_PIN_8

#define Segment3_Port 				GPIOC
#define Segment3_Pin				GPIO_PIN_3

#define Segment4_Port 				GPIOC
#define Segment4_Pin				GPIO_PIN_1

#define Segment5_Port 				GPIOC
#define Segment5_Pin				GPIO_PIN_0

#define Segment6_Port 				GPIOC
#define Segment6_Pin				GPIO_PIN_7

#define Segment7_Port 				GPIOC
#define Segment7_Pin				GPIO_PIN_6

#define Segment8_Port				GPIOC
#define Segment8_Pin 				GPIO_PIN_2

#define SegmentA_Port				GPIOA
#define SegmentA_Pin 				GPIO_PIN_5

#define SegmentB_Port				GPIOA
#define SegmentB_Pin				GPIO_PIN_6

#define SegmentC_Port				GPIOA
#define SegmentC_Pin 				GPIO_PIN_7

#define SEGMENT_ON 					0
#define SEGMENT_OFF 				1

#define NUM_LED						8

typedef struct {

	GPIO_TypeDef *port;
	uint16_t pin;

}Segment_PORT_Def;
// Segment_Init
void Segment_Init(void);
// present value set
void Segment_Set_Value(uint16_t u16_input_segmentvalue);
// present value get
uint16_t Segment_Get_Value(void);
// segment on
void Segment_On(uint8_t u8_segnum);
// segment power on
void Segment_Power_ON(void);
// segment power off
void Segment_Power_OFF(void);







#ifdef __cplusplus
}
#endif



#endif /* __SEGMENT_H_ */
