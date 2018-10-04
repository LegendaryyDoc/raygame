#pragma once
#include "raylib.h"

class ball
{
public:
	Vector2 pos;
	float radius;

	float speed;

	void update(float deltaTime);
	void draw();
};
