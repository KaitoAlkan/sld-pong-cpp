#pragma once

using namespace std;
#include <fstream>
#include <vector>
#include <stack>
#include "SDL.h"
#include "SDL_TTF.h"
#include "SDL_mixer.h"

typedef struct _InputState {
    bool UpPlayerOne = false;
    bool DownPlayerOne = false;
    bool leftp1 = false;
    bool rightp1 = false;
    bool FirePlayerOne = false;

    bool UpPlayerTwo = false;
    bool DownPlayerTwo = false;
    bool leftp2 = false;
    bool rightp2 = false;
    bool FirePlayerTwo = false;

    bool serve = false;
}InputState;

typedef struct _Sprite {
    SDL_Texture* texture = 0;
    SDL_Rect dest;
    bool isVisible = true;
    SDL_bool isColliding(const _Sprite& obj);
    SDL_Rect GetRectangle() const {
        return dest;
    }
}Sprite;

typedef struct _Text {
    TTF_Font* font;
    SDL_Color color;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect dest;
    bool isVisible = true;
}Text;

typedef struct _Bgm {
    Mix_Music* music;
}Bgm;

enum GAME_STAGES
{
    GS_INVALID = -1,
    GS_LOGO = 0,
    GS_MAIN_MENU,
    GS_GAMEPLAY,
    GS_GAMEPAUSE,
    GS_GAMEOVER,
    GS_CREDITS
};

typedef struct _GameStage {
    string stage_name;
    int game_stageID = GS_INVALID;
    int level;
}GameStage;


typedef vector<Sprite> SpriteAssets;
typedef vector<Text> TextAssets;
typedef vector<Bgm> BgmAssets;
typedef stack<GameStage> GameStages;

typedef struct _ResourceManager {
    SpriteAssets* spritesAssets;
    TextAssets* textAssets;
    BgmAssets* musicAssets;
    GameStages* gameStages;
    InputState* inputState;
}ResourceManager;
