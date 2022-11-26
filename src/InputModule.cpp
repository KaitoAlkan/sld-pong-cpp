#include "InputModule.h"
#include "StructsDef.h"

void onKeyUp(int keyCode, InputState& input) {
    switch (keyCode) {
    case SDLK_UP:
        input.UpPlayerTwo = false;
        break;
    case SDLK_DOWN:
        input.DownPlayerTwo = false;
        break;
    case SDLK_LEFT:
        input.leftp2 = false;
        break;
    case SDLK_RIGHT:
        input.rightp2 = false;
        break;
    case SDLK_w:
        input.UpPlayerOne = false;
        break;
    case SDLK_s:
        input.DownPlayerOne = false;
        break;
    case SDLK_a:
        input.leftp1 = false;
        break;
    case SDLK_d:
        input.rightp1 = false;
        break;
    default:
        break;
    }
}

void onKeyDown(int keyCode, InputState& input) {
    switch (keyCode) {
    case SDLK_UP:
        input.UpPlayerTwo = true;
        break;
    case SDLK_DOWN:
        input.DownPlayerTwo = true;
        break;
    case SDLK_LEFT:
        input.leftp2 = true;
        break;
    case SDLK_RIGHT:
        input.rightp2 = true;
        break;
    case SDLK_w:
        input.UpPlayerOne = true;
        break;
    case SDLK_s:
        input.DownPlayerOne = true;
        break;
    case SDLK_a:
        input.leftp1 = true;
        break;
    case SDLK_d:
        input.rightp1 = true;
        break;
    case SDLK_SPACE:
        input.serve = true;
        break;
    default:
        break;
    }
}