#include "objects.h"
#include "draw.h"

void Ball::draw(ezGame::Draw &draw, Arena &arena) const
{
	DrawObject::draw(*this,  arena, draw);

}

Radius NormalBall::radius() const
{
	return r;
}

Position NormalBall::center() const
{
	return c;
}

NormalArena::NormalArena() : world({ 0,-10 })
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	groundBody = world.CreateBody(&groundBodyDef);
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
}

Size NormalArena::size() const
{
	return{ 800,400 };
}

Position NormalArena::startPosition() const
{
	return{ 200,200 };
}

void NormalArena::draw(ezGame::Draw &draw) const
{
	auto shapes = world.GetBodyList();
	world.get


	for (auto& shape : shapes) {




	}


}
