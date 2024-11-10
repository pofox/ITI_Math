#include <SFML/Graphics.hpp>

template<class T>
T lerp(const T& start, const T& end, float alpha)
{
	if (alpha < 0) return T(start);
	if (alpha > 1) return T(end);

	return (1 - alpha) * start + alpha * end;
}

class Point {

	sf::CircleShape shape;
public:
	Point(const sf::Vector2f& position)
	{
		shape = sf::CircleShape(10);
		shape.setOrigin(10, 10);
		shape.setPosition(position);
	}

	void drag(const sf::Vector2i& mousePos)
	{
		shape.setPosition(lerp(shape.getPosition(), (sf::Vector2f)mousePos, 0.02));
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	sf::Vector2f getPosition()
	{
		return shape.getPosition();
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");

	Point p0(sf::Vector2f(100, 500));
	Point p1(sf::Vector2f(400, 100));
	Point p2(sf::Vector2f(700, 500));
	Point p3({ 0,0 });
	Point p4({ 0,0 });

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (sf::Mouse::isButtonPressed)
		{
			p0.drag(sf::Mouse::getPosition(window));
			p1.drag((sf::Vector2i)p0.getPosition());
			p2.drag((sf::Vector2i)p1.getPosition());
			p3.drag((sf::Vector2i)p2.getPosition());
			p4.drag((sf::Vector2i)p3.getPosition());
		}

		window.clear();

		p0.draw(window);
		p1.draw(window);
		p2.draw(window);
		p3.draw(window);
		p4.draw(window);

		window.display();
	}

	return 0;
}