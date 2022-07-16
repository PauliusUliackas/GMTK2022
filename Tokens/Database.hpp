#pragma once

#include "Card.hpp"

class Database
{
private:
    std::vector<Card*> cards; 
public:
    Database();
    ~Database();
    Card* getRandomCard();
};