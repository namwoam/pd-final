#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const int PLAYER_SIZE = 10;
const float GRAVITY = 0.1;
const float MANUAL_ACC = 0.3;
const int FUEL_CAPACITY = 500;
const int FUEL_PER_UNIT = 50;
const float FRICTION_CONSTANT = 0.001;
const int COOL_DOWN = 1000;
const int MONEY_UNIT = 25;
const int FUEL_PER_MONEY = 100;

int min(int a, int b);

class Entity
{
public:
	int timer;
	Entity()
	{
		circle.setRadius(PLAYER_SIZE);
		circle.setPosition(250, 10);
		vertStop = 0;
		horStop = 0;
		up = false;
		down = false;
		left = false;
		right = false;
		fuel = FUEL_CAPACITY * FUEL_PER_UNIT;
		speed = Vector2f(0, 0);
		money = 0;
		timer = 0;
	}

	Vector2f getPos()
	{
		Vector2f position(circle.getPosition().x + PLAYER_SIZE, circle.getPosition().y + PLAYER_SIZE);
		return position;
	}

	void setPos(int x, int y)
	{
		circle.setPosition(x - PLAYER_SIZE, y - PLAYER_SIZE);
	}

	void processEvents(Keyboard::Key key, bool checkPressed)
	{
		if (checkPressed == true && fuel > 0)
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

		speed.x -= horStop;
		speed.y += vertStop;

		// see example at https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
		circle.move(speed * elapsed.asSeconds());

		speed.x += horStop;
		speed.y -= vertStop;

		horStop = 0;
		vertStop = 0;

		// add friction see https://www.softschools.com/formulas/physics/air_resistance_formula/85/
		speed.x -= (speed.x > 0 ? 1 : -1) * FRICTION_CONSTANT * speed.x * speed.x * elapsed.asSeconds();
		speed.y -= (speed.y > 0 ? 1 : -1) * FRICTION_CONSTANT * speed.y * speed.y * elapsed.asSeconds();
	}

	void updateDisplay(RenderWindow& window)
	{
		if ((up || down || left || right) && fuel > 0)
			fuel--;

		window.draw(circle);
		Text moneyDisplay, fuelDisplay;
		Font spaceFont;
		// spaceFont.loadFromFile("SpaceGrotesk-Regular.ttf");
		spaceFont.loadFromFile("C:/Windows/Fonts/arial.ttf");
		// no default font QQ https://en.sfml-dev.org/forums/index.php?topic=8752.0
		std::string moneyText = "$: ";
		moneyText += std::to_string(money / MONEY_UNIT);
		std::string fuelText = "Fuel: ";
		fuelText += (std::to_string(fuel / FUEL_PER_UNIT) + std::string(1, '/') + std::to_string(FUEL_CAPACITY));
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

	void xStop(bool positive)
	{
		speed.x = 0;
		if (positive)
			horStop = 10;
		else
			horStop = -10;
	}

	void yStop(bool positive)
	{
		speed.y = 0;
		if (positive)
			vertStop = 10;
		else
			vertStop = -10;
	}

	void addFuel()
	{
		if (fuel == FUEL_CAPACITY * FUEL_PER_UNIT || money == 0)
			return;
		if (money > 0) // to be finished
		{
			if (money % MONEY_UNIT == 0)
				fuel += min(FUEL_PER_MONEY * FUEL_PER_UNIT, FUEL_CAPACITY * FUEL_PER_UNIT - fuel);
			money--;
			if (money < MONEY_UNIT)
				money = 0;
		}
	}

	void earn()
	{
		if (timer == 0)
		{
			money += MONEY_UNIT;
			timer = COOL_DOWN;
		}
	}

private:
	CircleShape circle;
	int vertStop;
	int horStop;
	bool up;
	bool down;
	bool left;
	bool right;
	int fuel;
	int money;
	Vector2f speed;
};

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}
