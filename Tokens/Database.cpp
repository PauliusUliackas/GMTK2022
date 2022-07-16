#include "Database.hpp"

Database::Database(/* args */)
{
    cards = {
        new Card("Side that the cube lands on is + 2"),
        new Card("Side that the cube lands on is - 2"), 
        new Card("Side that the cube lands on is * 2"), 
        new Card("Side that the cube lands on is / 2"), 
        };
}

Database::~Database()
{
}

Card* Database::getRandomCard()
{
    int i = Functions::Random(0, cards.size());
    return cards[i];
};