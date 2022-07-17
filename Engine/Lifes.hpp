#pragma once

#include <SFML/Graphics.hpp>
#include "../DS/DeltaTime.hpp"
class Lifes
{
private:
    int hp;
    sf::Font font;
    sf::Text txt;
    int length;
    float timer;
public:
    Lifes();
    ~Lifes();
    void display(sf::RenderWindow*, std::string text, double x, double y);
    int damage(int damage);
    bool dead();
};