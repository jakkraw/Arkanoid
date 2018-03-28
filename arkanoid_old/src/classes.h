
class Charset; 
class Object; 
class Stick;
class Brick;
class Ball;
class Powerup;
struct boostHelp;

enum Boost
{
	STICKY,
	LONG,
	MULTIBALL,
	SLOW,
	HEART,
	BULLET,
	NONE  // NONE MUST BE LAST!
};

class Charset
{
public:
	SDL_Surface *bmp;
	Charset();
};


class Object
{
public:
	enum Walls
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	Object();
	~Object();

	SDL_Surface *bmp;
	double posX;
	double posY;
	int edge(Walls which);
	void draw(SDL_Surface *screen);	
};
void move(Object*&bullet,double delta);
void bulletCollision(Object*&bullet, Brick *brick[BRICKS_IN_Y][BRICKS_IN_X], Powerup *power[POWERUP_HANDLE_NR], Stick *stick, long int &score);

class Stick :public Object
{
public:
	enum Direction
	{
		RIGHT,
		LEFT	
	};
	double speed;
	bool sticky;
	bool long_stick;
	bool bullet;
	
	Stick();

	void moveStick(Direction direction);
	void powerUpCollision(Powerup *power[POWERUP_HANDLE_NR], Boost &initBoost,long int &score);
	void movement(double delta);
	
};

class Brick :public Object
{
public:
	enum BrickTypes
	{
		NORMAL,
		SPECIAL,
		HARD,
		UNBREAKABLE,
	};
	enum StickedTypes
	{
		UP_,
		DOWN_,
		LEFT_,
		RIGHT_
	};

	int durability;
	int type;
	int score;

	Brick(BrickTypes type_ = NORMAL);

	void setPosition(int x, int y);
	void spawnPowerUp(Powerup*power[POWERUP_HANDLE_NR],Stick *stick);
	void reduceDurability();
	

};
void loadBricksTo(Brick *brickArray[BRICKS_IN_Y][BRICKS_IN_X], int &bricksCounter, int &levles);
void loadBricksTo1(Brick *brickArray[BRICKS_IN_Y][BRICKS_IN_X], int &bricksCounter, int &levles);


void drawAllBricks(Brick *brickArray[BRICKS_IN_Y][BRICKS_IN_X], SDL_Surface *screen);



class Ball : public Object
{

public:
	double distanceFromStick_;
	Stick *stick_;
	double vectorX;
	double vectorY;
    double speed;

	bool started;
	bool slow;

	Ball(Stick *stick=0,bool onMulti=false);
	void unstick();
	void collision();
	void bricksCollision(Brick *brick[BRICKS_IN_Y][BRICKS_IN_X], int &bricksCounter, Powerup *power[POWERUP_HANDLE_NR],long int &score);	
	void distanceFromStick();
	void changeAngle();
	void accelerate(double delta);
};
void checkSlow(Ball *ball[BALL_MAX_NUMBER]);
void doMultiball(Ball *balls[BALL_MAX_NUMBER],Stick *stick);
void drawAllBalls(Ball*ball[BALL_MAX_NUMBER], SDL_Surface *screen);
void ballIsUnder(Ball *balls[BALL_MAX_NUMBER], int &lives,long int&score);



class Powerup : public Object
{
	Stick *stick_;
public:

	Boost type;
	int acceleration;
	double whenCreatedTimer;
	int score;

	Powerup(Stick *stick,int x,int y,Boost type_);


};

void startBoost(boostHelp *event_h[NUMBER_OF_POWERUPS], Boost &initBoost, Stick *stick, Ball *balls[BALL_MAX_NUMBER],int &lives,double time);
void drawAllPowerUps(Powerup *power[POWERUP_HANDLE_NR], SDL_Surface *screen);
void movePowerUps(Powerup *powerUp[POWERUP_HANDLE_NR], int fallingSpeed, double delta);
