#pragma once
#include "Application.h"
class Tube
{
public :
    Tube(SDL_Renderer *renderer , SDL_Texture *texture , int y , bool isUp);
    // ~Tube();
    void tick();
    void draw();
private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
public:
    float y;
    float x = Application::HEIGHT + 128;
    bool isUp;
};
