/*
 * dynamixel.c
 *
 *  Created on: Oct 28, 2021
 *      Author: JeongSeongHo
 */

#include "dynamixel.h"

//0x01 Ping, 0x02 Read_data 0x03 Write_data 0x04 Reg_write 0x05 action 0x06 reset 0x083 sync write 0x092 bulk read (MX시리즈만 가능 )
uint8_t dynamix_instruction[8]= {0x01,0x02,0x03,0x04,0x05,0x06,0x83,0x92};
// id 0x00~ 0xFE 0부터 253까지
uint8_t dynamix_id =0;
const uint8_t *HexaString_DEC = "0123456789ABCDEF";

void READ_DATA_Instruct(uint8_t *packet_buffer,uint8_t id, uint8_t param_address ,uint8_t param1)
{

	uint8_t instruction_packet[8] = {0xFF,0xFF,id ,0x04, 0x02,param_address,param1,0x00};
	uint8_t size= sizeof(instruction_packet);
	instruction_packet[7] = Dynamix_Checksum(instruction_packet,size);
	Buffer_Data_Set(packet_buffer,instruction_packet,size);
}

void WRITE_DATA_Instruct(uint8_t *packet_buffer,uint8_t id, uint8_t param_address ,uint16_t param1, uint16_t param2 )
{
	uint8_t *data = (uint8_t*)malloc(2*sizeof(uint8_t)) ;
	if(param_address < 0x19)
	{
		uint8_t instruction_packet[8] = {0xFF, 0XFF, id, 0x04, 0x03 ,param_address, (uint8_t)param1, 0x00};
		uint8_t size= sizeof(instruction_packet);
		instruction_packet[7] = Dynamix_Checksum(instruction_packet,size);
		Buffer_Data_Set(packet_buffer,instruction_packet,size);
	}
	else if(param_address>0x19 && param2==0x00)
	{
		uint8_t instruction_packet[9] ={0xFF, 0XFF, id, 0x05, 0x03 ,param_address, 0x00,0x00, 0x00};
		uint8_t size= sizeof(instruction_packet);
		Dynamix_WriteHexa(data, param1);
		Buffer_Allocate_Divide_Hex(6,instruction_packet,data);
		instruction_packet[8] = Dynamix_Checksum(instruction_packet,size);
		Buffer_Data_Set(packet_buffer,instruction_packet,size);
	}
	else
	{
		uint8_t instruction_packet[11] ={0xFF, 0XFF, id, 0x07, 0x03 ,param_address,0x00 ,0x00,0x00,0x00, 0x00};
		uint8_t size= sizeof(instruction_packet);
		Dynamix_WriteHexa(data, param1);
		Buffer_Allocate_Divide_Hex(6,instruction_packet,data);
		Dynamix_WriteHexa(data, param2);
		Buffer_Allocate_Divide_Hex(8,instruction_packet,data);
		instruction_packet[10] = Dynamix_Checksum(instruction_packet,size);
		Buffer_Data_Set(packet_buffer,instruction_packet,size);
	}
	free(data);
}

void SYNC_WRITE_Instruct(uint8_t *packet_buffer, uint8_t param_address,
		uint8_t id1, uint16_t param1_position, uint16_t param1_speed,
		uint8_t id2, uint16_t param2_position, uint16_t param2_speed,
		uint8_t id3, uint16_t param3_position, uint16_t param3_speed,
		uint8_t id4, uint16_t param4_position, uint16_t param4_speed)
{
	uint8_t instruction_packet[28] = {0xFF,0xFF,0xFE,0x18,0x83, param_address, 0x04, id1, 0x00,0x00, 0x00,0x00,
			id2, 0x00,0x00, 0x00,0x00, id3, 0x00,0x00, 0x00,0x00, id4, 0x00,0x00, 0x00,0x00, 0x00 };
	uint8_t size= sizeof(instruction_packet);
	uint8_t *data = (uint8_t*)malloc(2*sizeof(uint8_t));
	Dynamix_WriteHexa(data, param1_position);
	Buffer_Allocate_Divide_Hex(8,instruction_packet,data);
	Dynamix_WriteHexa(data, param1_speed);
	Buffer_Allocate_Divide_Hex(10,instruction_packet,data);
	Dynamix_WriteHexa(data, param2_position);
	Buffer_Allocate_Divide_Hex(13,instruction_packet,data);
	Dynamix_WriteHexa(data, param2_speed);
	Buffer_Allocate_Divide_Hex(15,instruction_packet,data);
	Dynamix_WriteHexa(data, param3_position);
	Buffer_Allocate_Divide_Hex(18,instruction_packet,data);
	Dynamix_WriteHexa(data, param3_speed);
	Buffer_Allocate_Divide_Hex(20,instruction_packet,data);
	Dynamix_WriteHexa(data, param4_position);
	Buffer_Allocate_Divide_Hex(23,instruction_packet,data);
	Dynamix_WriteHexa(data, param4_speed);
	Buffer_Allocate_Divide_Hex(25,instruction_packet,data);
	instruction_packet[27] = Dynamix_Checksum(instruction_packet,size );
	Buffer_Data_Set(packet_buffer,instruction_packet,size);
	free(data);
}



/*uint8_t Dynamix_Length(uint8_t param_length)
{
	uint8_t count =0;
	count = sizeof(param_length)/sizeof(uint8_t);
	count = count - 4 ; //(2-6)
	return Dynamix_Dec_WriteHexa(count);
}*/



uint8_t Dynamix_Checksum(uint8_t *packet_arrangement, uint8_t size)
{
	uint8_t checksum = 0;

	for(uint8_t i =2; i<(size-1); i++)
	{
		checksum += packet_arrangement[i];
	}
	checksum = (uint8_t)~checksum;

	return checksum;
}



void Dynamix_Dec_WriteHexa(uint8_t *data_buffer,uint8_t dec)
{
	uint8_t Temp , i ;

	for(i = 0;i < 2; i++)
	{
		Temp = (dec >> (4 - 4*i))& 0x0F;
		Temp = HexaString_DEC[Temp] - '0';
		data_buffer[i] = Temp;
	}

}

void Dynamix_WriteHexa(uint8_t *data_buffer,uint16_t hex)
{
	uint8_t Temp , i;

	for(i = 0;i < 2; i++)
	{
		Temp = (hex >> (8 - 8*i))& 0xFF;
		//Temp = HexaString_DEC[Temp] - '0';
		data_buffer[1-i] = Temp;
	}
}

void Buffer_Data_Set(uint8_t *buffer, uint8_t *packet_data , uint8_t size)
{
	for(uint8_t i =0 ; i<size; i++)
	buffer[i] =packet_data[i];

}

void Buffer_Allocate_Divide_Hex(uint8_t start_buffer_index, uint8_t *buffer, uint8_t *data)
{
		buffer[start_buffer_index] = data[0];
		buffer[start_buffer_index +1] = data[1];
}










