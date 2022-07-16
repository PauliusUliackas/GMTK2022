#include "Game.hpp"


Game::Game()
{
    graphics = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
    Functions::init();

    Button* roll = new Button("LB");
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

    //test = new Card("Side that the cube lands on is + 2");

    newRound();

    texture.loadFromFile("Art/Arrow.png");
    arrow.setTexture(texture);
    arrow.scale(2,2);

    PG.setPosition(0,500);
    EG.setPosition(0 ,50);

    PG.scale(2, 2);
    EG.scale(2,2);

    log = false;
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

        if(playerGoal != side) player.damage(bet);
        if(enemyGoal != side) enemy.damage(bet);

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

    if(!isPlayerTurn)
    {
        isPlayerTurn = ai.process(enemyGoal, enemy.damage(0), player.damage(0), eh, round, currBet);
        
        if(ai.play != nullptr)
        {
            round.push(ai.play->getRule());
            ai.play = nullptr;
        }
        bet = ai.bet;

        if(isPlayerTurn)
            nextTurn();
    }

    if(currBet-1 > player.damage(0) || currBet-1 > enemy.damage(0)) dice.roll(8);
    

};

void Game::render()
{
    handler.render(graphics);
    dice.render(graphics);

    text.setString("Your bet: " + std::to_string(bet) +" HP");
    text.setPosition(650, 100);
    graphics->draw(text);

    ph.render(graphics);
    eh.enemyRender(graphics);

    if(isPlayerTurn) arrow.setPosition(620, 555);
    else arrow.setPosition(620, 45);

    graphics->draw(arrow);

    PG.setTexture(dice.getTexture(playerGoal));
    EG.setTexture(dice.getTexture(enemyGoal));

    graphics->draw(PG);
    //graphics->draw(EG);

};

void Game::newRound()
{
    ph.discard();
    eh.discard();
    ph.draw(5, db);
    eh.draw(5, db);
    isCall = false;
    isPlayerTurn = true;
    currBet = 0;
    bet = 0;

    playerGoal = Functions::Random(1, 7);
    enemyGoal = Functions::Random(1, 7);
    ai.reset();
}

void Game::nextTurn()
{
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
        std::cout<<"Roll"<<std::endl;
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

                if(event.key.code == sf::Keyboard::Enter && !dice.isRolling() && isPlayerTurn)
                {
                    if(currbutton == 0)
                    {
                        log = !log;
                    }
                    if(currbutton == 1)
                        bet++;
                    if(currbutton == 2)
                        bet--;
                    if(currbutton == 3 && ph.size() > 0)
                    {
                        Card* c = ph.play();
                        ai.predictPlayer(c->getRule(), round);
                        round.push(c->getRule());
                    }
                    if(currbutton == 4)
                    {
                        isPlayerTurn = !isPlayerTurn;
                        nextTurn();
                    }
                    if(currbutton == 5)
                    {
                        while(!round.empty())
                        {
                            round.pop();
                        }

                        if(isPlayerTurn) player.damage(currBet);
                        else enemy.damage(currBet);

                        isPlayerTurn = !isPlayerTurn;
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

        if(log)
        {
            text.setPosition(20, 20);
            text.setString("Log:");
            sf::RectangleShape rs(sf::Vector2f(600, 600));
            rs.setFillColor(sf::Color::Black);
            graphics->draw(rs);
            graphics->draw(text);
            for (size_t i = 0; i < round.size(); i++)
            {
                round.front().write(graphics, 20, 40+i * 30, text);
                round.push(round.front());
                round.pop();
            }
        }

        DeltaTime::tick();
        // end the current frame
        graphics->display();
    }
};