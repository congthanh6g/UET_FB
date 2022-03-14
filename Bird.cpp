#include "Bird.h"
#include "load_texture.h"
#include "Application.h"
Bird::Bird(SDL_Renderer *renderer) :
    renderer(renderer),
    bird1(loadTexture(renderer, "Image/penguin1.png")),
    bird2(loadTexture(renderer, "Image/penguin2.png"))
{

}
Bird::~Bird()
{
   SDL_DestroyTexture(bird1);
   SDL_DestroyTexture(bird2);
}

void Bird::draw()
{
    SDL_Rect r ;
    r.x =  x - 64;
    r.y =  y - 64;
    r.w = 128;
    r.h = 128;
    auto res = SDL_RenderCopyEx(renderer , SDL_GetTicks() % 300 > 150 ? bird1 : bird2 , nullptr , &r , v * 50 , nullptr ,  SDL_FLIP_NONE);
}
void Bird::tick(bool isMouseDown)
{
    v -= isMouseDown ? 0.003 : 0;
    v += 0.001;
    y += v;
}
