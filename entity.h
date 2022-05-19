#pragma once
#include<SDL.h>
#include<iostream>
#include<vector>
using namespace std;

class Entity
{
private:
    float x , y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
public:
    Entity(float p_x , float p_y , SDL_Texture* p_tex);
    void moveLeft();
    void init();
    float getX();
    float getY();
    int getWidth();
    int getHeight();
    void setX(float p_x);
    void setY(float p_y);
    SDL_Texture *getTex();
    SDL_Rect getCurrentFrame();
};
