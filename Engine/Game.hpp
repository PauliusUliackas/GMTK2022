#pragma once

#include "TokenHandler.hpp"
#include "../Tokens/Dice.hpp"
#include "../DS/Button.hpp"
#include "Lifes.hpp"

class Game
{
private:
    int state;
    sf::RenderWindow* graphics;
    TokenHandler handler;
    Dice dice;
    Lifes player, enemy;
    int currbutton;

    std::vector<Button*> buttons;

public:
    Game();
    ~Game();
    void run();

private:
    void update();
    void render();

};

