#include	 <stm32f0xx.h>                  // Device header
#include 	"display.h"
#include	"timer.h"
#include	"button.h"
#include	"game.h"
#include 	"main.h"
#include	<string.h>


int main(void)
{
	for(uint32_t z = 0; z<20000; z++);

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	I2C_Init();
	Display_Init();
	Timer_Init();
	Button_Init();
	Display_Clear();
	extern const char trex_logo[SIZE_DISP];
	unsigned int srand_number;
	
	
	while(1)
	{
		 
		while(1)
		{
		
			button = 0;
			long_press = 0;
			
			for (int x = 0; x < SIZE_DISP; x++)
			{
				buffer[x] = trex_logo[x];
			}
			Output_Image();
			while(1)
			{
				srand_number++;
				if(button == 1)
					break;
			}
			break;
		}
				
		Begin_Game(srand_number);
	}
}
