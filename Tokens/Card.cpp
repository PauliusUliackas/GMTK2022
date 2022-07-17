#include "Card.hpp"

Card::Card(std::string rule)
{
    this->rule.create(rule);

    font.loadFromFile("Art/BadComic-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    texture.loadFromFile("Art/Card.png");
    sprite.setTexture(texture);
    sprite.scale(4,4);
}

Card::~Card()
{
}

Rule& Card::getRule()
{
    return rule;
}

void Card::render(sf::RenderWindow* g, bool x, int posX)
{
    int y;
    if(x)
    {
        y = 400;
    }
    else
    {
        y = 450;
    }
    sprite.setPosition(posX, y);
    g->draw(sprite);
    rule.write(g, posX+10, y+10, text);
}

void Card::render(sf::RenderWindow* g, int x, int y)
{
    sprite.setPosition(x, y);
    sprite.scale(0.5,0.5);
    g->draw(sprite);
    rule.write(g, x+10, y+10, text);
}