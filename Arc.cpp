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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        updateArc(shape, sf::Vector2f(400, 300), 100, -M_PI / 4, M_PI / 4);

        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}
