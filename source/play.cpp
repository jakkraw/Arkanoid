#include "play.h"
#include "menu.h"
#include "objects.h"

using namespace ezGame;

void Play::setup(ezGame::Ez & ez)
{
	ez.settings().set(Background(RED));
}



void Play::logic(ezGame::Ez &ez)
{
	if (ez.pressed(Keyboard::Q)) return ez.quit();
	if (ez.pressed(Keyboard::BACKSPACE)) return ez.goTo(new Menu);

	NormalBall ball;
	NormalArena arena;
	ball.c = arena.startPosition();

	ball.draw(ez, arena);


}
