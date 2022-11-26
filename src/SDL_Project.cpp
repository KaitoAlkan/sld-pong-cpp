// SDL_Project.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <sstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "SDL_mixer.h"
#include "InputModule.h"
#include "GSLogoState.h"

using namespace std;

///////// Definicion de estructuras /////////////
#include "StructsDef.h"
///////// Definicion de estructuras /////////////


///////// Variables y Constantes Globales /////////////
const int WIDTH = 640;
const int HEIGHT = 480;
const int WIDTHPaleta = 10;
const int HEIGHTPaleta = 68;
const int starting_x_p1 = 5;
const int starting_y_p1 = 210;
const int starting_x_p2 = WIDTH - (starting_x_p1 + WIDTHPaleta);
const int starting_y_p2 = 210;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_bool isGameRunning = SDL_TRUE;
float time_multiplier = 1.0f;
InputState gameInputState;
SpriteAssets spritesAssets;
TextAssets textAssets;
BgmAssets musicAssets;
GameStages gameStages;
int LeftScore = 0;
int RightScore = 0;

ResourceManager resourceManager;

///////// Variables y Constantes Globales /////////////

///////// Funciones de inicializacion y destruccion /////////////
void initEngine()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    TTF_Init();

    int initted = Mix_Init(MIX_INIT_MP3);
    if ( (initted & MIX_INIT_MP3) != MIX_INIT_MP3) {
        cout << "Mix_Init: Failed to init required ogg and mod support!" << endl;
        cout << "Mix_Init: " << Mix_GetError() << endl;
        // handle error
    }

    window = SDL_CreateWindow("ULTIMATE Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initializing Resource Manager
    resourceManager.spritesAssets = &spritesAssets;
    resourceManager.textAssets = &textAssets;
    resourceManager.musicAssets = &musicAssets;
    resourceManager.gameStages = &gameStages;
    resourceManager.inputState = &gameInputState;

    // Starting Game stage
    GameStage logoGameStage;
    logoGameStage.game_stageID = GS_LOGO;
    logoGameStage.stage_name = "Logo";

    gameStages.push(logoGameStage);
}

void destroyEngine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

///////// Funciones de inicializacion y destruccion /////////////


///////// Funciones de carga y liberacion de recursos /////////////

