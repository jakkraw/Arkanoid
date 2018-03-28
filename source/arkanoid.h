#pragma once
#include "ezGame.h"


struct Arkanoid : public ezGame::Game {



	virtual void setup(ezGame::Ez&) override;
	// Inherited via Game
	virtual std::unique_ptr<ezGame::Stage> start() override;
};