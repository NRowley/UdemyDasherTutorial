#include "raylib.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	//window dimensions;
	const int WINDOW_WIDTH{512};
	const int WINDOW_HEIGHT{380};
	////rectangle dimensions
	//const int WIDTH{ 50 };
	//const int HEIGHT{ 80 };
	bool isInAir{false};
	// jump velocity
	const int JUMP_VEL{ -600 };
	//initialize the window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DASHER");

	/*int posY{ WINDOW_HEIGHT - HEIGHT };*/
	int velocity{0};

	//acceleration due to gravity (pixels/s)/s
	const int gravity{ 1000 };

	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	Rectangle scarfyRec;
	scarfyRec.width = scarfy.width / 6;
	scarfyRec.height = scarfy.height;
	scarfyRec.x = 0;
	scarfyRec.y = 0;
	Vector2 scarfyPos;
	scarfyPos.x = WINDOW_WIDTH / 2 - scarfyRec.width / 2;
	scarfyPos.y = WINDOW_HEIGHT - scarfyRec.height;

	//animation frame player
	int frame{ 0 };
	const float UPDATE_TIME{ 1.0 / 12.0 };
	float runningTime{};

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		//Start Drawing
		BeginDrawing();
		ClearBackground(WHITE);
		//delta time (time since last frame)
		float deltaTime{ GetFrameTime() };
		

		//ground check
		if (scarfyPos.y >= WINDOW_HEIGHT - scarfy.height) {
			//on the ground
			velocity = 0;
			isInAir = false;
		}
		else {
			//in the air
			//apply gravity
			velocity += gravity * deltaTime;
			isInAir = true;
		}
		if (IsKeyPressed(KEY_SPACE) && !isInAir) {
			velocity += JUMP_VEL;
		}


		//update position
		scarfyPos.y += velocity * deltaTime;
		runningTime += deltaTime;
		if (runningTime >= UPDATE_TIME) {
			runningTime = 0.0;
			//update animation frame
			scarfyRec.x = frame * scarfyRec.width;
			frame++;
			if (frame > 5) {
				frame = 0;
			}
		}
		

		DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

		//Stop drawing
		EndDrawing();
	}

	UnloadTexture(scarfy);
	CloseWindow();
}