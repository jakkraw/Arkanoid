#pragma once
#include "window.h"
#include "stage.h"

namespace ezGame {

	struct Ez : public virtual Window {
		virtual void goTo(Stage*&&) = 0;
		virtual Seconds delta() const = 0;
	};	
}