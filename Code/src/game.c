#include	<stm32f0xx.h>  
#include	"game.h"
#include	"display.h"
#include	"button.h"
#include	"timer.h"
#include	<stdlib.h>
#include	"main.h"
#include	<string.h>

#define size_byte 8
#define start_speed 15
#define start_min_distance 75
#define max_randon_distance 50

const char trex_logo[SIZE_DISP] = 
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
  0xF8, 0xD8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
  0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x80,
  0x00, 0x00, 0x80, 0xC0, 0xF0, 0xF0, 0xF8, 0xFF,
  0xFF, 0xFF, 0xFF, 0x47, 0x45, 0x05, 0x01, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFF,
  0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0x78,
  0x38, 0x3C, 0x78, 0x00, 0x00, 0xC0, 0xE0, 0xF8,
  0xF8, 0x38, 0x1C, 0x1C, 0x1C, 0x38, 0xF8, 0xF8,
  0xE0, 0x80, 0x00, 0x00, 0x18, 0x78, 0xF8, 0xF8,
  0xE0, 0x80, 0x80, 0xE0, 0xF8, 0xF8, 0x78, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xF8,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE,
  0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F,
  0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF,
  0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF,
  0xFE, 0x8E, 0x8E, 0x0E, 0x0E, 0x0E, 0x8F, 0x8F,
  0x8F, 0x07, 0x00, 0x00, 0x80, 0xE0, 0xF9, 0xFF,
  0x7F, 0x1F, 0x3F, 0xFF, 0xFF, 0xF1, 0xC0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07,
  0x06, 0x06, 0xFF, 0xFF, 0xFF, 0x03, 0x03, 0x03,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x05, 0x00, 0x00, 0x00, 0x07,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07,
  0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
  0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03,
  0x03, 0x00, 0x00, 0x02, 0x07, 0x07, 0x07, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

char font_numbers[][6] =
{
	 {0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00} //  0
	,{0x00, 0x42, 0x7f, 0x40, 0x00, 0x00} //  1
	,{0x42, 0x61, 0x51, 0x49, 0x46, 0x00} //  2
	,{0x21, 0x41, 0x45, 0x4b, 0x31, 0x00} //  3
	,{0x18, 0x14, 0x12, 0x7f, 0x10, 0x00} //  4
	,{0x27, 0x45, 0x45, 0x45, 0x39, 0x00} //  5
	,{0x3c, 0x4a, 0x49, 0x49, 0x30, 0x00} //  6
	,{0x01, 0x71, 0x09, 0x05, 0x03, 0x00} //  7
	,{0x36, 0x49, 0x49, 0x49, 0x36, 0x00} //  8
	,{0x06, 0x49, 0x49, 0x29, 0x1e, 0x00} //  9
};

char game_over[] = 
{
	0x3e, 0x41, 0x49, 0x49, 0x7a, 0x00,
	0x7e, 0x11, 0x11, 0x11, 0x7e, 0x00,
	0x7f, 0x02, 0x0c, 0x02, 0x7f, 0x00,
	0x7f, 0x49, 0x49, 0x49, 0x41, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00,
	0x1f, 0x20, 0x40, 0x20, 0x1f, 0x00,
	0x7f, 0x49, 0x49, 0x49, 0x41, 0x00,
	0x7f, 0x09, 0x19, 0x29, 0x46, 0x00,
	
	0x46, 0x49, 0x49, 0x49, 0x31, 0x00,
	0x38, 0x44, 0x44, 0x44, 0x20, 0x00,
	0x38, 0x44, 0x44, 0x44, 0x38, 0x00,
	0x7c, 0x08, 0x04, 0x04, 0x08, 0x00,
	0x38, 0x54, 0x54, 0x54, 0x18, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
	0xFC, 0xFE, 0xFE, 0xFE, 0x1E, 0xDE, 
	0xDE, 0x06, 0x8E, 0xDE, 0xFE, 0xFE, 
	0xDE, 0x1E, 0xFE, 0xFE, 0xFE, 0xFC, 
	0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
	0x3F, 0x7F, 0x7F, 0x7F, 0x78, 0x7B, 
	0x7B, 0x7B, 0x7B, 0x7B, 0x7B, 0x7B, 
	0x7B, 0x78, 0x7F, 0x7F, 0x7F, 0x3F, 
	0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

 char sprite_trex_1[32] =				//zize 16x14(16)
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x80, 0xF8, 0xFC, 0x74, 0x7C, 0x7C, 0x3C, 0x38,
  0x04, 0x04, 0x08, 0x18, 0x1C, 0xFE, 0x9F, 0x1F,
  0x7F, 0x4F, 0x07, 0x02, 0x02, 0x00, 0x00, 0x00};

 char sprite_trex_2[32] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x80, 0xF8, 0xFC, 0x74, 0x7C, 0x7C, 0x3C, 0x38,
  0x04, 0x04, 0x08, 0x18, 0x1C, 0x7E, 0x5F, 0x1F,
  0xFF, 0x8F, 0x07, 0x02, 0x02, 0x00, 0x00, 0x00};

  
