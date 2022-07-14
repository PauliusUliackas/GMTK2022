#pragma once

#include "Token.hpp"
#include "../Animation/Animation.hpp"

class Character : public Token
{
protected:
    sf::Vector2f velocity;
    Animation anime;
public:
    Character(float = 0, float = 0, float = 0, float = 0);
    ~Character();
    virtual void update();
    virtual void render(sf::RenderWindow* g);
    sf::Vector2f getVelocity();
};
