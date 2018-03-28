#pragma once
#include "objects.h"

namespace ezGame {
	struct Draw;
}


namespace DrawObject {
	void draw(const Ball&, const Arena&, ezGame::Draw&);
}