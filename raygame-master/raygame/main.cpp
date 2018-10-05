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
#include "AI.h"
#include <iostream>
#include <string>
#include <ctime>

static int PickupMax = 250;

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	static  int AIMax = 1;
	
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	ball player;
	player.pos = { 100, 100 };
	player.radius = 5.0f;
	player.speed = 40.0f;
	
	srand((unsigned int)time(NULL));

	ai ai[10];

	for (size_t i = 0; i < AIMax; ++i) // randomly spawning ai
	{
		Vector2 tmp = { (float)(rand() % 750), (float)(rand() % 400) };
		ai[i] = { tmp, 5.0f, 1.0f};
	}

	pickup smallPickUps[250];
	//pickup largePickUps[25];

	for (size_t i = 0; i < PickupMax; ++i) // randomly spawning small food
	{
		smallPickUps[i] = {{ (float)(rand() % 750), (float)(rand() % 400) }, 1.0f, 1, true };

		//smallPickUps[i] = { 500,300, 1.0f,1,true };
	}
	/*for (size_t i = 0; i < 25; ++i) // randomly spawning large food
	{
		largePickUps[i] = { { (float)(rand() % 750), (float)(rand() % 400) }, 2.0f, 5, true };
	}*/
	//--------------------------------------------------------------------------------------

	int score = 0;
	bool gameOn = true;

	// Main game loop
	while (gameOn)  
	{

		// Update
		//----------------------------------------------------------------------------------
		player.update(GetFrameTime());
		ai->findStar(smallPickUps,PickupMax,true);

		float randomWidth = (float)(rand() % 750);
		float randomHeight = (float)(rand() % 400);

		for (size_t i = 0; i < PickupMax; i++) // small food
		{
			if (smallPickUps[i].enabled && CheckCollisionCircles(player.pos, player.radius, smallPickUps[i].pos, smallPickUps[i].radius))
			{
				smallPickUps[i].enabled = false;
				score++;
				player.speed -= .01;
				player.radius += .01;

				smallPickUps[i] = { { (float)(rand() % 750), (float)(rand() % 400) }, 1.0f, 1, true };
			}
			if (smallPickUps[i].enabled && CheckCollisionCircles(ai->pos, ai->radius, smallPickUps[i].pos, smallPickUps[i].radius))
			{
				smallPickUps[i].enabled = false;
				score++;
				ai->speed -= .001;
				ai->radius += .001;

				ai->findStar(smallPickUps, PickupMax, false);

				smallPickUps[i] = { { (float)(rand() % 750), (float)(rand() % 400) }, 1.0f, 1, true };
			}
		}
		/*for (size_t i = 0; i < 25; i++) // large food
		{
			if (largePickUps[i].enabled && CheckCollisionCircles(player.pos, player.radius, largePickUps[i].pos, largePickUps[i].radius))
			{
				largePickUps[i].enabled = false;
				score += 5;
				player.speed -= .05;
				player.radius += .05;

				largePickUps[i] = { { randomWidth, randomHeight }, 2.0f, 5, true };
			}
		}*/

		if (player.pos.y > screenHeight + player.radius) // screen wrapping
		{	
			player.pos.y = -player.radius;
		}
		else if(player.pos.y < -player.radius)
		{
			player.pos.y = screenHeight + player.radius;
		}

		if (player.pos.x > screenWidth + player.radius)
		{
			player.pos.x = -player.radius;
		}
		else if (player.pos.x < -player.radius)
		{
			player.pos.x = screenWidth + player.radius;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		for (size_t i = 0; i < PickupMax; i++)
		{
			smallPickUps[i].draw();
		}
		/*for (size_t i = 0; i < 25; i++)
		{
			largePickUps[i].draw();
		}*/

		player.draw();
		for (size_t i = 0; i < AIMax; i++)
		{
			ai[i].draw();
		}

		DrawText(std::to_string(score).c_str(), 600, 75, 25, RED);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}