#include "Dice.hpp"

Dice::Dice()
{
    currentNumber = 1;
    times = 0;
    
    sf::Texture txt1;
    txt1.loadFromFile("Art/1.png");
    textures[0] = txt1;

    sf::Texture txt2;
    txt2.loadFromFile("Art/2.png");
    textures[1] = txt2;

    sf::Texture txt3;
    txt3.loadFromFile("Art/3.png");
    textures[2] = txt3;

    sf::Texture txt4;
    txt4.loadFromFile("Art/4.png");
    textures[3] = txt4;

    sf::Texture txt5;
    txt5.loadFromFile("Art/5.png");
    textures[4] = txt5;

    sf::Texture txt6;
    txt6.loadFromFile("Art/6.png");
    textures[5] = txt6;
}

Dice::~Dice()
{
}

int Dice::side()
{
    return currentNumber;
};

void Dice::roll(int times)
{
    this->times = times;
};

void Dice::render(sf::RenderWindow* g)
{
    if(times > 0 && delay <= 0)
    {
        times--;
        delay = 12;
        currentNumber = Functions::Random(1, 6);
    }
    delay -= DeltaTime::get();
    sf::Sprite s;
    s.setTexture(textures[currentNumber-1]);
    s.setPosition(300, 250);
    s.scale(3,3);
    g->draw(s);
};

bool Dice::isOver()
{
    return times <= 0;
}