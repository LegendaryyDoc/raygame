#include <iostream>
#include "AI.h"
#include "raylib.h"
#include <ctime>
#include <cmath>

//int ai::findStar(pickup arr[], int PickupMax, ai aiArr[], bool starEat)
int ai::findStar(pickup arr[], int PickupMax)
{
	int offsetX = 0; // ai - current
	int offsetY = 0;

	int currentTargetDistance = 0;
	int currentX = 0; // current food position
	int currentY = 0;

	int nearestDistance = 10000;

		for (size_t i = 0; i < PickupMax; i++) // going through food array
		{
			
			currentX = arr[i].pos.x; // current position of food
			currentY = arr[i].pos.y;

			// calculate the distance between the food and the ai
			offsetX = pos.x - currentX;
			offsetY = pos.y - currentY;

			currentTargetDistance = (((offsetX * offsetX) + (offsetY * offsetY))); // a^2 + b^2 = c^2
			currentTargetDistance = sqrtf(currentTargetDistance);

			if (currentTargetDistance < nearestDistance) // current target is closer then nearest target 
			{
				nearestDistance = currentTargetDistance; // make nearest target the closest target
				nearestX = currentX;
				nearestY = currentY;
			}
		}
			
				
		return 0;
}

void ai::draw()
{
	if (pos.x < nearestX)
	{
		pos.x += speed;
	}
	if (pos.x > nearestX)
	{
		pos.x -= speed;
	}
	if (pos.y < nearestY)
	{
		pos.y += speed;
	}
	if (pos.y > nearestY)
	{
		pos.y -= speed;
	}

	DrawCircle(pos.x, pos.y, radius, BLUE);
}