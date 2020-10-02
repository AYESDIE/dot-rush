#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/population.h"
#include "src/obstacle.h"

int main() {
    int width = 600;
    int height = 600;

    auto window = new sf::RenderWindow(sf::VideoMode(width, height), "Dots",sf::Style::Titlebar | sf::Style::Close);

    std::pair<float, float> goal(width / 2, 20);

    sf::CircleShape goalCircle(8);
    goalCircle.setPosition(goal.first, goal.second);
    goalCircle.setFillColor(sf::Color(255, 0, 0));

    obstacle obs1(window, std::pair<float, float>(400, 20), std::pair<float, float>(0, 400));
    obstacle obs2(window, std::pair<float, float>(400, 20), std::pair<float, float>(200, 200));


    sf::Clock clock;
    sf::Time time;

    population pop(200, goal, width, height, window);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }


        time = clock.getElapsedTime();
        if (time.asMilliseconds() >= 20)
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
            //    obs1.draw();
            //    obs2.draw();
                pop.draw();
            }

            window->draw(goalCircle);
            window->display();

            clock.restart();
        }
    }
}
