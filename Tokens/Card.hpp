#pragma once

#include "Rule.hpp"
#include <SFML/Graphics.hpp>
class Card
{
private:
    Rule rule;
    sf::Font font;
    sf::Text text;

    sf::Texture texture;
    sf::Sprite sprite;

public:
    Card(std::string rule);
    ~Card();
    Rule& getRule();
    void render(sf::RenderWindow* g, bool isSelected, int x);
};
