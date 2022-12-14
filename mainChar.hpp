#include "Platform/Platform.hpp"
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
using namespace sf;

class Entity
{
public:
	Entity(float r)
	{
		circle.setRadius(r);
		up = false;
		down = false;
		left = false;
		right = false;
	}

	void processEvents(Keyboard::Key key, bool checkPressed)
	{
		if (checkPressed == true)
		{
			if (key == Keyboard::W)
			{
				down = true;
			}
			if (key == Keyboard::A)
			{
				right = true;
			}
			if (key == Keyboard::S)
			{
				up = true;
			}
			if (key == Keyboard::D)
			{
				left = true;
			}
		}
		else
		{
			if (key == Keyboard::W)
			{
				down = false;
			}
			if (key == Keyboard::A)
			{
				right = false;
			}
			if (key == Keyboard::S)
			{
				up = false;
			}
			if (key == Keyboard::D)
			{
				left = false;
			}
		}
	}

	Vector2f update(Vector2f speed)
	{
		Vector2f acc(0, 0.0000025);
		if (up)
			acc.y -= 0.000005;
		if (down)
			acc.y += 0.000005;
		if (left)
			acc.x -= 0.000005;
		if (right)
			acc.x += 0.000005;
		speed.x += acc.x;
		speed.y += acc.y;
		circle.move(speed);
		if (abs(speed.x))
			speed.x *= 0.9999;
		if (abs(speed.x) < 0.000003)
			speed.x = 0;
		return speed;
	}

	void drawTo(RenderWindow& window)
	{
		window.draw(circle);
	}

private:
	CircleShape circle;
	bool up;
	bool down;
	bool left;
	bool right;
};