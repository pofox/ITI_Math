#include <SFML/Graphics.hpp>
#include <cmath>

sf::Color operator*(float value, sf::Color color)
{
	return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

float dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
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

void reflect(sf::VertexArray shape1, sf::VertexArray& shape2, sf::VertexArray line)
{
	int pointCount = (shape1.getVertexCount() >= shape2.getVertexCount()) ? shape2.getVertexCount() : shape1.getVertexCount();
	sf::Vector2f lineDir = line[1].position - line[0].position;
	lineDir /= sqrt(dot(lineDir, lineDir));
	for (int i = 0; i < pointCount; i++)
	{
		//v=s1[i]-l[0]
		//u=l[1]-l[0]
		//vl=(v.u)u
		//vp=v-vl
		//s2[1]=l[0]+vl-vp  //l[0]+(v.u)u-v+(v.u)u //l[0]+2(v.u)u-v
		sf::Vector2f v = shape1[i].position - line[0].position;
		shape2[i].position = line[0].position + 2 * dot(v, lineDir) * lineDir - v;
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

	void setColor(sf::Color color)
	{
		shape.setFillColor(color);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");

	DraggabelPoint p0(sf::Vector2f(100, 200));
	DraggabelPoint p1(sf::Vector2f(200, 100));
	DraggabelPoint p2(sf::Vector2f(200, 300));

	DraggabelPoint p3(sf::Vector2f(400, 100));
	DraggabelPoint p4(sf::Vector2f(400, 500));

	p3.setColor(sf::Color::Cyan);
	p4.setColor(sf::Color::Cyan);

	sf::VertexArray line(sf::LineStrip, 4);
	sf::VertexArray line2(sf::LineStrip, 2);
	line2[0].color = sf::Color::Cyan;
	line2[1].color = sf::Color::Cyan;
	sf::VertexArray tri(sf::Triangles, 3);
	tri[0].color = sf::Color::Red;
	tri[1].color = sf::Color::Green;
	tri[2].color = sf::Color::Blue;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				p0.beginDrag(sf::Mouse::getPosition(window));
				p1.beginDrag(sf::Mouse::getPosition(window));
				p2.beginDrag(sf::Mouse::getPosition(window));
				p3.beginDrag(sf::Mouse::getPosition(window));
				p4.beginDrag(sf::Mouse::getPosition(window));
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				p0.endDrag();
				p1.endDrag();
				p2.endDrag();
				p3.endDrag();
				p4.endDrag();
			}
		}


		if (sf::Mouse::isButtonPressed)
		{
			p0.drag(sf::Mouse::getPosition(window));
			p1.drag(sf::Mouse::getPosition(window));
			p2.drag(sf::Mouse::getPosition(window));
			p3.drag(sf::Mouse::getPosition(window));
			p4.drag(sf::Mouse::getPosition(window));
		}


		line[0].position = p0.getPosition();
		line[1].position = p1.getPosition();
		line[2].position = p2.getPosition();
		line[3].position = p0.getPosition();

		line2[0].position = p3.getPosition();
		line2[1].position = p4.getPosition();

		reflect(line, tri, line2);

		window.clear();

		window.draw(tri);

		p3.draw(window);
		p4.draw(window);

		window.draw(line2);

		p0.draw(window);
		p1.draw(window);
		p2.draw(window);

		window.draw(line);

		window.display();
	}

	return 0;
}