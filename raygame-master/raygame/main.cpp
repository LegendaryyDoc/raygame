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
	static  int AIMax = 10;
	
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	ball player;

	Vector2 tmpPos = { (float)(rand() % 750), (float)(rand() % 400) };

	player.pos = tmpPos;
	player.radius = 5.0f;
	player.speed = 40.0f;
	player.enabled = true;
	
	srand((unsigned int)time(NULL));

	ai ai[10];

	for (size_t i = 0; i < AIMax; ++i) // randomly spawning ai
	{
		Vector2 tmp = { (float)(rand() % 750), (float)(rand() % 400)};
		ai[i] = { tmp, 5.0f, 0.65f, true};
	}

	pickup smallPickUps[250];

	for (size_t i = 0; i < PickupMax; ++i) // randomly spawning small food
	{
		smallPickUps[i] = {{ (float)(rand() % 750), (float)(rand() % 400) }, 1.0f, 1, true };
	}

	//--------------------------------------------------------------------------------------

	int playerScore = 0;
	int aiScore[10] = {};
	bool gameOn = true;

	for (size_t i = 0; i < AIMax; i++) 
	{
		ai[i].findStar(smallPickUps, PickupMax);
	}
	// Main game loop
	while (gameOn)  
	{
		player.update(GetFrameTime());

		float randomWidth = (float)(rand() % 750);
		float randomHeight = (float)(rand() % 400);

		/*----------------------------------------------------------------------------------*/
		/*		Collision with Star		*/

		for (size_t i = 0; i < PickupMax; i++) // small food
		{
			if (smallPickUps[i].enabled && CheckCollisionCircles(player.pos, player.radius, smallPickUps[i].pos, smallPickUps[i].radius)) // player collision with a star
			{
				smallPickUps[i].enabled = false; // despawning the star
				playerScore++;
				player.speed -= .01;
				player.radius += .01;

				smallPickUps[i] = { { (float)(rand() % 750), (float)(rand() % 400) }, 1.0f, 1, true }; // respawning the star

				for (size_t j = 0; j < AIMax; j++)
				{
					ai[j].findStar(smallPickUps, PickupMax);
				}
			}
			for (size_t j2 = 0; j2 < AIMax; j2++)
			{
				if (smallPickUps[i].enabled && CheckCollisionCircles(ai[j2].pos, ai[j2].radius, smallPickUps[i].pos, smallPickUps[i].radius)) // ai collision with a star
				{
						smallPickUps[i].enabled = false; // despawning the star
						aiScore[j2]++;
						ai[j2].speed -= .0001;
						ai[j2].radius += .01;
						smallPickUps[i] = { { (float)(rand() % 750), (float)(rand() % 400) }, 1.0f, 1, true }; // respawning the star

						for (size_t j = 0; j < AIMax; j++) 
						{
							ai[j].findStar(smallPickUps, PickupMax);
						}
				}
			}
		}

		/*----------------------------------------------------------------------------------*/
		/*		Player and AI Killing		*/

		for (size_t i = 0; i < AIMax; i++)
		{
			std::cout << ai[i].speed << std::endl;

			if (ai[i].enabled && CheckCollisionCircles(player.pos, player.radius, ai[i].pos, ai[i].radius)) // checking collision between player and ai
			{
				if (playerScore > aiScore[i]) // if player score is higher
				{
					ai[i].enabled = false; // killing the ai
					playerScore = playerScore + aiScore[i];
					player.speed = (player.speed -(0.65f - ai[i].speed));
					player.radius = (player.radius +(ai[i].radius - 5.0f));

					aiScore[i] = 0; // reseting stats and score
					ai[i].speed = 0.65f;
					ai[i].radius = 5.0f;

					Vector2 tmp = { (float)(rand() % 750), (float)(rand() % 400) }; // respawning ai
					ai[i] = { tmp, 5.0f, 0.65f, true };
				}
				else if(playerScore < aiScore[i]) // if players score is lower
				{
					player.enabled = false; // killing player
					aiScore[i] = playerScore + aiScore[i];
					ai[i].speed = (ai[i].speed - (40.0f - player.speed));
					ai[i].radius = (ai[i].radius + (player.radius - 5.0f));

					playerScore = 0; // reseting sats
					player.speed = 40.0f;
					player.radius = 5.0f;

					Vector2 tmpPos = { (float)(rand() % 750), (float)(rand() % 400) }; // respawning player
					player.pos = tmpPos;
					player.radius = 5.0f;
					player.speed = 40.0f;
					player.enabled = true;
				}
		}
		for (size_t j = 0; j < AIMax; j++)
		{
			if (CheckCollisionCircles(ai[j].pos, ai[j].radius, ai[i].pos, ai[i].radius))
			{
				if (aiScore[i] > aiScore[j]) // one ai has more score then other ai
				{
					ai[j].enabled = false; // kills ai 
					aiScore[i] = aiScore[j] + aiScore[i];
					ai[i].speed = (ai[i].speed - (0.65f - ai[j].speed));
					ai[i].radius = (ai[i].radius + (ai[j].radius - 5.0f));

					aiScore[j] = 0; // reseting stats and score
					ai[j].speed = 0.65f;
					ai[j].radius = 5.0f;

					Vector2 tmp = { (float)(rand() % 750), (float)(rand() % 400) }; // respawning ai
					ai[j] = { tmp, 5.0f, 0.65f, true };

				}
				else if (aiScore[j] > aiScore[i])
				{
					ai[i].enabled = false; // kills ai
					aiScore[j] = aiScore[i] + aiScore[j];
					ai[j].speed = (ai[j].speed - (40.0f - ai[i].speed));
					ai[j].radius = (ai[j].radius + (ai[i].radius - 5.0f));

					aiScore[i] = 0; // reseting stats and score
					ai[i].speed = 0.65f;
					ai[i].radius = 5.0f;

					Vector2 tmp = { (float)(rand() % 750), (float)(rand() % 400) }; // respawning ai
					ai[i] = { tmp, 5.0f, 0.65f, true };
				}
			}
		}
	}
		/*----------------------------------------------------------------------------------*/
		/*		Wrapping the screen		*/	

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

		for (size_t i = 0; i < AIMax; i++)
		{
			if (ai[i].pos.y > screenHeight + player.radius) // screen wrapping
			{
				ai[i].pos.y = -player.radius;
			}
			else if (ai[i].pos.y < -player.radius)
			{
				ai[i].pos.y = screenHeight + player.radius;
			}

			if (ai[i].pos.x > screenWidth + player.radius)
			{
				ai[i].pos.x = -player.radius;
			}
			else if (ai[i].pos.x < -player.radius)
			{
				ai[i].pos.x = screenWidth + player.radius;
			}
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

		player.draw();

		for (size_t i = 0; i < AIMax; i++)
		{
			ai[i].draw();
		}

		DrawText(std::to_string(playerScore).c_str(), 600, 75, 25, RED); // displaying player score

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}