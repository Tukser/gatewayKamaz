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

#define READY_TO_SEND_MESSAGE_250 GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define WHAIT_TO_SEND_MESSAGE_250 GPIO_SetBits(GPIOB, GPIO_Pin_12)

void vTaskSendMessageSPI250(void* param);
void vTaskRecieveMessageSPI250(void* param);

void vTaskSendMessageSPI500(void* param);
void vTaskRecieveMessageSPI500(void* param);


#endif
