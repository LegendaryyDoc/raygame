/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "ball.h"
#include "pickUP.h"
#include <iostream>
#include <string>
#include <ctime>

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	ball player;
	player.pos = { 100, 100 };
	player.radius = 10.0f;
	player.speed = 70.0f;

	srand((unsigned int)time(NULL));

	pickup pickUps[3] =
	{
		{{rand() % 750, rand() % 400}, 5.0f, 1, true},
		{{ rand() % 750, rand() % 400 }, 5.0f, 1, true},
		{{rand() % 750, rand() % 400 }, 5.0f, 1, true}
	};
	//--------------------------------------------------------------------------------------

	int score = 0;

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		player.update(GetFrameTime());

		float randomWidth = rand() % 750;
		float randomHeight = rand() % 400;
		for (size_t i = 0; i < 3; i++)
		{
			if (pickUps[i].enabled && CheckCollisionCircles(player.pos, player.radius, pickUps[i].pos, pickUps[i].radius))
			{
				pickUps[i].enabled = false;
				score++;

				pickUps[i] = { { randomWidth, randomHeight }, 5.0f, 1, true };
			}
		}
		if (player.pos.y > screenHeight || player.pos.y < 0) 
		{
			if (player.pos.y > 400)
			{
				player.pos.y = 0;
			}
			else
			{
				player.pos.y = screenHeight;
			}
		}
		if (player.pos.x > screenWidth || player.pos.x <= 0) 
		{
			if (player.pos.x > 225)
			{
				player.pos.x = 0;
			}
			else
			{
				player.pos.x = screenWidth;
			}
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		for (size_t i = 0; i < 3; i++)
		{
			pickUps[i].draw();
		}

		player.draw();

		DrawText(std::to_string(score).c_str(), 600, 100, 25, RED);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}