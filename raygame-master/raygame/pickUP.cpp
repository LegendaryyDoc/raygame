#include "pickUP.h"
#include "raylib.h"

void pickup::draw()
{
	if (enabled)
	{
		DrawCircle(pos.x, pos.y, radius, GOLD);
	}
}