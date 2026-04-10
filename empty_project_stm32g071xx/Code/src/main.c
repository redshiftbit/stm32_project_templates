#include "main.h"

#define DEBUG_PIN_SWITCH	GPIOB->ODR ^= GPIO_ODR_OD1
#define DEBUG_PIN_OFF			GPIOB->BSRR |= GPIO_BSRR_BR1

void debug_pin_init(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE1_1;	// output mode enable
	DEBUG_PIN_OFF;
}

int main(void)
{
  debug_pin_init();
  while (1)
  {
    for(uint32_t clock_i = 0; clock_i < 500000; clock_i++);
    DEBUG_PIN_SWITCH;
  }
}