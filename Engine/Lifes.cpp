#include "Lifes.hpp"

Lifes::Lifes(/* args */)
{
    hp = 100;
    length = 100;
    font.loadFromFile("Art/BadComic-Regular.ttf");
    txt.setFont(font);
    txt.setCharacterSize(16);
    txt.setFillColor(sf::Color::White);
    timer = 0;
};

Lifes::~Lifes()
{
};

void Lifes::display(sf::RenderWindow* g, std::string text, double x, double y)
{
    txt.setPosition(x + 5, y - 18);
    txt.setString(text);
    g->draw(txt);
    sf::RectangleShape r(sf::Vector2f(100, 40));
    r.setFillColor(sf::Color::Red);
    r.setPosition(x, y);
    g->draw(r);

    if(timer <= 0)
    {
        if(length < hp) length++;
        if(length > hp) length--;
        timer = 3;
    }
    timer -= DeltaTime::get();
    sf::RectangleShape r2(sf::Vector2f(length, 40));
    r2.setFillColor(sf::Color::Green);
    r2.setPosition(x, y);
    txt.setString(std::to_string(hp));
    txt.setPosition(x+5, y+1);
    g->draw(r2);
    g->draw(txt);
};

int Lifes::damage(int x)
{
    hp -= x;
    if(hp < 0) hp = 0;
    return hp;
};

bool Lifes::dead()
{
    return length <= 0;
}