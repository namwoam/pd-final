#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int collidesWithRest(Image image, int x, int y);
int collidesWithWall(Image image, int x, int y);
int collidesWithTrans(Image image, int x, int y);
int collidesWithFinish(Image image, int x, int y);
bool collidesWithCoin(Image &image, int x, int y);

int main()
{

	RenderWindow window(VideoMode(900, 900), "PD Final", Style::Titlebar | Style::Close);

	Texture topLeft, topRight, bottomLeft, bottomRight;
	topLeft.loadFromFile("topLeft.png");
	topRight.loadFromFile("topRight.png");
	bottomLeft.loadFromFile("bottomLeft.png");
	bottomRight.loadFromFile("bottomRight.png");

	Sprite *map[4];
	map[0] = new Sprite(topLeft);
	map[1] = new Sprite(topRight);
	map[2] = new Sprite(bottomLeft);
	map[3] = new Sprite(bottomRight);

	Image imgMap[4];
	imgMap[0].loadFromFile("topLeft.png");
	imgMap[1].loadFromFile("topRight.png");
	imgMap[2].loadFromFile("bottomLeft.png");
	imgMap[3].loadFromFile("bottomRight.png");

	Event event;

	Entity player;
	Clock clock;

	int curBg = 0;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				player.processEvents(event.key.code, true);
			}
			if (event.type == Event::KeyReleased)
				player.processEvents(event.key.code, false);
		}

		window.clear();
		window.draw(*map[curBg]);
		Time elapsed = clock.restart();
		player.updateMotion(elapsed);

		switch (collidesWithRest(imgMap[curBg], player.getPos().x, player.getPos().y))
		{
		case 0:
			break;

		case 1:
			player.yStop(false);
			player.addFuel();
			break;

		case 2:
			player.yStop(true);
			break;

		case 3:
			player.xStop(false);
			break;

		case 4:
			player.xStop(true);
			break;

		default:
			break;
		}

		switch (collidesWithWall(imgMap[curBg], player.getPos().x, player.getPos().y))
		{
		case 0:
			break;

		case 1:
			player.yStop(false);
			player.damage();
			break;

		case 2:
			player.yStop(true);
			player.damage();
			break;

		case 3:
			player.xStop(false);
			player.damage();
			break;

		case 4:
			player.xStop(true);
			player.damage();
			break;

		default:
			break;
		}

		switch (collidesWithTrans(imgMap[curBg], player.getPos().x, player.getPos().y))
		{
		case 0:
			break;

		case 1:
			curBg += 2;
			player.setPos(player.getPos().x, player.getPos().y - 840);
			break;

		case 2:
			curBg -= 2;
			player.setPos(player.getPos().x, player.getPos().y + 840);
			break;

		case 3:
			// shift x-coordinate to the right
			curBg -= 1;
			player.setPos(player.getPos().x + 840, player.getPos().y);
			break;

		case 4:
			// shift x-coordinate to the left
			curBg += 1;
			player.setPos(player.getPos().x - 840, player.getPos().y);
			break;

		default:
			break;
		}

		if (collidesWithCoin(imgMap[curBg], player.getPos().x, player.getPos().y))
		{
			player.earn();
		}

		switch (collidesWithFinish(imgMap[curBg], player.getPos().x, player.getPos().y))
		{
		case 0:
			break;

		case 1:
			player.yStop(true);
			break;

		case 2:
			player.end();
			break;

		default:
			break;
		}
		topLeft.loadFromImage(imgMap[0]);
		topRight.loadFromImage(imgMap[1]);
		bottomLeft.loadFromImage(imgMap[2]);
		bottomRight.loadFromImage(imgMap[3]);
		map[0] = new Sprite(topLeft);
		map[1] = new Sprite(topRight);
		map[2] = new Sprite(bottomLeft);
		map[3] = new Sprite(bottomRight);
		player.updateDisplay(window);
		window.display();
	}

	return 0;
}

int collidesWithRest(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 180 && backGround.getPixel(x, y + PLAYER_SIZE).g < 180 && backGround.getPixel(x, y + PLAYER_SIZE).b < 150)
		return 1;

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 180 && backGround.getPixel(x, y - PLAYER_SIZE).g < 180 && backGround.getPixel(x, y - PLAYER_SIZE).b < 150)
		return 2;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 180 && backGround.getPixel(x - PLAYER_SIZE, y).g < 180 && backGround.getPixel(x - PLAYER_SIZE, y).b < 150)
		return 3;

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 180 && backGround.getPixel(x + PLAYER_SIZE, y).g < 180 && backGround.getPixel(x + PLAYER_SIZE, y).b < 150)
		return 4;

	return 0;
}

