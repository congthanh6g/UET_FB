#include<iostream>
#include<vector>
#include<random>
#include "RenderWindow.h"
#include "player.h"

using namespace std;
int random(int minN , int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
int main(int argc , char* argv[])
{
    // Tao man hinh
    RenderWindow renderWindow;
    renderWindow.create("Get Away Cursor");
    // ----------------------------------------------------------------//
    SDL_Event event;
    bool gameRunning = true;
    SDL_Rect res;
    bool mainmenu = true;
    TTF_Font *font24 = TTF_OpenFont("font/cocogoose.ttf" , 24);
    TTF_Font *font32 = TTF_OpenFont("font/cocogoose.ttf" , 32);
    SDL_Color white = {255 , 255 , 255};
    SDL_Texture *playerTex = renderWindow.loadTexture("Image/yellowbird1.png");
    SDL_Texture *groundTex = renderWindow.loadTexture("Image/base_resize_01.png");
    SDL_Texture *backgroundTex = renderWindow.loadTexture("Image/background.png");
    SDL_Texture *spriteTexture = renderWindow.loadTexture("Image/pipe-green-1.png");
    SDL_Texture *spriteTexture01 = renderWindow.loadTexture("Image/pipe-green.png");
    SDL_Texture *lifeTexture = renderWindow.loadTexture("Image/life_resize.png");
    SDL_Texture *appleTexture = renderWindow.loadTexture("Image/apple-removebg-preview.png");
    SDL_Texture *bananaTexture = renderWindow.loadTexture("Image/banana.png");
    Player player(0 , 0 , playerTex);

    Entity ground(0 , SCREEN_HEIGHT - 133 , groundTex);
    Entity background(0 , 0 , backgroundTex);
    Entity hearts[3] = {Entity(0 , 0 , lifeTexture) ,
                        Entity(50 , 0 , lifeTexture),
                        Entity(100 , 0 , lifeTexture)};
    vector<Entity> sprites ;
    vector<Entity> apples;
    vector<Entity> bananas;
    int i = 0;
    int number = 3;
    int j = 0;
    int k = 0;
    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(mainmenu)
                {
                    if(event.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() > 2500)
                    {
                        mainmenu = false;
                    }
                }
                else
                {
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        player.Jump();
                    }
                    break;
                }
            }
        }
        if(mainmenu)
        {
            if(SDL_GetTicks() < 2500)
            {
                renderWindow.clear();
                renderWindow.renderCenter(0 , sin(SDL_GetTicks() / 100) * 2 - 4 , "Ride my bird" , font24  , white );
                renderWindow.display();
            }
            else
            {
                renderWindow.clear();
                renderWindow.renderCenter(0 , 90 + sin(SDL_GetTicks() / 100) * 2 , "Click to Start" , font24 , white);
                renderWindow.display();
            }
        }
        else
        {
             Entity apple(300 + j , SCREEN_HEIGHT - 133 - 80 - 30 , appleTexture);
             apples.push_back(apple);

            Entity sprite(600 + i , SCREEN_HEIGHT - 133 - 80 , spriteTexture);
            sprites.push_back(sprite);


            Entity spriteShort(900 + i * 5  ,SCREEN_HEIGHT - 133 - 50 ,spriteTexture01);
            sprites.push_back(spriteShort);


         Entity banana( 1000 + k , SCREEN_HEIGHT - 133 - 80 - 30 - 90 , bananaTexture);
         bananas.push_back(banana);

         SDL_Rect playerRect;
         playerRect.x = player.getX();
         playerRect.y = player.getY();
         playerRect.w = 34 ;
         playerRect.h = 24 ;


        renderWindow.clear();
        renderWindow.render(background);
        renderWindow.render(ground);
        for(int i = 0 ; i < apples.size() ; i++)
        {
            auto iter1 = begin(apples);
            SDL_Rect appleRect;
            appleRect.x = apples[i].getX();
            appleRect.y = apples[i].getY();
            appleRect.w = 30 ;
            appleRect.h = 30 ;

            renderWindow.render(apples[i]);
            apples[i].moveLeft();
            if(player.checkCollision(playerRect , appleRect  , res))
            {
                if(number >= 3)
                {
                    number = 3;
                }
                else
                {
                    number ++;
                }
                apples.erase(iter1);
            }
            if(apples[i].getX() < 0 && iter1 != end(apples))
            {
                apples.erase(iter1);
            }
            else
            {
                iter1 ++;
            }

        }

        // banana
         for(int i = 0 ; i < bananas.size() ; i++)
        {
            auto iter1 = begin(bananas);
            SDL_Rect bananaRect;
            bananaRect.x = bananas[i].getX();
            bananaRect.y = bananas[i].getY();
            bananaRect.w = 30 ;
            bananaRect.h = 30 ;

            renderWindow.render(bananas[i]);
            bananas[i].moveLeft();
            if(player.checkCollision(playerRect , bananaRect  , res))
            {
                player.setTimer(player.getTimer() * 2);
                bananas.erase(iter1);
            }
            if(bananas[i].getX() < 0 && iter1 != end(bananas))
            {
                bananas.erase(iter1);
            }
            else
            {
                iter1 ++;
            }

        }


        // hearts
        for(int i = 0 ; i < number ; i++)
        {
            renderWindow.render(hearts[i]);
        }
        for(int i = 0 ; i < sprites.size() ; i++)
        {
            SDL_Rect spriteRect;
            spriteRect.x = sprites[i].getX();
            spriteRect.y = sprites[i].getY();
            spriteRect.w = 52 ;
            spriteRect.h = 80 ;

            renderWindow.render(sprites[i]);
            sprites[i].moveLeft();
            if(player.checkCollision(playerRect , spriteRect  , res))
            {
                player.setX(SCREEN_WIDTH / 2 - player.getWidth() / 2);
                player.setY(0);
                player.setVelocityX(0);
                player.setVelocityY(0);
                number --;
                if(number == 0)
                {
                    renderWindow.clear();
                    renderWindow.renderCenter(0 , -24 , "Oh my you should have been more careful" , font24 , white);
                    renderWindow.renderCenter(0 , 12 , player.getScore() , font24 , white);
                    renderWindow.display();
                    waitUntilKeyPressed();
                    gameRunning = false;
                }
            }
        }
        for(int i = 0 ; i < sprites.size() ; i++)
        {
            auto iter1 = begin(sprites);
            if(sprites[i].getX() < 0 && iter1 != end(sprites))
            {
                sprites.erase(iter1);
            }
            else
            {
                iter1 ++;
            }
        }
        if(player.getHit() == true)
        {
            number --;
            if(number == 0)
            {
                renderWindow.clear();
                renderWindow.renderCenter(0 , -24 , "Oh my you should have been more careful" , font24 , white);
                renderWindow.renderCenter(0 , 12 , player.getScore() , font24 , white);
                renderWindow.display();
                waitUntilKeyPressed();
                gameRunning = false;

            }
        }
        renderWindow.render(player);
        player.Update();

        renderWindow.render(300 , 23 , player.getScore() , font32 , white);


        renderWindow.display();
        i += random(200 , 300);
        j += random(300 , 400);
        k += random(900 , 1000);
        }
    }


    renderWindow.cleanUp();
    return 0;
}

