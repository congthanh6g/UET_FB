#include "Tube.h"

Tube::Tube(SDL_Renderer *renderer , SDL_Texture *texture , int y , bool isUp):
    renderer(renderer),
    texture(texture),
    y(y),
    isUp(isUp)
{

}
void Tube::tick()
{
    x -= 0.25f;
}
void Tube::draw()
{
    if(!isUp)
    {
         SDL_Rect r ;
         r.x =  x - 128 ;
         r.y =  y ;
         r.w = 52;
         r.h = 320;
         auto res = SDL_RenderCopyEx(renderer , texture , nullptr , &r , 0 , nullptr ,  SDL_FLIP_NONE);
    }
    else
    {
        SDL_Rect r ;
         r.x =  x - 128 ;
         r.y =  y - Application::HEIGHT / 2;
         r.w = 52;
         r.h = 320;
         auto res = SDL_RenderCopyEx(renderer , texture , nullptr , &r , 0 , nullptr ,  SDL_FLIP_VERTICAL);
    }
}
