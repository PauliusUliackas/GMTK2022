#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include "../DS/DeltaTime.hpp" 
#include <iostream>

class Animation
{
    private:
        std::unordered_map<std::string, std::vector<sf::Sprite>> animations;
        bool isPlaying;
        int index;
        float length;
        float currLength;
        std::string currentAnimation;

    public:
        Animation(int);
        ~Animation();
        void load(std::string name, std::string path, double width);
        void play(sf::RenderWindow*, double x, double y);
        void stop();
        void pause();
        void resume();
        void select(std::string name);
        void setLength(float);
        void flip(std::string name, std::string newname, bool x, bool y);
        void scale(std::string name, double x, double y);
        sf::Vector2f getSize();
};