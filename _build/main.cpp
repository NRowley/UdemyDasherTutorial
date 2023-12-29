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
	int windowDimensions[2];
	windowDimensions[0] = 512;
	windowDimensions[1] = 380;
	
	bool isInAir{ false };
	// jump velocity
	const int JUMP_VEL{ -600 };
	//initialize the window
	InitWindow(windowDimensions[0], windowDimensions[1], "DASHER");

	/*int posY{ WINDOW_HEIGHT - HEIGHT };*/
	int velocity{ 0 };

	//acceleration due to gravity (pixels/s)/s
	const int gravity{ 1000 };

	//Nebula variables
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");


	AnimData nebulae[3]{};
	for (int i = 0; i < 3; i++) {
		nebulae[i].rec.x = 0.0;
		nebulae[i].rec.y = 0.0;
		nebulae[i].rec.width = nebula.width / 8;
		nebulae[i].rec.height = nebula.height / 8;
		nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
		nebulae[i].frame = 0;
		nebulae[i].updateTime = 1.0 / 16.0;
		nebulae[i].runningTime = 0;
	}

	nebulae[0].pos.x = windowDimensions[0];
	nebulae[1].pos.x = windowDimensions[0] + 300;
	nebulae[2].pos.x = windowDimensions[0] + 600;

	//nebula X velocity
	int nebVel{-200};


	//Scarfy variables
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyData;
	scarfyData.rec.width = scarfy.width / 6;
	scarfyData.rec.height = scarfy.height;
	scarfyData.rec.x = 0;
	scarfyData.rec.y = 0;
	scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
	scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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
		if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height) {
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
		nebulae[0].pos.x += nebVel * deltaTime;

		nebulae[1].pos.x += nebVel * deltaTime;


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
		nebulae[0].runningTime += deltaTime;
		if (nebulae[0].runningTime >= nebulae[0].runningTime) {
			nebulae[0].runningTime = 0.0;
			nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
			nebulae[0].frame++;
			if (nebulae[0].frame > 7) {
				nebulae[0].frame = 0;
			}
		}

		nebulae[1].runningTime += deltaTime;
		if (nebulae[1].runningTime >= nebulae[1].updateTime) {
			nebulae[1].runningTime = 0.0;
			nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
			nebulae[1].frame++;
			if (nebulae[1].frame > 7) {
				nebulae[1].frame = 0;
			}
		}

		//draw nebula 2
		DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
		//draw nebula 
		DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

		//draw scarfy
		DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

		//Stop drawing
		EndDrawing();
	}

	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
}