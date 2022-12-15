#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const int PLAYER_SIZE = 10;
const float GRAVITY = 0.1;
const float MANUAL_ACC = 0.3;
const int FUEL_CAPACITY = 200;
const float FRICTION_CONSTANT = 0.001;

class Entity
{
public:
	Entity()
	{
		circle.setRadius(PLAYER_SIZE);
		circle.setPosition(150, 10);
		up = false;
		down = false;
		left = false;
		right = false;
		fuel = FUEL_CAPACITY;
		speed = Vector2f(0, 0);
		money = 0;
	}

	Vector2f getPos()
	{
		Vector2f position(circle.getPosition().x, circle.getPosition().y);
		return position;
	}

	void processEvents(Keyboard::Key key, bool checkPressed)
	{
		if (checkPressed == true && fuel > 0)
		{
			fuel -= 1;
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

	void updateMotion(Time elapsed)
	{
		// default y-acceleration is the gravity
		Vector2f acc(0, GRAVITY);

		// add additional acceleration to acc
		if (up)
			acc.y -= MANUAL_ACC;
		if (down)
			acc.y += MANUAL_ACC;
		if (left)
			acc.x -= MANUAL_ACC;
		if (right)
			acc.x += MANUAL_ACC;

		// alter the speed and then move
		speed.x += acc.x;
		speed.y += acc.y;

		circle.move(speed * elapsed.asSeconds());
		// see example at https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php

		// add friction see https://www.softschools.com/formulas/physics/air_resistance_formula/85/
		speed.x -= (speed.x > 0 ? 1 : -1) * FRICTION_CONSTANT * speed.x * speed.x * elapsed.asSeconds();
		speed.y -= (speed.y > 0 ? 1 : -1) * FRICTION_CONSTANT * speed.y * speed.y * elapsed.asSeconds();
	}

	void updateDisplay(RenderWindow& window)
	{
		window.draw(circle);
		Text moneyDisplay, fuelDisplay;
		Font spaceFont;
		// spaceFont.loadFromFile("SpaceGrotesk-Regular.ttf");
		spaceFont.loadFromFile("C:/Windows/Fonts/arial.ttf");
		// no default font QQ https://en.sfml-dev.org/forums/index.php?topic=8752.0
		std::string moneyText = "$: ";
		moneyText += std::to_string(money);
		std::string fuelText = "Fuel: ";
		fuelText += (std::to_string(fuel) + std::string(1, '/') + std::to_string(FUEL_CAPACITY));
		moneyDisplay.setString(moneyText.c_str());
		moneyDisplay.setFont(spaceFont);
		moneyDisplay.setCharacterSize(32);
		moneyDisplay.setFillColor(Color::White);
		moneyDisplay.setPosition(Vector2f(5, 5));
		fuelDisplay.setString(fuelText.c_str());
		fuelDisplay.setFont(spaceFont);
		fuelDisplay.setCharacterSize(32);
		fuelDisplay.setFillColor(Color::White);
		fuelDisplay.setPosition(Vector2f(100, 5));
		window.draw(moneyDisplay);
		window.draw(fuelDisplay);
	}

private:
	CircleShape circle;
	bool up;
	bool down;
	bool left;
	bool right;
	int fuel;
	int money;
	Vector2f speed;
};
