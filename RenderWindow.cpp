#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>

#include "RenderWindow.h"
#include "entity.h"


RenderWindow::RenderWindow()
{

}

void RenderWindow::create(const char* p_title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        cout << "SDL_INIT error : " << SDL_GetError() << endl;

    TTF_Init();

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) cout << "WINDOW error : " << SDL_GetError() << endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) cout << "Renderer error : " << SDL_GetError() << endl;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer , p_filePath);

    if(texture == NULL)
    {
        cout << "Failed Texture Error : " << SDL_GetError() << endl ;
    }
    return texture;
}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(renderer ,90 , 90 , 90 , 255);
    SDL_RenderClear(renderer);
}
void RenderWindow::render(Entity& p_entity)
{
    SDL_Rect src; // actual size of texture
    src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = p_entity.getX();
    dest.y = p_entity.getY();
    dest.w = p_entity.getCurrentFrame().w;
    dest.h = p_entity.getCurrentFrame().h ;

    SDL_RenderCopy(renderer , p_entity.getTex() , &src , &dest);
}
void RenderWindow::render(float p_x , float p_y , SDL_Texture* p_tex)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(p_tex , NULL , NULL , &src.w , &src.h);

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer , p_tex , &src , &dst);
}
void RenderWindow::render(SDL_Texture* p_tex)
{
    render(0 , 0 , p_tex);
}
void RenderWindow::render(float p_x , float p_y , const char* p_text , TTF_Font *font , SDL_Color textColor)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font , p_text , textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer , surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage -> w;
    src.h = surfaceMessage -> h;

    SDL_Rect dst;
    dst.x = p_x ;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer , message , &src , &dst);
    SDL_FreeSurface(surfaceMessage);
}
void RenderWindow::renderCenter(float p_x , float p_y , const char* p_text , TTF_Font *font , SDL_Color textColor)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font , p_text , textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer , surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage -> w;
    src.h = surfaceMessage -> h;

    SDL_Rect dst;
    dst.x = p_x + SCREEN_WIDTH / 2 - src.w / 2 ;
    dst.y = p_y + SCREEN_HEIGHT /2 - src.h / 2;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer , message , &src , &dst);
    SDL_FreeSurface(surfaceMessage);
}
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}
