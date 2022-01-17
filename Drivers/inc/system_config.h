/*
 * sytem_config.h
 *
 *  Created on: Aug 18, 2021
 *      Author: JeongSeongHo
 */

#ifndef __SYSTEM_CONFIG_H_
#define __SYSTEM_CONFIG_H_


#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f1xx.h"






void System_Clock_Config(void);

void Error_System_Handler(void);





#ifdef __cplusplus
 extern "C" {
#endif

#endif /* __SYSTEM_CONFIG_H_ */
