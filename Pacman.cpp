#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>

void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle)
{
    int pointCount = shape.getPointCount();
    for (int i = 0; i < pointCount-1; i++)
    {
        shape.setPoint(i, sf::Vector2f(center.x + radius * cos(i * (endAngle - startAngle) / (pointCount -2) + startAngle), center.y + radius * sin(i * (endAngle - startAngle) / (pointCount - 2) + startAngle)));
    }
    shape.setPoint(pointCount-1, center);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");
    sf::ConvexShape shape(20);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    float time;

    float offset = 0;
    
    while (window.isOpen())
    {
        time = clock.getElapsedTime().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) offset=-M_PI/2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) offset=M_PI/2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) offset=M_PI;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) offset=0;

        updateArc(shape, sf::Vector2f(400, 300), 100, (sin(5*time)+1)*M_PI/12+offset, M_PI * 11 / 6+(1-sin(5*time))*M_PI/12+offset);

        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}