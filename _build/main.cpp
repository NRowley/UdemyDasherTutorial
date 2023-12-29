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

bool isOnGround(AnimData data, int windowHeight) {
	return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame) {
	//update running time
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime) {
		data.runningTime = 0.0;
		// update animation frame
		data.rec.x = data.frame * data.rec.width;
		data.frame++;
		if (data.frame > maxFrame) {
			data.frame = 0;
		}
	}
	return data;
}

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

	const int nebulaeSize{ 10 };
	AnimData nebulae[nebulaeSize]{};
	for (int i = 0; i < nebulaeSize; i++) {
		nebulae[i].rec.x = 0.0;
		nebulae[i].rec.y = 0.0;
		nebulae[i].rec.width = nebula.width / 8;
		nebulae[i].rec.height = nebula.height / 8;
		nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
		nebulae[i].frame = 0;
		nebulae[i].updateTime = 1.0 / 16.0;
		nebulae[i].runningTime = 0;
		nebulae[i].pos.x = windowDimensions[0] + (i * 300);
	}

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

	//Background, midground, foreground
	Texture2D background = LoadTexture("textures/far-buildings.png");
	float bgX{};
	Texture2D midGround = LoadTexture("textures/back-buildings.png");
	float mgX{};
	Texture2D foreGround = LoadTexture("textures/foreground.png");
	float fgX{};


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		//delta time (time since last frame)
		float deltaTime{ GetFrameTime() };
		//Start Drawing
		
		BeginDrawing();
		ClearBackground(WHITE);
		bgX -= 20 * deltaTime;
		if (bgX <= -background.width * 2) {
			bgX = 0.0;
		}

		mgX -= 40 * deltaTime;
		if (mgX <= -midGround.width * 2) {
			mgX = 0.0;
		}

		fgX -= 80 * deltaTime;
		if (fgX <= -foreGround.width * 2) {
			fgX = 0.0;
		}

		//draw background
		Vector2 bg1Pos{ bgX, 0.0 };
		DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
		Vector2 bg2Pos{ bgX + background.width * 2, 0.0 };
		DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
		//mid
		Vector2 mg1Pos{ mgX, 0.0 };
		DrawTextureEx(midGround, mg1Pos, 0.0, 2.0, WHITE);
		Vector2 mg2Pos{ mgX + midGround.width*2, 0.0 };
		DrawTextureEx(midGround, mg2Pos, 0.0, 2.0, WHITE);
		//fore
		Vector2 fg1Pos{ fgX, 0.0 };
		DrawTextureEx(foreGround, fg1Pos, 0.0, 2.0, WHITE);
		Vector2 fg2Pos{ fgX + foreGround.width*2, 0.0 };
		DrawTextureEx(foreGround, fg2Pos, 0.0, 2.0, WHITE);

		//ground check
		if (isOnGround(scarfyData, windowDimensions[1])) {
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
		for (int i = 0; i < nebulaeSize; i++) {
			nebulae[i].pos.x += nebVel * deltaTime;
		}

		//update position
		scarfyData.pos.y += velocity * deltaTime;
		//scarfy anim update
		if (!isInAir) {
			scarfyData = updateAnimData(scarfyData, deltaTime, 5);
		}
		//nebula anim update
		for (int i = 0; i < nebulaeSize; i++) {
			nebulae[i] = updateAnimData(nebulae[i], deltaTime, 7);
		}

		for (int i = 0; i < nebulaeSize; i++) {
			DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
		}

		//draw scarfy
		DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

		//Stop drawing
		EndDrawing();
	}

	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	UnloadTexture(background);
	UnloadTexture(midGround);
	UnloadTexture(foreGround);
	CloseWindow();
}