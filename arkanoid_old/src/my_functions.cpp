#include"functions.h"

double secPassed(int past)
{
	return  (SDL_GetTicks() - past) *0.001;
}

double deltaFunction()
{
	

	static int past;
	if (!past) past =SDL_GetTicks();

	int presentTime = SDL_GetTicks();
	double delta=(presentTime - past)*0.001;
	past = presentTime;
		return delta;
}



void fpsTime(double &fps,double &worldTime,int &frames)
{
	static double past;
	if (!past) past = SDL_GetTicks();

	int presentTime = SDL_GetTicks();
	static double fpsTimer;
	double delta;
	delta = (presentTime - past) * 0.001;
	past = presentTime;
	worldTime += delta;
	fpsTimer += delta;
	if (fpsTimer > 0.5) 
	{
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	}
}

void quitP(bool &quit,SDL_Surface *screen,SDL_Texture *scrtex, SDL_Window *window, SDL_Renderer *renderer)
{
	quit = 1;
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void drawInfo(SDL_Surface *screen, SDL_Surface *charset,Stick *stick, double worldtime, double fps,int lives, int brickCounter, boostHelp *event_h[NUMBER_OF_POWERUPS],int level,long int score)
{
	////////////////
	static SDL_Surface *sticky, *long_stick, *slow,*heart,*bullet;
	if (!sticky)
	{
		sticky = SDL_LoadBMP(POWER_UP_STICKY);
		SDL_SetColorKey(sticky, true, 0x000000);
	}
	if (!bullet)
	{
		bullet = SDL_LoadBMP(POWER_UP_BULLET);
		SDL_SetColorKey(bullet, true, 0x000000);
	}
	if (!long_stick)
	{
		long_stick = SDL_LoadBMP(POWER_UP_LONG_STICK);
		SDL_SetColorKey(long_stick, true, 0x000000);
	}
	if (!slow)
	{
		slow = SDL_LoadBMP(POWER_UP_SLOW);
		SDL_SetColorKey(slow, true, 0x000000);
	}
	if (!heart)
	{
		heart = SDL_LoadBMP(SMALL_HEART);
		SDL_SetColorKey(heart, true, 0x000000);
	}
	//////////////////////
	static char text[128];
	const static int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	const static int lightGreen = SDL_MapRGB(screen->format, 0x5D, 0xBA, 0x4A);
	const static int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	const static int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const static int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	static int timers[NUMBER_OF_POWERUPS];
	for (int i = 0; i < NUMBER_OF_POWERUPS; i++)
	{
		if (event_h[i])
		{
			timers[i] = POWERUP_TIME - secPassed(event_h[i]->startTime)+1;
		}
		else timers[i] = 0;
	}
	// DRAW WALLS
	DrawRectangle(screen, 0, 0, WALL_WIDTH, SCREEN_HEIGHT, INFO_COLOR, INFO_COLOR);
	DrawRectangle(screen, SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, SCREEN_HEIGHT, INFO_COLOR, INFO_COLOR);
	//
	

	DrawRectangle(screen, WALL_WIDTH, 0, SCREEN_WIDTH-2*WALL_WIDTH , INFO_HEIGHT, INFO_COLOR, INFO_COLOR);
	sprintf(text, "Time = %.1lf s  %.0lf frames / s", worldtime, fps);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 6, text, charset);
	sprintf(text, "Level = %i  Bricks = %i",level,brickCounter);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 22, text, charset);
	sprintf(text, "SCORE = %li", score);
	DrawString(screen, 2*screen->w/3+screen->w / 6 - strlen(text) * 8 / 2, 14, text, charset);


	// DRAW LIVES

	sprintf(text, "Lives", level, brickCounter);
	DrawString(screen, screen->w/3 , 38, text, charset);
	for (int i = 0; i < lives; i++)
	{
		DrawSurface(screen, heart, screen->w/3+(i+3)*(heart->w+5)+strlen(text), 42);

	}



	// DRAW POWERUP ICONS WHEN ACTIVE

	if (event_h[STICKY])
	{
		DrawSurface(screen, sticky, SCREEN_WIDTH/20, (INFO_HEIGHT / 2) );
		sprintf(text, " = %i ",timers[STICKY]);
		DrawString(screen, SCREEN_WIDTH / 20 + sticky->w / 2, (INFO_HEIGHT / 2), text, charset);
	}
	if (event_h[LONG])
	{
		DrawSurface(screen, long_stick, 3*SCREEN_WIDTH / 20, (INFO_HEIGHT / 2) );
		sprintf(text, " = %i ", timers[LONG]);
		DrawString(screen,3*SCREEN_WIDTH / 20 + sticky->w / 2, (INFO_HEIGHT / 2) , text, charset);
	}

	if (event_h[SLOW])
	{
		DrawSurface(screen, slow, 5 * SCREEN_WIDTH / 20, (INFO_HEIGHT / 2) );
		sprintf(text, " = %i ", timers[SLOW]);
		DrawString(screen, 5 * SCREEN_WIDTH / 20 + sticky->w / 2, (INFO_HEIGHT / 2) , text, charset);
	}
	if (event_h[BULLET])
	{
		sprintf(text, "%i", timers[BULLET]);
		DrawSurface(screen, bullet, stick->posX, stick->posY);
		if (timers[BULLET] >= 10)	DrawString(screen, stick->posX - 7, stick->posY - 3, text, charset);
		if (timers[BULLET] < 10)	DrawString(screen, stick->posX - 3, stick->posY - 3, text, charset);
	
		
	}
	
	
}

