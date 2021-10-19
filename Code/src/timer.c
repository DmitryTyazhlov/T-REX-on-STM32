#include 	"timer.h"
#include	<stm32f0xx.h>

int frame = 0, long_press = 0, count_time = 0;

void TIM14_IRQHandler(void)
{
	if (count_time == 1)
		long_press = 1;
	count_time++;
	TIM14->SR &= ~TIM_SR_UIF; 
}

void TIM3_IRQHandler(void)
{
	frame = 1;
	TIM3->SR &= ~TIM_SR_UIF; 
}

void Timer_Init (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	TIM14->PSC = SystemCoreClock / 1000 - 1; // button 700ms
	TIM14->ARR = 700 - 1;                         
	TIM14->DIER |= TIM_DIER_UIE;	

	TIM3->PSC = SystemCoreClock / 1000 - 1; // frame 20ms
	TIM3->ARR = 20 - 1;                                           
	TIM3->DIER |= TIM_DIER_UIE;
	
	
	NVIC_EnableIRQ(TIM14_IRQn); 
	NVIC_EnableIRQ(TIM3_IRQn);                    
	
//	TIM3->CR1 |= TIM_CR1_CEN;

}
