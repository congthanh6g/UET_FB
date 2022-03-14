#pragma once
#include<SDL.h>
#include "Bird.h"
#include "Tube.h"
#include "Background.h"
#include<vector>
class Game
{
public:
    Game(SDL_Renderer *renderer);
    ~Game();
    int exec();
private:
    SDL_Renderer *renderer;
    SDL_Texture *tubeTexture;
   // Background background;
    Bird bird;
    vector<Tube> TubeList;
    bool tick(bool isMouseDown);
    int counter = 0;
};
