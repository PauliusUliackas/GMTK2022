#include "TokenHandler.hpp"


TokenHandler::TokenHandler(/* args */)
{
    //player = new Player(10, 20, 100, 100);
    //tokens.push_back(player);
    //tokens.push_back(new Character( 400, 40, 30, 30));
};

TokenHandler::~TokenHandler()
{
};

void TokenHandler::update()
{
    for(Token* t: tokens)
    {
        t->update();
        if(t->isType(Token::TYPE::Character) || t->isType(Token::TYPE::Player))
        {
            move((Character*) t);
        }
    }
};

void TokenHandler::render(sf::RenderWindow* g)
{
    for(Token* t: tokens)
    {
        t->render(g);
    }
};

void TokenHandler::move(Character* c)
{
    std::vector<Token*> collisions;

    c->moveBy(c->getVelocity().x * DeltaTime::get(), 0);

    for(Token* t: this->tokens)
    {
        if(t != c && t->collides(c))
        {
            collisions.push_back(t);
        }
    }

    for(Token* t: collisions)
    {
        if(c->getVelocity().x > 0)
        {
            c->setX(t->getX() - c->getWidth());
        }
        if(c->getVelocity().x < 0)
        {
            c->setX(t->getX() + t->getWidth());
        }
    }

    collisions.clear();

    c->moveBy(0, c->getVelocity().y * DeltaTime::get());

    for(Token* t: this->tokens)
    {
        if(t != c && t->collides(c))
        {
            collisions.push_back(t);
        }
    }

    for(Token* t: collisions)
    {
        if(c->getVelocity().y > 0)
        {
            c->setY(t->getY() - c->getHeight());
        }
        if(c->getVelocity().y < 0)
        {
            c->setY(t->getY() + t->getHeight());
        }
    }
    
};

void TokenHandler::handleEvents(sf::Event e)
{
    player->handleEvents(e);
};