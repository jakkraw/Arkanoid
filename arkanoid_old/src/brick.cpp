#include "functions.h"

Brick::Brick(BrickTypes type_)
{
	type = type_;
	switch (type)
	{
	case NORMAL:
		bmp = SDL_LoadBMP(NORMAL_BMP);
		score = 100;
		durability = 1;
		break;
	case SPECIAL:
		score = 200;
		bmp = SDL_LoadBMP(SPECIAL_BMP);
		durability = 1;
		break;
	case HARD:
		score = 75;
		bmp = SDL_LoadBMP(HARD_BMP);
		durability = 2;
		break;
	case UNBREAKABLE:
		score = 1;
		bmp = SDL_LoadBMP(UNBREAKABLE_BMP);
		durability = -1;
		break;

	}
	SDL_SetColorKey(bmp, true, 0x000000);
}

void Brick::setPosition(int x, int y)
{
	static int max_width, max_height;

	if ((max_width == 0) && (max_height == 0))
	{
		max_width += bmp->w;
		max_height += bmp->h;
	}

	if (max_height < bmp->h)
	{
		max_height = bmp->h;
	}

	if (max_width < bmp->w)
	{
		max_width = bmp->w;
	}

	int GAP = (SCREEN_WIDTH - BRICKS_IN_X * (max_width + BRICK_PADDING)) / 2 + BRICK_PADDING / 2;
	posX = GAP + max_width / 2 + (max_width + BRICK_PADDING)*x;
	posY = INFO_HEIGHT + BRICK_PADDING + max_height / 2 + (max_height + BRICK_PADDING)*y;

}

void Brick::reduceDurability()
{
	
	if (durability > 0)
	{
		if (type == HARD)
		{
			bmp = SDL_LoadBMP(DAMAGED_HARD_BMP);
			SDL_SetColorKey(bmp, true, 0x000000);
		}
		durability--;
	}

}



void drawAllBricks(Brick *brickArray[BRICKS_IN_Y][BRICKS_IN_X], SDL_Surface *screen)
{

	for (int y = 0; y < BRICKS_IN_Y; y++)
	{
		for (int x = 0; x < BRICKS_IN_X; x++)
		{
			if (brickArray[y][x] != 0)
			{
				brickArray[y][x]->draw(screen);

			}
		}
	}


}

void loadBricksTo(Brick *brickArray[BRICKS_IN_Y][BRICKS_IN_X], int &bricksCounter, int &level)
{
	FILE *file;
	int temp = 0, x = 0, y = 0;
	bool end=false;
	file = fopen(LOAD_LVL_FROM, "r");
	int levels_counter=1;
	bricksCounter = 0;
	
	//COUNT LEVELS
	while ((temp = fgetc(file)) != EOF)
	{
		if (temp == '>')
		{
			++levels_counter;
		}
	}
	rewind(file);

	
	if (levels_counter <= level) level = -1;
	//SET POINT TO LOAD FROM
		for (int i = 0; i < level-1; i++)
		{
			while (fgetc(file) != '>')
			{

			}
		}
	

	//FILL ARRAY WITH BLOCKS
	while (((temp = fgetc(file)) != EOF) && !end)
	{
		if (temp == 'N')
		{
			brickArray[y][x] = new Brick(Brick::NORMAL);
			brickArray[y][x]->setPosition(x, y);
			loadXYManagement(x, y, temp);
			bricksCounter++;
		}

		if (temp == 'H')
		{
			brickArray[y][x] = new Brick(Brick::HARD);
			brickArray[y][x]->setPosition(x, y);
			loadXYManagement(x, y, temp);
			bricksCounter++;
		}

		if (temp == 'S')
		{
			brickArray[y][x] = new Brick(Brick::SPECIAL);
			brickArray[y][x]->setPosition(x, y);
			loadXYManagement(x, y, temp);
			bricksCounter++;
		}

		if (temp == 'U')
		{
			brickArray[y][x] = new Brick(Brick::UNBREAKABLE);
			brickArray[y][x]->setPosition(x, y);
			loadXYManagement(x, y, temp);
			bricksCounter++;
		}


		if (temp == '-')
		{
			loadXYManagement(x, y, temp);
		}

		if (temp == '>')
		{
			end = true;
		}

	}

	fclose(file);

}


