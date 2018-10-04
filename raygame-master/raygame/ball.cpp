#include "ball.h"
#include "raylib.h"

void ball::update(float deltaTime)
{
	if (IsKeyDown(KEY_W))
	{
		pos.y -= speed * deltaTime;
	}
	if (IsKeyDown(KEY_S))
	{
		pos.y += speed * deltaTime;
	}
	if (IsKeyDown(KEY_A))
	{
		pos.x -= speed * deltaTime;
	}
	if (IsKeyDown(KEY_D))
	{
		pos.x += speed * deltaTime;
	}
}

void ball::draw()
{
	DrawCircle(pos.x, pos.y, radius, LIME);
}