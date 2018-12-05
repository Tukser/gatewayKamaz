#include "main.h"

#define CAN_QUEUE_LENGTH 10

xQueueHandle xMessageUsart = NULL;
xQueueHandle xMessageCAN = NULL;

int main()
{
	xMessageUsart = xQueueCreate(1, sizeof(unsigned char)); // Queue for send data on USART
	xMessageCAN = xQueueCreate(CAN_QUEUE_LENGTH, sizeof(CAN_msg)); // Queue for send data in CAN
	
	TaskHandle_t xHandle;


	xTaskCreate(vTaskInitialization, "Initialization_device", configMINIMAL_STACK_SIZE , NULL, 1, &xHandle);
	xTaskCreate(vTaskSendMessageUSART, "Send a message to USART", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);
	xTaskCreate(vTaskRecieveMessageUsart, "Recieve a message to USART", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);
	
	xTaskCreate(vTaskAddMessageCAN_EEC2, "Add EEC1 message to queue", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);
	/*xRecieveUsart = xQueueCreate(1,sizeof(unsigned char)); //Queue for recieve data on USART
	sSendSPI250 = xQueueCreate(1, sizeof(unsigned char)); //Queue for send data on SPI 250kb/s
	sRecieveSPI250 = xQueueCreate(1, sizeof(unsigned char)); //Queue for recieve data on SPI 250kb/s

	sSendSPI500 = xQueueCreate(1, sizeof(unsigned char)); //Queue for send data on SPI 250kb/s
	sRecieveSPI500 = xQueueCreate(1, sizeof(unsigned char)); //Queue for recieve data on SPI 250kb/s*/

	vTaskStartScheduler();
	while (1)
	{
	}
	return 0;
}


void vTaskSendMessageUSART(void* param)
{
	unsigned char i;
	portBASE_TYPE xStatus;
	const portTickType xTickWait = 100;
	
	while(1)
	{	
		if (uxQueueMessagesWaiting(xMessageUsart)!=0)
		{
		}
		xStatus = xQueueReceive(xMessageUsart, &i,xTickWait);
		if (xStatus == pdPASS)
		{
			while (!(USART_GetFlagStatus(USART1, USART_FLAG_TXE)));
			USART_SendData(USART1, i);		
		}
	}

}

void vTaskRecieveMessageUsart(void* param)
{
	unsigned char i=0;
	portBASE_TYPE xStatus;
	while(1)
	{
		i++;
		xStatus = xQueueSendToBack(xMessageUsart, &i,0);
		if (xStatus !=pdFALSE)
		{
			
		}
		taskYIELD();
	}
}

/*void xTaskSendUsart(void* param)
{
	unsigned char data;
	while (1)
	{
		xQueueReceive(xSendUsart,&data,0);
		sendMessageUSART(data);
		vTaskDelay(1000);
	}
}

void xTaskSendQueue(void* param)
{
	unsigned char buffer=0xFF;
	while(1)
	{
		xQueueSend(xSendUsart, &buffer, 0);
		vTaskDelay(1000);
	}
}*/



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */
