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