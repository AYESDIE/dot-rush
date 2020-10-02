//
// Created by ayesdie on 01/10/20.
//

#include "brain.h"
#include <cmath>

brain::brain() {

}

brain::brain(size_t size) {
    step = 0;
    directions = std::vector<std::pair<float, float>>(size);
    randomize();
}

void brain::randomize() {
    for (int i = 0; i < directions.size(); ++i) {
        auto randomAngle = float (rand() * (2 * M_PI) / RAND_MAX);
        directions[i] = std::pair<float, float>(std::cos(randomAngle), std::sin(randomAngle));
    }
}

bool brain::hasMoves() {
    return directions.size() > step;
}

std::pair<float, float> brain::getDirectionAtStep(){
    if (step < directions.size())
        return directions[step];
    else
        return std::pair<float, float>(0, 0);
}

void brain::nextStep() {
    step += 1;
}

int brain::getStep() {
    return step;
}

void brain::setStep(int _step) {
    step = _step;
}

void brain::mutate() {
    float mutationRate = 0.01;
    for (int i = 0; i < directions.size(); ++i) {
        float rng = (float) rand() / RAND_MAX;
        if (rng < mutationRate) {
            auto randomAngle = float (rand() * (2 * M_PI) / RAND_MAX);
            directions[i] = std::pair<float, float>(std::cos(randomAngle), std::sin(randomAngle));
        }
    }
}