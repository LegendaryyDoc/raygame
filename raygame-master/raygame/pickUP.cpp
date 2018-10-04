#include <iostream>
#include "pickUP.h"
#include "raylib.h"
#include <ctime>



void pickup::draw()
{
	srand(time(NULL));

	Color colors[24] =
	{
		LIGHTGRAY,
		GRAY,
		DARKGRAY,
		YELLOW,
		GOLD,
		ORANGE,
		PINK,
		RED,
		MAROON,
		GREEN,
		LIME,
		DARKGREEN,
		SKYBLUE,
		BLUE,
		DARKBLUE,
		PURPLE,
		VIOLET,
		DARKPURPLE,
		BEIGE,
		BROWN,
		DARKBROWN,
		WHITE,
		MAGENTA,
		RAYWHITE,
	};

	if (enabled)
	{
		DrawCircle(pos.x, pos.y, radius, colors[rand() % 24]);
	}
}