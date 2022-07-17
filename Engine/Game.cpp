#include "Game.hpp"


Game::Game()
{
    graphics = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
    Functions::init();
    lastLog = "";
    Button* roll = new Button("LB", "Round Log");
    Button* AB = new Button("AB", "Raise Bet");
    Button* B = new Button("B", "Lower Bet");
    Button* PB = new Button("PB", "Play Card");
    Button* NB = new Button("NB", "Next turn");
    Button* QB = new Button("QB", "Bail");
    buttons.push_back(roll);
    buttons.push_back(AB);
    buttons.push_back(B);
    buttons.push_back(PB);
    buttons.push_back(NB);
    buttons.push_back(QB);

    menuButtons = {new Button("SB", "Start"), new Button("MB", "Mini Manual"), new Button("QB", "Quit")};
    
    currbutton = 0;

    bet = 0;

    font.loadFromFile("Art/BadComic-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    //test = new Card("Side that the cube lands on is + 2");
    isPlayerTurn = Functions::Random(1,3) == 2;
    newRound();

    texture.loadFromFile("Art/Arrow.png");
    arrow.setTexture(texture);
    arrow.scale(2,2);

    PG.setPosition(0,500);
    EG.setPosition(0 ,50);

    PG.scale(2, 2);
    EG.scale(2,2);

    log = false;
    manual = false;
    state =  0;

    background.loadFromFile("Art/Background1.png");
    BGSprite.setTexture(background);
    BGSprite.scale(2,2);

    aiTimer = 50;

    buffer.loadFromFile("Art/Song.wav");
    sound.setBuffer(buffer);
    sound.play();
    sound.setLoop(true);
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
        lastLog = "";
        lastLog += "Dice landed on: " + std::to_string(side) + " ";

        while(!round.empty())
        {
            side = round.front().interprit(side);
            round.pop();
        }

        lastLog += "Output was: " + std::to_string(side);

        if(playerGoal != side) player.damage(bet);
        if(enemyGoal != side) enemy.damage(bet);

        newRound();
    }

    int pHp = player.damage(0);
    int eHp = enemy.damage(0);

    if(!isPlayerTurn)
    {
        if(aiTimer <= 0 && !dice.isRolling())
        {
            //aiTimer = 250;
            isPlayerTurn = ai.process(enemyGoal, enemy.damage(0), player.damage(0), eh, round, currBet);
            if(ai.play != nullptr)
            {
                std::cout<<"Played Card"<<std::endl;
                round.push(ai.play->getRule());
                ai.play = nullptr;
            }
            bet = ai.bet;
        }
        aiTimer -= DeltaTime::get();
        if(isPlayerTurn)
        {
            nextTurn();
        }
    }

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
    
    if(player.dead()) state = 2;
    if(enemy.dead()) state = 2;

};

