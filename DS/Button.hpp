#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    sf::Texture sel, nrml;
public:
    Button(std::string name);
    ~Button();
    void render(sf::RenderWindow*, bool isSelected, double, double);
};
