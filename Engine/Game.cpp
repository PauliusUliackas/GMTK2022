#include "Game.hpp"


Game::Game()
{
    graphics = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
    Functions::init();

    Button* roll = new Button("RB");
    buttons.push_back(roll);

    currbutton = 0;
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
    dice.render(graphics);
};


void Game::run()
{
    while (graphics->isOpen())
    {
        sf::Event event;
        while (graphics->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                graphics->close();
            handler.handleEvents(event);

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Enter && currbutton == 0 && dice.isOver()) dice.roll(5);
            }
            
            if(event.type == sf::Event::KeyReleased)
            {
                
            }
        }

        graphics->clear(sf::Color::Black);

        

        player.display(graphics, "Player", 10, 40);
        enemy.display(graphics, "Enemy", 600, 40);

        for(int i = 0; i< buttons.size(); i++)
        {
            buttons[i]->render(graphics, currbutton == i, 700, 300+50*i);
        }

        update();
        render();
        DeltaTime::tick();
        // end the current frame
        graphics->display();
    }
};