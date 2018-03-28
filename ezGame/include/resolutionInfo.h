#pragma once
#include "common.h"

namespace ezGame {

	struct ResolutionInfo {
		virtual const Resolution resolution() const = 0;
	};

}