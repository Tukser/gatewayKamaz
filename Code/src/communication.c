#include "communication.h"

void sendMessageSPI250(void* param)
{
	
	WHAIT_TO_SEND_MESSAGE_250;
	vTaskDelay(2000);
	READY_TO_SEND_MESSAGE_250;
	vTaskDelay(2000);
	SPI_I2S_SendData(SPI1,command);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
	while(1)
	{	
	}
	vTaskDelete(NULL);
}


void vTaskSendMessageUSART(void* param)
{
	while(1)
	{	
		if (USART_GetITStatus(USART1, USART_IT_TXE) !=RESET)
		{
		USART_SendData(USART1, 5);		
		while (!(USART_GetFlagStatus(USART1, USART_FLAG_TXE)));
		}
	}
}

void vTaskRecieveMessageUsart(void* param)
{
	while(1)
	{
	}
}



/*void USART1_IRQHandler()
{
	unsigned char buffer = 0x32;
    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
    {
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
			USART_SendData(USART1, buffer);    
    }
}*/