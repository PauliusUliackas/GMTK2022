#include "AI.hpp"


AI::AI()
{
    reset();
};

AI::~AI()
{
};

bool AI::process(int goal, int HP, int playerHP, Hand& ownHand, std::queue<Rule> currentRules, int currentBet)
{   
    std::cout<<"Start"<<std::endl;
    std::vector<Rule> rules;

    int rightSide = 0;

    while(!currentRules.empty())
    {
        rules.push_back(currentRules.front());
        currentRules.pop();
    }
    std::cout<<"1"<<std::endl;
    for(int i = 1; i <= 6; i++)
    {
        int out = i;
        for(Rule r: rules)
        {
            out = r.interprit(out);
        }
        if(out == goal) rightSide++;
        probabilities[i-1] = out;
    }
    std::cout<<"2"<<std::endl;
    // Our Chance Of win
    double chance = rightSide/probabilities.size();

    // Player chance of Win
    //std::cout<<"PlayerGoals"<<std::endl;
    //print(playerGoal);
    double chanceOfPlayer = 0;

    for(double c: playerProbabilities)
    {
        chanceOfPlayer += c;
    }

    chanceOfPlayer /= playerProbabilities.size();
    std::cout<<"3"<<std::endl;
    // 1) Check card influences depth.
    // 2) If hp more than player check if it can harm the player.
    // 3) Else less than player check if it can win.
    // 4) Bail if it has no positive influence.

    // 5) if Winning current round Raise
    // 6) if Losing current round call

    int Card;
    Card = search(rules, ownHand, goal, 3, HP > playerHP, chance);
    std::cout<<"4"<<std::endl;
    for(int i = 0; i < ownHand.size(); i++)
    {
        if(i == Card)
        {
            play = ownHand.play();
            return false;
        }
        ownHand.next();
    }
    std::cout<<"5"<<std::endl;
    if(Functions::Random(0, 100) == 2) bet = 100;
    else if(chanceOfPlayer > chance && Functions::Random(0, 100) > 30) bet = currentBet;
    else bet = currentBet + Functions::Random(1, 10);

    if(playerHP < bet) bet = playerHP;
    std::cout<<"End"<<std::endl;
    return true;
};

int AI::search(std::vector<Rule> rules, Hand& hand, int goal, int depth, bool winning, int chance)
{
    std::cout<<"3.1"<<std::endl;
    for(int i = 0; i< hand.size(); i++)
    {
        Card* c = hand.play();
        rules.push_back(c->getRule());
        //std::cout<<"3.1.0"<<std::endl;
        selfChances[i] = selfChance(rules, goal);
        //std::cout<<"3.1.1"<<std::endl;
        playerChances[i] = enemyChance(rules);
        //std::cout<<"3.1.2"<<std::endl;
        hand.next();
        if(depth > 0 && hand.size() > 0) search(rules, hand, goal, depth-1, winning, chance);
        //std::cout<<"3.1.3"<<std::endl;
        hand.add(c);
        rules.pop_back();
    }
    //std::cout<<"3.2"<<std::endl;
    if(!winning) playerChances = {0,0,0,0,0,0};

    int out = -1;
    double max = chance;
    for(int i = 0; i < hand.size(); i++)
    {
        if(selfChances[i] - playerChances[i] >= max)
        {
            out = i;
            max = selfChances[i] - playerChances[i];
        }
    }
    
    return out;
}

double AI::selfChance(std::vector<Rule> rules, int goal)
{
    int rightSide = 0;
    for(int i = 1; i <= 6; i++)
    {
        int out = i;
        for(Rule r: rules)
        {
            out = r.interprit(out);
        }
        if(out == goal) rightSide++;
    }
    // Our Chance Of win
    double output = rightSide/6;
    return output;
}

double AI::enemyChance(std::vector<Rule> rules)
{
    std::vector<int> outs;
    for(int i = 1; i <= 6; i++)
    {
        int out = i;
        for(Rule r: rules)
        {
            outs.push_back(r.interprit(out));
        }
    }

    double chance = 0;
    //std::cout<<"3.1.1.1"<<std::endl;
    for(int i: outs)
    {
        for(int x = 0; x < playerGoal.size(); x++)
        {
            int player = playerGoal[x];
            if(player == i)
            {
                //std::cout<<player<<":"<<playerProbabilities[player-1]<<std::endl;
                chance += playerProbabilities[playerGoal[x]-1];
            }
        }
    }
    //std::cout<<"3.1.1.2"<<std::endl;
    return chance;
}

void AI::reset()
{
    playerGoal.clear();
    playerProbabilities = {0,0,0,0,0,0};
    for(int i = 1; i <= 6; i++) playerGoal.push_back(i);
    probabilities = {1,2,3,4,5,6};
    selfChances = {0,0,0,0,0,0};
    playerChances = {0,0,0,0,0,0};
    play = nullptr;
};

void AI::predictPlayer(Rule newRule, std::queue<Rule> currentRules)
{
    int bluffLikelyhood = 0;

    std::vector<Rule> rules;

    int rightSide = 0;

    while(!currentRules.empty())
    {
        rules.push_back(currentRules.front());
        currentRules.pop();
    }

    std::vector<int> prev = {1,2,3,4,5,6};

    for(int i = 0; i < prev.size(); i++)
    {
        for(Rule r: rules)
        {
            prev[i] = r.interprit(i+1);
        }
    }

    std::vector<double> pProbabilites = {0,0,0,0,0,0};

    for(int i = 0; i < prev.size(); i++)
    {
        pProbabilites[prev[i]-1] += 1;
    }

    for(double &i : pProbabilites)
    {
        i/=6;
    }
    
    // -----------------------------------------
    std::vector<int> after = {1,2,3,4,5,6};
    int index2 = 0;
    for(int r: prev)
    {
        after[index2] = newRule.interprit(r);
        index2++;
    }
    
    std::vector<double> newProbabilites = {0,0,0,0,0,0};

    //std::cout<<"After"<<std::endl;

    for(int i = 0; i < after.size(); i++)
    {
        //std::cout<<after[i]<<std::endl;
        newProbabilites[after[i]-1] += 1;
    }

    for(double &i : newProbabilites)
    {
        i/=6;
    }

    for(int i = playerGoal.size()-1; i >= 0; i--)
    {
        if(pProbabilites[playerGoal[i]-1] > newProbabilites[playerGoal[i]-1]) playerGoal.erase(playerGoal.begin() + i); 
    }

    for(int i = 6; i >= 0; i--)
    {
        if(newProbabilites[i-1] - pProbabilites[i-1] > 0.17)
        {
            bool contains = false;
            for(int j = 0; j < playerGoal.size(); j++)
            {
                if(playerGoal[j] == i) contains = true;
            }
            if(!contains) playerGoal.push_back(i);
        }
    }
    
    if(playerGoal.size() == 0)
    {
        for(int i = 0; i < playerGoal.size(); i++)
        {
            if(pProbabilites[playerGoal[i]] <= newProbabilites[playerGoal[i]]) playerGoal.push_back(i+1); 
        }
    }

    playerProbabilities = newProbabilites;

}

void AI::print(std::vector<int> list)
{
    for(auto i: list)
    {
        std::cout<<i<<std::endl;
    }
}