#pragma once
#include "Application.h"
#include<SDL.h>
class Bird
{
public:
    Bird(SDL_Renderer *renderer);
    ~Bird();
    void draw();
    void tick(bool isMouseDown);
    float y = Application::HEIGHT / 2 ;
    const float x = Application::WIDTH / 4 ;
private:
    SDL_Renderer *renderer;
    SDL_Texture *bird1;
    SDL_Texture *bird2;
    float v = 0.0f;
};
