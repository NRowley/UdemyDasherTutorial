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

	Rectangle nebRec{ 0.0, 0.0, nebula.width / 8, nebula.height / 8 };
	Vector2 nebPos{ WINDOW_WIDTH, WINDOW_HEIGHT - nebRec.height };

	Rectangle neb2Rec{ 0.0, 0.0, nebula.width / 8, nebula.height / 8 };
	Vector2 neb2Pos{ WINDOW_WIDTH + 300, WINDOW_HEIGHT - neb2Rec.height };


	// nebula anim var
	int nebFrame{};
	const float NEB_UPDATE_TIME{ 1.0 / 12.0 };
	float nebRunningTime{};
	
	int neb2Frame{};
	const float NEB2_UPDATE_TIME{ 1.0 / 16.0 };
	float neb2RunningTime{};

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

		//update nebula position
		nebPos.x += nebVel * deltaTime;

		neb2Pos.x += nebVel * deltaTime;


		//update position
		scarfyPos.y += velocity * deltaTime;
		//scarfy anim update
		if (!isInAir) {
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
		}

		//nebula anim update
		nebRunningTime += deltaTime;
		if (nebRunningTime >= NEB_UPDATE_TIME) {
			nebRunningTime = 0.0;
			nebRec.x = nebFrame * nebRec.width;
			nebFrame++;
			if (nebFrame > 7) {
				nebFrame = 0;
			}
		}

		neb2RunningTime += deltaTime;
		if (neb2RunningTime >= NEB2_UPDATE_TIME) {
			neb2RunningTime = 0.0;
			neb2Rec.x = neb2Frame * neb2Rec.width;
			neb2Frame++;
			if (neb2Frame > 7) {
				neb2Frame = 0;
			}
		}

		//draw nebula
		DrawTextureRec(nebula, nebRec, nebPos, WHITE);
		//draw nebula 2
		DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

		//draw scarfy
		DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

		//Stop drawing
		EndDrawing();
	}

	UnloadTexture(scarfy);
	UnloadTexture(scarfy);
	CloseWindow();
}