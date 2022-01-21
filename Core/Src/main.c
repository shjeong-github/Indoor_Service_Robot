/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

uint8_t Rx1_Array[SERIAL_BUFFER_SIZE];
uint8_t Rx2_Array[SERIAL_BUFFER_SIZE];
/* Private variables ---------------------------------------------------------*/
uint8_t Rx1_Index= 0;
uint8_t Rx2_Index= 0;
uint8_t GPS_Rx1_Flag = 0;
uint8_t GPS_Rx1_Flag1 =0;
uint8_t GPS_Rx2_Flag = 0;
uint8_t dynamix_buffer=0;
// GPS TEST 전용 변수
float Latitude_distance_serial=0;
float Hardness_distance_serial=0;
uint8_t serial_flag =0; // 다이나믹셀도 포함
float Latitude_distance_buffer[20] = {0,};
float Hardness_distance_buffer[20] = {0,};
uint8_t serial_save_data[100] ={0,};
//여기까지
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// LED 실행 알람 함수
void Blink(void);
// 보드 SYSTEM 확인 LED 알람함수
void Blink_System(void);
// SEGMENT 정상 작동 확인 함수
void Counter(void);
// 엔코더 데이터 세그먼트 전달함수
void Encoder_Data_Send_Segment(void);
// 시리얼 패킷 통신 설정 함수
void Serial_Packet(void);
//GPS 데이터 검출 테스트함수
void GPS_Serial_Packet(void);
void Serial_callback2(void);
// 시리얼 콜백 함수
void Serial_callback(void);
// 엔코더 속도 세그먼트 출력함수
void Encoder_Speed_Data_send_Segment(void);
// 엔코더 각속도 세그먼트 출력함수
void Encoder_Angle_Data_send_Segment(void);
uint16_t u16_count = 0;
void test_callback(void);
void test_dynamix(void);
//GPS 데이터 확인 함수
void GPS_Serial_Send(void);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  System_Clock_Config();

  /* USER CODE BEGIN Init */
  LED_Init();
  Timer_Init();
  Segment_Init();
  QEP_Init();
  PWM_Init(60000, 60000);
  //PWM_Init(20000); 기존에 쓰던 코드
  PWM_Open(0,0);
  //PWM_Open(0,3.5);
  Serial1_Init();
  Serial2_Init();
  //PWM_Open(0,15);
  //PWM_Open(0,15);
  //PWM_Open(0,15);
  Serial_Open(0,115200,Serial_callback);
  Serial_Open(1,115200,Serial_callback2);
  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */


  //LED interrupt
  Alarm_Open(ALARM4,1000,Blink);

  //Segment interrupt
  Alarm_Open(ALARM1,5,Segment_Power_ON);
  //qep interrupt
  //Alarm_Open(ALARM2,5,QEP_Read);
  Alarm_Open(ALARM3,1000,Encoder_Data_Send_Segment);
  // Alarm_Open(ALARM4,500,Counter);
  //Alarm_Open(ALARM6,SERIAL_BUFFER_SIZE,Serial_Packet);
  Alarm_Open(ALARM5,100,GPS_Serial_Packet );
 //Alarm_Open(ALARM6,1000,GPS_Serial_Send );
  //Alarm_Open(ALARM6,SERIAL_BUFFER_SIZE,test_dynamix);
  //HAL_UART_Transmit(&huart2, "Start1OK\n", 10, 100);
  HAL_UART_Transmit(&huart3, "Start2OK\n", 10, 100);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //PWM angle test2
  //float i=5.5;
  uint8_t id =0x0F , param_address =0x1E , param1 =0x200, param2 = 0x200;
  uint16_t param3=0x200, param4=0x200;
  while (1)
  {
	 //Segment_Powerset();
	 //HAL_Delay(5);
    /* USER CODE END WHILE */
	  /*for(int i =1 ; i<5 ; i++)
	  	  {
	  	  LED_On_Unit(i,LED_ON);
	  	  HAL_Delay(500);
	  	  LED_On_Unit(i,LED_OFF);
	  	  HAL_Delay(500);
	  	  }*/
    /* USER CODE BEGIN 3 */

	//PWM angle test1
	//PWM_Duty_Set(0,3);
	//HAL_Delay(5000);
	//PWM_Duty_Set(0,12.5);
	//HAL_Delay(5000);
	//PWM_Duty_Set(0,22);
	//HAL_Delay(5000);


	  //PWM angle test2
	  /*PWM_Duty_Set(0,i);
	  Segment_Set_Value(i*10);
	  HAL_Delay(3000);
	  i+=9;
	  if(i >24)
	  {i=5.5;
	  }*/



	 //id=Rx1_Array[0];
	 //param_address=Rx1_Array[1];
	 //param1=Rx1_Array[2];
	 //param2=Rx1_Array[3];
	 //param3 = 0x0200;
	 //param4 = 0x0200;
	 //READ_DATA_Instruct(&dynamix_buffer, id,param_address,param1);
	 param3=0x200;
	 param4=0x200;
	 WRITE_DATA_Instruct(&dynamix_buffer,id,param_address,param3,param4);
	 //SYNC_WRITE_Instruct(&dynamix_buffer,0x1E,0x00,0x010,0x150,0x01,0x220,0x360,0x02,0x030,0x170,0x03,0x220,0x380);
	 Serial_Send(0,&dynamix_buffer,11);
	 Serial_Send(1,&dynamix_buffer,11);
	 HAL_Delay(3000);
	 param3=0x20;
	 param4=0x200;
	 WRITE_DATA_Instruct(&dynamix_buffer,id,param_address,param3,param4);
	 Serial_Send(0,&dynamix_buffer,11);
	 Serial_Send(1,&dynamix_buffer,11);
	 HAL_Delay(3000);
  }
  /* USER CODE END 3 */
  return 0;
}





