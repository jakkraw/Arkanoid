#pragma once
#include <chrono>

typedef double Coord;
typedef double Length;
typedef double Radius;
namespace ezGame {
	struct Draw;
}


struct Position {
	Coord x, y;
};

struct Size {
	Length width, height;
};

using std::chrono::seconds;

struct Arena {
	virtual ::Size size() const = 0;
	virtual ::Position startPosition() const = 0;
	

	

};
#include "Box2D.h"
struct NormalArena : public Arena {
	b2Body* groundBody;
	b2PolygonShape groundBox;
	b2World world;
	NormalArena();
	// Inherited via Arena
	virtual ::Size size() const override;
	virtual ::Position startPosition() const override;
	// Inherited via Drawable
	virtual void draw(ezGame::Draw &) const;
};

struct Circle {
	virtual Radius radius() const = 0;
	virtual ::Position center() const = 0;
};

struct Rectangle {
	virtual ::Position topLeft() const = 0;
	virtual ::Size size() const = 0;
};

struct Drawable {
	virtual void draw(ezGame::Draw&, Arena&) const = 0;
};

namespace Powerup {
	enum Type {
		LongPaddle, MultiBall, StickyPaddle
	};

	struct Effect {
		virtual Type type() const = 0;
		virtual seconds duration() const = 0;
	};

	struct Block : public Drawable, ::Rectangle {
		virtual Type type() const = 0;
		virtual Effect*&& get() = 0;
		
	};


	

}


struct Ball : public Drawable {
	virtual Radius radius() const = 0;
	virtual ::Position center() const = 0;

	// Inherited via Drawable
	virtual void draw(ezGame::Draw &, Arena &) const override;
};

struct NormalBall : public Ball {
	const Radius r = (Length)50;
	::Position c = { 0,0 };


	// Inherited via Ball
	virtual Radius radius() const override;

	virtual ::Position center() const override;

};


struct Stick : public ::Rectangle {
};