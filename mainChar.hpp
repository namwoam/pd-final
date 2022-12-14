#include "Platform/Platform.hpp"
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
using namespace sf;

const int Gravity = 0.0000025;
const int manualAcc = 0.000005;
const int trivialSpeed = 0.000003;

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
		// default y-acceleration is the gravity
		Vector2f acc(0, Gravity);

		// add additional acceleration to acc
		if (up)
			acc.y -= manualAcc;
		if (down)
			acc.y += manualAcc;
		if (left)
			acc.x -= manualAcc;
		if (right)
			acc.x += manualAcc;

		// alter the speed and then move
		speed.x += acc.x;
		speed.y += acc.y;

		circle.move(speed);

		// forms a horizontal drag to prevent player from moving infinitely
		if (abs(speed.x))
			speed.x *= 0.9999;

		// stop horizontal movement entirely if the horizontal speed is small
		// enough
		if (abs(speed.x) < trivialSpeed)
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