void Blink(void)
{
	static uint8_t flag = 1;

	if(flag == 0)
	{
		LED_On_Unit(2,LED_ON);
 		flag = 1;
	}
	else
	{
		LED_On_Unit(2,LED_OFF);

		flag = 0;
	}
}

void Blink_System(void)
{
	static uint8_t flag = 1;
	if(flag == 0)
	{
		LED_On_Unit(4,1);
 		flag = 1;
	}
	else
	{
		LED_On_Unit(4,0);
		flag = 0;
	}

}


void Counter(void)
{
	// 세그먼트 카운트 증가
	u16_count++;
	// 카운트 MAX값에 맞춰 변환
	u16_count = u16_count%1000;
	// 세그먼트 출력
	Segment_Set_Value(u16_count);
}

void Encoder_Data_Send_Segment(void)
{
	// 엔코더 현재 카운트값 확인
	uint16_t encoder_value = QEP_Get();
	// 세그먼트 출력
	Segment_Set_Value(encoder_value);
}
void Encoder_Speed_Data_send_Segment(void)
{
	// 엔코더 정보 입력
	Encoder_value_Set(ENCODER_COUNT, ENCODER_MULTIPUL, ENCODER_SAMPLING_TIME);
	// 엔코더 속도값 받기
	uint16_t encoder_speed = Encoder_speed();
	// 엔코더 속도값 세그먼트 출력
	Segment_Set_Value(encoder_speed);
	// 엔코더 리셋
	QEP_Reset();

}
void Encoder_Angle_Data_send_Semgment(void)
{
	// 엔코더 정보 입력
	Encoder_value_Set(ENCODER_COUNT, ENCODER_MULTIPUL, ENCODER_SAMPLING_TIME);
	// 엔코더 각도값 받기
	uint16_t encoder_angle = Encoder_angular_velocity();
	// 엔코더 각도값 세그먼트 출력
	Segment_Set_Value(encoder_angle);
	// 엔코더 리셋
	QEP_Reset();


}




void Serial_Packet(void)
{
	// 시리얼 버퍼 검출 인덱스 변수
	static uint8_t Start_Index = 0;
	// 시리얼 데이터 ASCII 값 저장 변수
	uint8_t A,B;

	//각도가 증가 함께 다른 duty 비의 변화를 계산
	Angle_Value_Set(0.04777777777, 2.8, 0,180);

	// 인덱스가 8보다 크거나 같으면(패킷 형식임)
	if(Rx1_Index >= 8)
	{
		// !검출할때까지 대기
		if(Rx1_Array[Start_Index] == '!')
		{
			// 시리얼 저장 데이터에 , 데이터 확인
			if((Rx1_Array[Start_Index+4] ==','))
			{
				// 패킷 정보를 ASCII로 계산
				A = (Rx1_Array[Start_Index+1]-'0')*100 + (Rx1_Array[Start_Index+2] - '0')*10 + (Rx1_Array[Start_Index+3] - '0');
				B = (Rx1_Array[Start_Index+5]-'0')*100 + (Rx1_Array[Start_Index+6] - '0')*10 + (Rx1_Array[Start_Index+7] - '0');

				// 세그먼트에 시리얼 정보 출력
				Segment_Set_Value(A);
				// 시리얼 정보로 Duty퍼센트 값 입력
				PWM_Duty_Set(0,0,A);
				//PWM_Duty_Set(0,1,B);
				// 시리얼 정보 전송
				Serial_Send(0,Rx1_Array,(uint16_t)Rx1_Index);
			}
			// 시리얼 버퍼 초기화, 검출 인덱스 초기화
			Rx1_Index = 0;
			Start_Index = 0;
		}
		else
			Start_Index ++; //데이터 확인을 위해 검출 인덱스 ++
	}
}
uint8_t point_flag =2;
float start_point_x =0;
float start_point_y =0;


