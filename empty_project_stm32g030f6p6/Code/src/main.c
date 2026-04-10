#include "main.h"

int main(void)
{
	RCC-> IOPENR |= RCC_IOPENR_GPIOAEN;
	GPIOA-> MODER &= ~GPIO_MODER_MODE8_1;
  while (1)
  {
    for(uint32_t clock_i = 0; clock_i < 500000; clock_i++);
	GPIOA-> BSRR |= GPIO_BSRR_BR8;
    for(uint32_t clock_i = 0; clock_i < 500000; clock_i++);
	GPIOA-> BSRR |= GPIO_BSRR_BS8;
  }
}