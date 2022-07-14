#include "Hitbox.hpp"


Hitbox::Hitbox(float x, float y, float width, float height)
{
    hitbox = sf::FloatRect(sf::Vector2f(x, y), sf::Vector2f(width, height));
}

Hitbox::~Hitbox()
{
}

bool Hitbox::collides(Hitbox other)
{
    return hitbox.intersects(other.hitbox);
};

bool Hitbox::collides(sf::FloatRect hb)
{
    return hb.intersects(hitbox);
};

void Hitbox::render(sf::RenderWindow*  g)
{
    sf::RectangleShape drawable;
    drawable.setPosition(hitbox.left, hitbox.top);
    drawable.setSize(sf::Vector2f(hitbox.width, hitbox.height));
    g->draw(drawable);
}

sf::FloatRect& Hitbox::get()
{
    return hitbox;
}