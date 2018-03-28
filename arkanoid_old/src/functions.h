#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<fstream>
#include<string>
#include<iostream>
#include <conio.h>
#include"sdl/include/SDL.h"
#include"sdl/include/SDL_main.h"


#define FULLSCREEN		0
#define SCREEN_WIDTH	848
#define SCREEN_HEIGHT	480

#define INFO_HEIGHT		50
#define INFO_COLOR		lightGreen
#define WALL_WIDTH		20
#define WALLPAPER		0

#define MARGIN	2 //DO NOT CHANGE


//BMP
#define NONE_BMP				"none.bmp"
#define CHARSET_BMP				"charset_black.bmp"
#define SMALL_HEART				"small_heart.bmp"
#define STICK_BMP				"stick.bmp"
#define STICK_LONG_BMP			"stick_long.bmp"
#define STICKY_STICK_BMP		"sticky_stick.bmp"
#define LONG_STICKY_STICK_BMP	"long_sticky_stick.bmp"
#define BALL_BMP				"ball.bmp"
#define BULLET_BMP				"bullet.bmp"	
#define BULLET_FALL				"bullet_fall.bmp"		
//BRICKS
#define NORMAL_BMP			"normal.bmp"	
#define HARD_BMP			"hard.bmp"
#define DAMAGED_HARD_BMP	"damaged.bmp"
#define UNBREAKABLE_BMP		"unbreakable.bmp"
#define SPECIAL_BMP			"special.bmp"
//POWER UP
#define POWER_UP_STICKY		"sticky.bmp"
#define POWER_UP_LONG_STICK	"long.bmp"
#define POWER_UP_SLOW		"slow.bmp"
#define POWER_UP_HEART		"heart.bmp"
#define POWER_UP_MULTIBALL  "multiball.bmp"
#define POWER_UP_BULLET  "bulletp.bmp"
//
#define LOAD_LVL_FROM	"levels.txt"
#define LOAD_SCORES_FROM "scores.txt"

#define BRICKS_IN_X					8
#define BRICKS_IN_Y					19
#define BRICK_PADDING				1
#define TOGGLE_EDGES_ABOVE_PADDING 20


#define STICK_CURVATURE 7
#define STICK_SPEED		600

#define BALL_START_SPEED	14
#define BALL_MAX_SPEED		20
#define BALL_ACCELERATION	0.5 // /s
#define BALL_RESET_DISTANCE	150 // pixels after down wall
#define BALL_MAX_NUMBER		3
#define BALL_MAX_ANGLE		60

#define NUMBER_OF_POWERUPS		6
#define POWERUP_TIME			20 
#define POWERUP_HANDLE_NR		25 // IS THE MAX NUMBER OF POWERUP ICONS ON SCREEN AT ONE TIME 
#define POWERUP_ACCELERATION	6 
#define POWERUP_FALLING_SPEED   2



#include "classes.h"

struct boostHelp
{
	int startTime;
	Boost boost;
	boostHelp(Boost b=NONE)
	{
		startTime = SDL_GetTicks();
		boost = b;
	}
	void refresh()
	{
		startTime = SDL_GetTicks();
	}
};



void drawWallpaper(SDL_Surface *screen,SDL_Surface *wallpaper,int bgColor);

double secPassed(int past);
double deltaFunction();

void addScore(SDL_Surface *screen, SDL_Texture *scrtex,
	SDL_Window *window,
	SDL_Renderer *renderer, Charset charset,int score);

void showScores(SDL_Surface *screen, SDL_Texture *scrtex,
	SDL_Window *window,
	SDL_Renderer *renderer, Charset charset);
void fpsTime(double &fps, double &worldTime, int &frames);
void quitP(bool &quit, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Window *window, SDL_Renderer *renderer);
void loadXYManagement(int &x, int &y, int &temp);
bool toggleEdges(Brick *brick[BRICKS_IN_Y][BRICKS_IN_X], int x, int y, Brick::StickedTypes type);

void loadLevel(Brick*bricks[BRICKS_IN_Y][BRICKS_IN_X], Ball* balls[BALL_MAX_NUMBER], boostHelp*events_h[NUMBER_OF_POWERUPS], Powerup*power[POWERUP_HANDLE_NR], Stick *&stick, int &brickCounter, int &lives, int&level);

void startScreen(SDL_Surface *screen, SDL_Texture *scrtex,
	SDL_Window *window,
	SDL_Renderer *renderer, Charset charset, int&level, int&lives,long int&score, bool&quit, bool &endProgram);
void interface(SDL_Surface *screen, SDL_Texture *scrtex,
	SDL_Window *window,
	SDL_Renderer *renderer, Charset charset, int &level,int score, int brickCounter, int &lives, bool &quit);
void drawInfo(SDL_Surface *screen, SDL_Surface *charset,Stick*stick, double worldtime, double fps,int lives,int brickCounter,boostHelp *event_h[NUMBER_OF_POWERUPS],int level,long int score);




/////////////////////////////////////////////////////////////////////////////////////////

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,Uint32 outlineColor, Uint32 fillColor);
void DrawString(SDL_Surface *screen, int x, int y, const char *text,SDL_Surface *charset);

