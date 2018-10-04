#pragma once
#include "raylib.h"

class pickup
{
public:
	Vector2 pos;
	float radius;

	int value;
	bool enabled;
	
	void draw();
};
