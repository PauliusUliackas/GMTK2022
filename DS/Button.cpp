#include "Button.hpp"

Button::Button(std::string name)
{
    sel.loadFromFile("Art/"+name+"2.png");
    nrml.loadFromFile("Art/"+name+"1.png");
}

Button::~Button()
{
}

void Button::render(sf::RenderWindow* g, bool isSelected, double x, double y)
{
    if(isSelected) sprite.setTexture(sel);
    else sprite.setTexture(nrml);

    sprite.setPosition(x, y);

    g->draw(sprite);
};