#include "main.h"

int main()
{
		initTask();
	while (1)
	{
			GPIOC->ODR|=GPIO_ODR_ODR7;
	}
	return 0;
}
