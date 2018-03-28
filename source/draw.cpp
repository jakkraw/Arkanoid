#include "draw.h"
#include "ezGame.h"
using namespace ezGame;

void DrawObject::draw(const Ball & ball, const Arena &arena, ezGame::Draw & draw)
{
	draw.draw(Image("ball/normal.bmp",  ezGame::Pos(ball.center().x - ball.radius(), ball.center().y - ball.radius()), ezGame::Size(ball.radius() * 2, ball.radius() * 2)));
}