char sprite_trex_dead[32] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x80, 0xFC, 0xE0, 0x68, 0x60, 0x7C, 0x3C, 0x38,
  0x04, 0x04, 0x08, 0x18, 0x1C, 0xFE, 0x9F, 0x1F,
  0x7F, 0x4F, 0x07, 0x02, 0x02, 0x00, 0x00, 0x00};

char sprite_cactus_1[16] =				//size 8x14(16)
{ 0xC0, 0xC0, 0x00, 0xFC, 0xFC, 0x00, 0xC0, 0xC0,
  0x0F, 0x1F, 0x1C, 0xFF, 0xFF, 0x1C, 0x1F, 0x0F};

char sprite_cactus_2[32] =
{ 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, // size 16x16
  0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00,
  0x00, 0x07, 0x04, 0xFF, 0xFF, 0x10, 0x1E, 0x00,
  0x00, 0x00, 0x3F, 0x20, 0xFF, 0xFF, 0x10, 0x1E}; 

char sprite_cactus_3[40] =  //size 20x16
{ 0x00, 0x00, 0x80, 0x80,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x3C, 0x20, 0xFF, 0xFF,
  0x08, 0x0E, 0x00, 0x1F,
  0x10, 0xFF, 0xFF, 0x40,
  0x7C, 0x00, 0x38, 0x20,
  0xFF, 0xFF, 0x10, 0x1C};

  
 struct sprite Trex1 = {16, 2, sprite_trex_1};
 struct sprite Trex2 = {16, 2, sprite_trex_2};
 struct sprite TrexDead = {16, 2, sprite_trex_dead};
 struct sprite Cactus1 = {8, 2, sprite_cactus_1};
 struct sprite Cactus2 = {16, 2, sprite_cactus_2};
 struct sprite Cactus3 = {20, 2, sprite_cactus_3};
 struct sprite Game_over = {54, 4, game_over};
 
