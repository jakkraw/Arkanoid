#pragma once

#include "ezGame.h"
#include "Box2D.h"


class Play : public ezGame::Stage {
	NormalArena arena;


	void setup(ezGame::Ez&) override;
	void logic(ezGame::Ez &) override;
};