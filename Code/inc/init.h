#ifndef INIT_H
#define INIT_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_usart.h"
#include "communication.h"
#include "stdbool.h"

//----------------------------------------------------------------------------------------------------

//define for STM32f103ret6

//#define UBAUDRATE 4800
#define UBAUDRATE 9600
//#define UBAUDRATE 19200
//#define UBAUDRATE 115200

void vTaskInitializationRCC(void* param);
void vTaskInitializationUsart(void* param);
void vTaskInitializationSPI1(void* param);
void vTaskInitializationSPI2(void* param);
void vTaskCANMCPinit(void* param);


bool testUsartReady(void);


#endif
