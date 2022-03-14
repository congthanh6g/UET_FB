#pragma once
#include<SDL.h>
#include<iostream>
using namespace std;
// Khoi Tao Window
class Application
{
public:
    static const auto WIDTH = 800;
    static const auto HEIGHT = 640;
    // constructor
    Application();
    int exec();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};

