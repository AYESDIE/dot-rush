//
// Created by ayesdie on 02/10/20.
//

#include "obstacle.h"

obstacle::obstacle(sf::RenderWindow *window, std::pair<float, float> size, std::pair<float, float> pos) :
    window(window), size(size), pos(pos)
{
}

void obstacle::setSize(std::pair<float, float> _size) {
    size = _size;
}

void obstacle::setPosition(std::pair<float, float> _pos) {
    pos = _pos;
}

void obstacle::draw()
{
    sf::RectangleShape obs(sf::Vector2f(size.first, size.second));
    obs.setPosition(pos.first, pos.second);
    obs.setFillColor(sf::Color(0, 0, 255));
    window -> draw(obs);
}

bool obstacle::isColliding(std::pair<float, float> loc) {
    return ((loc.first > pos.first) && (loc.first < (size.first + pos.first))) && ((loc.second > pos.second) && (loc.second < (size.second + loc.second)));
}