void GPS_Serial_Packet(void)
{
	uint8_t Gindex=0;
	//uint8_t Gindex_Save_Point_Dot[3] = {0,};
	//uint8_t dot_index =0;
	uint8_t serial_buffer[SERIAL_BUFFER_SIZE]={0,};
	uint8_t test_buf[20]={0,};
	uint8_t Gps_buffer[60] = {0,};
	uint8_t Latitude_dec[10] ={0,};
	uint8_t Latitude_decimal[100] = {'0',};
	uint8_t Hardness_dec[10] ={0,};
	uint8_t Hardness_decimal[100] = {'0',};
	uint8_t GPS_Point_Index[9] ={0,};
	uint8_t Latitude_buffer[10]={0,};
	uint8_t Hardness_buffer[10]={0,};
	uint8_t distance_buffer_x[100] ={'0',};
	uint8_t distance_buffer_y[100] ={'0',};
	//uint8_t Latitude_String;
	//uint8_t Hardness_String;
	uint8_t Hardness_distance_buf[100] = {0,};
	uint8_t Latitude_distance_buf[100] = {0,};


	float Latitude1=0;
	float Hardness1=0;
	float Latitude1_dec = 0;
	float Latitude1_decimal = 0;
	float Hardness1_dec = 0;
	float Hardness1_decimal = 0;
	float Latitude2=36.83369; //37.565577
	float Hardness2=127.18081; //126.978082
	float gps_coordinate[2] = {0,};
	double distance1 = 0;
	float Hardness_distance=0;
	float Latitude_distance=0;
	float move_distance_x =0;
	float move_distance_y =0;

	if(GPS_Rx1_Flag ==1 && GPS_Rx1_Flag1==1)
	{
		for(uint8_t i = 0; i<strlen(Rx1_Array);i++)
		{
			serial_buffer[i] = Rx1_Array[i];
		}
		Checksum_GPS(serial_buffer, GPS_Point_Index);
		if(serial_buffer[GPS_Point_Index[1]] == 'V')
		{
			Serial_Send(0,"not_real_data\n",15);
		}
		else if(serial_buffer[GPS_Point_Index[1]] == 'A')
		{
			serial_flag =1;
			if(serial_buffer[GPS_Point_Index[4]] == 'N')
			{
				for(uint8_t i= GPS_Point_Index[2]+1 ;i<GPS_Point_Index[3]; i++ )
				{
					Gps_buffer[Gindex++] = serial_buffer[i];
				}
				for(uint8_t j =0; j<Gindex; j++)
				{
					if(j == 0 || j == 1)
					Latitude_dec[j] = Gps_buffer[j];
					else
					Latitude_decimal[j-2] = Gps_buffer[j];
				}
				Gindex =0;


			}
			if(serial_buffer[GPS_Point_Index[7]]=='E')
			{
				for(uint8_t i= GPS_Point_Index[5]+1 ;i<GPS_Point_Index[6]; i++ )
				{
					Gps_buffer[Gindex++] = serial_buffer[i];
				}
				for(uint8_t j =0;j<Gindex; j++)
				{
					if(j == 0 || j == 1 || j ==2)
					Hardness_dec[j] = Gps_buffer[j];
					else
					Hardness_decimal[j-3] = Gps_buffer[j];
				}
				Gindex =0;

			}


		//Serial_Send(0,Latitude_decimal,15);
		Latitude1_dec = atof(Latitude_dec);
		Latitude1_decimal = atof(Latitude_decimal);
		//Serial_Send(0,Hardness_decimal,15);
		Hardness1_dec = atof(Hardness_dec);
		Hardness1_decimal = atof(Hardness_decimal);
		gcvt(Latitude1_decimal,15,test_buf);
		gcvt(Hardness1_decimal,15,test_buf);
		Latitude1_decimal = Latitude1_decimal /60.0;
		Latitude1 = Latitude1_dec + Latitude1_decimal;
		Hardness1_decimal =Hardness1_decimal /60.0;
		Hardness1 = Hardness1_dec + Hardness1_decimal;
		Latitude_distance = Gps_Latitude_Distance_Cal(Latitude1,Latitude2);
		Hardness_distance = Gps_Hardness_Distance_Cal(Hardness1,Hardness2);


		if(point_flag != 2)
		{

			move_distance_x = Gps_Latitude_Distance_Cal(start_point_x, Latitude1);
			move_distance_y = Gps_Hardness_Distance_Cal(start_point_y, Hardness1);
		}

		if((point_flag ==2))
		{
			for(uint8_t i=0 ; i<100; i++)
			{
				distance_buffer_x[i] = '0';
				distance_buffer_y[i] = '0';
			}
			start_point_x = Latitude1;
			start_point_y = Hardness1;
			gcvt(start_point_x,15,distance_buffer_x);
			gcvt(start_point_y,15,distance_buffer_y);
			Serial_Send(1,"x0\n",4);
			Serial_Send(1,distance_buffer_x,15);
			Serial_Send(1,"y0\n",4);
			Serial_Send(1,distance_buffer_y,15);
			point_flag =0;
		}
		if((move_distance_x !=0 && move_distance_y != 0))
		{
			gcvt(move_distance_x,15,distance_buffer_x);
			gcvt(move_distance_y,15,distance_buffer_y);
			Serial_Send(1,"x1\n",4);
			Serial_Send(1,distance_buffer_x,15);
			Serial_Send(1,"y1\n",4);
			Serial_Send(1,distance_buffer_y,15);

		}
		gcvt(Latitude_distance,15,Latitude_distance_buf);
		gcvt(Hardness_distance,15,Hardness_distance_buf);
		}
		//Serial_Send(1,serial_buffer,60);
		GPS_Rx1_Flag = 0;
		GPS_Rx1_Flag1 = 0;

	}
}

