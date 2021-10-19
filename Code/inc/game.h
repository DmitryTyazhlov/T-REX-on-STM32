#ifndef		__game_h_
#define		__game_h_

#include	"display.h"

extern const char trex_logo[SIZE_DISP];

typedef enum type
{
	Image1,
	Image2,
	Image3,
}type;

struct sprite
 {
	int wigth;
	int height;
	char* adress;
 };
  struct location
 {
   int x;
	int y;
   type Type;
 };

	void Game_Trex(void);
	int Output_Sprite(int x, int y, struct sprite image);
	void Begin_Game(unsigned int);

#endif
