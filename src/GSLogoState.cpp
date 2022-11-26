#include "GSLogoState.h"
#include "StructsDef.h"

#include <stdlib.h>
#include <ctime>

SDL_bool _Sprite::isColliding(const _Sprite& obj)
{
	const SDL_Rect temp = obj.GetRectangle();
	return SDL_HasIntersection(&dest, &temp);
}

float ballSpeedX = 0.2;
float ballSpeedY = 0.2;

int P1score = 0;
int P2score = 0;

int randNum(int high, int low) {
	return rand() % high + low;
}

void GSLogoStateUpdate(float delta, ResourceManager& resource) {

	InputState inputState = *resource.inputState;
	GameStages gameStages = *resource.gameStages;

	SpriteAssets& spr_assets = *resource.spritesAssets;
	Sprite& spr = spr_assets[0];

	/* Si presione cualquier tecla(arriba, abajo, izquierda
	if (inputState.DownPlayerOne || inputState.UpPlayerOne || 
		inputState.leftp1 || inputState.rightp1 || inputState.FirePlayerOne) {

	}*/

}

void P1StateUpdate(float delta, ResourceManager& resource) {

	InputState inputState = *resource.inputState;
	GameStages gameStages = *resource.gameStages;

	SpriteAssets& spr_assets = *resource.spritesAssets;
	Sprite& spr = spr_assets[1];

	if (inputState.DownPlayerOne) {

		spr.dest.y += 0.5 * delta;

	}
		
	if (inputState.UpPlayerOne) {

		spr.dest.y -= 0.5 * delta;

	}
		
	if (inputState.FirePlayerOne) {

	}

	if (spr.isColliding(spr_assets[4])) {

		spr.dest.y += 10;

	}

	if (spr.isColliding(spr_assets[5])) {

		spr.dest.y -= 10;

	}
}

void P2StateUpdate(float delta, ResourceManager& resource) {

	InputState inputState = *resource.inputState;
	GameStages gameStages = *resource.gameStages;

	SpriteAssets& spr_assets = *resource.spritesAssets;
	Sprite& spr = spr_assets[2];

	if (inputState.DownPlayerTwo) {

		spr.dest.y += 0.5 * delta;

	}

	if (inputState.UpPlayerTwo) {

		spr.dest.y -= 0.5 * delta;

	}

	if (inputState.FirePlayerTwo) {

	}

	if (spr.isColliding(spr_assets[4])) {

		spr.dest.y += 10;

	}

	if (spr.isColliding(spr_assets[5])) {

		spr.dest.y -= 10;

	}

}

void BallStateUpdate(float delta, ResourceManager& resource) {

	InputState inputState = *resource.inputState;
	GameStages gameStages = *resource.gameStages;

	SpriteAssets& spr_assets = *resource.spritesAssets;
	Sprite& spr = spr_assets[3];

	TextAssets& text_assets = *resource.textAssets;

	srand(time(NULL));

	if (inputState.serve) {

		spr_assets[0].isVisible = false;
		spr.dest.x += ballSpeedX * delta;
		spr.dest.y += ballSpeedY * delta;
		
	}

	
	if (spr.isColliding(spr_assets[4])) {

		spr.dest.y += 1;
		ballSpeedY = -ballSpeedY;

	}

	if (spr.isColliding(spr_assets[5])) {

		spr.dest.y -= 1;
		ballSpeedY = -ballSpeedY;

	}

	if (spr.isColliding(spr_assets[1]) || spr.isColliding(spr_assets[2])) {

		ballSpeedX = -ballSpeedX * 1.1;

	}
	
	if (spr.isColliding(spr_assets[6])) {

		P2score += 1;
		ballSpeedX = 0.2;
		ballSpeedY = 0.2;
		spr.dest.x = (640 / 2) - 24;
		spr.dest.y = (480 / 2) - 24;
		int serveNum = randNum(4, 1);

		switch (serveNum)
		{
		case 1:
			break;
		case 2:
			ballSpeedX = -ballSpeedX;
			break;
		case 3:
			ballSpeedY = -ballSpeedY;
			break;
		case 4:
			ballSpeedX = -ballSpeedX;
			ballSpeedY = -ballSpeedY;
			break;
		default:
			break;
		}

	}

	if (spr.isColliding(spr_assets[7])) {

		P1score += 1;
		ballSpeedX = 0.2;
		ballSpeedY = 0.2;
		spr.dest.x = (640 / 2) - 24;
		spr.dest.y = (480 / 2) - 24;
		int serveNum = randNum(4, 1);

		switch (serveNum)
		{
		case 1:
			break;
		case 2:
			ballSpeedX = -ballSpeedX;
			break;
		case 3:
			ballSpeedY = -ballSpeedY;
			break;
		case 4:
			ballSpeedX = -ballSpeedX;
			ballSpeedY = -ballSpeedY;
			break;
		default:
			break;
		}

	}

	if (P1score == 5) {
		
		spr.isVisible = false;
		inputState.serve = false;

	}

	if (P2score == 5) {

		spr.isVisible = false;
		inputState.serve = false;

	}

}

void EndStateUpdate(float delta, ResourceManager& resource) {

	InputState inputState = *resource.inputState;
	GameStages gameStages = *resource.gameStages;

	SpriteAssets& spr_assets = *resource.spritesAssets;

	if (P1score == 5) {
		spr_assets[8].isVisible = true;
		spr_assets[0].isVisible = true;
	}

	if (P2score == 5) {
		spr_assets[9].isVisible = true;
		spr_assets[0].isVisible = true;
	}

}