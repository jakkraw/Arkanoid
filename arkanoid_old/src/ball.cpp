#include "functions.h"


Ball::Ball(Stick *stick, bool onMulti)
{
	bmp = SDL_LoadBMP(BALL_BMP);
	// if not then TODO

	SDL_SetColorKey(bmp, true, 0x000000);

	stick_ = stick; // ball remembers on which stick to bounce
	speed = BALL_START_SPEED;
	distanceFromStick_ = 0;
	slow = false;

	posY = stick_->edge(UP) - bmp->h / 2 + MARGIN;

	if (!onMulti)
	{
		started = false;
		vectorX = 0;
		vectorY = 0;
		posX = stick_->posX;
		
	}

	if (onMulti)
	{
		started = true;
	}

}



void Ball::unstick()
{
	if ((!vectorX ) && (!vectorY))
	{
		if ((edge(DOWN) >= stick_->edge(UP) - MARGIN) && (edge(DOWN) <= stick_->edge(UP)+MARGIN))
		{
			if ((edge(RIGHT) >= stick_->edge(LEFT)) && (edge(LEFT) <= stick_->edge(RIGHT)))
			{
				started = true;
				posY -= MARGIN;
				vectorX = 0;
				vectorY = -1;
				changeAngle();
				
			}
		}
	}
	
}

void  Ball::distanceFromStick()
{
	distanceFromStick_ = posX - stick_->posX;
}


void Ball::changeAngle()
{
		distanceFromStick();
		double inclination = distanceFromStick_ / (stick_->bmp->w / 2);
		double angle = atan2(vectorX, vectorY);

		vectorX = 30 * sin((angle + BALL_MAX_ANGLE*inclination)* M_PI / 180.0);
		vectorY = -30 * cos((angle + BALL_MAX_ANGLE*inclination)* M_PI / 180.0);
		
	
}


void Ball::collision()
{

	if (edge(LEFT) <= WALL_WIDTH) //LEFT WALL
	{
		vectorX = -vectorX;
		posX += MARGIN;
	}

	if (edge(RIGHT) >= SCREEN_WIDTH-WALL_WIDTH) //RIGHT WALL
	{
		vectorX = -vectorX;
		posX -= MARGIN;
	}

	if (edge(UP) <= INFO_HEIGHT) //UP WALL
	{
		vectorY = -vectorY;
		posY += MARGIN;
	}


	if	((edge(RIGHT) >= stick_->edge(LEFT)-MARGIN) && (edge(RIGHT) <= stick_->edge(LEFT))//STICK FROM LEFT 
	&&	(edge(DOWN) >stick_->edge(UP) + STICK_CURVATURE))
		{
			posX -= MARGIN;
			if (vectorX>0) vectorX = -vectorX;
		}

	if	((edge(LEFT) <= stick_->edge(RIGHT)+MARGIN) && (edge(LEFT) >= stick_->edge(RIGHT)) //STICK FROM RIGHT 
	&&	(edge(DOWN) > stick_->edge(UP) + STICK_CURVATURE))
		{
			
			posX += MARGIN;
			if(vectorX<0) vectorX = -vectorX;	
		}

	if	((edge(DOWN) >= stick_->edge(UP)) && (edge(DOWN) <= stick_->edge(UP)+MARGIN+STICK_CURVATURE) //STICK UP DOWN 
	&&	(edge(RIGHT) >= stick_->edge(LEFT)) && (edge(LEFT) <= stick_->edge(RIGHT)))
	{
				
		

			if ( stick_->sticky) // GLUE TO STICK
			{
				distanceFromStick();
				started = false;
			}

		
			else //NORMAL BOUNCE
			{
				changeAngle();
			}
			
	}

	if (!started) // WHEN GLUED TO THE STICK
	{
		//fixes sticky ball when going Long stick to Short;
		if (distanceFromStick_ > stick_->bmp->w / 2)
			distanceFromStick_ = stick_->bmp->w / 2-MARGIN;

		if (distanceFromStick_ < -stick_->bmp->w / 2)
			distanceFromStick_ = -stick_->bmp->w / 2+MARGIN;
		///////////////////////////////////////////////////

		vectorX = 0;
		vectorY = 0;

		posX = stick_->posX + distanceFromStick_;
		posY = stick_->edge(UP) - bmp->h / 2 -MARGIN;
	}

}



