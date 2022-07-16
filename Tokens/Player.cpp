#include "Player.hpp"


Player::Player(float x, float y, float width, float height) : Character(x, y, width, height)
{
    type = TYPE::Player;
};

Player::~Player()
{
};

void Player::handleEvents(sf::Event e)
{
    
};

void Player::update()
{
    Character::update();
    if(inputs[0]) velocity.y = -3;
    if(inputs[1]) velocity.x = -3;
    if(inputs[2]) velocity.y = 3;
    if(inputs[3]) velocity.x = 3;
};