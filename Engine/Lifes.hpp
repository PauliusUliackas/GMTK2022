#pragma once

#include <SFML/Graphics.hpp>

class Lifes
{
private:
    int hp;
    sf::Font font;
    sf::Text txt;

public:
    Lifes();
    ~Lifes();
    void display(sf::RenderWindow*, std::string text, double x, double y);
    int damage(int damage);
};