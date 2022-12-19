#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

const int PLAYER_SIZE = 10;
const float GRAVITY = 0.1;
const float MANUAL_ACC = 0.3;
const int FUEL_CAPACITY = 4;
const int FUEL_PER_UNIT = 50; // effects how fast fuel consumes
const float FRICTION_CONSTANT = 0.001;
const int COIN_COOL_DOWN = 1000; // effects how often a player can gain a coin
const int DMG_COOL_DOWN = 250;	 // effects the invincible time after taking damage
const int MONEY_UNIT = 25;		 // effects the frequency of adding fuel
const int FUEL_PER_MONEY = 50;	 // effects how much fuel a player gains through one coin
const float HURT_EFFECT = 0.3;

int min(int a, int b);
float linearTransformation(float startVal, float endVal, float startPos, float endPos, float currentPos);

class Entity
{
public:
	Entity()
	{
		circle.setRadius(PLAYER_SIZE);
		circle.setPosition(250, 300);
		haveBeenReset = true;
		vertStop = 0;
		horStop = 0;
		stop = true;
		up = false;
		down = false;
		left = false;
		right = false;
		fuel = FUEL_CAPACITY * FUEL_PER_UNIT;
		speed = Vector2f(0, 0);
		money = 0;
		coinTimer = 0;
		dmgTimer = 0;
		hurtTime = 0;
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
		if (stop)
			return;
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
		if (stop)
			return;

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

		if (hurtTime < 1000)
		{
			hurtTime += elapsed.asSeconds();
		}
		if (hurtTime > HURT_EFFECT)
		{
			hurtTime = 2000;
			circle.setFillColor(Color::White);
		}
		else
		{
			float r = linearTransformation(Color::Red.r, Color::White.r, 0, HURT_EFFECT, hurtTime);
			float g = linearTransformation(Color::Red.g, Color::White.g, 0, HURT_EFFECT, hurtTime);
			float b = linearTransformation(Color::Red.b, Color::White.b, 0, HURT_EFFECT, hurtTime);
			//std::cout << r << ' ' << g << ' ' << b << std::endl;
			auto currentColor = Color(r, g, b, 255);
			circle.setFillColor(currentColor);
		}
	}

	void updateDisplay(RenderWindow& window)
	{
		if (stop)
			return;

		if ((up || down || left || right) && fuel > 0)
			fuel--;

		if (coinTimer > 0)
			coinTimer--;

		if (dmgTimer > 0)
			dmgTimer--;

		window.draw(circle);
		Text moneyDisplay, fuelDisplay;
		Font spaceFont;
		spaceFont.loadFromFile("SpaceGrotesk-Regular.ttf");
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
		if (coinTimer == 0)
		{
			money += MONEY_UNIT;
			coinTimer = COIN_COOL_DOWN;
		}
	}

	void damage()
	{
		if (dmgTimer == 0 && fuel > 0)
		{
			fuel -= min(25 * FUEL_PER_UNIT, fuel);
			dmgTimer = DMG_COOL_DOWN;
			circle.setFillColor(Color::Red);
			hurtTime = 0;
		}
	}

	void begin()
	{
		stop = false;
	}

	void reset()
	{
		circle.setPosition(250, 300);
		vertStop = 0;
		horStop = 0;
		up = false;
		down = false;
		left = false;
		right = false;
		fuel = FUEL_CAPACITY * FUEL_PER_UNIT;
		speed = Vector2f(0, 0);
		money = 0;
		coinTimer = 0;
		dmgTimer = 0;
		hurtTime = 0;
		haveBeenReset = true;
	}

	void end()
	{
		stop = true;
		speed.x = 0;
		speed.y = 0;
		up = false;
		down = false;
		left = false;
		right = false;
		haveBeenReset = false;
	}

	bool empty()
	{
		return !fuel;
	}

	bool available()
	{
		return haveBeenReset;
	}

private:
	CircleShape circle;
	int vertStop;
	int horStop;
	bool stop;
	bool up;
	bool down;
	bool left;
	bool right;
	int fuel;
	int money;
	int coinTimer;
	int dmgTimer;
	Vector2f speed;
	float hurtTime;
	bool haveBeenReset;
};

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

float linearTransformation(float startVal, float endVal, float startPos, float endPos, float currentPos)
{
	return startVal + (endVal - startVal) * ((currentPos - startPos) / (endPos - startPos));
}