void loadAssets() {

    // Cargo el Logo principal.
    string filePathBg = "assets/img/background.jpg";
    SDL_Texture* textureBg = IMG_LoadTexture(renderer, filePathBg.c_str());
    SDL_Rect destBg;
    destBg.x = 0;
    destBg.y = 0;
    destBg.w = WIDTH;
    destBg.h = HEIGHT;

    Sprite bgSprite;
    bgSprite.dest = destBg;
    bgSprite.texture = textureBg;
    spritesAssets.push_back(bgSprite);      //spr_assets[0]

    string filePathPaleta = "assets/img/paleta.png";
    SDL_Texture* texturePaleta = IMG_LoadTexture(renderer, filePathPaleta.c_str());
    SDL_Rect destPaleta;
    destPaleta.x = starting_x_p1;
    destPaleta.y = starting_y_p1;
    destPaleta.w = WIDTHPaleta;
    destPaleta.h = HEIGHTPaleta;

    Sprite paletaSpriteP1;
    paletaSpriteP1.dest = destPaleta;
    paletaSpriteP1.texture = texturePaleta;
    spritesAssets.push_back(paletaSpriteP1);    //spr_assets[1]

    SDL_Rect destPaletaP2;
    destPaletaP2.x = starting_x_p2;
    destPaletaP2.y = starting_y_p2;
    destPaletaP2.w = WIDTHPaleta;
    destPaletaP2.h = HEIGHTPaleta;

    Sprite paletaSpriteP2;
    paletaSpriteP2.dest = destPaletaP2;
    paletaSpriteP2.texture = texturePaleta;
    spritesAssets.push_back(paletaSpriteP2);    //spr_assets[2]

    string filePathBall = "assets/img/ball.png";
    SDL_Texture* textureBall = IMG_LoadTexture(renderer, filePathBall.c_str());
    SDL_Rect destBall;
    destBall.x = (WIDTH / 2) - 24;
    destBall.y = (HEIGHT / 2) - 24;
    destBall.w = 50;
    destBall.h = 50;

    Sprite ballSprite;
    ballSprite.dest = destBall;
    ballSprite.texture = textureBall;
    spritesAssets.push_back(ballSprite);    //spr_assets[3]

    SDL_Texture* textureWallN = IMG_LoadTexture(renderer, filePathPaleta.c_str());
    SDL_Rect destWallN;
    destWallN.x = 0;
    destWallN.y = 0;
    destWallN.w = WIDTH;
    destWallN.h = 5;

    Sprite wallNSprite;
    wallNSprite.dest = destWallN;
    wallNSprite.texture = textureWallN;
    spritesAssets.push_back(wallNSprite);   //spr_assets[4]

    SDL_Texture* textureWallS = IMG_LoadTexture(renderer, filePathPaleta.c_str());
    SDL_Rect destWallS;
    destWallS.x = 0;
    destWallS.y = HEIGHT - 6;
    destWallS.w = WIDTH;
    destWallS.h = 5;

    Sprite wallSSprite;
    wallSSprite.dest = destWallS;
    wallSSprite.texture = textureWallS;
    spritesAssets.push_back(wallSSprite);   //spr_assets[5]

    SDL_Rect destWallW;
    destWallW.x = 0;
    destWallW.y = 0;
    destWallW.w = 2;
    destWallW.h = HEIGHT;

    Sprite wallWSprite;
    wallWSprite.dest = destWallW;
    spritesAssets.push_back(wallWSprite);   //spr_assets[6]

    SDL_Rect destWallE;
    destWallE.x = WIDTH - 3;
    destWallE.y = 0;
    destWallE.w = 2;
    destWallE.h = HEIGHT;

    Sprite wallESprite;
    wallESprite.dest = destWallE;
    spritesAssets.push_back(wallESprite);   //spr_assets[7]

    string filePathV1 = "assets/img/victory1.png";
    SDL_Texture* textureV1 = IMG_LoadTexture(renderer, filePathV1.c_str());
    SDL_Rect destV1;
    destV1.x = (WIDTH / 2) - 60;
    destV1.y = (HEIGHT / 2) - 60;
    destV1.w = 120;
    destV1.h = 80;

    Sprite V1Sprite;
    V1Sprite.dest = destV1;
    V1Sprite.texture = textureV1;
    V1Sprite.isVisible = false;

    spritesAssets.push_back(V1Sprite);  //spr_assets[8]

    string filePathV2 = "assets/img/victory2.png";
    SDL_Texture* textureV2 = IMG_LoadTexture(renderer, filePathV2.c_str());
    SDL_Rect destV2;
    destV2.x = (WIDTH / 2) - 60;
    destV2.y = (HEIGHT / 2) - 60;
    destV2.w = 120;
    destV2.h = 80;

    Sprite V2Sprite;
    V2Sprite.dest = destV2;
    V2Sprite.texture = textureV2;
    V2Sprite.isVisible = false;

    spritesAssets.push_back(V2Sprite);

    string filePath = "assets/img/logo.png";
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    SDL_Rect dest;
    dest.x = 180;
    dest.y = 0;
    dest.w = 260;
    dest.h = 180;

    Sprite logoSprite;
    logoSprite.dest = dest;
    logoSprite.texture = texture;
    spritesAssets.push_back(logoSprite);


    // Cargo el texto...
    string fontfilePath = "assets/fonts/arial.ttf";

    TTF_Font* Sans = TTF_OpenFont(fontfilePath.c_str(), 24); //this opens a font style and sets a size

    SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    stringstream Player1Score;
    stringstream Player2Score;

    Player1Score << LeftScore;
    Player2Score << RightScore;
    
    SDL_Surface* surfaceMessage1 = TTF_RenderText_Solid(Sans, Player1Score.str().c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message1 = SDL_CreateTextureFromSurface(renderer, surfaceMessage1); //now you can convert it into a texture

    SDL_Rect scoreP1_rect; //create a rect
    scoreP1_rect.w = WIDTH * 0.05; // controls the width of the rect
    scoreP1_rect.h = HEIGHT * 0.10; // controls the height of the rect
    scoreP1_rect.x = (WIDTH / 2) - 64;  //controls the rect's x coordinate 
    scoreP1_rect.y = 20; // controls the rect's y coordinte

    Text scoreP1;
    scoreP1.font = Sans;
    scoreP1.color = White;
    scoreP1.surface = surfaceMessage1;
    scoreP1.texture = Message1;
    scoreP1.dest = scoreP1_rect;
    scoreP1.isVisible = false;

    textAssets.push_back(scoreP1);

    SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Sans, Player2Score.str().c_str(), White);
    SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);
    
    SDL_Rect scoreP2_rect;
    scoreP2_rect.w = WIDTH * 0.05;
    scoreP2_rect.h = HEIGHT * 0.10;
    scoreP2_rect.x = (WIDTH / 2) + 32;
    scoreP2_rect.y = 20;
    
    Text scoreP2;
    scoreP2.font = Sans;
    scoreP2.color = White;
    scoreP2.surface = surfaceMessage2;
    scoreP2.texture = Message2;
    scoreP2.dest = scoreP2_rect;
    scoreP2.isVisible = false;

    textAssets.push_back(scoreP2);

    // Cargo Sonidos y BGM
    string soundFilePath = "assets/bgm/persona3ost.mp3";
    Mix_Music* music;
    music = Mix_LoadMUS(soundFilePath.c_str());
    
    Bgm bgm01;
    bgm01.music = music;

    musicAssets.push_back(bgm01);

}

