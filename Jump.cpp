#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");
    sf::CircleShape shape(20);
    shape.setOrigin(20, 20);
    shape.setFillColor(sf::Color::Green);


    sf::Vector2f position(400, 500);


    sf::Clock clock;
    float time;

    bool jumping = false;

    float d = 1;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == ' ' && time>d)
                {
                    jumping = true;
                    clock.restart();
                }
            }
        }

        time = clock.getElapsedTime().asSeconds();

        //y=ax^2+bx+c
        //y(0)=0,y(1)=0
        //c=0,a=-b
        //y=a(x^2-x)
        //y(0.5)=h
        //a=-4h
        //y=4hx(1-x)

        if (time < d && jumping)
        {
            position.y = 500 - 4 * 100 * time * (1 - time);
        }
        else {
            jumping = false;
        }

        shape.setPosition(position);

        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}