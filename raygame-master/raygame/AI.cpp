#include <iostream>
#include "AI.h"
#include "raylib.h"
#include <ctime>
#include <cmath>

int ai::findStar(pickup arr[])
{
	int offsetX = 0; // ai - current
	int offsetY = 0;

	int aiX = 0; // ai position
	int aiY = 0;

	int currentTargetDistance = 0; 
	int currentX = 0; // current food position
	int currentY = 0;

	int nearestDistance = 10000;
	int nearestX = 0; // nearest food
	int nearestY = 0;

	for (size_t i = 0; i < 250; i++) // going through food array
	{
		currentX = arr[i].pos.x; // current position of food
		currentY = arr[i].pos.y;

		aiX = pos.x; // current ai position
		aiY = pos.y;

		// calculate the distance between the food and the ai
		offsetX = aiX - currentX;
		offsetY = aiY - currentY;

		currentTargetDistance = (((offsetX * offsetX) + (offsetY * offsetY))); // a^2 + b^2 = c^2
		currentTargetDistance = sqrtf(currentTargetDistance);

		if (currentTargetDistance > nearestDistance) // current target is closer then nearest target 
		{
			nearestDistance = currentTargetDistance; // make nearest target the closest target
		}
	}
	return 0;
}

void ai::draw()
{
	DrawCircle(pos.x, pos.y, radius, BLUE);
}