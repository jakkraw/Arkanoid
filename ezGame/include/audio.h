#pragma once
#include "common.h"

namespace ezGame {

	enum class LoopTimes {
		Zero, Infinite
	};

	struct Effect {
		Path path;
		LoopTimes loopTimes;
		Effect(Path path, LoopTimes loopTimes = LoopTimes::Zero) : path(path), loopTimes(loopTimes){}
		const char* cPath() const {
			return path.c_str();
		}
	};

	struct Music {
		Path path;
		LoopTimes loopTimes;
		Music(Path path, LoopTimes loopTimes = LoopTimes::Zero) : path(path), loopTimes(loopTimes) {}
		const char* cPath() const {
			return path.c_str();
		}
	};


	struct Audio {
		virtual void play(const Music&) = 0;
		virtual void play(const Effect&) = 0;
		virtual void stopMusic() = 0;
		virtual void stopAllEffects() = 0;
		virtual void stopAllSound() = 0;
	};
}