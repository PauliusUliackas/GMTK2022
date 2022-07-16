#pragma once

#include "../Tokens/Database.hpp"

class Hand
{
private:
    std::vector<Card*> hand;
    int selected;

    sf::Texture txt;
public:
    Hand();
    ~Hand();
    void draw(int x, Database db);
    Card* play();
    void next();
    void prev();
    void render(sf::RenderWindow* g);
    void enemyRender(sf::RenderWindow* g);
};