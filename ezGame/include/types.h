#pragma once
#include <string> 
#include <functional>

typedef int Pixel;
typedef double Angle;
typedef std::string Title;
typedef std::string Path;

constexpr Angle Radian(double r) { return r * 180. / 3.14159265358979323846; }
constexpr Angle Degree(double d) { return d; }

struct Position {
	Position(Pixel x, Pixel y) : x(x), y(y) { }
	Pixel x, y;
};

struct Size {
	Size(Pixel x, Pixel y) : width(x), height(y) { }
	Pixel width, height;
};

typedef Size Resolution;

struct Color {
	Color() : red(255), blue(255), green(0), alpha(1.f) {  }
	Color(unsigned char r, unsigned char g, unsigned char b, float alpha = 1.f) : red(r), green(g), blue(b), alpha(alpha) {	}
	unsigned char red, green, blue; float alpha;
};

namespace Colors {
	const Color
		RED(255, 0, 0),
		GREEN(0, 255, 0),
		BLUE(0, 0, 255),
		WHITE(255, 255, 255),
		BLACK(0, 0, 0);
};

struct Point {
	Point(Position p, Color color = Colors::WHITE) : x(p.x), y(p.y), color(color) {}
	Pixel x, y; Color color;
};

struct Rectangle {
	Rectangle(Position topLeft, Size size, Color color = Colors::BLACK, bool filled = true) : topLeft(topLeft), size(size), color(color), filled(filled) {}
	Position topLeft; Size size; Color color; bool filled;
};

struct Line {
	Line::Line(Position begin, Position end, Color color = Colors::WHITE) : begin(begin), end(end), color(color) {}
	Position begin, end; Color color;
};

struct Circle {
	Circle(Position center, Pixel radius, Color color = Colors::WHITE, bool filled = true) : mouse(center), radius(radius), color(color), filled(filled) {}
	Position mouse; Pixel radius; Color color; bool filled;
};



struct Texture {
	Texture(Path path, Position position, Size size = { -1,-1 }, Angle angle = Radian(0)) : position(position), size(size), path(path), angle(angle) {}
	Path path; Position position; Size size; Angle angle;
};

struct KeyState {
	bool pressed, released, down;
};

enum class Mouse { LEFT = 1, MIDDLE, RIGHT };

enum class Keyboard
{
	// Numbers according to SDL_Scancodes
	RIGHT = 79, LEFT, DOWN, UP,
	A = 4, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	N1 = 30, N2, N3, N4, N5, N6, N7, N8, N9, N0,
	RETURN = 40, ESCAPE, BACKSPACE, TAB, SPACE, MINUS, EQUALS, LEFTBRACKET, RIGHTBRACKET,
	BACKSLASH, NONUSHASH, SEMICOLON, APOSTROPHE, GRAVE, COMMA, PERIOD, SLASH, CAPSLOCK,
	F1 = 58, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	PRINTSCREEN = 70, SCROLLLOCK, PAUSE, INSERT, HOME, PAGEUP, DELETE, END, PAGEDOWN,
	LCTRL = 224, LSHIFT, LALT, LGUI, RCTRL, RSHIFT, RALT, RGUI
};

struct Draw {
	virtual void draw(const Rectangle&) = 0;
	virtual void draw(const Line&) = 0;
	virtual void draw(const Point&) = 0;
	virtual void draw(const Texture&) = 0;
};

struct Input
{
	virtual const KeyState button(Mouse) const = 0;
	virtual const KeyState button(Keyboard) const = 0;
	virtual const Position cursor() const = 0;
};

struct Audio {
	virtual void playMusic(Path, bool loop = false) = 0;
	virtual void playEffect(Path, bool loop = false) = 0;
	virtual void stopMusic() = 0;
	virtual void stopEffects() = 0;
	virtual void stopAll() = 0;
};

struct Window :
	virtual public Draw,
	virtual public Input,
	virtual public Audio
{
	virtual void quit() = 0;
};


struct Settings
{
	enum WindowType {
		Windowed,
		Fullscreen
	};

	Settings(Title title = "ezWindow", Size size = { 640,480 }, Resolution resolution = { 640, 480 }, WindowType windowType = Windowed)
		: title(std::move(title)), resolution(std::move(resolution)), size(std::move(size)), windowType(windowType) {}

	Title title;
	Size size;
	Resolution resolution;
	WindowType windowType;
};
typedef std::function<void(Window&)> WindowLogic;

