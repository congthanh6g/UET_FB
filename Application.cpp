#include "Application.h"
#include "Bird.h"
#include "Game.h"
#include<stdexcept>

Application::Application()
{
   auto res = SDL_Init(SDL_INIT_EVERYTHING);
   if(res != 0)
   {
       throw runtime_error(string("SDL_Init ") + SDL_GetError());
   }
   SDL_CreateWindowAndRenderer(WIDTH , HEIGHT , SDL_WINDOW_BORDERLESS , &window , &renderer);
   SDL_SetRenderDrawBlendMode(renderer , SDL_BLENDMODE_BLEND);
   SDL_SetWindowPosition(window , 275, HEIGHT/8);
}

int Application::exec()
{
    for(;;)
    {
        Game g(renderer);
        if(g.exec() == 0 )
        {
            break;
        }
    }
    return 0;
}