void Game::render()
{
    handler.render(graphics);
    dice.render(graphics);

    text.setString("Your bet: " + std::to_string(bet) +" HP");
    text.setPosition(650, 100);
    graphics->draw(text);

    ph.render(graphics);
    eh.enemyRender(graphics, ai.play);

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
    currBet = 1;
    bet = 1;

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
                if(state == 1)
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

                if(state == 0)
                {
                    if(event.key.code == sf::Keyboard::Down)
                    {
                        currbutton++;
                        if(currbutton >= menuButtons.size()) currbutton = 0;
                    };
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        currbutton--;
                        if(currbutton < 0) currbutton = menuButtons.size()-1;
                    };
                    if(event.key.code == sf::Keyboard::Enter)
                    {
                        if(currbutton == 0)
                        {
                            state = 1;
                        }
                        if(currbutton == 1)
                        {
                            manual = !manual;
                        }
                        if(currbutton == 2)
                        {
                            return;
                        }
                    }

                }
            }
            
            if(event.type == sf::Event::KeyReleased)
            {
                
            }
        }

        graphics->clear(sf::Color::Black);

        if(state == 0)
        {
            int shift = 380;
            for(int i = 0; i< menuButtons.size(); i++)
            {
                if(manual) shift = 630;
                menuButtons[i]->render(graphics, currbutton == i, shift, 200+80*i);
            }

            if(manual)
            {
                text.setPosition(20, 20);
                text.setString("Manual");
                graphics->draw(text);

                text.setPosition(20, 60);
                text.setString("Use Up and Down arrow keys to navigate Buttons, use Left and Right arrow keys to navigate cards.");
                graphics->draw(text);

                text.setPosition(20, 90);
                text.setString("Your Goal is to decrease opponent's health to 0, before your opponent does that to you.");
                graphics->draw(text);

                text.setPosition(20, 120);
                text.setString("There is a cube on the left hand side, if center cube lands on the same side you win.");
                graphics->draw(text);

                text.setPosition(20, 150);
                text.setString("However your opponent may or may not have a different goal number.");
                graphics->draw(text);

                text.setPosition(20, 180);
                text.setString("If the cube lands on the wrong side you lose the amount of hp you betted.");
                graphics->draw(text);

                text.setPosition(20, 210);
                text.setString("The Cube is rolled when both of the players bet the same amount of HP.");
                graphics->draw(text);

                text.setPosition(20, 240);
                text.setString("You can bail any time, meaning lose current bet of hp.");
                graphics->draw(text);

                text.setPosition(20, 270);
                text.setString("Each of you also have cards that influence the outcome.");
                graphics->draw(text);

                text.setPosition(20, 300);
                text.setString("For example if +2 card is played, and the side that then cube landed on is 3");
                graphics->draw(text);

                text.setPosition(20, 330);
                text.setString("Then you win if you goal number is (cube on the left indicates) 5");
                graphics->draw(text);

                text.setPosition(20, 360);
                text.setString("The sides are capped on 1 and 6, so if you play *2 and cube lands on 5.");
                graphics->draw(text);

                text.setPosition(20, 390);
                text.setString("The outcome is 6 as it is a 6 sided cube.");
                graphics->draw(text);

                text.setPosition(20, 420);
                text.setString("Card effects stack in a form of a queue (First in, First out)");
                graphics->draw(text);
            }
            else
            {
                text.setPosition(180, 50);
                text.setString("Use Arrow Buttons (UP or Down) To Navigate, To Select Click Enter.");
                graphics->draw(text);
            }

        }
        if(state == 1)
        {
            graphics->draw(BGSprite);
            player.display(graphics, "Player", 660, 550);
            enemy.display(graphics, "Enemy", 660, 40);

            for(int i = 0; i< buttons.size(); i++)
            {
                buttons[i]->render(graphics, currbutton == i, 650, 150+64*i);
            }

            update();
            render();

            text.setPosition(200, 180);
            text.setString(lastLog);
            graphics->draw(text);

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
                    if(i < 15)
                        round.front().write(graphics, 20, 40+i * 30, text, 550);

                    round.push(round.front());
                    round.pop();
                }
                std::vector<int> out;
                for(int i = 1; i<= 6; i++)
                {
                    int test = i;
                    for (size_t i = 0; i < round.size(); i++)
                    {
                    round.push(round.front());
                    test = round.front().interprit(test);
                    round.pop();
                    }
                    out.push_back(test);
                }

                for(int i = 0; i < out.size(); i++)
                {
                    text.setPosition(50+50*i, 550);
                    text.setString(std::to_string(i+1)+": "+std::to_string(out[i]));
                    graphics->draw(text);
                }
                text.setPosition(50, 530);
                text.setString("Automatic Calculator:");
                graphics->draw(text);

            }
        }

        if(state == 2)
        {
            int pHp = player.damage(0);
            int eHp = enemy.damage(0);
            if(pHp == 0 && eHp == 0)
            {
                text.setString("You Drew");
                text.setPosition(350, 200);
                graphics->draw(text);
            }
            else if(pHp == 0)
            {
                text.setString("You Lost");
                text.setPosition(350, 200);
                graphics->draw(text);
            }
            else if(eHp == 0)
            {
                text.setString("You Won, but at what cost");
                text.setPosition(350, 200);
                graphics->draw(text);
            }
        }

        DeltaTime::tick();
        // end the current frame
        graphics->display();
    }
};