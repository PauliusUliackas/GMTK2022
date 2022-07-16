#pragma once

#include "TokenHandler.hpp"
#include "../Tokens/Dice.hpp"
#include "../DS/Button.hpp"
#include "Lifes.hpp"
#include "math.h"
#include "../DS/Hand.hpp"
#include <queue>

class Game
{
private:
    int state;
    sf::RenderWindow* graphics;
    TokenHandler handler;
    Dice dice;
    Lifes player, enemy;
    Hand ph, eh;
    int currbutton;

    std::vector<Button*> buttons;

    int bet, currBet;
    sf::Font font;
    sf::Text text;

    Card* test;
    Database db;

    std::queue<Rule> round;

    sf::Texture texture;
    sf::Sprite arrow;

    bool isCall, isPlayerTurn;

public:
    Game();
    ~Game();
    void run();

private:
    void update();
    void render();
    void newRound();

};

