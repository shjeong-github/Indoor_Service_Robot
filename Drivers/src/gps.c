/*
 * gps.c
 *
 *  Created on: 2021. 9. 28.
 *      Author: JeongSeongHo
 */
#include "gps.h"

//RMC

#define PI 3.1415926535897932384626433832795
#define TIME 60
#define SECOND 1.1515
#define MILE 1.609344
#define KILLOMETER 1000
#define LATITUDE_MINUTE 111.3194
#define HARDNESS_MINUTE 88.9036


void Checksum_GPS(uint8_t *buffer, uint8_t *Check_Point)
{
	//체크 변수
	uint8_t Check_Index =0;
	// 체크 포문 데이터 들어온만큼
	for(uint8_t Index =0 ; Index<strlen(buffer); Index++)
	{
		// GPS패킷 시작 검출
		if(buffer[Index] == '$')
		{
			//시작패킷검색 이후 인덱스만큼 내가 원하는 패킷이 있는지 검사
			if( buffer[Index+3] == 'R' && buffer[Index+4] == 'M' && buffer[Index+5] == 'C' ) //buffer[Index+1] == 'G'&& buffer[Index+2] == 'P' &&
			{
				//데이터 구분 쉼표 검사
				for(uint8_t i = 7;i<strlen(buffer);i++)
				{
					if(buffer[Index+i] == ',' || buffer[Index +i] == 'A'|| buffer[Index +i] == 'V'|| buffer[Index +i] == 'N'|| buffer[Index +i] == 'E' )
					{
						Check_Point[Check_Index++] = Index+i;
					}
				}
			}
		}
	}
}

double ConvertRadiansToDecimalDegrees(double rad)
{
	// Degree 라디안 변환
	return (rad*180/PI);
}
double ConvertDecimalDegreesToRadians( double deg)
{	//라디안 Degree 변환
	return (deg*PI/180);
}


double GPS_Distance_Cal(float Latitude1,float  Hardness1 ,float  Latitude2, float Hardness2)
{
	double distance=0;
	double theta =0;
	theta = Hardness2 - Hardness1;

	// 아직 잘모릅니다
	distance = acos(sin(ConvertDecimalDegreesToRadians(Latitude1))*sin(ConvertDecimalDegreesToRadians(Latitude2)) + cos(ConvertDecimalDegreesToRadians(Latitude1))* cos(ConvertDecimalDegreesToRadians(Latitude2))*cos(ConvertDecimalDegreesToRadians(theta)));
	distance = ConvertRadiansToDecimalDegrres(distance);
	distance =GPS_to_Kilo(distance);
	return distance;
}

float Gps_Latitude_Distance_Cal(float Latitude1, float Latitude2)
{
	// 위도값 좌표 거리 구한후 미터단위로 변경
	return (Latitude2- Latitude1)* LATITUDE_MINUTE * 1000;
}
float Gps_Hardness_Distance_Cal(float Hardness1, float Hardness2)
{
	// 경도값 좌표 거리 구한후 미터단위로 변경
	return (Hardness2-Hardness1)* HARDNESS_MINUTE * 1000;
}
float GPS_to_Kilo(float GPS)
{
	//아직 설명못함
	return GPS * TIME * SECOND	* MILE * KILLOMETER;
}

float GPS_Move_Distance_X(float start_point_x, float present_point_x)
{
	return present_point_x - start_point_x;
}

float GPS_Move_Distance_Y(float start_point_y, float present_point_y)
{
	return present_point_y - start_point_y;
}








