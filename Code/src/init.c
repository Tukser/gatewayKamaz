#include "init.h"

void vTaskInitializationRCC(void* param)
{
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	SPI_I2S_DeInit(SPI1);
	SPI_I2S_DeInit(SPI2);
	USART_DeInit(USART1);
	RCC_DeInit();
	
	uint8_t HSEStartUpStatus =0;
	
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_HCLKConfig(RCC_HCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
	}
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	//Indicator
	GPIO_InitTypeDef _GpioInitIndicator;
	
	_GpioInitIndicator.GPIO_Mode =GPIO_Mode_Out_PP;
	_GpioInitIndicator.GPIO_Pin = GPIO_Pin_13;
	_GpioInitIndicator.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &_GpioInitIndicator);

	while(1)
	{
	}
	vTaskDelete(NULL);
}


	//Init SPI1
void vTaskInitializationSPI1(void* param)
{
	GPIO_InitTypeDef _GpioCS250;
	
	_GpioCS250.GPIO_Pin = GPIO_Pin_4;
	_GpioCS250.GPIO_Mode = GPIO_Mode_AF_PP;
	_GpioCS250.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &_GpioCS250);
	
	//SPI1 250kb/s
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	
	SPI_InitTypeDef _GpioInitSPI250;
	GPIO_InitTypeDef _GpioPinForSpi250;
	
	_GpioPinForSpi250.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	_GpioPinForSpi250.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &_GpioPinForSpi250);
	
	SPI_StructInit(&_GpioInitSPI250);
	_GpioInitSPI250.SPI_Mode = SPI_Mode_Master;
	_GpioInitSPI250.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	_GpioInitSPI250.SPI_FirstBit = SPI_FirstBit_MSB;	
	_GpioInitSPI250.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	_GpioInitSPI250.SPI_CPHA = SPI_CPHA_1Edge;
	_GpioInitSPI250.SPI_CPOL = SPI_CPOL_Low;
	_GpioInitSPI250.SPI_CRCPolynomial = 7;
	_GpioInitSPI250.SPI_DataSize = SPI_DataSize_8b;
	_GpioInitSPI250.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &_GpioInitSPI250);
	SPI_Cmd(SPI1, ENABLE);
	
	//Test
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(200);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(200);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(200);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	while(1)
	{
	}
	vTaskDelete(NULL);
}
	
	//SPI2 500kb/s
void vTaskInitializationSPI2(void* param)
{
	GPIO_InitTypeDef _GpioCS500;
	
	_GpioCS500.GPIO_Pin = GPIO_Pin_12;
	_GpioCS500.GPIO_Mode = GPIO_Mode_Out_PP;
	_GpioCS500.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &_GpioCS500);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	SPI_InitTypeDef _GpioInitSPI500;	
	GPIO_InitTypeDef _GpioPinForSpi500;
	
	_GpioPinForSpi500.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	_GpioPinForSpi500.GPIO_Mode = GPIO_Mode_AF_PP;
	_GpioPinForSpi500.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &_GpioPinForSpi500);
	
	SPI_StructInit(&_GpioInitSPI500);
	_GpioInitSPI500.SPI_Mode = SPI_Mode_Master;
	_GpioInitSPI500.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	_GpioInitSPI500.SPI_CPHA = SPI_CPHA_1Edge;
	_GpioInitSPI500.SPI_CPOL = SPI_CPOL_Low;
	_GpioInitSPI500.SPI_CRCPolynomial = 7;
	_GpioInitSPI500.SPI_DataSize = SPI_DataSize_8b;
	_GpioInitSPI500.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	_GpioInitSPI500.SPI_FirstBit = SPI_FirstBit_MSB;
	_GpioInitSPI500.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_Init(SPI2, &_GpioInitSPI500);
	SPI_Cmd(SPI2, ENABLE);
		
	//Test
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(500);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(500);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(500);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
	while(1)
	{
	}
	vTaskDelete(NULL);
}
	
//USART	
void vTaskInitializationUsart(void* param)
{
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
	_GpioPinForUSART.GPIO_Speed = GPIO_Speed_50MHz;
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
	
	//Test
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(1000);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(1000);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	vTaskDelay(1000);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
	while(1)
	{

	}
	vTaskDelete(NULL);
}

void vTaskCANMCPinit(void* param)
{
	if (!(CANSPI_Initialize()))
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	while(1)
	{
	}
}
