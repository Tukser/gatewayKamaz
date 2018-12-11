#include "main.h"


int main()
{
	
	xMessageUsartTest = xQueueCreate(1, sizeof(unsigned char)); //Queue for send data on USARTtest
	xMessageCanTest = xQueueCreate(1, sizeof(unsigned char)); //Queue for send data on CANtest
	
	xTaskCreate(vTaskInitializationRCC, "Initialization_RCC", configMINIMAL_STACK_SIZE , NULL, 1, &xHandle);
	xTaskCreate(vTaskInitializationUsart, "Initialization_USART", configMINIMAL_STACK_SIZE , NULL, 1, &xHandle);
	xTaskCreate(vTaskSendMessageUSART, "Send a message to USART", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);
	xTaskCreate(vTaskRecieveMessageUsart, "Recieve a message to USART", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);	
	xTaskCreate(vTaskCANMCPinit, "vTaskCANMCPinit", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);	
	
	xTaskCreate(vTaskInitializationSPI1, "Initialization_SPI1", configMINIMAL_STACK_SIZE , NULL, 1, &xHandle);
	xTaskCreate(vTaskInitializationSPI2, "Initialization_SPI2", configMINIMAL_STACK_SIZE , NULL, 1, &xHandle);

	//xTaskCreate(vTaskSendMessageSPI1, "Send a message to SPI1", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);
	//xTaskCreate(vTaskRecieveMessageSPI2, "Recieve a message to SPI2", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);
 	//xTaskCreate(vTaskAddMessageCAN_EEC2, "Send EEC2 message to CAN", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle);

	
	vTaskStartScheduler();
	while (1)
	{
	}
	return 0;
}



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
