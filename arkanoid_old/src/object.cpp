#include "functions.h"


Charset::Charset()
{
	bmp = SDL_LoadBMP(CHARSET_BMP);
	if (!bmp)
	{
		SDL_FreeSurface(bmp);
		SDL_Quit();
		exit(1);
	}
	SDL_SetColorKey(bmp, true, 0xFFFFFF);
}

Object::Object()
{
	bmp = SDL_LoadBMP(NONE_BMP);
	if (!bmp)
	{
		SDL_FreeSurface(bmp);
		SDL_Quit();
		exit(1);
	}
	SDL_SetColorKey(bmp, true, 0x000000);
	posX = SCREEN_WIDTH / 2;
	posY = SCREEN_HEIGHT / 2;
};

Object::~Object()
{
	SDL_FreeSurface(bmp);
}



int Object::edge(Walls which)
{
	switch (which)
	{
	case UP:
		return posY - (bmp->h / 2);
			break;
	case DOWN:
		return posY + (bmp->h / 2);
			break;
	case LEFT:
		return posX - (bmp->w / 2);
			break;
	case RIGHT:
		return posX + (bmp->w / 2);
			break;
	default:
		return -1;
	}
}

void Object::draw(SDL_Surface *screen)
{
	DrawSurface(screen, bmp, posX, posY);
}

void move(Object *&bullet,double delta)
{
	if (bullet)
	{
		bullet->posY -= 600*delta;
	}
}

void bulletCollision(Object*&bullet, Brick *brick[BRICKS_IN_Y][BRICKS_IN_X], Powerup *power[POWERUP_HANDLE_NR], Stick *stick, long int &score)
{
	if (bullet)
	{
		if (bullet->edge(Object::UP) < INFO_HEIGHT)
		{
			delete bullet;
			bullet = NULL;
		}

		for (int y = 0; y < BRICKS_IN_Y; y++)
		{
			for (int x = 0; x < BRICKS_IN_X; x++)
			{
				if ((brick[y][x]) && (bullet))
				{
					if ((bullet->edge(Object::UP)<=brick[y][x]->edge(Object::DOWN))
						&& (bullet->edge(Object::LEFT)<=brick[y][x]->edge(Object::RIGHT))
						&& (bullet->edge(Object::RIGHT)>=brick[y][x]->edge(Object::LEFT)))
					{
						score += brick[y][x]->score;
						delete bullet;
						bullet = NULL;
						brick[y][x]->reduceDurability();

						if ((brick[y][x]->type == Brick::SPECIAL) && !brick[y][x]->durability)
						{
							brick[y][x]->spawnPowerUp(power, stick);
						}


						if (!brick[y][x]->durability)
						{
							delete brick[y][x];
							brick[y][x] = NULL;
						}
					}

				}

			}
		}
	}
}