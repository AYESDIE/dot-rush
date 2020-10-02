//
// Created by ayesdie on 01/10/20.
//

#ifndef DOT_RUSH_DOTS_H
#define DOT_RUSH_DOTS_H

#include <iostream>
#include "brain.h"
#include "obstacle.h"
#include <SFML/Graphics.hpp>

class dot {
private:
    std::pair<float, float> goal;
    std::pair<float, float> pos;
    std::pair<float, float> vel;
    std::pair<float, float> acc;
    int width;
    int height;
    sf::RenderWindow* window;

    std::vector<obstacle>* obstacles;

public:
    dot(const std::pair<float, float>& goal, int _width, int _height, sf::RenderWindow* _window, std::vector<obstacle>* _obstacles);

    void draw();
    void move();
    void update();

    void calculateFitness();
    dot gimmeBaby();

    bool isDead;
    bool isAtGoal;
    brain dotBrain;
    bool isBest;
    float fitness;
};


#endif //DOT_RUSH_DOTS_H
