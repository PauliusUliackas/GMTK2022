#include "Game.hpp"


Game::Game()
{
    graphics = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
    Functions::init();

    Button* roll = new Button("RB");
    Button* AB = new Button("AB");
    Button* B = new Button("B");
    Button* PB = new Button("PB");
    Button* NB = new Button("NB");
    Button* QB = new Button("QB");
    buttons.push_back(roll);
    buttons.push_back(AB);
    buttons.push_back(B);
    buttons.push_back(PB);
    buttons.push_back(NB);
    buttons.push_back(QB);
    
    currbutton = 0;

    bet = 0;

    font.loadFromFile("Art/BadComic-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(650, 100);

    //test = new Card("Side that the cube lands on is + 2");
    test = db.getRandomCard();

    newRound();

    texture.loadFromFile("Art/Arrow.png");
    arrow.setTexture(texture);
    arrow.scale(2,2);
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

        newRound();
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

    if(bet < currBet) bet = currBet;
    

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

    if(isPlayerTurn) arrow.setPosition(620, 555);
    else arrow.setPosition(620, 45);

    graphics->draw(arrow);

};

void Game::newRound()
{
    ph.discard();
    eh.discard();
    ph.draw(5, db);
    eh.draw(5, db);
    isCall = false;
    isPlayerTurn = true;
    currBet = 1;
    bet = 1;
}


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

                if(event.key.code == sf::Keyboard::Enter )//&& isPlayerTurn)
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
                    if(currbutton == 4)
                    {
                        isPlayerTurn = !isPlayerTurn;
                        if(isPlayerTurn)
                        {
                            ph.draw(1, db);
                        }
                        else
                        {
                            eh.draw(1,db);
                        }

                        if(currBet == bet && isCall)
                        {
                            dice.roll(5);
                        }
                        else if(currBet == bet)
                        {
                            isCall = true;
                        }
                        else
                        {
                            isCall = false;
                            currBet = bet;
                        }
                    }
                    if(currbutton == 5)
                    {
                        while(!round.empty())
                        {
                            round.pop();
                        }

                        if(isPlayerTurn) player.damage(currBet);
                        else enemy.damage(currBet);

                        newRound();
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
                }
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