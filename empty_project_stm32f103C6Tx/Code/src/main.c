#include "main.h"

#define DEBUG_PIN_SWITCH	GPIOC-> ODR ^= GPIO_ODR_ODR13
#define DEBUG_PIN_OFF			GPIOC-> BSRR |= GPIO_BSRR_BR13

void debug_pin_init(void)
{
	RCC-> APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC-> CRH |= GPIO_CRH_MODE13;
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