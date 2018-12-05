/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "usart.h"
#include "CANSPI.h"
#include "can.h"

/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* USER CODE BEGIN Variables */

osThreadId xHandle;
xQueueHandle xMessageUsart;
xQueueHandle xMessageCAN = NULL;

unsigned char accel_pedal = 0;
float xbr_accel_demand = 0.0;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void vTaskSendMessageUSART(void* param);
void vTaskRecieveMessageUsart(void* param);
void vTaskSendMessageSPI1(void *param);
void vTaskRecieveMessageSPI1(void* param);

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
 
 	

	/* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	xTaskCreate(vTaskSendMessageUSART, "Send a message to USART", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);
	xTaskCreate(vTaskRecieveMessageUsart, "Recieve a message to USART", configMINIMAL_STACK_SIZE, NULL, 0, &xHandle);
	xTaskCreate(vTaskRecieveMessageSPI1, "Send a message to SPI 1", configMINIMAL_STACK_SIZE, NULL, 0, &xHandle);
 	xTaskCreate(vTaskAddMessageCAN_EEC2, "Send EEC2 message to CAN", configMINIMAL_STACK_SIZE, NULL, 0, &xHandle);

 
 /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	 xMessageUsart = xQueueCreate(9, sizeof(unsigned char)); //Queue for send data on USART
	 xMessageCAN = xQueueCreate(9, sizeof(uCAN_MSG)); //Queue for send data on USART
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
 void vTaskSendMessageUSART(void* param)
{
	uint8_t incommingData;
	portBASE_TYPE xStatus;
	const portTickType xTickWait = 100;
	
	while(1)
	{	
		if (uxQueueMessagesWaiting(xMessageUsart)!=0)
		{
		}
		xStatus = xQueueReceive(xMessageUsart, &incommingData, xTickWait);
		if (xStatus == pdPASS)
		{
			HAL_UART_Transmit(&huart1, &incommingData, 1, 500);
		}
		taskYIELD();
	}
	
}

void vTaskRecieveMessageUsart(void* param)
{
	uint8_t outgoingData;
	portBASE_TYPE xStatus;
	while(1)
	{
		HAL_UART_Receive(&huart1, &outgoingData, 1, 500);
		xStatus = xQueueSendToBack(xMessageUsart, &outgoingData,0);
		if (xStatus !=pdPASS)
		{
			
		}
		taskYIELD();
	}
}

void vTaskSendMessageSPI1(void* param)
{
	uCAN_MSG incomingData;
	portBASE_TYPE xStatus;
	const portTickType xTickWait = 100;
	
	for(;;)
	{	
		xStatus = xQueueReceive(xMessageCAN, &incomingData, xTickWait);
		if (xStatus == pdPASS)
		{
			CANSPI_Transmit(&incomingData);
		}
		taskYIELD();
	}
}

void vTaskRecieveMessageSPI1(void* param)
{
	while(1)
	{
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
