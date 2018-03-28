#include "functions.h"

Stick::Stick()
{
	
	bmp = SDL_LoadBMP(STICK_BMP);

	if (!bmp)
	{
		SDL_FreeSurface(bmp);
		SDL_Quit();
		exit(1);
	}
	posY = SCREEN_HEIGHT - (bmp->h/2); 
	speed = 0;
	sticky = false;
	long_stick = false;
	bullet = false;
	SDL_SetColorKey(bmp, true, 0x000000);
	
}



void Stick::moveStick(Direction direction)
{
	switch (direction)
	{
	case LEFT:
		speed = -STICK_SPEED;
		break;
	case RIGHT:
		speed = STICK_SPEED;
		break;
	default:
		speed = 0;
	}

}

void Stick::movement(double delta)
{
	if ( !sticky && !long_stick && (bmp != SDL_LoadBMP(STICK_BMP)))
	{
		bmp = SDL_LoadBMP(STICK_BMP); 
		SDL_SetColorKey(bmp, true, 0x000000);
		posY = SCREEN_HEIGHT - (bmp->h / 2);
	}

	else if (sticky && long_stick && (bmp != SDL_LoadBMP(LONG_STICKY_STICK_BMP)))
	{
		bmp = SDL_LoadBMP(LONG_STICKY_STICK_BMP);
		SDL_SetColorKey(bmp, true, 0x000000);
		posY = SCREEN_HEIGHT - (bmp->h / 2);
	}

	else if (sticky && (bmp != SDL_LoadBMP(STICKY_STICK_BMP)))
	{
		bmp = SDL_LoadBMP(STICKY_STICK_BMP);
		SDL_SetColorKey(bmp, true, 0x000000);
		posY = SCREEN_HEIGHT - (bmp->h / 2);
	}

	else if ( long_stick && (bmp != SDL_LoadBMP(STICK_LONG_BMP)))
	{
		bmp = SDL_LoadBMP(STICK_LONG_BMP);
		SDL_SetColorKey(bmp, true, 0x000000);
		posY = SCREEN_HEIGHT - (bmp->h / 2);
	}
	

	// FIXES BUG WHEN TURNING INTO LONG
	if (edge(Object::LEFT) <= WALL_WIDTH-MARGIN) posX = WALL_WIDTH + bmp->w / 2;
	if (edge(Object::RIGHT) >= SCREEN_WIDTH - WALL_WIDTH + MARGIN) posX = SCREEN_WIDTH - WALL_WIDTH - bmp->w / 2;
	////////////////////////////////

	//MOVE
	if (((speed >= 0) && (edge(Object::RIGHT)<SCREEN_WIDTH-WALL_WIDTH))
	||	((speed <= 0) && (edge(Object::LEFT)>WALL_WIDTH)))
	{
		posX += speed*delta;
	}



}





