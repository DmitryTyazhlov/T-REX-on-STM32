#include	<stm32f0xx.h>                  // Device header
#include	"display.h"


//extern uint8_t buffer[SIZE_DISP];

char buffer[SIZE_DISP];



void Output_Image(void)
{
//	for(uint32_t z = 0; z<20; z++);
	I2C_Write_Command(0x21); //column
	I2C_Write_Command(0);
	I2C_Write_Command(127);
//	for(uint32_t z = 0; z<20; z++);
	I2C_Write_Command(0x22); //page
	I2C_Write_Command(0);
	I2C_Write_Command(4);	
//		for(uint32_t z = 0; z<20; z++);
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | ((254+1)<<16) | I2C_CR2_AUTOEND;			
	
	I2C1->CR2 |= I2C_CR2_START;	
	
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = DATA;
	
	for(uint32_t byte = 0; byte < 254; byte++)
	{
		while (!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = *(buffer+byte);
	}
	
//		for(uint32_t z = 0; z<20; z++);
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | ((254+1)<<16) | I2C_CR2_AUTOEND;			
	
	I2C1->CR2 |= I2C_CR2_START;	
	
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = DATA;
	
	for(uint32_t byte = 0; byte < 254; byte++)
	{
		while (!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = *(buffer+byte+254);
	}
	
//		for(uint32_t z = 0; z<20; z++);
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | ((4+1)<<16) | I2C_CR2_AUTOEND;			
	
	I2C1->CR2 |= I2C_CR2_START;	
	
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = DATA;
	
	for(uint32_t byte = 0; byte < 4; byte++)
	{
		while (!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = *(buffer+byte+508);
	}
}

void I2C_Init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	GPIOA->MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;

	
	GPIOA->AFR[1] |= (4<<GPIO_AFRH_AFSEL9_Pos) | (4<<GPIO_AFRH_AFSEL10_Pos);
	
	//I2C1->TIMINGR |= (uint32_t)  0x00B01A4B; //0x00B01A4B;
	I2C1->CR1 = I2C_CR1_PE;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | (1<<17) | I2C_CR2_AUTOEND; // 2 byte mode
	

	
}

void I2C_Write_Command(uint8_t command)
{
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | (2<<16) | I2C_CR2_AUTOEND; // 2 byte mode
	I2C1->CR2 |= I2C_CR2_START;
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = COM;
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = command;	

}
void Buf_Clear(void)
{
	for(uint32_t byte = 0; byte < SIZE_DISP; byte++) 
		buffer[byte] = 0;
}

void Display_Clear(void)
{
	
	for (uint8_t y = 0; y<2; y++)
	{
	I2C_Write_Command(0x21); //column
	I2C_Write_Command(0);
	I2C_Write_Command(127);
	I2C_Write_Command(0x22); //page
	I2C_Write_Command(y*2);
	I2C_Write_Command((y*2)+1);
	
	
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | (255<<16) | I2C_CR2_AUTOEND; // 255 byte mode
	I2C1->CR2 |= I2C_CR2_START;
	
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = DATA;
	
		for (uint32_t gfga = 0; gfga < 254; gfga++)
		{
			while (!(I2C1->ISR & I2C_ISR_TXIS));
			I2C1->TXDR = 0x00;
		}

	}
	
	I2C_Write_Command(0x21); //column
	I2C_Write_Command(126);
	I2C_Write_Command(127);
	I2C_Write_Command(0x22); //page
	I2C_Write_Command(0);
	I2C_Write_Command(7);
	
	
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | (17<<16) | I2C_CR2_AUTOEND; // 255 byte mode
	I2C1->CR2 |= I2C_CR2_START;
	
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = DATA;
	
	for (uint32_t gfga = 0; gfga < 16; gfga++)
	{
		while (!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = 0x00;
	}
	
	/*
	I2C_Write_Command(0x21); //column
	I2C_Write_Command(126);
	I2C_Write_Command(127);
	I2C_Write_Command(0x22); //page
	I2C_Write_Command(0);
	I2C_Write_Command(7);
	
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1);
	I2C1->CR2 |= I2C_CR2_START;
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = DATA;
	
	for (uint32_t gfga = 0; gfga < 512 ; gfga++)
	{
		while (!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = 0x00;
	}
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->CR2 |= I2C_CR2_STOP;
	*/
}
/*
void I2C_Write_Data(uint8_t x_start, uint8_t x_end, uint8_t string_start, uint8_t string_end, uint32_t quantity_byte, const uint8_t *data)
{
	for(uint32_t z = 0; z<40; z++);
	I2C_Write_Command(0x21); //column
	I2C_Write_Command(x_start);
	I2C_Write_Command(x_end);
	for(uint32_t z = 0; z<40; z++);
	I2C_Write_Command(0x22); //page
	I2C_Write_Command(string_start);
	I2C_Write_Command(string_end);	
		for(uint32_t z = 0; z<40; z++);
	I2C1->CR2 = 0;
	I2C1->CR2 |= (I2C1_DISP_ADDRESS << 1) | ((quantity_byte+1)<<16) | I2C_CR2_AUTOEND;			
	
	I2C1->CR2 |= I2C_CR2_START;	
	
	while (!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = DATA;
	
	for(uint32_t byte = 0; byte < quantity_byte; byte++)
	{
		while (!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = *(data+byte);
	}
	
}
	*/

void Display_Init(void)

{
	uint8_t Disp_init[] = 
	{
0xAF,     // Display Off** 0xAE

0xD5,     // clock
0x80,     // upper nibble is rate, lower nibble is divisor***

0xA8,     // Set multiplex ratio
0x1F,     // rtfm

0xD3,     // Set Display Offset 0xD3
0x00,     // no offset

0x40,     // Set display start line

0x8D,     // Set charge pump
0x14,     // 0x10 - Suplied Externally

0xA0,     // Segrment remap - 0xA1 (A0->SEG0=column0, A1->SEG0=column127)

0xC0,     // Set COM output scan Direction (C0=up, C8=down)

0xDA,     // Seet COM pins hardware configuration
0x02,     //  bits [5],[4] & b1=1 0x02=128x32 0x12=128x64
	
0x81,     // Set Contrast 0x81
0xCF,     // 0x9F - Suplied Externally (CF)
	
0xD9,     // Set Pre-Charge period
0xF1,     // 0x22 - Suplied Externally
	
0xDB,     // Set VCOMH Deselect Level
0x70,     // 
	
0xA4,     // Set entire DISPLAY on/off
	
0xA6,     // Normal Display 0xA6 (Invert A7)
	
0x20,     // Set Memory Addressing Mode
0x00     // Default => 0x02
};
	
	for(uint32_t x = 0; x<24; x++) I2C_Write_Command(Disp_init[x]);
	for(uint32_t z = 0; z<1000; z++);
}
