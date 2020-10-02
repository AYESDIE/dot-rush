//
// Created by ayesdie on 01/10/20.
//

#ifndef DOT_RUSH_BRAIN_H
#define DOT_RUSH_BRAIN_H

#include <iostream>
#include <vector>

class brain {
private:
    std::vector<std::pair<float, float>> directions;
    int step;

public:
    brain();
    brain(size_t size);

    void randomize();
    bool hasMoves();
    std::pair<float, float> getDirectionAtStep();
    void nextStep();
    int getStep();
    void setStep(int _step);

    void mutate();
};


#endif //DOT_RUSH_BRAIN_H
