#include "Game.hpp"


Game::Game()
{
    graphics = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
};

Game::~Game()
{
};

void Game::update()
{
    handler.update();
};

void Game::render()
{
    handler.render(graphics);
};


void Game::run()
{
    while (graphics->isOpen())
    {
        DeltaTime::tick();
        sf::Event event;
        while (graphics->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                graphics->close();
            handler.handleEvents(event);
        }

        graphics->clear(sf::Color::Black);

        update();
        render();

        // end the current frame
        graphics->display();
    }
};