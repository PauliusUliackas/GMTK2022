#include "Button.hpp"

Button::Button(std::string name, std::string label)
{
    sel.loadFromFile("Art/"+name+"2.png");
    nrml.loadFromFile("Art/"+name+"1.png");
    this->label = label;

    font.loadFromFile("Art/BadComic-Regular.ttf");
    t.setFont(font);
    t.setCharacterSize(16);
    t.setString(label);
}

Button::~Button()
{
}

void Button::render(sf::RenderWindow* g, bool isSelected, double x, double y)
{
    sf::Sprite sprite;
    if(isSelected)
    { 
        sprite.setTexture(sel);
        sprite.scale(3,3);
    }
    else{
        sprite.setTexture(nrml);
        sprite.scale(2,2);
    }

    sprite.setPosition(x, y);
    t.setPosition(x+64, y + 4);
    if(isSelected)
        g->draw(t);
    g->draw(sprite);
};