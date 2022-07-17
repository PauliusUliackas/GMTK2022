#include "Rule.hpp"

Rule::Rule()
{
}

Rule::~Rule()
{
}

void Rule::create(std::string s)
{
    cond = s;
}

int Rule::interprit(int side)
{
    std::vector<std::string> conds = Functions::split(cond, ' ');
    for(int i = 0; i<conds.size(); i++)
    {
        if(conds[i] == "+")
        {
            side += std::stoi(conds[i+1]);
        }
        if(conds[i] == "-")
        {
            side -= std::stoi(conds[i+1]);
        }
        if(conds[i] == "/")
        {
            side /= std::stoi(conds[i+1]);
        }
        if(conds[i] == "*")
        {
            side *= std::stoi(conds[i+1]);
        }
    }

    if(side > 6) side = 6;
    if(side < 1) side = 1;

    return side;
};

void Rule::write(sf::RenderWindow* g, int x, int y, sf::Text t, int w)
{
    drawDescription(g, x, y, cond, 14, t, w);
};

void Rule::drawDescription(sf::RenderWindow* g, double x, double y, std::string description, int size, sf::Text text, int w)
{
    text.setCharacterSize(size);
    int yOffset = 0;
    std::vector<std::string> words = Functions::split(cond, ' ');
    std::string line;
    std::string checker;
    for (std::string word : words)
    {
        checker += " " + word;
        text.setString(checker);
        if (text.getGlobalBounds().width > w)
        {
            text.setPosition(x, y + yOffset);
            text.setString(line);
            g->draw(text);
            line = word;
            checker = word;
            yOffset += size;
        }
        else
        {
            line += " " + word;
        }
    }
    text.setPosition(x, y + yOffset);
    text.setString(line);
    g->draw(text);
}