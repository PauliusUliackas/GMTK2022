#include "Character.hpp"

Character::Character(float x, float y, float width, float height) : Token(x, y, width, height),
velocity(0,0),
anime(10)
{
    type = TYPE::Character;
}

Character::~Character()
{
}

void Character::update()
{
    velocity.x = 0;
    velocity.y = 0;
};

void Character::render(sf::RenderWindow* g)
{
    Token::render(g);
};

sf::Vector2f Character::getVelocity()
{
    return velocity;
};