void drawWallpaper(SDL_Surface *screen, SDL_Surface *wallpaper,int bgColor)
{
	if (wallpaper == NULL)
	{
		SDL_FillRect(screen, NULL, bgColor);
	}
	else
	{
		DrawSurface(screen, wallpaper, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
}

void loadXYManagement(int &x, int &y, int &temp)
{


	if ((x == BRICKS_IN_X - 1) && (y == BRICKS_IN_Y - 1)) // When all array full
	{
		temp = -1;
	}

	else if (x == BRICKS_IN_X - 1) // When new line occurs
	{
		x = 0;
		y++;
	}

	else if ((x < BRICKS_IN_X - 1) && (y < BRICKS_IN_Y - 1))//	Normal
	{
		x++;
	}
}

bool toggleEdges(Brick *brick[BRICKS_IN_Y][BRICKS_IN_X], int x, int y, Brick::StickedTypes type)
{

	if (BRICK_PADDING > TOGGLE_EDGES_ABOVE_PADDING) return true;

	switch (type)
	{
	case Brick::RIGHT_:
		if (x == BRICKS_IN_X - 1)return true;
		if (brick[y][x + 1] == NULL) return true;
		else return false;

	case Brick::LEFT_:
		if (x == 0)return true;
		if (brick[y][x - 1] == NULL) return true;
		else return false;
	case Brick::UP_:
		if (y == 0)return true;
		if (brick[y - 1][x] == NULL) return true;
		else return false;
	case Brick::DOWN_:
		if (y == BRICKS_IN_Y - 1) return true;
		if (brick[y + 1][x] == NULL) return true;
		else return false;
	}
	return false;
}

void loadLevel(Brick*bricks[BRICKS_IN_Y][BRICKS_IN_X], Ball* balls[BALL_MAX_NUMBER], boostHelp*events_h[NUMBER_OF_POWERUPS], Powerup*power[POWERUP_HANDLE_NR], Stick *&stick, int &brickCounter, int &lives, int&level)
{
	static int loaded;
	

	if ((level != loaded) || (!level))
	{
		// DELETE PREV STICK
		delete stick;
		stick = NULL;

		// DELETE PREV BALLS
		for (int i = 0; i < BALL_MAX_NUMBER; i++)
		{
			delete balls[i];
			balls[i] = NULL;
		}
		//DELETE TIMERS 
		for (int i = 0; i < NUMBER_OF_POWERUPS; i++)
		{
			delete events_h[i];
			events_h[i] = NULL;
		}
		//DELETE POWERUP ICONS
		for (int i = 0; i <POWERUP_HANDLE_NR; i++)
		{
			delete power[i];
			power[i] = NULL;
		}
		//DELETE BRICKS
		for (int y = 0; y < BRICKS_IN_Y; y++)
		{
			for (int x = 0; x < BRICKS_IN_X; x++)
			{
				delete bricks[y][x];
				bricks[y][x] = NULL;
			}
		}





		stick = new Stick();
		balls[0] = new Ball(stick);
		if (level==0)
		{
			level = 1;
		}
		loadBricksTo(bricks, brickCounter, level);
		
		loaded = level;
	}

	 
	
}

void interface(SDL_Surface *screen, SDL_Texture *scrtex,
	SDL_Window *window,
	SDL_Renderer *renderer, Charset charset, int &level,int score,int brickCounter, int &lives, bool &quit)
{

	const static int lG = SDL_MapRGB(screen->format, 0x5D, 0xBA, 0x4A);
	const static int r = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const static int bl = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	char text[128];


	//end of levels
	if (level == -1)
	{
		SDL_Event event;
		quit = 1;

		do
		{
			SDL_PollEvent(&event);
			DrawRectangle(screen, 1, 4 * screen->h / 10, screen->w, screen->h / 5, bl, bl);
			sprintf(text, "You Win!", level);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 5 * screen->h / 10, text, charset.bmp);
			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

		} while ((event.key.keysym.sym != SDLK_RETURN) || (event.type != SDL_KEYDOWN));
		addScore(screen, scrtex, window, renderer, charset,score);
		showScores(screen, scrtex, window, renderer, charset);
	}
	
	
	// next level
	else if (!brickCounter&&lives)
	{
		SDL_Event event;
		level++;
		do
		{
			SDL_PollEvent(&event);
			DrawRectangle(screen, 1, 4 * screen->h / 10, screen->w, screen->h / 5, bl, bl);
			sprintf(text, "Level %i",level);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 5 * screen->h / 10, text, charset.bmp);
			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

		} while ((event.key.keysym.sym != SDLK_RETURN) || (event.type != SDL_KEYDOWN));
	}
	//end of lives
	if (!lives)
	{
		quit = 1;
		SDL_Event event;
		char text[128];
		do
		{
			SDL_PollEvent(&event);
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
			sprintf(text, " You Died... ");
			DrawString(screen, screen->w / 2 - 2 * strlen(text), screen->h / 2, text, charset.bmp);
			sprintf(text, " Score %i",score);
			DrawString(screen, screen->w / 2 - 2 * strlen(text), 25+screen->h / 2, text, charset.bmp);


			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);


		} while ((event.key.keysym.sym != SDLK_RETURN) || (event.type != SDL_KEYDOWN));

		addScore(screen, scrtex, window, renderer, charset,score);
		showScores(screen, scrtex, window, renderer, charset);



	}

}

