#pragma once

namespace ezGame {
	typedef float Alpha;

	struct Color {
		Color() : red(255), blue(255), green(0), alpha(1.f) {  }
		Color(unsigned char r, unsigned char g, unsigned char b, Alpha alpha = 1.f) : red(r), green(g), blue(b), alpha(alpha) {	}
		unsigned char red, green, blue; Alpha alpha;
		Color with(Alpha alpha) const { 
			return{ red,green,blue, alpha };
		}
	};
}

