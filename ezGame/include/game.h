#pragma once
#include <memory>
#include "stage.h"
#include "ez.h"

namespace ezGame {
	struct Game {
		virtual void setup(Ez&) {};
		virtual ~Game() = default;
		virtual std::unique_ptr<Stage> start() = 0;
	};
}