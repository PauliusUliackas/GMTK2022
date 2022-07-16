#include "Game.hpp"


Game::Game()
{
    graphics = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
    Functions::init();

    Button* roll = new Button("RB");
    Button* AB = new Button("AB");
    Button* B = new Button("B");
    Button* PB = new Button("PB");
    buttons.push_back(roll);
    buttons.push_back(AB);
    buttons.push_back(B);
    buttons.push_back(PB);
    currbutton = 0;

    bet = 0;

    font.loadFromFile("Art/BadComic-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(650, 100);

    //test = new Card("Side that the cube lands on is + 2");
    test = db.getRandomCard();

    ph.draw(5, db);
    eh.draw(5, db);
};

Game::~Game()
{
};

void Game::update()
{
    handler.update();

    if(dice.isOver())
    {
        int side = dice.side();

        while(!round.empty())
        {
            side = round.front().interprit(side);
            round.pop();
        }

        if(side <= 3) player.damage(bet);
        else enemy.damage(bet);
    }

    int pHp = player.damage(0);
    int eHp = enemy.damage(0);

    if(bet < 0) bet = 0;

    if(pHp < eHp)
    {
        if(bet > pHp) bet = pHp;
    }
    else
    {
        if(bet > eHp) bet = eHp;
    }
    

};

void Game::render()
{
    handler.render(graphics);
    dice.render(graphics);

    text.setString("Your bet: " + std::to_string(bet) +" HP");
    graphics->draw(text);

    test->render(graphics, false, 100);

    ph.render(graphics);
    eh.enemyRender(graphics);
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
                if(event.key.code == sf::Keyboard::Enter)
                {
                    if(currbutton == 0)
                        dice.roll(5);
                    if(currbutton == 1)
                        bet++;
                    if(currbutton == 2)
                        bet--;
                    if(currbutton == 3)
                    {
                        round.push(ph.play()->getRule());
                    }
                }

                if(event.key.code == sf::Keyboard::Down)
                {
                    currbutton++;
                    if(currbutton >= buttons.size()) currbutton = 0;
                };
                if(event.key.code == sf::Keyboard::Up)
                {
                    currbutton--;
                    if(currbutton < 0) currbutton = buttons.size()-1;
                };
                if(event.key.code == sf::Keyboard::Left)
                {
                    ph.prev();
                };
                if(event.key.code == sf::Keyboard::Right)
                {
                    ph.next();
                };
            }
            
            if(event.type == sf::Event::KeyReleased)
            {
                
            }
        }

        graphics->clear(sf::Color::Black);

        player.display(graphics, "Player", 660, 550);
        enemy.display(graphics, "Enemy", 660, 40);

        for(int i = 0; i< buttons.size(); i++)
        {
            buttons[i]->render(graphics, currbutton == i, 650, 150+50*i);
        }

        update();
        render();
        DeltaTime::tick();
        // end the current frame
        graphics->display();
    }
};