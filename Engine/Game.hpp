#pragma once

#include "TokenHandler.hpp"
#include "../DS/DeltaTime.hpp"

class Game
{
private:
    int state;
    sf::RenderWindow* graphics;
    TokenHandler handler;
public:
    Game();
    ~Game();
    void run();

private:
    void update();
    void render();

};

