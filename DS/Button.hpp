#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    sf::Texture sel, nrml;
    std::string label;
    sf::Font font;
    sf::Text t;
public:
    Button(std::string name, std::string);
    ~Button();
    void render(sf::RenderWindow*, bool isSelected, double, double);
};
