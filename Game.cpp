#include "Game.h"
#include "load_texture.h"
Game::Game(SDL_Renderer *renderer):
    renderer(renderer),
    tubeTexture(loadTexture(renderer , "Image/pipe-green.png")),
   // background(renderer),
    bird(renderer)
{
}
Game::~Game()
{
    SDL_DestroyTexture(tubeTexture);
}
bool Game::tick(bool isMouseDown)
{
    if(counter++ % 1500 == 0)
    {
        auto y = rand() % (Application::HEIGHT - 200 - 200 - 100) + 100;
        TubeList.emplace_back(renderer , tubeTexture , y + 200 , false);
        TubeList.emplace_back(renderer , tubeTexture , y, true);
    }
    bird.tick(isMouseDown);
        SDL_Rect birdRect;
        birdRect.x = bird.x - 64/2;
        birdRect.y = bird.y - 81/2;
        birdRect.w = 64;
        birdRect.h = 81;
    SDL_Rect res;
    for (auto &tube : TubeList)
    {
        tube.tick();
        SDL_Rect TubeRect;
        TubeRect.x = tube.x - 128;
        TubeRect.w  = 52 ;
        TubeRect.h = 10000;
    if(tube.isUp)
    {
        TubeRect.y = tube.y - 10000;
        if (SDL_IntersectRect(&birdRect , &TubeRect , &res ))
        {
            return false;
        }
    }
    else
    {
        TubeRect.y = tube.y + 10 ;
        if (SDL_IntersectRect(&birdRect , &TubeRect , &res ))
        {
            return false;
        }
    }

    }
    for(auto iter = begin(TubeList) ; iter != end(TubeList);)
    {
        if(iter->x < -128)
        {
            iter = TubeList.erase(iter);
        }
        else{
            iter++;
        }
    }
    return bird.y < Application::HEIGHT;
}

int Game::exec()
{
    auto oldTick = SDL_GetTicks();
    bool isMouseDown = false;
     for(auto done = false; !done ; )
    {
        SDL_Event e;
        if(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                    case SDL_QUIT :
                    done = true;
                    break;

                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_SPACE)
                        {
                            isMouseDown = true;
                        }
                    break;

                    case SDL_KEYUP:
                        isMouseDown = false;
                    break;

            }
        }

        //physics
        auto currentTick = SDL_GetTicks();
        for(auto i = oldTick ; i < currentTick ; i++)
        {
            if(!tick(isMouseDown))
            {
                SDL_Delay(4000);
                return 1;
            }
        }
        oldTick = currentTick;

        SDL_SetRenderDrawColor(renderer , 225 , 225 , 225 , .3);
        //background.draw();
        //background.draw();
        //SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        bird.draw();
        for (auto &tube : TubeList)
        {
        tube.draw();
        }
        SDL_RenderPresent(renderer);
    }
}
