#ifndef INIT_H
#define INIT_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_usart.h"

//----------------------------------------------------------------------------------------------------

//define for STM32f103ret6

//#define UBAUDRATE 4800
#define UBAUDRATE 9600
//#define UBAUDRATE 19200
//#define UBAUDRATE 115200

void vTaskInitialization(void* param);


#endif
