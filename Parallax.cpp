#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(592, 272), "SFML Template!");
    sf::Texture bg1,bg2,bg3,bg4;
    sf::Vector2f p1, p2, p3, p4;
    float temp;

    p1 = p2 = p3 = p4 = { 0,0 };

    float speed = 100; //at distance 1

    if (bg1.loadFromFile("background_1.png")){}
    if (bg2.loadFromFile("background_2.png")) {}
    if (bg3.loadFromFile("background_3.png")) {}
    if (bg4.loadFromFile("background_4.png")) {}

    sf::Sprite Bg1(bg1);
    sf::Sprite Bg2(bg2);
    sf::Sprite Bg3(bg3);
    sf::Sprite Bg4(bg4);

    sf::Clock clock;
    float dt;
    
    while (window.isOpen())
    {
        dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        p1.x -= speed * dt / 4;
        p1.x = (int)p1.x % 592;

        p2.x -= speed * dt / 3;
        p2.x = (int)p2.x % 592;

        p3.x -= speed * dt / 2;
        p3.x = (int)p3.x % 592;

        p4.x -= speed * dt;
        p4.x = (int)p4.x % 592;

        Bg1.setPosition(p1);
        Bg2.setPosition(p2);
        Bg3.setPosition(p3);
        Bg4.setPosition(p4);

        window.clear();

        window.draw(Bg1);
        temp = (int)(592 * 3 + p1.x) % (592 * 2);
        Bg1.setPosition({ temp,0 });
        window.draw(Bg1);
        window.draw(Bg2);
        temp = (int)(592 * 3 + p2.x) % (592 * 2);
        Bg2.setPosition({ temp,0 });
        window.draw(Bg2);
        window.draw(Bg3);
        temp = (int)(592 * 3 + p3.x) % (592 * 2);
        Bg3.setPosition({ temp,0 });
        window.draw(Bg3);
        window.draw(Bg4);
        temp = (int)(592 * 3 + p4.x) % (592 * 2);
        Bg4.setPosition({ temp,0 } );
        window.draw(Bg4);

        window.display();
    }

    return 0;
}