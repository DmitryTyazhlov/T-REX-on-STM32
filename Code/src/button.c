#include	<stm32f0xx.h>                  // Device header
#include	"button.h"
#include	"timer.h"

int button = 0;

void EXTI2_3_IRQHandler(void)
{
	if (!(GPIOA->IDR & GPIO_IDR_3))
	{
		button = 1;
		TIM14->CR1 |= TIM_CR1_CEN;
	}
	else 
	{
		TIM14->CR1 &= ~TIM_CR1_CEN;
		count_time = 0;
	}
	EXTI->PR |= EXTI_PR_PR3;
}

void Button_Init(void)
{
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
	EXTI->FTSR |= EXTI_FTSR_TR3;
	EXTI->RTSR |= EXTI_RTSR_TR3;
	EXTI->IMR |= EXTI_IMR_MR3;
	
	NVIC_EnableIRQ(EXTI2_3_IRQn);
	NVIC_SetPriority(EXTI2_3_IRQn,0);
}
