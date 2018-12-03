#include "init.h"

void vTaskInitialization(void* param)
{
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_4);
	RCC_PLLCmd(ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef _GpioInitIndicator;
	
	_GpioInitIndicator.GPIO_Mode =GPIO_Mode_Out_PP;
	_GpioInitIndicator.GPIO_Pin = GPIO_Pin_7;
	_GpioInitIndicator.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &_GpioInitIndicator);
	
	//CS pin SPI
	GPIO_InitTypeDef _GpioCS250;
	GPIO_InitTypeDef _GpioCS500;
	
	_GpioCS250.GPIO_Pin = GPIO_Pin_12;
	_GpioCS250.GPIO_Mode = GPIO_Mode_Out_PP;
	_GpioCS250.GPIO_Speed = GPIO_Speed_2MHz;
	
	_GpioCS500.GPIO_Pin = GPIO_Pin_4;
	_GpioCS500.GPIO_Mode = GPIO_Mode_Out_PP;
	_GpioCS500.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &_GpioCS250);
	GPIO_Init(GPIOA, &_GpioCS500);	
	
	//SPI1 250kb/s
	SPI_I2S_DeInit(SPI1);
	SPI_InitTypeDef _GpioInitSPI250;
	GPIO_InitTypeDef _GpioPinForSpi250;
	
	_GpioPinForSpi250.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	_GpioPinForSpi250.GPIO_Mode = GPIO_Mode_AF_PP;
	_GpioPinForSpi250.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &_GpioPinForSpi250);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	_GpioInitSPI250.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	_GpioInitSPI250.SPI_CPHA = SPI_CPHA_1Edge;
	_GpioInitSPI250.SPI_CPOL = SPI_CPOL_High;
	_GpioInitSPI250.SPI_CRCPolynomial = 7;
	_GpioInitSPI250.SPI_DataSize = SPI_DataSize_8b;
	_GpioInitSPI250.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	_GpioInitSPI250.SPI_FirstBit = SPI_FirstBit_MSB;
	_GpioInitSPI250.SPI_Mode = SPI_Mode_Master;
	_GpioInitSPI250.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &_GpioInitSPI250);
	SPI_Cmd(SPI1, ENABLE);
	
	//SPI2 500kb/s
	SPI_I2S_DeInit(SPI2);
	SPI_InitTypeDef _GpioInitSPI500;	
	GPIO_InitTypeDef _GpioPinForSpi500;
	
	_GpioPinForSpi500.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	_GpioPinForSpi500.GPIO_Mode = GPIO_Mode_AF_PP;
	_GpioPinForSpi500.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &_GpioPinForSpi500);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	_GpioInitSPI500.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	_GpioInitSPI500.SPI_CPHA = SPI_CPHA_1Edge;
	_GpioInitSPI500.SPI_CPOL = SPI_CPOL_High;
	_GpioInitSPI500.SPI_CRCPolynomial = 7;
	_GpioInitSPI500.SPI_DataSize = SPI_DataSize_8b;
	_GpioInitSPI500.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	_GpioInitSPI500.SPI_FirstBit = SPI_FirstBit_MSB;
	_GpioInitSPI500.SPI_Mode = SPI_Mode_Master;
	_GpioInitSPI500.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &_GpioInitSPI500);
	SPI_Cmd(SPI2, ENABLE);
	
	//USART
	NVIC_InitTypeDef _NVICStruct;
	_NVICStruct.NVIC_IRQChannel = USART1_IRQn;
	_NVICStruct.NVIC_IRQChannelPreemptionPriority = 0;
	_NVICStruct.NVIC_IRQChannelSubPriority = 0;
	_NVICStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&_NVICStruct);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	GPIO_InitTypeDef _GpioPinForUSART;
	USART_InitTypeDef _GpioInitUSART;
	//TX
	_GpioPinForUSART.GPIO_Pin = GPIO_Pin_9;
	_GpioPinForUSART.GPIO_Mode = GPIO_Mode_AF_PP;
	_GpioPinForUSART.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &_GpioPinForUSART);
	//RX
	_GpioPinForUSART.GPIO_Pin = GPIO_Pin_10;
	_GpioPinForUSART.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &_GpioPinForUSART);
	
	_GpioInitUSART.USART_BaudRate = UBAUDRATE;
	_GpioInitUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	_GpioInitUSART.USART_Mode = USART_Mode_Tx |  USART_Mode_Rx;
	_GpioInitUSART.USART_Parity = USART_Parity_No;
	_GpioInitUSART.USART_StopBits = USART_StopBits_2;
	_GpioInitUSART.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &_GpioInitUSART);
	
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	while(1)
	{
		
	}
	vTaskDelete(NULL);
}

