#include <SFML/Graphics.hpp>

sf::Color operator*(float value, sf::Color color)
{
	return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

template<class T>
T lerp(const T& start, const T& end, float alpha)
{
	if (alpha < 0) return T(start);
	if (alpha > 1) return T(end);

	return (1 - alpha) * start + alpha * end;
}


void updateCurve(sf::VertexArray& curve, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2,sf::Vector2f p3)
{
	int pointsCount = curve.getVertexCount();
	float t = 0;

	float delta = 1.f / (pointsCount - 1);

	for (size_t i = 0; i < pointsCount; i++)
	{
		sf::Vector2f p01 = lerp(p0, p1, t);
		sf::Vector2f p12 = lerp(p1, p2, t);
		sf::Vector2f p23 = lerp(p2, p3, t);

		sf::Vector2f p012 = lerp(p01, p12, t);
		sf::Vector2f p123 = lerp(p12, p23, t);

		curve[i].position = lerp(p012, p123, t);
		curve[i].color = lerp(sf::Color::Cyan, sf::Color::Magenta, t);
		t += delta;
	}
}

class DraggabelPoint {

	sf::CircleShape shape;
	bool isDragging;
public:
	DraggabelPoint(const sf::Vector2f& position)
	{
		shape = sf::CircleShape(10);
		shape.setOrigin(10, 10);
		shape.setPosition(position);
		isDragging = false;
	}

	void beginDrag(const sf::Vector2i& mousePos)
	{
		isDragging = shape.getGlobalBounds().contains((sf::Vector2f)mousePos);
	}

	void drag(const sf::Vector2i& mousePos)
	{
		if (!isDragging) return;
		shape.setPosition((sf::Vector2f)mousePos);
	}

	void endDrag()
	{
		isDragging = false;
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

	DraggabelPoint p0(sf::Vector2f(100, 500));
	DraggabelPoint p1(sf::Vector2f(400, 100));
	DraggabelPoint p2(sf::Vector2f(700, 500));
	DraggabelPoint p3(sf::Vector2f(300, 300));

	sf::VertexArray line(sf::LineStrip, 4);
	sf::VertexArray curve(sf::LineStrip, 30);

	bool moving = false;

	sf::CircleShape shape(20);
	shape.setOrigin(20, 20);
	shape.setFillColor(sf::Color::Transparent);

	sf::Clock clock;
	float Time=5;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.text.unicode == ' ' && !moving)
			{
				shape.setPosition(p0.getPosition());
				moving = true;
				clock.restart();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				p0.beginDrag(sf::Mouse::getPosition(window));
				p1.beginDrag(sf::Mouse::getPosition(window));
				p2.beginDrag(sf::Mouse::getPosition(window));
				p3.beginDrag(sf::Mouse::getPosition(window));
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				p0.endDrag();
				p1.endDrag();
				p2.endDrag();
				p3.endDrag();
			}
		}

		if (moving)
		{
			Time = clock.getElapsedTime().asSeconds();
			sf::Vector2f p01 = lerp(p0.getPosition(), p1.getPosition(), Time);
			sf::Vector2f p12 = lerp(p1.getPosition(), p2.getPosition(), Time);
			sf::Vector2f p23 = lerp(p2.getPosition(), p3.getPosition(), Time);

			sf::Vector2f p012 = lerp(p01, p12, Time);
			sf::Vector2f p123 = lerp(p12, p23, Time);

			shape.setPosition(lerp(p012, p123, Time));
			shape.setFillColor(lerp(sf::Color::Cyan, sf::Color::Magenta, Time));
		}

		if (shape.getPosition() == p3.getPosition())
		{
			moving = false;
			shape.setFillColor(sf::Color::Transparent);
		}

		if (sf::Mouse::isButtonPressed)
		{
			p0.drag(sf::Mouse::getPosition(window));
			p1.drag(sf::Mouse::getPosition(window));
			p2.drag(sf::Mouse::getPosition(window));
			p3.drag(sf::Mouse::getPosition(window));
		}


		line[0].position = p0.getPosition();
		line[1].position = p1.getPosition();
		line[2].position = p2.getPosition();
		line[3].position = p3.getPosition();

		updateCurve(curve, p0.getPosition(), p1.getPosition(), p2.getPosition(),p3.getPosition());


		window.clear();

		window.draw(curve);

		p0.draw(window);
		p1.draw(window);
		p2.draw(window);
		p3.draw(window);

		window.draw(line);

		window.draw(shape);

		window.display();
	}

	return 0;
}