void startScreen(SDL_Surface *screen, SDL_Texture *scrtex,
SDL_Window *window,
SDL_Renderer *renderer, Charset charset, int&level, int&lives,  long int&score ,bool&quit, bool &endProgram)
{
	quit = false;
	char text[128];
	bool end = false;
	const static int lG = SDL_MapRGB(screen->format, 0x5D, 0xBA, 0x4A);
	const static int r = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const static int bl = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	const static int ble = SDL_MapRGB(screen->format, 0x04, 0x66, 0x2C);
	
	

	SDL_Event event;
	unsigned int choose = 0;

	while (!end)
	{
		SDL_FillRect(screen, NULL, lG);
		switch (choose % 3)
		{
		case 0:
			DrawRectangle(screen, 1, 2 * screen->h / 10, screen->w, screen->h / 5, bl, bl);

			break;
		case 1:
			DrawRectangle(screen, 1, 4 * screen->h / 10, screen->w, screen->h / 5, ble, ble);
			break;
		case 2:
			DrawRectangle(screen, 1, 6 * screen->h / 10, screen->w, screen->h / 5, r, r);
			break;
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
						quit = true;
						end = true;
						endProgram = true;	
				}
				if (event.key.keysym.sym == SDLK_UP)
				{
					choose--;
				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					choose++;
				}
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					switch (choose % 3)
					{
					case 0:
						level = 0; // to start from 1 lvl;
						lives = 3;
						score = 0;	
						end = true;
						break;
					case 1:
						quit = true;
						endProgram = true;
						end = true;
						break;	
					case 2:
						SDL_FillRect(screen, NULL, lG);
						showScores(screen, scrtex, window, renderer, charset);
						break;
					}	
				}
			}

			sprintf(text, "Play ");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 3 * screen->h / 10, text, charset.bmp);
			sprintf(text, "Exit");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 5 * screen->h / 10, text, charset.bmp);
			sprintf(text, "High Scores");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 7 * screen->h / 10, text, charset.bmp);

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
	}

		
}

void showScores(SDL_Surface *screen, SDL_Texture *scrtex,
	SDL_Window *window,
	SDL_Renderer *renderer, Charset charset)
{
	std::fstream file;
	char bestScores[5][256];
	file.open(LOAD_SCORES_FROM, std::ios::in);
	for (int i = 0; i < 5; i++)
	{
		file.getline(bestScores[i], 256);
	}


	const static int lG = SDL_MapRGB(screen->format, 0x5D, 0xBA, 0x4A);
	const static int r = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const static int bl = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	char text[128] = { 0 };

	SDL_Event event;
	do
	{
		SDL_PollEvent(&event);
		DrawRectangle(screen, 1, 4 * screen->h / 10, screen->w, screen->h / 4, r, r);
		for (int i = 0; i < 5; i++)
		{
			DrawString(screen, screen->w / 2 - strlen(bestScores[i]) * 8 / 2, 4 * screen->h / 10
				+i*20+ 15, bestScores[i], charset.bmp);
		}
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

	} while ((event.key.keysym.sym != SDLK_ESCAPE) && (event.key.keysym.sym != SDLK_RETURN) || (event.type != SDL_KEYDOWN));
	
}

