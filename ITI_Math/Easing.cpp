#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>


float easeInOutSine(float x){
return -(cos(M_PI * x) - 1) / 2;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");
    sf::CircleShape shape(20);
    shape.setOrigin(20, 20);
    shape.setFillColor(sf::Color::Green);


    sf::Vector2f position(20, 20);
    sf::Vector2f targetPosition(position);
    sf::Vector2f startPosition(position);


    sf::Clock clock;
    float time;

    float d = 1;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                targetPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                startPosition = position;
                clock.restart();
            }
        }

        time = clock.getElapsedTime().asSeconds();

        if (time < d)
        {
            float factor = easeInOutSine(time / d);
            position = startPosition * (1 - factor) + targetPosition * factor;
        }

        shape.setPosition(position);

        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}