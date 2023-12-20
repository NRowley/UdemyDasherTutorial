#include "raylib.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	//window dimensions;
	const int WINDOW_WIDTH{512};
	const int WINDOW_HEIGHT{380};
	//rectangle dimensions
	const int WIDTH{ 50 };
	const int HEIGHT{ 80 };

	int posY{ WINDOW_HEIGHT - HEIGHT };
	int velocity{0};

	//acceleration due to gravity (pixels/frame/frame)
	const int gravity{ 1 };

	//initialize the window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DASHER");

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		//Start Drawing
		BeginDrawing();
		ClearBackground(WHITE);

		DrawRectangle(WINDOW_WIDTH / 2, posY, WIDTH, HEIGHT, BLUE);

		//ground check
		if (posY >= WINDOW_HEIGHT - HEIGHT) {
			//on the ground
			velocity = 0;
		}
		else {
			//in the air
			//apply gravity
			velocity += gravity;
		}
		if (IsKeyPressed(KEY_SPACE)) {
			velocity -= 10;
		}


		//update position
		posY += velocity;

		//Stop drawing
		EndDrawing();
	}
	CloseWindow();
}