#include "main.h"

#define DEBUG_PIN_SWITCH	GPIOC-> ODR ^= GPIO_ODR_ODR_13
#define DEBUG_PIN_OFF			GPIOC-> BSRR |= GPIO_BSRR_BR_13

void debug_pin_init(void)
{
	RCC-> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC-> MODER |= GPIO_MODER_MODER13_0;
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