void addScore(SDL_Surface *screen, SDL_Texture *scrtex,
	SDL_Window *window,
	SDL_Renderer *renderer, Charset charset, int score)
{
	std::fstream file;
	file.open(LOAD_SCORES_FROM, std::ios::in);
	bool File = file.good();

	//CHECK IF SCORE QUALIFICATES FOR LIST
	bool qualifies[5] = { 0,0,0,0,0};
	bool pass = true;
	std::string prevScore;
	int counter = -1;
	int ct = -1;
	if (file.good())
	{
		while (!file.eof())
		{
			counter++;
			file >> prevScore;
			if (counter % 2 != 0) // When prevScore Shows Number 
			{
				ct++;
				if (std::atoi(prevScore.c_str()) <= score) // if bigger than prevScore,only biggest 
				{
					qualifies[ct] = true;	
				}
				pass = false;
			}
		}
	}
	file.close();

	if ((ct + 1)<5) qualifies[ct + 1] = true; // when empty places


	if (!file.good()&&pass) qualifies[0] = true; // when file doesnt exist
	
	int cnt = 0;				//check if qualifies
	for (int i = 0; i < 5; i++)
	{
		if (qualifies[i]) cnt++;
	}
	if (!cnt) return;

	/////////////////////////////////////
	


	// Ask if you want to save
	const static int lG = SDL_MapRGB(screen->format, 0x5D, 0xBA, 0x4A);
	const static int r = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const static int bl = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	char text[128];

	SDL_Event event;

	do
	{
		SDL_PollEvent(&event);
		DrawRectangle(screen, 1, 4 * screen->h / 10, screen->w, screen->h / 5, r, r);
		sprintf(text, "You are Qualified for the High Score list do You want to save your Score ? ");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, -25+(screen->h / 2), text, charset.bmp);
		sprintf(text, "Score %i ",score);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2,   (screen->h / 2), text, charset.bmp);
		sprintf(text, "Press Enter to accept or ESC to exit ");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 25+(5 * screen->h / 10), text, charset.bmp);
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
		if (((event.key.keysym.sym == SDLK_ESCAPE) && (event.type == SDL_KEYDOWN)))return;

	} while ((event.key.keysym.sym != SDLK_RETURN) || (event.type != SDL_KEYDOWN));

	////////////////////////
	
	// ENTER YOUR NAME
	bool isRunning = true;
	SDL_Event ev;
	std::string name= "";
	
	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			
			if (ev.key.keysym.sym == SDLK_RETURN&&name.length()>0)
				isRunning = false;
			else if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
			{
				

				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE&& name.length() > 0) // BACKSPACE
					name = name.substr(0, name.length() - 1);

				
				else if (ev.type == SDL_TEXTINPUT) 
				{	
					if ((*ev.text.text != ' ')&&(name.length()<10))//WITHOUT SPACE
					name += ev.text.text;
				}

				DrawRectangle(screen, 1, 4 * screen->h / 10, screen->w, screen->h / 5, r, r);
				sprintf(text, "Enter Your Name: ");
				DrawString(screen, screen->w / 2 - 2*strlen(text) * 8 / 2, (screen->h / 2), text, charset.bmp);
				const char *text1 = name.c_str(); // TO SHOW IT ON DRAW STRING
				DrawString(screen, screen->w / 2,(screen->h / 2), text1, charset.bmp);

				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}

		}
	}
	//////////////////////////////////////////////////////////
		


	// Add high Score
	//when doesn't exist
	if (!File)
	{
		file.open(LOAD_SCORES_FROM, std::ios::out);
		file << name << "  " << score;
		file.close();
		return;
	}
	
	//////////////////////////
	std::string line[5];
	
	file.open(LOAD_SCORES_FROM, std::ios::in); // get all lines

	int i=0;
	while (!file.eof()&&(i<5))
	{
	getline(file,line[i]);
	i++;
	}
	file.close();
	///////////////////////////
	bool changed = false;
	file.open(LOAD_SCORES_FROM, std::ios::out); // get all lines
	int j=0;
	while (!changed)
	{
		if (qualifies[j] == false)
		{
			file << line[j] << "\n";

		}
			
		if (qualifies[j] == true)
		{
			file << name << "  " << score << "\n";
			changed = true;
		}
		j++;
		if (changed) j--;
	}

	for (j; j < 4; j++)
	{
		file << line[j] << '\n';
	}		
	
	file.close();

}