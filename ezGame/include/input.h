#pragma once
#include "common.h"
#include "info.h"


namespace ezGame {
	struct KeyState {
		bool pressed, released, down;
	};

	class Mouse {
	public:
		enum Key {
			LEFT = 1, MIDDLE, RIGHT
		};

		typedef Position Position;
	};

	class Keyboard
	{
	public:
		enum Key {
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
		
	};

	


	struct KeyData {

		enum class InputType {
			Keyboard, Mouse
		};


		InputType type;
		union {
			Keyboard keyboardKey;
			Mouse mouseKey;
		};
	};

	struct Input : public virtual Info
	{
		virtual const bool pressed(Mouse::Key) const = 0;
		virtual const bool pressed(Keyboard::Key) const = 0;
		virtual const bool down(Mouse::Key) const = 0;
		virtual const bool down(Keyboard::Key) const = 0;
		virtual const bool released(Mouse::Key) const = 0;
		virtual const bool released(Keyboard::Key) const = 0;
		virtual const Mouse::Position cursor() const = 0;
		//virtual const std::vector<KeyData> keyData() const = 0;
	};
}