void Begin_Game(unsigned int rand_number)
	{
		srand(rand_number);
		long_press = 0;
		while(1)
		{			
			button = 0;
			Game_Trex();
			if (long_press == 1)
				break;
		}
		return;
	}
 
 void Game_Trex(void)
 {
	 uint32_t speed = start_speed, swipe_bit, buf_swipe = 0, score = 0, run_tirex = 0, froze_tirex = 0, min_distance = start_min_distance;
	int flag_jump = 0, flag_end_game = 0, flag_up = 0;
	 
	struct location LOC_TREX = {20, 0, Image2};
	struct location LOC_CACTUS1 = {200, 0, Image1};
	struct location LOC_CACTUS2 = {-30, 0, Image2};
	
	 
	 TIM3->CR1 |= TIM_CR1_CEN;
	 while(1)
	 {
		 
		 Buf_Clear();
		 buf_swipe += speed;
		 swipe_bit = buf_swipe/10;
		 buf_swipe = buf_swipe-(swipe_bit*10);
		 
		 // end game:
		 if(flag_end_game == 1)
		 {
			 TIM3->CR1 &= ~TIM_CR1_CEN;
			 
			score--;
			 
			memcpy (&game_over[90], &font_numbers[score/100%10][0], 6); 
			memcpy (&game_over[96], &font_numbers[score/10%10][0], 6);
			memcpy (&game_over[102], &font_numbers[score%10][0], 6);
			

			Output_Sprite(LOC_TREX.x, LOC_TREX.y, TrexDead);
			 
			if (LOC_CACTUS1.x<SIZE_DISP)
			{
				if (LOC_CACTUS1.Type == Image1)
					Output_Sprite(LOC_CACTUS1.x, LOC_CACTUS1.y, Cactus1);
				if (LOC_CACTUS1.Type == Image2)
					Output_Sprite(LOC_CACTUS1.x, LOC_CACTUS1.y, Cactus2);
				if (LOC_CACTUS1.Type == Image3)
					Output_Sprite(LOC_CACTUS1.x, LOC_CACTUS1.y, Cactus3);
			};
		
			if (LOC_CACTUS2.x<SIZE_DISP)
			{
				if (LOC_CACTUS2.Type == Image1)
					Output_Sprite(LOC_CACTUS2.x, LOC_CACTUS2.y, Cactus1);
				if (LOC_CACTUS2.Type == Image2)
					Output_Sprite(LOC_CACTUS2.x, LOC_CACTUS2.y, Cactus2);
				if (LOC_CACTUS2.Type == Image3)
					Output_Sprite(LOC_CACTUS2.x, LOC_CACTUS2.y, Cactus3);
			};
			
			Output_Sprite(40, 0, Game_over);
			
			Output_Image();
			while ((button == 0) && (long_press == 0));
			return;				
			 
		 }
		 
		 //running animation:
		 run_tirex++;
		if (run_tirex == 5)
		{
			if(LOC_TREX.Type == Image1)
				LOC_TREX.Type = Image2;
			else
				LOC_TREX.Type = Image1;
			run_tirex = 0;
		}

		// location and type cactus:		
		 LOC_CACTUS1.x -= swipe_bit;
		 LOC_CACTUS2.x -= swipe_bit;
		 
		 if (LOC_CACTUS1.Type == Image1)
		 {
				if (LOC_CACTUS1.x < (0-Cactus1.wigth))
				{
					LOC_CACTUS1.x = LOC_CACTUS2.x + min_distance + (rand()%max_randon_distance);
					LOC_CACTUS1.Type = (type)(rand()%3);
					score++;
					if ((score%6) == 0)
					{
						speed++;
						min_distance += 2; 
					}
				}
					
		 }
		 if (LOC_CACTUS1.Type == Image2)
		 {
			  if (LOC_CACTUS1.x < (0-Cactus2.wigth))
				{
					LOC_CACTUS1.x = LOC_CACTUS2.x + min_distance + (rand()%max_randon_distance);
					LOC_CACTUS1.Type = (type)(rand()%3);
					score++;
					if ((score%6) == 0)
					{
						speed++;
						min_distance += 2; 
					}
				}
		 }
		 if (LOC_CACTUS1.Type == Image3)
		 {
			 if (LOC_CACTUS1.x < (0-Cactus3.wigth))
				{
					LOC_CACTUS1.x = LOC_CACTUS2.x + min_distance + (rand()%max_randon_distance);
					LOC_CACTUS1.Type = (type)(rand()%3);
					score++;
					if ((score%6) == 0)
					{
						speed++;
						min_distance += 2; 
					}
				}
		 }
		 
		if (LOC_CACTUS2.Type == Image1)
		 {
				if (LOC_CACTUS2.x < (0-Cactus1.wigth))
				{
					LOC_CACTUS2.x = LOC_CACTUS1.x + min_distance + (rand()%max_randon_distance);
					LOC_CACTUS2.Type = (type)(rand()%3);
					score++;
					if ((score%6) == 0)
					{
						speed++;
						min_distance += 2; 
					}
				}
					
		 }
		 if (LOC_CACTUS2.Type == Image2)
		 {
			  if (LOC_CACTUS2.x < (0-Cactus2.wigth))
				{
					LOC_CACTUS2.x = LOC_CACTUS1.x + min_distance + (rand()%max_randon_distance);
					LOC_CACTUS2.Type = (type)(rand()%3);
					score++;
					if ((score%6) == 0)
					{
						speed++;
						min_distance += 2; 
					}
				}
		 }
		 if (LOC_CACTUS2.Type == Image3)
		 {
			 if (LOC_CACTUS2.x < (0-Cactus3.wigth))
				{
					LOC_CACTUS2.x = LOC_CACTUS1.x + min_distance + (rand()%max_randon_distance);
					LOC_CACTUS2.Type = (type)(rand()%3);
					score++;
					if ((score%6) == 0)
					{
						speed++;
						min_distance += 2; 
					}
				}
		 }


		 // jump t-rex: 
		 if (button==1)
		 {
			 if (flag_jump == 0)
				 flag_up = 1;
			 flag_jump = 1;
			 button = 0;
		 }
		 
			 
		 if ((flag_jump == 1)&&(flag_up ==1)&&(LOC_TREX.y < 18))
		 {
			 LOC_TREX.y++;
			 LOC_TREX.Type = Image1;
		 }
		 else if ((flag_jump == 1)&&(flag_up == 1)&&(LOC_TREX.y == 18))
		 	 flag_up = 0;
			 
		 if ((flag_jump == 1)&&(flag_up == 0)&&(LOC_TREX.y > 0))
		 {
			 if(froze_tirex < 8)
				 froze_tirex++;
			else
				LOC_TREX.y--;
			LOC_TREX.Type = Image1;
		 }
		 if ((flag_jump == 1)&&(flag_up == 0)&&(LOC_TREX.y == 0))
		 { 
			 froze_tirex = 0;
			 flag_jump = 0;
			 button = 0;
		 }
		 
		 
		 // output image:

		 
		 if(LOC_TREX.Type == Image1)
				Output_Sprite(LOC_TREX.x, LOC_TREX.y, Trex1);
		 if(LOC_TREX.Type == Image2)
				Output_Sprite(LOC_TREX.x, LOC_TREX.y, Trex2);
		 
		 if (LOC_CACTUS1.x<SIZE_DISP)
		 {
			 if (LOC_CACTUS1.Type == Image1)
				flag_end_game |= Output_Sprite(LOC_CACTUS1.x, LOC_CACTUS1.y, Cactus1);
			 if (LOC_CACTUS1.Type == Image2)
				flag_end_game |= Output_Sprite(LOC_CACTUS1.x, LOC_CACTUS1.y, Cactus2);
			 if (LOC_CACTUS1.Type == Image3)
				flag_end_game |= Output_Sprite(LOC_CACTUS1.x, LOC_CACTUS1.y, Cactus3);
		 };
		
		 if (LOC_CACTUS2.x<SIZE_DISP)
		{
			 if (LOC_CACTUS2.Type == Image1)
				flag_end_game |= Output_Sprite(LOC_CACTUS2.x, LOC_CACTUS2.y, Cactus1);
			 if (LOC_CACTUS2.Type == Image2)
				flag_end_game |= Output_Sprite(LOC_CACTUS2.x, LOC_CACTUS2.y, Cactus2);
			 if (LOC_CACTUS2.Type == Image3)
				flag_end_game |= Output_Sprite(LOC_CACTUS2.x, LOC_CACTUS2.y, Cactus3);
		 
			
		 
		 Output_Image();
	 }
		 frame = 0;
		while (frame == 0);
		 
		 if (long_press == 1)
				break;
	 }
	 return;
 }
 

