#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/population.h"
#include "src/obstacle.h"

int main() {
    srand(time(0));

    int width = 600;
    int height = 600;

    auto window = new sf::RenderWindow(sf::VideoMode(width, height), "Dots",sf::Style::Titlebar | sf::Style::Close);

    std::pair<float, float> goal(300, 300);

    sf::CircleShape goalCircle(8);
    goalCircle.setPosition(goal.first, goal.second);
    goalCircle.setFillColor(sf::Color(255, 0, 0));

    obstacle obs1(window, std::pair<float, float>(200, 20), std::pair<float, float>(200, 450));
    obstacle obs2(window, std::pair<float, float>(20, 200), std::pair<float, float>(200, 200));
    obstacle obs3(window, std::pair<float, float>(200, 20), std::pair<float, float>(220, 150));
    obstacle obs4(window, std::pair<float, float>(20, 220), std::pair<float, float>(400, 200));

    auto obs = new std::vector<obstacle>();
    obs->push_back(obs1);
    obs->push_back(obs2);
    obs->push_back(obs3);
    obs->push_back(obs4);

    sf::Clock clock;
    sf::Time time;

    population pop(500, goal, width, height, window, obs);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }


        time = clock.getElapsedTime();
        if (time.asMilliseconds() >= 10)
        {
            window->clear(sf::Color::Black);

            if (pop.allDotsDead())
            {
                pop.calculateFitness();
                pop.naturalSelection();
                pop.mutateDemBabies();
            }
            else
            {
                pop.update();
                for (auto &item : *obs) {
                    item.draw();
                }
                pop.draw();
            }

            window->draw(goalCircle);
            window->display();

            clock.restart();
        }
    }
}
