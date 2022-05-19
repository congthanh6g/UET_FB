#pragma once
#include "entity.h"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;


class RenderWindow
{
private:
    SDL_Window* window;
    SDL_Renderer *renderer;

public:
    RenderWindow();
    void create(const char* p_title);
    SDL_Texture *loadTexture(const char* p_filePath);
    void clear();
    void render(Entity& p_entity);
    void render(float p_x , float p_y , SDL_Texture* p_tex);
    void render(SDL_Texture* p_tex);
    void render(float p_x , float p_y , const char* p_text , TTF_Font *font , SDL_Color textColor);
    void renderCenter(float p_x , float p_y , const char* p_text , TTF_Font *font , SDL_Color textColor);
    void display();
    void cleanUp();
};
