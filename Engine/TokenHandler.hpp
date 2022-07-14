#pragma once

#include <vector>

#include "../Tokens/Player.hpp"

class TokenHandler
{
private:
    std::vector<Token*> tokens;
    Player* player;
public:
    TokenHandler();
    ~TokenHandler();
    virtual void update();
    virtual void render(sf::RenderWindow*);
    void handleEvents(sf::Event);
private:
    void move(Character* c);

};
