#pragma once
#include "Application.h"
#include<SDL.h>

class Background
{
public:
    Background(SDL_Renderer *renderer);
    void draw();
private:
    SDL_Renderer *renderer;
    SDL_Texture *background;

};
