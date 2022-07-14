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
    if(e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::W)
        {
            inputs[0] = true;
        }
        if(e.key.code == sf::Keyboard::A)
        {
            inputs[1] = true;
        }
        if(e.key.code == sf::Keyboard::S)
        {
            inputs[2] = true;
        }
        if(e.key.code == sf::Keyboard::D)
        {
            inputs[3] = true;
        }
    }
    
    if(e.type == sf::Event::KeyReleased)
    {
        if(e.key.code == sf::Keyboard::W)
        {
            inputs[0] = false;
        }
        if(e.key.code == sf::Keyboard::A)
        {
            inputs[1] = false;
        }
        if(e.key.code == sf::Keyboard::S)
        {
            inputs[2] = false;
        }
        if(e.key.code == sf::Keyboard::D)
        {
            inputs[3] = false;
        }
    }
};

void Player::update()
{
    Character::update();
    if(inputs[0]) velocity.y = -3;
    if(inputs[1]) velocity.x = -3;
    if(inputs[2]) velocity.y = 3;
    if(inputs[3]) velocity.x = 3;
};