
#include "delay.h"
#include "stm32f10x.h"

void delay_ms(unsigned int delay)
{
     TIM7->PSC = SystemCoreClock / 1000 + 1;
     TIM7->ARR = delay; 
     TIM7->EGR |= TIM_EGR_UG;
     TIM7->CR1 |= TIM_CR1_CEN | TIM_CR1_OPM;
     while ((TIM7->CR1 & TIM_CR1_CEN) != 0);
}

void delay_us(unsigned int delay)
{
     TIM7->PSC = SystemCoreClock / 1000000 + 1;
     TIM7->ARR = delay; 
     TIM7->EGR |= TIM_EGR_UG;
     TIM7->CR1 |= TIM_CR1_CEN | TIM_CR1_OPM;
     while ((TIM7->CR1 & TIM_CR1_CEN) != 0);
}


	
