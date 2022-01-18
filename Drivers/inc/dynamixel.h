/*
 * dynamixel.h
 *
 *  Created on: Oct 28, 2021
 *      Author: JeongSeongHo
 */

#ifndef __DYNAMIXEL_H_
#define __DYNAMIXEL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include <stdlib.h>

 void READ_DATA_Instruct(uint8_t *packet_buffer,uint8_t id, uint8_t param_address ,uint8_t param1);
 void WRITE_DATA_Instruct(uint8_t *packet_buffer, uint8_t id, uint8_t param_address ,uint16_t param1, uint16_t param2 );
 void SYNC_WRITE_Instruct(uint8_t *packet_buffer, uint8_t param_address,
			uint8_t id1, uint16_t param1_position, uint16_t param1_speed,
			uint8_t id2, uint16_t param2_position, uint16_t param2_speed,
			uint8_t id3, uint16_t param3_position, uint16_t param3_speed,
			uint8_t id4, uint16_t param4_position, uint16_t param4_speed);
 //uint8_t Dynamix_Length(uint8_t param_length);
 uint8_t Dynamix_Checksum(uint8_t *packet_arrangement, uint8_t size);
 void Dynamix_Dec_WriteHexa(uint8_t *data_buffer,uint8_t dec);
 void Dynamix_WriteHexa(uint8_t *data_buffer,uint16_t hex);
 void Buffer_Data_Set(uint8_t *buffer, uint8_t *packet_data,uint8_t size);
 void Buffer_Allocate_Divide_Hex(uint8_t start_buffer_index, uint8_t *buffer, uint8_t *data);








#ifdef __cplusplus
 extern "C" {
#endif

#endif /* __DYNAMIXEL_H_ */