void unloadAssets() {
    for (int i = 0; i < spritesAssets.size(); i++) {
        SDL_DestroyTexture(spritesAssets[i].texture);
    }

    for (int i = 0; i < textAssets.size(); i++) {
        SDL_FreeSurface(textAssets[i].surface);
        SDL_DestroyTexture(textAssets[i].texture);
    }

    for (int i = 0; i < musicAssets.size(); i++) {
        Mix_FreeMusic(musicAssets[i].music);
    }
}

///////// Funciones de carga y liberacion de recursos /////////////

///////// Funciones de actualizacion y pintado /////////////

void inputUpdate() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        
        switch (event.type) {
        case SDL_KEYDOWN:
            onKeyDown(event.key.keysym.sym, gameInputState);
            break;
        case SDL_KEYUP:
            onKeyUp(event.key.keysym.sym, gameInputState);
            break;
        case SDL_MOUSEBUTTONDOWN:
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_QUIT:
            isGameRunning = SDL_FALSE;
            break;
        default:
            break;
        }
    }
}

// Para ser usado en distintos contadores..
float timer = 1.0f * 1000; // 1000 ms

void updateGame(float deltaTime) {
    const float BLINK_SPEED = 5.0f;

    timer -= BLINK_SPEED * deltaTime;

    /* para efecto de parpadeo...
    if (timer <= 0.0f) {
        timer = 1.0f * 1000;
        textAssets[0].isVisible = !textAssets[0].isVisible;
    }
    */

    // Small state machine using stack collection
    switch (gameStages.top().game_stageID)
    {
    case GS_LOGO:
        GSLogoStateUpdate(deltaTime, resourceManager);
        P1StateUpdate(deltaTime, resourceManager);
        P2StateUpdate(deltaTime, resourceManager);
        BallStateUpdate(deltaTime, resourceManager);
        EndStateUpdate(deltaTime, resourceManager);
        break;
    case GS_MAIN_MENU:
        break;
    case GS_GAMEPLAY:
        break;
    case GS_GAMEOVER:
        break;
    case GS_INVALID:
    default:
        break;
    }

}

void render()
{
    // Limpio la pantalla 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Pinto todos los sprites...
    for (int i = 0; i < spritesAssets.size(); i++) {
        if (spritesAssets[i].isVisible) {
            SDL_RenderCopy(renderer, spritesAssets[i].texture, NULL, &spritesAssets[i].dest);
        }
    }

    // Pinto todos los textos...
    for (int i = 0; i < textAssets.size(); i++) {
        if (textAssets[i].isVisible) {
            SDL_RenderCopy(renderer, textAssets[i].texture, NULL, &textAssets[i].dest);
        }
    }

    // Presento la imagen en pantalla
    SDL_RenderPresent(renderer);
}

///////// Funciones de actualizacion y pintado /////////////

///////// Funcione principal y GameLoop /////////////

void updateScore(int i, int score) {
    string fontfilePath = "assets/fonts/arial.ttf";

    TTF_Font* Sans = TTF_OpenFont(fontfilePath.c_str(), 24);

    SDL_Color White = { 255, 255, 255 };

    stringstream Player1Score;
    stringstream Player2Score;

    Player1Score << score;
    Player2Score << score;

    if (i == 0)
    {
        SDL_Surface* surfaceMessageNew = TTF_RenderText_Solid(Sans, Player1Score.str().c_str(), White);
        SDL_Texture* MessageNew = SDL_CreateTextureFromSurface(renderer, surfaceMessageNew);
        textAssets[0].surface = surfaceMessageNew;
        textAssets[0].texture = MessageNew;
        render();
    }
    else
    {
        SDL_Surface* surfaceMessageNew = TTF_RenderText_Solid(Sans, Player2Score.str().c_str(), White);
        SDL_Texture* MessageNew = SDL_CreateTextureFromSurface(renderer, surfaceMessageNew);
        textAssets[1].surface = surfaceMessageNew;
        textAssets[1].texture = MessageNew;
        render();
    }
    
}

int main(int argc, char* argv[])
{
    initEngine();

    // Cargo Assets
    loadAssets();

    Mix_PlayMusic(musicAssets[0].music, -1);

    Uint64 currentTime = SDL_GetTicks64();

    while (isGameRunning) {

        Uint64 previousTime = currentTime;

        currentTime = SDL_GetTicks64();

        Uint64 deltaTime = currentTime - previousTime;

        inputUpdate();

        updateGame(deltaTime * time_multiplier);

        if (spritesAssets[3].isColliding(spritesAssets[6])) {
            RightScore += 1;
            updateScore(1, RightScore);
        }

        if (spritesAssets[3].isColliding(spritesAssets[7])) {
            LeftScore += 1;
            updateScore(0, LeftScore);
        }

        render();
    }

    // Detendo la musica 
    Mix_HaltMusic();

    // Descargo Assets
    unloadAssets(); 
    destroyEngine();
    return 0;
}

///////// Funcione principal y GameLoop /////////////

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
