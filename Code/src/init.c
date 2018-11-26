#include "init.h"

void initTask(void)
{
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_4);
	RCC_PLLCmd(ENABLE);
	
	GPIO_InitTypeDef _GpioInitIndicator;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	_GpioInitIndicator.GPIO_Mode =GPIO_Mode_Out_PP;
	_GpioInitIndicator.GPIO_Pin = GPIO_Pin_7;
	_GpioInitIndicator.GPIO_Speed = GPIO_Speed_2MHz;
	
	//SPI 250kb/s
	SPI_InitTypeDef _GpioInitSPI250;
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
	
	//SPI 500kb/s
	SPI_InitTypeDef _GpioInitSPI500;
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
	while(1)
	{
	}
	vTaskDelete(NULL);
}

unsigned char sendMessageSPI250(unsigned char command, unsigned char data)
{
	
	while(1)
	{
		
	}
	vTaskDelay(NULL);
	
}