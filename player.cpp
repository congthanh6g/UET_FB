#include "player.h"
#include<math.h>
Player::Player(float p_x , float p_y , SDL_Texture* p_tex)
    : Entity{ p_x , p_y , p_tex}
{
    setX(SCREEN_WIDTH/2 - getWidth() / 2);
}

float Player::DistanceFromCursor()
{
    int mouseX = 0;
    int mouseY = 0;
    SDL_GetMouseState(&mouseX , &mouseY);

    return sqrt(pow( getX() + getWidth() / 2 - mouseX , 2) + pow( getY() + getHeight() / 2 - mouseY , 2));
}

void Player::Jump()
{
    if(grounded)
    {
        velocityY = -(1/DistanceFromCursor() * 200);
        grounded = false;
    }
}
bool Player::checkCollision(SDL_Rect rectA , SDL_Rect rectB , SDL_Rect result)
{
    if(SDL_IntersectRect(&rectA , &rectB , &result) == true)
    {
        return true; // co va cham
    }
    else
    {
        return false;
    }
}
void Player::Update()
{
    hit = false;
    timer++;
    score = timer / 50;
    int mouseX = 0;
    int mouseY = 0;
    SDL_GetMouseState(&mouseX , &mouseY);

    if(mouseX < getX())
    {
        velocityX = 1/DistanceFromCursor() * 100;
        if(getX() > SCREEN_WIDTH - getWidth())
        {
            velocityX = 0;
            setX(SCREEN_WIDTH / 2 - getWidth() / 2);
            setY(0);
        }
    }
    else if(mouseX > getX() + getWidth())
    {
        velocityX = 1/DistanceFromCursor() * -100;
        if(getX() < 0)
        {
            velocityX = 0;
            setX(SCREEN_WIDTH / 2 - getWidth() / 2);
            setY(0);
        }
    }
    else
    {
        velocityX = 0;
        if(mouseY > getY() && mouseY < getY() + getHeight())
        {
            velocityY = 0;
            setX(SCREEN_WIDTH / 2 - getWidth() / 2);
            setY(0);
            hit = true;
        }
    }
    setX(getX() + velocityX);
    setY(getY() + velocityY);

    if(getY() + getHeight() + 133 < SCREEN_HEIGHT)
    {
        velocityY += GRAVITY;
        grounded = false;
    }
    else
    {
        setY(SCREEN_HEIGHT - getHeight() - 133);
        grounded = true;
    }
}
