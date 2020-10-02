//
// Created by ayesdie on 02/10/20.
//

#ifndef DOT_RUSH_OBSTACLE_H
#define DOT_RUSH_OBSTACLE_H

#include <SFML/Graphics.hpp>

class obstacle {
    sf::RenderWindow* window;
    std::pair<float, float> size;
    std::pair<float, float> pos;

public:
    obstacle(sf::RenderWindow* window, std::pair<float, float> size, std::pair<float, float> pos);

    void setSize(std::pair<float, float> _size);
    void setPosition(std::pair<float, float> _pos);
    bool isColliding(std::pair<float, float> loc);

    void draw();
};


#endif //DOT_RUSH_OBSTACLE_H