int collidesWithWall(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 220 && backGround.getPixel(x, y + PLAYER_SIZE).g > 220 && backGround.getPixel(x, y + PLAYER_SIZE).b > 220)
		return 1;

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 220 && backGround.getPixel(x, y - PLAYER_SIZE).g > 220 && backGround.getPixel(x, y - PLAYER_SIZE).b > 220)
		return 2;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 220 && backGround.getPixel(x - PLAYER_SIZE, y).g > 220 && backGround.getPixel(x - PLAYER_SIZE, y).b > 220)
		return 3;

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 220 && backGround.getPixel(x + PLAYER_SIZE, y).g > 220 && backGround.getPixel(x + PLAYER_SIZE, y).b > 220)
		return 4;

	return 0;
}

int collidesWithTrans(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 150 && backGround.getPixel(x, y + PLAYER_SIZE).r < 190 && backGround.getPixel(x, y + PLAYER_SIZE).g > 200 && backGround.getPixel(x, y + PLAYER_SIZE).b > 160 && backGround.getPixel(x, y + PLAYER_SIZE).b < 210)
		return 1;

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 150 && backGround.getPixel(x, y - PLAYER_SIZE).r < 190 && backGround.getPixel(x, y - PLAYER_SIZE).g > 200 && backGround.getPixel(x, y - PLAYER_SIZE).b > 160 && backGround.getPixel(x, y - PLAYER_SIZE).b < 210)
		return 2;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 150 && backGround.getPixel(x - PLAYER_SIZE, y).r < 190 && backGround.getPixel(x - PLAYER_SIZE, y).g > 200 && backGround.getPixel(x - PLAYER_SIZE, y).b > 160 && backGround.getPixel(x - PLAYER_SIZE, y).b < 210)
		return 3;

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 150 && backGround.getPixel(x + PLAYER_SIZE, y).r < 190 && backGround.getPixel(x + PLAYER_SIZE, y).g > 200 && backGround.getPixel(x + PLAYER_SIZE, y).b > 160 && backGround.getPixel(x + PLAYER_SIZE, y).b < 210)
		return 4;

	return 0;
}

int collidesWithFinish(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 215 && backGround.getPixel(x, y - PLAYER_SIZE).r < 235 && backGround.getPixel(x, y - PLAYER_SIZE).g > 150 && backGround.getPixel(x, y - PLAYER_SIZE).g < 180 && backGround.getPixel(x, y - PLAYER_SIZE).b > 230 && backGround.getPixel(x, y - PLAYER_SIZE).b < 255)
		return 1;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 215 && backGround.getPixel(x - PLAYER_SIZE, y).r < 235 && backGround.getPixel(x - PLAYER_SIZE, y).g > 150 && backGround.getPixel(x - PLAYER_SIZE, y).g < 180 && backGround.getPixel(x - PLAYER_SIZE, y).b > 230 && backGround.getPixel(x - PLAYER_SIZE, y).b < 255)
		return 2;
	return 0;
}

bool isCoinColor(Color c)
{
	if (c.r > 220 && c.g > 180 && c.b < 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void clearCoin(Image &backGround, int x, int y)
{
	if (isCoinColor(backGround.getPixel(x, y)))
	{
		backGround.setPixel(x, y, Color::Black);
		// std::cout << "found coin pixel at " << x << ' ' << y << std::endl;
		int interval = 5;
		for (int i = -interval; i <= interval; i++)
		{
			for (int k = -interval; k <= interval; k++)
			{
				if (i == 0 && k == 0)
				{
					continue;
				}
				clearCoin(backGround, x + i, y + k);
			}
		}
		return;
	}
	return;
}

bool collidesWithCoin(Image &backGround, int x, int y)
{
	bool flag = false;
	auto coinPos = Vector2i();
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 220 && backGround.getPixel(x, y + PLAYER_SIZE).g > 180 && backGround.getPixel(x, y + PLAYER_SIZE).b < 50)
	{
		flag = true;
		coinPos.x = x;
		coinPos.y = y + PLAYER_SIZE;
	}

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 220 && backGround.getPixel(x, y - PLAYER_SIZE).g > 180 && backGround.getPixel(x, y - PLAYER_SIZE).b < 50)
	{
		flag = true;
		coinPos.x = x;
		coinPos.y = y - PLAYER_SIZE;
	}

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 220 && backGround.getPixel(x - PLAYER_SIZE, y).g > 180 && backGround.getPixel(x - PLAYER_SIZE, y).b < 50)
	{
		flag = true;
		coinPos.x = x - PLAYER_SIZE;
		coinPos.y = y;
	}

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 220 && backGround.getPixel(x + PLAYER_SIZE, y).g > 180 && backGround.getPixel(x + PLAYER_SIZE, y).b < 50)
	{
		flag = true;
		coinPos.x = x + PLAYER_SIZE;
		coinPos.y = y;
	}
	if (flag == true)
	{
		clearCoin(backGround, coinPos.x, coinPos.y);
	}
	return flag;
}