int Output_Sprite( int x, int y, struct sprite image) //x = 0..127, y = 0..31
{

	int begin_string;
	int end = 0;
	if (y%size_byte)
	{
		image.height++;
		begin_string =  DISPLAY_BYTE_HEIGHT - (y / size_byte + image.height);
		for(int z = 0; z < image.height; z++)
		{
			for(int r = 0; r < image.wigth; r++)
			{
				if (z == 0)
				{
					if ((y + ((image.height - 1) * size_byte)) < 32) //
					{
						if(buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] & *(image.adress + (z * image.wigth)+r) << (size_byte - (y%size_byte)))
							end = 1;
						buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] |= *(image.adress + (z * image.wigth)+r) << (size_byte - (y%size_byte));
					}
				}
				else if(z == (image.height-1))
				{
					if(buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] & *(image.adress + ((z-1)* image.wigth)+r) >> (y%size_byte))
						end = 1;
				  buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] |= *(image.adress + ((z-1)* image.wigth)+r) >> (y%size_byte);
				}
				
				else 		
				{
					if (buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] & *(image.adress + (z * image.wigth)+r) << (size_byte - (y%size_byte)))
						end = 1;
					buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] |= *(image.adress + (z * image.wigth)+r) << (size_byte - (y%size_byte));
					if (buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] & *(image.adress + ((z-1)* image.wigth)+r) >> (y%size_byte))
						end = 1;
					buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] |= *(image.adress + ((z-1)* image.wigth)+r) >> (y%size_byte);
					
				}
			}
		}
	}
	else
	{
		if ((x+image.wigth)>DISPLAY_WIGHT)
		{
			int real_image_wight;
			 real_image_wight = image.wigth - ((image.wigth + x) - DISPLAY_WIGHT);
			
			begin_string =  DISPLAY_BYTE_HEIGHT - (y / size_byte + image.height);
			for(int z = 0; z < image.height; z++)
			{
				for(int r = 0; r < real_image_wight; r++)
				{
					if(buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] & *(image.adress + (z * image.wigth)+r))
						end=1;
					buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] |= *(image.adress + (z * image.wigth)+r);
				}
			}
		}
		else if (x<0)
		{
			int real_image_wight, swype_byte;
			
			 real_image_wight = image.wigth + x;
			swype_byte = image.wigth - real_image_wight;
			
			begin_string =  DISPLAY_BYTE_HEIGHT - (y / size_byte + image.height);
			
			x = 0;
			for(int z = 0; z < image.height; z++)
			{
				for(int r = 0; r < real_image_wight; r++)
				{
					if(buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] & *(image.adress + (z * image.wigth)+r+swype_byte))
						end = 1;
					buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] |= *(image.adress + (z * image.wigth)+r+swype_byte);
				}
			}
		}
		else
		{ 
			begin_string =  DISPLAY_BYTE_HEIGHT - (y / size_byte + image.height);
			for(int z = 0; z < image.height; z++)
			{
				for(int r = 0; r < image.wigth; r++)
				{	
					if (buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] & *(image.adress + (z * image.wigth)+r))
						end = 1;
					buffer[(begin_string+z)*DISPLAY_WIGHT+x+r] |= *(image.adress + (z * image.wigth)+r);
				}
			}
		}
	}
		return end;
}
