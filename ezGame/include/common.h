#pragma once
#include <string>

namespace ezGame {

	typedef int Pixel;
	typedef double Angle;
	typedef double Seconds;

	typedef std::string Path;
	typedef const char* Title;
	typedef std::string TextString;
	typedef double Relative;


	constexpr Angle Radian(double r) { return r * 180. / 3.14159265358979323846; }
	constexpr Angle Degree(double d) { return d; }

	struct Size {
		Size(const Size&) = default;
		Size(Pixel width, Pixel height) : width(width), height(height) { }
		Pixel width, height;

		Size operator + (const Size& size) {
			return{ this->width + size.width,this->height + size.height };
		}

		Size operator - (const Size& size) {
			return{ this->width - size.width,this->height - size.height };
		}

	} const DEFAULT_SIZE = Size(-1, -1);
	constexpr bool operator==(const Size &a, const Size &b) { return a.height == b.height && a.width == b.width; }
	constexpr bool operator!=(const Size &a, const Size &b) { return a.height != b.height || a.width != b.width; }
	typedef Size Resolution;

	struct RelativeSize : public Size {
		RelativeSize(const RelativeSize&) = default;
		RelativeSize(Relative width, Relative height,const Resolution& res) : Size(Pixel(width * res.width),Pixel(height * res.height)) {}
	};
	typedef RelativeSize RSize;

	struct Position {
		Position(Pixel x, Pixel y) : x(x), y(y) { }
		Pixel x, y;

		Position operator + (const Position& pos) {
			return{ this->x + pos.x,this->y + pos.y };
		}

		Position operator - (const Position& pos) {
			return{ this->x - pos.x,this->y - pos.y };
		}

	};

	typedef Position Pos;

	struct RelativePosition : public Position {
		RelativePosition(const RelativePosition&) = default;
		RelativePosition(Relative x, Relative y,const Resolution& res) : Position(Pixel(x * res.width), Pixel(y * res.height)) {}
	};

	typedef RelativePosition RPos;
}