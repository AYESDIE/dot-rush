//
// Created by ayesdie on 01/10/20.
//

#ifndef DOT_RUSH_POPULATION_H
#define DOT_RUSH_POPULATION_H

#include "dots.h"
#include "obstacle.h"

class population {
private:
    std::vector<dot> dots;
    int gen;
    float fitnessSum;
    int bestDot;
    int minStep;

public:
    population(size_t size, const std::pair<float, float>& goal, int width, int height, sf::RenderWindow* window, std::vector<obstacle>* _obstacles);

    void draw();
    void update();
    void calculateFitness();

    bool allDotsDead();

    void naturalSelection();
    void calculateFitnessSum();
    void selectBestDot();

    dot selectParent();
    void mutateDemBabies();
};


#endif //DOT_RUSH_POPULATION_H
