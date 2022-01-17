/*
 * gps.h
 *
 *  Created on: 2021. 9. 28.
 *      Author: JeongSeongHo
 */

#ifndef __GPS_H_
#define __GPS_H_

#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f1xx.h"
#include <stdio.h>
#include <math.h>

// GSP 버퍼 패킷 데이터 검사
 void Checksum_GPS(uint8_t *buffer, uint8_t *Check_Point);
 // 두 위도 경도 좌표간의 거리 계산
 double GPS_Distance_Cal(float Latitude1,float  Hardness1 ,float  Latitude2, float Hardness2);
 // 위도거리 계산
 float Gps_Latitude_Distance_Cal(float Latitude1, float Latitude2);
 //경도 거리 계산
 float Gps_Hardness_Distance_Cal(float Hardness1, float Hardness2);
 // 라이안의 정보를 거리정보로 변경
 double ConvertRadiansToDecimalDegrees(double rad);
 //거리정보를 라이안값으로변경
 double ConvertDecimalDegreesToRadians( double deg);
 // Km변환
 float GPS_to_Kilo(float GPS);
 float GPS_Move_Distance_X(float start_point_x, float present_point_x);
 float GPS_Move_Distance_Y(float start_point_y, float present_point_y);












#ifdef __cplusplus
 extern "C" {
#endif

#endif /* __GPS_H_ */
