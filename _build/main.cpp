#include "raylib.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	//window dimensions;
	const int WINDOW_WIDTH{512};
	const int WINDOW_HEIGHT{380};
	//initialize the window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DASHER");

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		//Start Drawing
		BeginDrawing();
		ClearBackground(WHITE);

		//Stop drawing
		EndDrawing();
	}
	CloseWindow();
}