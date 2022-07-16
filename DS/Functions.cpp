#include "Functions.hpp"

Functions::Functions()
{
}

Functions::~Functions()
{
}

void Functions::init()
{
    srand(time(NULL));
};

int Functions::Random(int min, int max)
{
    return std::rand() % (max-min)+min;
};

std::vector<std::string> Functions::split(std::string string, char by)
{
    std::vector<std::string> out;
    std::string current = "";
    for(int i = 0; string[i] != '\0'; i++)
    {
        char curr = string[i];
        if(curr == by)
        {
            if(current.length() > 0)
                out.push_back(current);
            current = "";
        }
        else
            current += curr;

    }
    out.push_back(current);
    return out;
};