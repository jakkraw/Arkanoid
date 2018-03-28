#include "functions.h"


Powerup::Powerup(Stick *stick,int x, int y,Boost type_)
{
	posX = x;
	posY = y;
	acceleration = POWERUP_ACCELERATION;
	type = type_;
	stick_=stick;
	whenCreatedTimer=SDL_GetTicks();
	score =500;
	switch (type_)
	{
	case STICKY:
		if (SDL_LoadBMP(POWER_UP_STICKY)) bmp = SDL_LoadBMP(POWER_UP_STICKY);
		
		break;
	case LONG:
		if (SDL_LoadBMP(POWER_UP_LONG_STICK)) bmp = SDL_LoadBMP(POWER_UP_LONG_STICK);
		break;
	case SLOW:
		if (SDL_LoadBMP(POWER_UP_SLOW)) bmp = SDL_LoadBMP(POWER_UP_SLOW);
		break;
	case HEART:
		if (SDL_LoadBMP(POWER_UP_HEART)) bmp = SDL_LoadBMP(POWER_UP_HEART);
		break;
	case MULTIBALL:
		if (SDL_LoadBMP(POWER_UP_MULTIBALL)) bmp = SDL_LoadBMP(POWER_UP_MULTIBALL);
		break;
	case BULLET:
		if (SDL_LoadBMP(BULLET_FALL)) bmp = SDL_LoadBMP(BULLET_FALL);
		break;
	}
	
	SDL_SetColorKey(bmp, true, 0x000000);
}

void movePowerUps(Powerup *powerUp[POWERUP_HANDLE_NR], int fallingSpeed, double delta)
{
	for (int i = 0; i < POWERUP_HANDLE_NR; i++)
	{
		if (powerUp[i])
		{
			powerUp[i]->posY += (fallingSpeed + powerUp[i]->acceleration*(SDL_GetTicks()-powerUp[i]->whenCreatedTimer)*0.01)*delta;
		}
	}
}

void drawAllPowerUps(Powerup *power[POWERUP_HANDLE_NR], SDL_Surface *screen)
{
	for (int i = 0; i < POWERUP_HANDLE_NR; i++)
	{
		if (power[i]!=NULL)
		{
			power[i]->draw(screen);
		}
	}
}


void Stick::powerUpCollision(Powerup *power[POWERUP_HANDLE_NR],Boost &initBoost,long int&score)
{

	for (int i = 0; i < POWERUP_HANDLE_NR; i++)
	{
		if (power[i] != NULL)
		{
			//HITS STICK
			if ((power[i]->edge(Object::DOWN) >= edge(Object::UP)-MARGIN) && (power[i]->edge(Object::DOWN) < edge(Object::UP)+MARGIN)
				&& (power[i]->edge(Object::LEFT) <= edge(Object::RIGHT)) && (power[i]->edge(Object::RIGHT) >= edge(Object::LEFT)))
			{
				initBoost = power[i]->type;
				score += power[i]->score;
				delete (power[i]);
				power[i] = NULL;	
			}
			//GETS UNDER
			else if ((power[i]->edge(Object::UP) > SCREEN_HEIGHT + BALL_RESET_DISTANCE))
			{
				delete (power[i]);
				power[i] = NULL;
			}
		}
	}
}


void Brick::spawnPowerUp(Powerup*power[POWERUP_HANDLE_NR], Stick *stick)
{
	static int count;
	if (count == POWERUP_HANDLE_NR)
	{
		count = 0;
	}

	if (power[count] != NULL)
		{
		delete power[count];
			power[count] = NULL;
		}
	
		switch ( rand()% NUMBER_OF_POWERUPS )
		{
		case STICKY:
			power[count] = new Powerup(stick, posX, posY, STICKY);
			count++;
			break;
			
		case LONG:
			power[count] = new Powerup(stick, posX, posY, LONG);
			count++;
			break;

		case MULTIBALL:
			power[count] = new Powerup(stick, posX, posY, MULTIBALL);
			count++;
			break;

		case SLOW:
			power[count] = new Powerup(stick, posX, posY, SLOW);
			count++;
			break;

		case HEART:
			power[count] = new Powerup(stick, posX, posY, HEART);
			count++;
			break;
		case BULLET:
			power[count] = new Powerup(stick, posX, posY, BULLET);
			count++;
			break;
		}

}



void startBoost(boostHelp *event_h[NUMBER_OF_POWERUPS], Boost &initBoost, Stick *stick, Ball *balls[BALL_MAX_NUMBER],int &lives,double time)
{
	//INSTANT POWERUPS
	switch (initBoost)
	{
	case HEART:
		lives++;

		break;
	case MULTIBALL:
		doMultiball(balls,stick);
		break;
	}


	// START TIMERS
	if (initBoost!=NONE)
	{
		if (!event_h[initBoost])event_h[initBoost] = new boostHelp(initBoost);
		else event_h[initBoost]->refresh();
	}

	// TOGGLE EVENTS
	for (int i = 0; i < NUMBER_OF_POWERUPS; i++)
	{
		if (event_h[i] != NULL)
		{
			//TIMED
			if (secPassed(event_h[i]->startTime) <= POWERUP_TIME)
			{
				//EFFECT STARTS
				switch (i)
				{
				case STICKY:
					stick->sticky = true;
					break;

				case LONG:
					stick->long_stick = true;
					break;

				case SLOW:
					for (int i = 0; i < BALL_MAX_NUMBER; i++)
					{
						if (balls[i]) balls[i]->slow = true;
					}
					break;
				case BULLET:
					stick->bullet = true;
					break;

				}
			}
			else
			{ 
				//EFFECT ENDS
				switch (i)
				{
				case STICKY:
					stick->sticky = false;
					for (int i = 0; i < BALL_MAX_NUMBER; i++)
					{
						if (balls[i]) balls[i]->unstick();
					}

					break;

				case LONG:
					stick->long_stick = false;
					break;

				case SLOW:
					for (int i = 0; i < BALL_MAX_NUMBER; i++)
					{
						if (balls[i]) balls[i]->slow = false;		
						
					}
					break;
				case BULLET:
					stick->bullet = false;
					break;
				}

				//DELETE UNUSED
				delete event_h[i];
				event_h[i] = NULL;
			}
		}
		
		}	
	

	// RESET TRIGGER
	initBoost = NONE;

}

