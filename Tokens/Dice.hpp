#pragma once

#include <SFML/Graphics.hpp>
#include "../DS/Functions.hpp"
#include "../DS/DeltaTime.hpp"
#include <vector>

class Dice
{
private:
    int currentNumber;
    int times;
    sf::Texture textures[6];
    float delay;
    bool triggered;
public:
    Dice();
    ~Dice();
    void roll(int times);
    void render(sf::RenderWindow* g);
    int side();
    bool isOver();
    bool isRolling();
    sf::Texture& getTexture(int i);
};