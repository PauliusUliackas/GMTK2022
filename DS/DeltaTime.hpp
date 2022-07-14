#pragma once

#include<SFML/System.hpp>

class DeltaTime
{
private:
    static float dt;
    static sf::Clock timer;

public:
    ~DeltaTime();
    static float get();
    static void tick();
};
