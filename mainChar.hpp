#include <SFML/Graphics.hpp>
using namespace sf;

const float Gravity = 0.07;
const float manualAcc = 0.2;
// trivial horizontal speed that can be omitted
const int cells = 5;
const int fuelPerCell = 150;
const float frictionConstant = 0.001;

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
		fuel = cells * fuelPerCell;
	}

	void processEvents(Keyboard::Key key, bool checkPressed)
	{
		if (checkPressed == true)
		{
			fuel -= 1;
			std::cout << fuel << " ";
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

	Vector2f update(Vector2f speed , Time elapsed)
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

		circle.move(speed*elapsed.asSeconds());
		// see example at https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
		
		// add friction see https://www.softschools.com/formulas/physics/air_resistance_formula/85/
		speed.x -= (speed.x>0?1:-1)*frictionConstant * speed.x * speed.x * elapsed.asSeconds();
		speed.y -= (speed.y>0?1:-1)*frictionConstant * speed.y * speed.y *elapsed.asSeconds();



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
	int fuel;
};
