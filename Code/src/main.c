#include "main.h"

xQueueHandle xSendUsart = NULL;
xQueueHandle xRecieveUsart;
xQueueHandle sSendSPI250;
xQueueHandle sRecieveSPI250;
xQueueHandle sSendSPI500;
xQueueHandle sRecieveSPI500;


int main()
{

	xTaskCreate(vTaskInitialization, "Initialization_device", configMINIMAL_STACK_SIZE , NULL, 1, NULL);
	xTaskCreate(vTaskSendMessageUSART, "Send a message to USART", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	xSendUsart = xQueueCreate(1, sizeof(unsigned char)); //Queue for send data on USART
	xRecieveUsart = xQueueCreate(1,sizeof(unsigned char)); //Queue for recieve data on USART
	sSendSPI250 = xQueueCreate(1, sizeof(unsigned char)); //Queue for send data on SPI 250kb/s
	sRecieveSPI250 = xQueueCreate(1, sizeof(unsigned char)); //Queue for recieve data on SPI 250kb/s

	sSendSPI500 = xQueueCreate(1, sizeof(unsigned char)); //Queue for send data on SPI 250kb/s
	sRecieveSPI500 = xQueueCreate(1, sizeof(unsigned char)); //Queue for recieve data on SPI 250kb/s

	vTaskStartScheduler();
	while (1)
	{
	}
	return 0;
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
