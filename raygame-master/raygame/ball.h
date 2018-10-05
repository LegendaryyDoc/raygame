#pragma once
#include "raylib.h"

class ball
{
public:
	Vector2 pos;
	float radius;

	float speed;

	bool enabled;

	void update(float deltaTime);
	void draw();
};
