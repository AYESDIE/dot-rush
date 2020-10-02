//
// Created by ayesdie on 01/10/20.
//

#include "dots.h"
#include <cmath>

dot::dot(const std::pair<float, float>& goal, int _width, int _height, sf::RenderWindow *_window) : goal(goal), width(_width), height(_height) {
    isDead = false;
    isAtGoal = false;
    isBest = false;
    fitness = 0;
    pos = std::pair<float, float>(_width / 2.0, _height - 10.0);
    vel = std::pair<float, float>(0.0, 0.0);
    acc = std::pair<float, float>(0.0, 0.0);

    dotBrain = brain(size_t(1000));

    window = _window;
}

void dot::draw() {
    sf::CircleShape dot;
    if (isBest) {
        dot = sf::CircleShape(4);
        dot.setFillColor(sf::Color(0, 255, 0));
    }
    else {
        dot = sf::CircleShape(2);
        dot.setFillColor(sf::Color(255, 255, 255));
    }

    dot.setPosition(pos.first, pos.second);
    window->draw(dot);
}

void dot::move() {
    if (dotBrain.hasMoves()) {
        acc = dotBrain.getDirectionAtStep();
        dotBrain.nextStep();
    }
    else
    {
        isDead = true;
    }

    vel.first += acc.first;
    vel.second += acc.second;

    // normalize vector and scale it by 5.
    float mag = std::sqrt((vel.first * vel.first) + (vel.second * vel.second));
    vel.first *= 5 / mag;
    vel.second *= 5 / mag;

    pos.first += vel.first;
    pos.second += vel.second;
}

void dot::update() {
    if (!isDead && !isAtGoal)
    {
        move();
        if (pos.first < 2 || pos.second < 2 || pos.first > width - 2 || pos.second > height - 2) {
            isDead = true;
        }
        else if (std::sqrt(std::pow(pos.first - goal.first, 2) + std::pow(pos.second - goal.second, 2)) < 5)
        {
            isAtGoal = true;
        }
    }
}

void dot::calculateFitness() {
    if (isAtGoal)
    {
        fitness = 1.0/8.0 + 10000.0/(dotBrain.getStep() * dotBrain.getStep());
    }
    else
    {
        double distanceToGoal = std::sqrt(std::pow(pos.first - goal.first, 2) + std::pow(pos.second - goal.second, 2));
        fitness = 1.0/(distanceToGoal * distanceToGoal * distanceToGoal);
    }
}

dot dot::gimmeBaby() {
    dot baby(goal, width, height, window);
    baby.dotBrain = dotBrain;
    baby.dotBrain.setStep(0);
    return baby;
}
