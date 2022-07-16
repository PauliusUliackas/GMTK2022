#include "Hand.hpp"

Hand::Hand(/* args */)
{
    selected = 0;
    txt.loadFromFile("Art/CardBack.png");
}

Hand::~Hand()
{
}

void Hand::draw(int x, Database db)
{
    for(int i = 0; i < x; i++) hand.push_back(db.getRandomCard());
    selected = 0;
}

Card* Hand::play()
{
    Card* c = hand[selected];
    hand.erase(hand.begin() + selected);
    next();
    return c;
}

void Hand::next()
{
    selected++;
    if(selected >= hand.size()) selected = 0;
}

void Hand::prev()
{
    selected--;
    if(selected < 0) selected = hand.size() - 1;
}

void Hand::render(sf::RenderWindow* g)
{
    for(int i = 0; i < hand.size(); i++)
    {
        hand[i]->render(g, selected == i, 100+80*i);
    }
}

void Hand::enemyRender(sf::RenderWindow* g)
{
    for(int i = 0; i < hand.size(); i++)
    {
        sf::Sprite sprite;
        sprite.scale(4,4);
        sprite.setTexture(txt);
        sprite.setPosition(250+40*i, 0);
        g->draw(sprite);
    }
}
