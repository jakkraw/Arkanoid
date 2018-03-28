
#include"functions.h"


int main(int argc, char **argv) {
	
	srand(time(NULL));

	int frames = 0, rc, bgColor;
	bool quit = false;
	bool quitProgram=false;
	int brickCounter,lives,level;
	double worldTime = 0,fps=0,delta;
	long int score;



	Boost initBoost=NONE; // TIMER TRIGGER
	boostHelp *events_h[NUMBER_OF_POWERUPS] = { 0 }; // TIMERS FOR POWERUPS
	Powerup *powerArray[POWERUP_HANDLE_NR] = { 0 }; // POWERUPS ON SCREEN
	Charset charset;
	Stick *stick = NULL;
	Ball *ballArray[BALL_MAX_NUMBER] = { 0 };
	Brick *brickArray[BRICKS_IN_Y][BRICKS_IN_X] = { 0 };
	Object *bullet = NULL;
	
	SDL_Event event;
	SDL_Surface *screen, *wallpaper;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;


	wallpaper = SDL_LoadBMP(WALLPAPER);


	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO)) quit=1;

	if (FULLSCREEN)		rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	if (!FULLSCREEN)	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	if(rc) quit=1;
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_ShowCursor(SDL_DISABLE);


	bgColor = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	

retry:
	
	startScreen(screen,scrtex,window,renderer,charset,level,lives,score,quit,quitProgram);

	while(!quit) {
		
		//LOAD 
		loadLevel(brickArray, ballArray,events_h,powerArray,stick, brickCounter,lives,level);

		//LOGIC
		delta = deltaFunction();
		fpsTime(fps, worldTime, frames);
		bulletCollision(bullet, brickArray, powerArray, stick, score);
		startBoost(events_h, initBoost, stick, ballArray, lives, POWERUP_TIME);
		stick->powerUpCollision(powerArray,initBoost,score);
		ballIsUnder(ballArray, lives,score);
		
		//MOVE
		move(bullet, delta);
		stick->movement(delta);
		movePowerUps(powerArray,POWERUP_FALLING_SPEED, delta);
		
		//BALL CONTROL
		checkSlow(ballArray);
		for (int i = 0; i < BALL_MAX_NUMBER; i++)
		{
			if (ballArray[i])
			{
				ballArray[i]->collision();
				ballArray[i]->bricksCollision(brickArray, brickCounter, powerArray,score);
				ballArray[i]->posX += ballArray[i]->vectorX*ballArray[i]->speed*delta;
				ballArray[i]->posY += ballArray[i]->vectorY*ballArray[i]->speed*delta;
				ballArray[i]->accelerate(delta);
				
			}
		}
		
		//DRAWING
		drawWallpaper(screen, wallpaper, bgColor);
		drawAllBalls(ballArray, screen);
		stick->draw(screen);
		drawAllBricks(brickArray, screen);
		if (bullet) bullet->draw(screen);
		drawAllPowerUps(powerArray,screen);
		drawInfo(screen, charset.bmp, stick,worldTime,fps,lives,brickCounter,events_h,level,score);
	
		//CONTROLS
		while(SDL_PollEvent(&event)) 
		{
			switch(event.type) 
			{
				case SDL_KEYDOWN:
					
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
						

					else if (event.key.keysym.sym == SDLK_LEFT)
					{	
						stick->moveStick(Stick::LEFT);
					}
						
			
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						stick->moveStick(Stick::RIGHT);
					}


					else if (event.key.keysym.sym == SDLK_s)
					{
						for (int i = 0; i < BALL_MAX_NUMBER; i++)
						{
							if (ballArray[i])
							{
								ballArray[i]->unstick();
							}
						}	
					}
					else if (event.key.keysym.sym == SDLK_f)
					{
						if ((stick->bullet) && (!bullet))
						{
							bullet = new Object();
							bullet->bmp = SDL_LoadBMP(BULLET_BMP);
							SDL_SetColorKey(bullet->bmp, true, 0x000000);
							bullet->posX = stick->posX;
							bullet->posY = stick->posY;
						}
					}
					break;


				case SDL_KEYUP:


					if ((event.key.keysym.sym == SDLK_RIGHT) || (event.key.keysym.sym == SDLK_LEFT))
					{
						stick->speed = 0;
					}
						
					break;


				case SDL_QUIT:
					quit = true;
					break;

				};
			};

		interface(screen, scrtex, window, renderer, charset,level,score, brickCounter, lives, quit);

		frames++;
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
		};
		if (!quitProgram) goto retry; //GO TO MAIN MENU

	quitP(quit, screen, scrtex, window, renderer);
	return 0;
	};
