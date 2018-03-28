#pragma once

#include "draw.h"
#include "input.h"
#include "audio.h"

namespace ezGame {
	struct Settings;
	typedef Color Background;
	

	enum class CursorVisibility {
		Hide,
		Show
	};

	struct Window :
		virtual public Draw,
		virtual public Input,
		virtual public Audio
	{
		enum class Type {
			Windowed,
			Fullscreen
		};

		virtual Settings& settings() const = 0;
		virtual void quit() = 0;
	};

}


