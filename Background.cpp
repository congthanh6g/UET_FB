#include "Background.h"
#include "load_texture.h"
#include "Application.h"
Background::Background(SDL_Renderer *renderer) :
    renderer(renderer),
    background(loadTexture(renderer, "Image/background.png"))
{

}

void Background::draw()
{
    SDL_RenderCopy ( renderer , background , NULL , NULL );
}
