#pragma once

#include "../DS/Hand.hpp"
#include <queue>

class AI
{
private:
    std::vector<int> playerGoal;
    std::vector<double> probabilities;
    std::vector<double> playerProbabilities;

    std::vector<double> selfChances;
    std::vector<double> playerChances;

public:
    Card* play;
    int bet;

public:
    AI();
    ~AI();
    bool process(int goal, int HP, int playerHP, Hand& ownHand, std::queue<Rule> currentRules, int currentBet);
    void reset();
    void predictPlayer(Rule newRule, std::queue<Rule> currentRules);
    void print(std::vector<int> i);
    int search(std::vector<Rule> rules, Hand& hand, int goal, int depth, bool winning, int chance);

    double selfChance(std::vector<Rule>, int goal);
    double enemyChance(std::vector<Rule>);
};
