#include "load_texture.h"
#include<SDL_image.h>
SDL_Texture *loadTexture(SDL_Renderer *ren , const char *filelocation)
{
    SDL_Surface* surface;
    surface = IMG_Load(filelocation);
    SDL_Texture* tex;
    tex = SDL_CreateTextureFromSurface(ren , surface);
    return tex;
}
