#pragma once
#include "window.h"
#include "resolutionInfo.h"
namespace ezGame {

	struct Settings : virtual public ResolutionInfo {
		virtual const CursorVisibility cursorVisibility() const = 0;
		virtual const Window::Type windowType() const = 0;
		virtual const Background background() const = 0;
		virtual const Title title() const = 0;
	
		virtual void set(CursorVisibility) = 0;
		virtual void set(Window::Type) = 0;
		virtual void set(Background) = 0;
		virtual void set(Resolution) = 0;
		virtual void set(Title) = 0;
	};

}