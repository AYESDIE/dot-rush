//
// Created by ayesdie on 01/10/20.
//

#include "population.h"

population::population(size_t size, const std::pair<float, float>& goal, int width, int height, sf::RenderWindow* window, std::vector<obstacle>* obstacles) {
    gen = 1;
    fitnessSum = 0;
    minStep = 1000;

    dots.clear();
    for (int i = 0; i < size; ++i) {
        dots.push_back(dot(goal, width, height, window, obstacles));
    }
}

void population::draw() {
    for (auto &item : dots) {
        item.draw();
    }
}

void population::update() {
    for (int i = 0; i < dots.size(); ++i) {
        if (dots[i].dotBrain.getStep() > minStep) {
            dots[i].isDead = true;
        }
        else {
            dots[i].update();
        }
    }

    for (int i = 0; i < dots.size(); ++i) {
        dots[i].update();
    }
}

void population::calculateFitness() {
    for (auto &item : dots) {
        item.calculateFitness();
    }
}

bool population::allDotsDead() {
    for (auto &item : dots) {
        if (!item.isDead && !item.isAtGoal) {
            return false;
        }
    }
    return true;
}

void population::naturalSelection() {
    std::vector<dot> newDots;
    selectBestDot();
    calculateFitnessSum();

    refine.clear();

    newDots.push_back(dots[bestDot].gimmeBaby());
    newDots[0].isBest = true;
    for (int i = 1; i < dots.size(); i++) {
        dot parent = selectParent();
        newDots.push_back(parent.gimmeBaby());

        if(!dots[i].isAtGoal)
        {
            refine.push_back(i);
        }
    }

    gen++;
    dots = newDots;
    std::cout << " > Gen:" << gen << std::endl;
    std::cout << " > Fitness: " << fitnessSum << std::endl;
}

void population::calculateFitnessSum() {
    fitnessSum = 0;
    for (dot &item : dots) {
        fitnessSum += item.fitness;
    }
}

void population::selectBestDot() {
    float max = 0;
    int maxIndex = 0;
    for (int i = 0; i < dots.size(); ++i) {
        if (dots[i].fitness > max) {
            max = dots[i].fitness;
            maxIndex = i;
        }
    }

    bestDot = maxIndex;

    if(dots[bestDot].isAtGoal) {
        minStep = dots[bestDot].dotBrain.getStep();
        std::cout << " > Step: " << minStep << std::endl;
    }
}

dot population::selectParent() {
    float rng = fitnessSum * (float)rand() / RAND_MAX;
    float runningSum = 0;
    for (auto &item : dots) {
        runningSum += item.fitness;
        if (runningSum > rng) {
            return item;
        }
    }
}

void population::mutateDemBabies() {
    for (int i = 1; i < refine.size(); ++i) {
        dots[refine[i]].dotBrain.mutate();
    }
}