#pragma once
#include "raylib.h"
#include "pickUP.h"


class ai
{
public:
	Vector2 pos;
	float radius;

	float speed;

	bool enabled;

	int nearestX = 0; // nearest food
	int nearestY = 0;


	int findStar(pickup arr[], int PickupMax);
	void draw();
};