void ballIsUnder(Ball *balls[BALL_MAX_NUMBER],int &lives,long int &score)
{
	int balls_active = 0;
	//COUNT ACTIVE BALLS
	for (int i = 0; i < BALL_MAX_NUMBER; i++)
	{
		if (balls[i]) balls_active++;
	}
	/////////////////////


	for (int i = 0; i < BALL_MAX_NUMBER; i++)
	{
		// IF LAST BALL
		/////////////////////////////////////////////////
		if (balls[i] && balls_active == 1)
		{
			if (balls[i]->edge(Object::DOWN) >= balls[i]->stick_->edge(Object::DOWN) + BALL_RESET_DISTANCE) //FLOOR HIT
			{
				score -= 1000;
				balls[i]->started = false;
				balls[i]->posX = balls[i]->stick_->posX;
				balls[i]->posY = balls[i]->stick_->edge(Object::UP) - balls[i]->bmp->h / 2 - MARGIN;
				balls[i]->distanceFromStick_ = 0;

				if (lives>0) lives--;

				if (lives == 0)
				{
					delete balls[i];
					balls[i] = NULL;
				}
			}
		}
		//////////////////////////////////////////////

		if ((balls[i] && balls_active > 1) // DELETE ADDITIONAL BALLS WHEN HIT FLOOR
			&& (balls[i]->edge(Object::UP) >= balls[i]->stick_->edge(Object::DOWN)))
		{
			score -= 100;
			delete balls[i];
			balls[i] = NULL;
		}

	}


}

void Ball::accelerate(double delta)
{
	if (!stick_->sticky && (!started)) speed = BALL_START_SPEED;
	if ((speed < BALL_MAX_SPEED) && started &&(!slow))	speed += BALL_ACCELERATION *delta;	
}

void checkSlow(Ball *ball[BALL_MAX_NUMBER])
{
	static int change[BALL_MAX_NUMBER];
	for (int i = 0; i < BALL_MAX_NUMBER; i++)
	{	
		if (ball[i])
		{
			if (!change[i]) change[i] = 6;
			if (ball[i]->slow)
			{
				if (change[i] == 5)ball[i]->speed = ball[i]->speed/2 ;

				change[i] = 6;

			}
			if (!ball[i]->slow)
			{
				if (change[i] == 6)
				ball[i]->speed = BALL_START_SPEED ;
				change[i] = 5;
			}
		}
	}

}

void drawAllBalls(Ball*ball[BALL_MAX_NUMBER], SDL_Surface *screen)
{
	for (int i = 0; i < BALL_MAX_NUMBER; i++)
	{
		if (ball[i])
		{
			ball[i]->draw(screen);
		}
	}
}

void doMultiball(Ball *balls[BALL_MAX_NUMBER],Stick*stick)
{
	for (int i = 0; i < BALL_MAX_NUMBER; i++)
	{
		if (!balls[i])
		{
			static int leftRight;
			if (!leftRight) leftRight = 1;
			
			balls[i] = new Ball(stick,true);
			balls[i]->posX = balls[i]->stick_->posX + leftRight*balls[i]->stick_->bmp->w / 2 - leftRight*balls[i]->bmp->w;
			balls[i]->posY = balls[i]->stick_->edge(Object::UP) - balls[i]->stick_->bmp->h / 2;
			balls[i]->distanceFromStick();
			balls[i]->changeAngle();
		
			leftRight = (leftRight>0 ? -1 : 1); // one ball on left side next on right side
		}
	}
}