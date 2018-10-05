#pragma once
#include "raylib.h"
#include "pickUP.h"


class ai
{
public:
	Vector2 pos;
	float radius;

	float speed;

	int findStar(pickup arr[],int PickupMax, bool starEat);
	void draw();
};