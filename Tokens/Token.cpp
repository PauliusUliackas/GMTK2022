#include "Token.hpp"

Token::Token(float x, float y, float width, float height) :
hitbox(x, y, width, height)
{
    type = Obj;
}

Token::~Token()
{
}

void Token::update()
{

}

void Token::render(sf::RenderWindow* g)
{
    hitbox.render(g);
}

bool Token::isType(TYPE t)
{
    return type == t;
}

bool Token::collides(Token* other)
{
    return hitbox.collides(other->hitbox);
};

bool Token::collides(sf::FloatRect other)
{
    return hitbox.collides(other);
};

void Token::setX(float x)
{
    hitbox.get().left = x;
};

void Token::setY(float y)
{
    hitbox.get().top = y;
};

float Token::getX()
{
    return hitbox.get().left;
};

float Token::getY()
{
    return hitbox.get().top;
};

float Token::getWidth()
{
    return hitbox.get().width;
};

float Token::getHeight()
{
    return hitbox.get().height;
};

bool Token::operator==(const Token* other)
{
    return other == this;
};

void Token::moveBy(float x, float y)
{
    hitbox.get().left += x;
    hitbox.get().top  += y;
};