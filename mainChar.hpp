#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
const float Gravity = 0.1;
const float manualAcc = 0.3;
const int fuelCapacity = 200;
const float frictionConstant = 0.001;
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
		fuel = fuelCapacity;
		speed = Vector2f(0, 0);
		money = 0;
	}

	void processEvents(Keyboard::Key key, bool checkPressed)
	{
		if (checkPressed == true)
		{
			if (fuel<=0){
				return;
			}
			fuel -= 1;
			std::cout << fuel <<std::endl;
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
	}

	void updateDisplay(RenderWindow& window)
	{
		window.draw(circle);
		Text moneyDisplay , fuelDisplay;
		Font spaceFont;
		spaceFont.loadFromFile("SpaceGrotesk-Regular.ttf");
		// no default font QQ https://en.sfml-dev.org/forums/index.php?topic=8752.0
		std::string moneyText = "$: ";
		moneyText += std::to_string(money);
		std::string fuelText = "Fuel: ";
		fuelText += (std::to_string(fuel) + std::string (1 , '/') + std::to_string(fuelCapacity));
		moneyDisplay.setString(moneyText.c_str());
		moneyDisplay.setFont(spaceFont);
		moneyDisplay.setCharacterSize(32);
		moneyDisplay.setFillColor(Color::White);
		moneyDisplay.setPosition(Vector2f(5 , 5));
		fuelDisplay.setString(fuelText.c_str());
		fuelDisplay.setFont(spaceFont);
		fuelDisplay.setCharacterSize(32);
		fuelDisplay.setFillColor(Color::White);
		fuelDisplay.setPosition(Vector2f(100 , 5));
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
