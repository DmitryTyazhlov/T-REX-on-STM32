#ifndef  	__display_h_
#define		__display_h_

#include	<stdint.h>

#define		I2C1_DISP_ADDRESS	0b0111100
#define		COM					0b10000000
#define		DAT					0b11000000
#define		DATA				0b01000000
#define		SIZE_DISP			512
#define		DISPLAY_WIGHT		128
#define		DISPLAY_BYTE_HEIGHT		4
/*
  struct Name {
	uint8_t x, y;
	uint32_t size_byte, size_bit;
	uint8_t *buffer;
} display;
*/
 

 
  
extern char buffer[SIZE_DISP];
void Buf_Clear(void);
void Output_Image(void);
void I2C_Init(void);
//void I2C_Write_Data(uint8_t x_start, uint8_t x_end, uint8_t string_start, uint8_t string_end, uint32_t quantity_byte, const uint8_t *data);
void Display_Clear(void);
void I2C_Write_Command(uint8_t command);
void Display_Init(void);








#endif
