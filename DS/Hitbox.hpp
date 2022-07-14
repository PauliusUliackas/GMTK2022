#pragma once

#include <SFML/Graphics.hpp>

class Hitbox
{
private:
    sf::FloatRect hitbox;
public:
    Hitbox(float x, float y, float width, float height);
    ~Hitbox();
    bool collides(Hitbox other);
    bool collides(sf::FloatRect);
    void render(sf::RenderWindow* g);

    sf::FloatRect& get();
};