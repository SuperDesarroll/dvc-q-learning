#ifndef QLEARNING_H
#define QLEARNING_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>

class QLearning
{
private:
    int numActions;
    double learningRate;
    double discountFactor;
    double epsilon;
    double valueReward;
    int angleDelta;
    Library lib;
    std::vector<std::vector<double>> qTable;

public:
    int angleDeltaActions;

    QLearning(int numActions, double learningRate, double discountFactor, double epsilon,double valueReward, int angleDelta)
        : numActions(numActions), learningRate(learningRate), discountFactor(discountFactor), epsilon(epsilon),
          valueReward(valueReward), angleDelta(angleDelta)
    {
        lib.randomseed();
        angleDeltaActions = 180 / angleDelta;
        qTable = std::vector<std::vector<double>>(angleDeltaActions, std::vector<double>(numActions, 0.0));
    }

    int chooseAction(int state)
    {
        std::vector<double> qValues = qTable[state];
        if ((rand() / double(RAND_MAX)) < epsilon)
        {
            return rand() % numActions; // Acción aleatoria
        }
        else
        {
            return std::distance(qValues.begin(), std::max_element(qValues.begin(), qValues.end()));
        }
    }

    double getReward(double currentValue)
    {
        return -std::abs(valueReward - currentValue);
    }

    void updateQTable(int state, int action, int newState, double reward)
    {     
        qTable[state][action]                   = qTable[state][action]                 + learningRate  * (reward + discountFactor  * *std::max_element(qTable[newState].begin()                , qTable[newState].end())                 - qTable[state][action]);
    }

    void showQTable()
    {
        lib.println("Q-Table:");
        for (int i = 0; i < qTable.size(); i++)
        {
            lib.print("Position " + std::to_string(i) + ": ");
            for (int j = 0; j < qTable[i].size(); j++)
            {
                lib.print(std::to_string(qTable[i][j]) + " ");
            }
            lib.println("");
        }
        lib.println("Training finished");
    }
};

#endif // QLEARNING_H