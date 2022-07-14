#pragma once

#include "Character.hpp"

class Player : public Character
{
private:
    bool inputs[4];
public:
    Player(float x, float y, float width, float height);
    ~Player();
    void handleEvents(sf::Event);
    void update();
};