#pragma once

#include <string>
#include "../DS/Functions.hpp"
#include <SFML/Graphics.hpp>
class Rule
{
private:
    std::string cond;
public:
    Rule();
    ~Rule();
    int interprit(int i);
    void create(std::string);
    void write(sf::RenderWindow*, int x, int y, sf::Text, int w = 140);
    void drawDescription(sf::RenderWindow* g, double x, double y, std::string description, int size, sf::Text, int w);
};
