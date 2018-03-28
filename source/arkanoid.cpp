#include "arkanoid.h"
#include "menu.h"

using namespace ezGame;

void Arkanoid::setup(ezGame::Ez& ez)
{
	auto& settings = ez.settings();
	settings.set(Title{ "Arkanoid" });
	settings.set(Resolution(800, 600));
}

std::unique_ptr<ezGame::Stage> Arkanoid::start()
{
	return std::make_unique<Menu>();
}
