#pragma once

#include "../DS/Hitbox.hpp"
#include <iostream>

class Token
{
public:
    enum TYPE
    {
        Obj,
        Character,
        Player
    };

protected:
    TYPE type;
    Hitbox hitbox;
public:
    Token(float = 0, float = 0, float = 0, float = 0);
    virtual ~Token();

    virtual void update();
    virtual void render(sf::RenderWindow* g);

    bool isType(TYPE);

    bool collides(Token*);
    bool collides(sf::FloatRect);

    void setX(float);
    void setY(float);

    float getX();
    float getY();
    float getWidth();
    float getHeight();

    void moveBy(float x, float y);

    virtual bool operator==(const Token*);
};