void GPS_Serial_Send(void)
{

	gcvt(Latitude_distance_serial,15,Latitude_distance_buffer);
	gcvt(Hardness_distance_serial,15,Hardness_distance_buffer);
	Serial_Send(1,Latitude_distance_buffer,15);
	Serial_Send(1,Hardness_distance_buffer,15);
	Serial_Send(1, serial_save_data, 60);
	for(uint8_t i = 0; i<20 ; i++)
	{
		Latitude_distance_buffer[i] =0;
		Hardness_distance_buffer[i] =0;
	}

}

void test_dynamix(void)
{
	uint8_t id =0x0F , param_address =0x1E , param1 =0x20, param2 = 0x20;
	uint16_t param3=0x20, param4=0x20;
	//id=Rx1_Array[0];
	//param_address=Rx1_Array[1];
	//param1=Rx1_Array[2];
	//param2=Rx1_Array[3];
	//param3 = 0x0200;
	//param4 = 0x0200;
	//READ_DATA_Instruct(&dynamix_buffer, id,param_address,param1);
	WRITE_DATA_Instruct(&dynamix_buffer,id,param_address,param3,param4);
	//SYNC_WRITE_Instruct(&dynamix_buffer,0x1E,0x00,0x010,0x150,0x01,0x220,0x360,0x02,0x030,0x170,0x03,0x220,0x380);
	Serial_Send(0,&dynamix_buffer,11);
	Serial_Send(1,&dynamix_buffer,11);


	/*if( (Rx1_Array[0] != 0) &&(serial_flag ==0))
	{
		for(uint8_t i = 0; i<13;i++ )
			Rx2_Array[i] = Rx1_Array[i];
		Serial_Send(0,Rx1_Array,11);
		HAL_HalfDuplex_EnableTransmitter(&huart3);
		Serial_Send(1, Rx2_Array,11);
		HAL_HalfDuplex_EnableReceiver(&huart3);
		serial_flag = 2;
	}*/
}






void test_callback(void)
{

	Serial_Send(1,Rx1_Array,40);
}


void Serial_callback(void)
{
	static uint8_t packet_count =0;
	// 시리얼 버퍼 공간 확인
	  if(Rx1_Index  == SERIAL_BUFFER_SIZE)
		  Rx1_Index =0; // 가득차면 초기화
	  // 시리얼 레지스터 버퍼 정보를 버퍼로 정보 전달
	  uint8_t get_char =  Serial_Data_GET(0);
	  if(get_char == '$')
	  {
		  Rx1_Index = 0;
		  GPS_Rx1_Flag = 1;
		  packet_count =0;
	  }
	  if(get_char =='*')
	  {
		 GPS_Rx1_Flag1 = 1;
		 packet_count=2;
	  }
	  if(packet_count != 2)
	  {
		  Rx1_Array[Rx1_Index++] = get_char;
	  }
	  //Rx1_Array[Rx1_Index++] = get_char;
	  //Rx2_Array[Rx1_Index++] = get_char;
}

void Serial_callback2(void)
{
	// 시리얼 버퍼 공간 확인
	  if(Rx2_Index  == SERIAL_BUFFER_SIZE)
		  Rx2_Index =0; // 가득차면 초기화
	  // 시리얼 레지스터 버퍼 정보를 버퍼로 정보 전달
	  uint8_t get_char =  Serial_Data_GET(1);
	  /*if(get_char == '$')
	  {
		  Rx2_Index = 0;
		  GPS_Rx2_Flag = 1;
	  }*/
	  Rx2_Array[Rx2_Index++] = get_char;
	 // Serial_Send(1,Rx2_Array,10);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */


/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
