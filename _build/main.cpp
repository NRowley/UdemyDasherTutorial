#include "raylib.h"
#include <iostream>
#include <string>
using namespace std;

struct AnimData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};


int main() {
	//window dimensions;
	const int WINDOW_WIDTH{ 512 };
	const int WINDOW_HEIGHT{ 380 };
	////rectangle dimensions
	//const int WIDTH{ 50 };
	//const int HEIGHT{ 80 };
	bool isInAir{ false };
	// jump velocity
	const int JUMP_VEL{ -600 };
	//initialize the window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DASHER");

	/*int posY{ WINDOW_HEIGHT - HEIGHT };*/
	int velocity{ 0 };

	//acceleration due to gravity (pixels/s)/s
	const int gravity{ 1000 };

	//Nebula variables
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

	//AnimData for nebula
	AnimData nebData{ 
		{ 0.0, 0.0, nebula.width / 8, nebula.height / 8 }, // Rectangle Rec
		{WINDOW_WIDTH, WINDOW_HEIGHT - nebula.height / 8 }, // Vector2 pos
		0, //int frame
		{1.0 / 12.0 }, // float updateTime
		0 //float runningTime
	};

	AnimData neb2Data{
		{ 0.0, 0.0, nebula.width / 8, nebula.height / 8 },
		{ WINDOW_WIDTH + 300, WINDOW_HEIGHT - nebula.height / 8 },
		0,
		{1.0 / 16.0 },
		0
	};

	//nebula X velocity
	int nebVel{-200};


	//Scarfy variables
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyData;
	scarfyData.rec.width = scarfy.width / 6;
	scarfyData.rec.height = scarfy.height;
	scarfyData.rec.x = 0;
	scarfyData.rec.y = 0;
	scarfyData.pos.x = WINDOW_WIDTH / 2 - scarfyData.rec.width / 2;
	scarfyData.pos.y = WINDOW_HEIGHT - scarfyData.rec.height;
	scarfyData.frame = 0;
	scarfyData.updateTime = 1.0 / 12.0;
	scarfyData.runningTime = 0.0;

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		//Start Drawing
		BeginDrawing();
		ClearBackground(WHITE);
		//delta time (time since last frame)
		float deltaTime{ GetFrameTime() };
		

		//ground check
		if (scarfyData.pos.y >= WINDOW_HEIGHT - scarfyData.rec.height) {
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

		//update nebula position
		nebData.pos.x += nebVel * deltaTime;

		neb2Data.pos.x += nebVel * deltaTime;


		//update position
		scarfyData.pos.y += velocity * deltaTime;
		//scarfy anim update
		if (!isInAir) {
			scarfyData.runningTime += deltaTime;
			if (scarfyData.runningTime >= scarfyData.updateTime) {
				scarfyData.runningTime = 0.0;
				//update animation frame
				scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
				scarfyData.frame++;
				if (scarfyData.frame > 5) {
					scarfyData.frame = 0;
				}
			}
		}

		//nebula anim update
		nebData.runningTime += deltaTime;
		if (nebData.runningTime >= nebData.runningTime) {
			nebData.runningTime = 0.0;
			nebData.rec.x = nebData.frame * nebData.rec.width;
			nebData.frame++;
			if (nebData.frame > 7) {
				nebData.frame = 0;
			}
		}

		neb2Data.runningTime += deltaTime;
		if (neb2Data.runningTime >= neb2Data.updateTime) {
			neb2Data.runningTime = 0.0;
			neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
			neb2Data.frame++;
			if (neb2Data.frame > 7) {
				neb2Data.frame = 0;
			}
		}

		//draw nebula 2
		DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
		//draw nebula 
		DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

		//draw scarfy
		DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

		//Stop drawing
		EndDrawing();
	}

	UnloadTexture(scarfy);
	UnloadTexture(scarfy);
	CloseWindow();
}