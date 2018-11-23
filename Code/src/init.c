#include "init.h"

void initTask(void)
{
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_4);
	RCC_PLLCmd(ENABLE);
	
	GPIO_InitTypeDef GPIO_INIT_LED;
	RCC_Ah
	GPIO_INIT_LED.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_INIT_LED.GPIO_Pin = GPIO_Pin_7;
	GPIO_INIT_LED.GPIO_Speed = GPIO_Speed_2MHz;
}
