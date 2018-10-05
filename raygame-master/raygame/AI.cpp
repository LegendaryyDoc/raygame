#include <iostream>
#include "AI.h"
#include "raylib.h"
#include <ctime>
#include <cmath>

int ai::findStar(pickup arr[], int PickupMax, bool starEat)
{
	
	
	int offsetX = 0; // ai - current
	int offsetY = 0;

	int aiX = 0; // ai position
	int aiY = 0;

	int currentTargetDistance = 0;
	int currentX = 0; // current food position
	int currentY = 0;

	static int nearestDistance = 10000;
	static int nearestX = 0; // nearest food
	static int nearestY = 0;

	aiX = pos.x; // current ai position
	aiY = pos.y;

	if (starEat)
	{
		if (nearestDistance < 10000) {
			// movement of the ai
			if (aiX < nearestX)
			{
				pos.x += speed;
			}
			if (aiX > nearestX)
			{
				pos.x -= speed;
			}
			if (aiY < nearestY)
			{
				pos.y += speed;
			}
			if (aiY > nearestY)
			{
				pos.y -= speed;
			}
			return 0;
		}

		for (size_t i = 0; i < PickupMax; i++) // going through food array
		{
			currentX = arr[i].pos.x; // current position of food
			currentY = arr[i].pos.y;


			// calculate the distance between the food and the ai
			offsetX = aiX - currentX;
			offsetY = aiY - currentY;

			currentTargetDistance = (((offsetX * offsetX) + (offsetY * offsetY))); // a^2 + b^2 = c^2
			currentTargetDistance = sqrtf(currentTargetDistance);

			if (currentTargetDistance < nearestDistance) // current target is closer then nearest target 
			{
				nearestDistance = currentTargetDistance; // make nearest target the closest target
				nearestX = currentX;
				nearestY = currentY;
			}
		}
	}

	if (!starEat)
	{
		nearestDistance = 10000;
		nearestX = 0;
		nearestY = 0;

		starEat = true;
	}

	return 0;
}

void ai::draw()
{
	DrawCircle(pos.x, pos.y, radius, BLUE);
}