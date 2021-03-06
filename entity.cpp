#include "entity.h"

Entity::Entity(float p_x , float p_y , SDL_Texture* p_tex)
    : x(p_x) , y(p_y) , tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    SDL_QueryTexture(p_tex , NULL , NULL , &currentFrame.w , &currentFrame.h);
}
    void Entity::moveLeft()
    {
        x -= 2.09f;
    }
    float Entity::getX()
    {
        return x;
    }
    float Entity::getY()
    {
        return y;
    }
    int Entity::getWidth()
    {
        return currentFrame.w;
    }
    int Entity::getHeight()
    {
        return currentFrame.h;
    }
    void Entity::setX(float p_x)
    {
        x = p_x;
    }
    void Entity::setY(float p_y)
    {
        y = p_y;
    }
    SDL_Texture* Entity::getTex()
    {
        return tex;
    }
    SDL_Rect Entity::getCurrentFrame()
    {
        return currentFrame;
    }
