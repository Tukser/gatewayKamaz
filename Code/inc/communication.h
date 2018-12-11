#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_usart.h"
#include "CANSPI.h"
#include "can.h"

void vTaskSendMessageUSART(void* param);
void vTaskRecieveMessageUsart(void* param);

void vTaskSendMessageSPI1(void* param);
void vTaskRecieveMessageSPI1(void* param);

void vTaskSendMessageSPI2(void* param);
void vTaskRecieveMessageSPI2(void* param);

extern xQueueHandle xMessageUsartTest;
extern xQueueHandle xMessageCanTest;

#endif