void Ball::bricksCollision(Brick *brick[BRICKS_IN_Y][BRICKS_IN_X], int &bricksCounter, Powerup *power[POWERUP_HANDLE_NR],long int &score)
{
	double helpX = vectorX, helpY = vectorY; //PREVENTS FROM DOUBLE VECTOR CHANGING
	short marginX = 0, marginY = 0;
	bool touchUp, touchDown, touchLeft, touchRight;//FOR TOGGLE EDGES OPTION
	bool hit,multihit=false;
	

	bricksCounter = 0;

	for (int y = 0; y < BRICKS_IN_Y; y++)
	{
		for (int x = 0; x < BRICKS_IN_X; x++)
		{
			if (brick[y][x])
			{

				if(brick[y][x]->type!=Brick::UNBREAKABLE) 
					bricksCounter++;


				hit = false;
				touchUp = false;
				touchDown = false;
				touchLeft = false;
				touchRight = false;

				/////////////////////////////////////////////////////////////////////////
				//OVER BRICK COLLISION
				if ((edge(DOWN) >= brick[y][x]->edge(UP)) && (edge(DOWN) <= brick[y][x]->edge(UP) + 2 * MARGIN)
					&& (edge(LEFT) <= brick[y][x]->edge(RIGHT)) && (edge(RIGHT) >= brick[y][x]->edge(LEFT)))
				{
					if (helpY > 0)
					{
						vectorY = -helpY;
						touchUp = true;
						hit = true;
					}

					marginY = -1;

				}

				//UNDER BRICK COLLISION
				if ((edge(UP) <= brick[y][x]->edge(DOWN)) && (edge(UP) >= brick[y][x]->edge(DOWN) - 2 * MARGIN)
					&& (edge(LEFT) <= brick[y][x]->edge(RIGHT)) && (edge(RIGHT) >= brick[y][x]->edge(LEFT)))
				{

					if (helpY < 0)
					{
						vectorY = -helpY;
						touchDown = true;
						hit = true;
					}
					marginY = 1;
				}

				//LEFT BRICK COLLISION
				if ((edge(UP) <= brick[y][x]->edge(DOWN)) && (edge(DOWN) >= brick[y][x]->edge(UP))
					&& (edge(RIGHT) >= brick[y][x]->edge(LEFT)) && (edge(RIGHT) <= brick[y][x]->edge(LEFT) + 2 * MARGIN))
				{

					if (helpX>0)
					{
						vectorX = -helpX;
						touchLeft = true;
						hit = true;
					}
					marginX = -1;
				}

				//RIGHT BRICK COLLISION
				if ((edge(UP) <= brick[y][x]->edge(DOWN)) && (edge(DOWN) >= brick[y][x]->edge(UP))
					&& (edge(LEFT) <= brick[y][x]->edge(RIGHT)) && (edge(LEFT) >= brick[y][x]->edge(RIGHT) - 2 * MARGIN))
				{

					if (helpX < 0)
					{
						vectorX = -helpX;
						touchRight = true;
						hit = true;
					}
					marginX = 1;
				}
				////////////////////////////////////////////////////////////////////////		
				
				if (multihit) hit = false; // ONLY ONE BLOCK PER HIT
			
				if (hit)  // DO WHEN BALL HITS THE BRICK
				{
					multihit = true;
					score += brick[y][x]->score;
					brick[y][x]->reduceDurability();

					if ((brick[y][x]->type == Brick::SPECIAL) && !brick[y][x]->durability)
					{
						brick[y][x]->spawnPowerUp(power, stick_);
					}
						

					if (!brick[y][x]->durability) 
					{
						delete brick[y][x];
						brick[y][x] = NULL;
					}

				}


				////////////////////////////////////////////////////////////////////////
				//FOR TOGGLE EDGES OPTION
				if (touchRight&&touchUp)
				{
					//RIGHT
					if (!toggleEdges(brick, x, y, Brick::RIGHT_)) vectorX = -vectorX;

					//UP
					if (!toggleEdges(brick, x, y, Brick::UP_)) vectorY = -vectorY;

				}
				if (touchRight&&touchDown)
				{
					//RIGHT
					if (!toggleEdges(brick, x, y, Brick::RIGHT_)) vectorX = -vectorX;
					//DOWN
					if (!toggleEdges(brick, x, y, Brick::DOWN_)) vectorY = -vectorY;
				}
				if (touchLeft&&touchUp)
				{
					//LEFT
					if (!toggleEdges(brick, x, y, Brick::LEFT_)) vectorX = -vectorX;
					//UP
					if (!toggleEdges(brick, x, y, Brick::UP_)) vectorY = -vectorY;
				}
				if (touchLeft&&touchDown)
				{
					//LEFT
					if (!toggleEdges(brick, x, y, Brick::LEFT_)) vectorX = -vectorX;
					//DOWN
					if (!toggleEdges(brick, x, y, Brick::DOWN_)) vectorY = -vectorY;
				}
				////////////////////////////////////////////////////////////////////////

			}
		}
	}

	posX += marginX*MARGIN;
	posY += marginY*MARGIN;

}