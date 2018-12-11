#include "communication.h"
/*void sendMessageSPI250(void* param)
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
}*/

void vTaskRecieveMessageUsart(void* param)
{
	unsigned char outgoingData;
	portBASE_TYPE xStatus;
	while(1)
	{
		while((USART_GetFlagStatus(USART1, USART_FLAG_RXNE))==RESET);
		outgoingData = USART_ReceiveData(USART1);
		xStatus = xQueueSendToBack(xMessageCanTest, &outgoingData,0);
		if (xStatus !=pdFALSE)
		{
			
		}
		taskYIELD();
	}
}

void vTaskSendMessageSPI1(void* param)
{
	unsigned int incommingDataCAN;
	portBASE_TYPE xStatus;
	const portTickType xTickWait = 100;
	
	while(1)
	{	
		if (uxQueueMessagesWaiting(xMessageCanTest)!=0)
		{
		}
		xStatus = xQueueReceive(xMessageCanTest, &incommingDataCAN,xTickWait);
		if (xStatus == pdPASS)
		{
			while (!(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)));
			SPI_I2S_SendData(SPI1, incommingDataCAN);
			//USART_SendData(USART1, incommingDataCAN);		
		}
	}
}

void vTaskRecieveMessageSPI2(void* param)
{
	unsigned char outgoingData;
	portBASE_TYPE xStatus;
	while(1)
	{
		while((SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE))==RESET);
		outgoingData = SPI_I2S_ReceiveData(SPI2);
		xStatus = xQueueSendToBack(xMessageUsartTest, &outgoingData,0);
		if (xStatus !=pdFALSE)
		{
			
		}
		taskYIELD();
	}
}


void vTaskSendMessageUSART(void* param)
{
	unsigned int incommingData;
	portBASE_TYPE xStatus;
	const portTickType xTickWait = 100;
	
	while(1)
	{	
		if (uxQueueMessagesWaiting(xMessageUsartTest)!=0)
		{
		}
		xStatus = xQueueReceive(xMessageUsartTest, &incommingData,xTickWait);
		if (xStatus == pdPASS)
		{
			while (!(USART_GetFlagStatus(USART1, USART_FLAG_TXE)));
			USART_SendData(USART1, incommingData);		
		}
	}

}