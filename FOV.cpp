#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>

float dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle)
{
	int pointCount = shape.getPointCount();
	for (int i = 0; i < pointCount - 1; i++)
	{
		shape.setPoint(i, sf::Vector2f(center.x + radius * cos(i * (endAngle - startAngle) / (pointCount - 2) + startAngle), center.y + radius * sin(i * (endAngle - startAngle) / (pointCount - 2) + startAngle)));
	}
	shape.setPoint(pointCount - 1, center);
}

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


void updateCurve(sf::VertexArray& curve, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2)
{
	int pointsCount = curve.getVertexCount();
	float t = 0;

	float delta = 1.f / (pointsCount - 1);

	for (size_t i = 0; i < pointsCount; i++)
	{
		sf::Vector2f p01 = lerp(p0, p1, t);
		sf::Vector2f p12 = lerp(p1, p2, t);

		curve[i].position = lerp(p01, p12, t);
		curve[i].color = lerp(sf::Color::Cyan, sf::Color::Magenta, t);
		t += delta;
	}
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");

	sf::CircleShape A(20);
	sf::CircleShape B(20);

	A.setOrigin(20, 20);
	B.setOrigin(20, 20);

	A.setFillColor(sf::Color::Black);
	B.setFillColor(sf::Color::Cyan);

	A.setPosition(400, 300);
	B.setPosition(600, 200);

	sf::ConvexShape FOV(20);
	FOV.setFillColor(sf::Color::Green);

	sf::Vector2f pos(600,200);

	sf::Clock clock;
	float dt;

	float speed = 200;

	float r = 100;

	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) pos.y -= speed * dt;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) pos.y += speed * dt;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) pos.x += speed * dt;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) pos.x -= speed * dt;

		B.setPosition(pos);
		
		sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

		float mangle = atan2(mouse.y - pos.y, mouse.x - pos.x);

		float fangle = M_PI / 6;

		updateArc(FOV, B.getPosition(), r, mangle - fangle, mangle + fangle);

		float distance2 = pow(A.getPosition().x - pos.x, 2) + pow(A.getPosition().y - pos.y, 2);
		
		sf::Vector2f dir1 = mouse - pos;
		dir1 /= sqrt(dot(dir1, dir1));

		sf::Vector2f dir2 = A.getPosition() - pos;
		dir2 /= sqrt(dot(dir2, dir2));

		float tangle = acos(dot(dir1, dir2));
		
		if (distance2 < pow(r+B.getRadius(),2) && tangle<fangle)
		{
			FOV.setFillColor(sf::Color::Red);
		}
		else {
			FOV.setFillColor(sf::Color::Green);
		}

		window.clear(sf::Color::White);

		window.draw(A);
		window.draw(FOV);
		window.draw(B);

		window.display();
	}

	return 0;
}