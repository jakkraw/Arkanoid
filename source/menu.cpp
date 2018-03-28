#include "menu.h"
#include "play.h"
#include "scores.h"

using namespace ezGame;

void Menu::setup(ezGame::Ez & ez)
{
	ez.settings().set(Background(98, 152, 239));
}

void Menu::logic(Ez& ez)
{
	if (ez.pressed(Keyboard::Q) || ez.pressed(Keyboard::ESCAPE)) ez.quit();
	if (ez.pressed(Keyboard::UP) || ez.pressed(Keyboard::W)) selected = (MenuOptions)((unsigned int(selected) + 2) % 3);
	if (ez.pressed(Keyboard::DOWN) || ez.pressed(Keyboard::S)) selected = (MenuOptions) ((unsigned int(selected) + 1) % 3);

	
	if (ez.pressed(Keyboard::RETURN)) {
		switch (selected) {
		case Quit: return ez.quit();
		case Play: return ez.goTo(new ::Play);
		case Scores: return ez.goTo(new ::Scores);
		}
	}

	auto res = ez.resolution();

	ez.draw(Rectangle(RPos(0, int(selected) * 1/3., res), RSize{ 1, 1/3., res }, BLUE.with(Alpha(0.2))));

	auto size = RSize{ 0.5,0.2, res };
	auto offset = RPos(0.3, 0.05, res);

	ez.draw(Text{ "Play", offset, size });
	ez.draw(Text{ "Scores", offset + RPos(0, 1/3., res),  size });
	ez.draw(Text{ "Quit", offset + RPos(0, 2/3., res),  size });

}
