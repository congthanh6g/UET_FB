#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string.h>
#include "entity.h"
#include "RenderWindow.h"
using namespace std;

const float GRAVITY = 0.09f;

class Player : public Entity {
public:
    Player(float p_x , float p_y , SDL_Texture* p_tex);
    float DistanceFromCursor();
    void Jump();
    void Update();
    bool checkCollision(SDL_Rect rectA , SDL_Rect rectB , SDL_Rect result);
    void setVelocityX(float v_x)
    {
        velocityX = v_x;
    }
    void setVelocityY(float v_y)
    {
        velocityY = v_y;
    }
    bool getHit()
    {
        return hit;
    }
    const char *getScore()
    {
        string s = to_string(score);
        s = "DISTANCE: " + s;
        return s.c_str();
    }
    int getScoreInt()
    {
        return score;
    }
    void setTimer(int t)
    {
        timer = t;
    }
    void setScore(int doublescore)
    {
        score = doublescore * 2;
    }
    int getTimer()
    {
        return timer;
    }
private:
    float velocityX , velocityY;
    bool grounded;
    bool hit = false;
    int score = 0;
    int timer = 0;
};
