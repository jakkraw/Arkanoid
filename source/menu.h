#pragma once

#include "ezGame.h"

class Menu : public ezGame::Stage {
	enum MenuOptions {
		Play = 0, Scores = 1, Quit = 2
	};

	MenuOptions selected = Play;

	void setup(ezGame::Ez&) override;
	void logic(ezGame::Ez&) override;
};