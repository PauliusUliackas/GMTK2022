#include "DeltaTime.hpp"

float DeltaTime::dt = 0;
sf::Clock DeltaTime::timer;

DeltaTime::~DeltaTime(){};

float DeltaTime::get()
{
    return dt * 60;
};

void DeltaTime::tick()
{
    dt = timer.getElapsedTime().asSeconds();
    timer.restart();
};