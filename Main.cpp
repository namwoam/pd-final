#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int collidesWithRest(Image image, int x, int y);
int collidesWithWall(Image image, int x, int y);
int collidesWithTrans(Image image, int x, int y);
bool collidesWithCoin(Image image, int x, int y);

int main()
{

	RenderWindow window(VideoMode(900, 900), "PD Final", Style::Titlebar | Style::Close);

	Texture topLeft, topRight, bottomLeft, bottomRight;
	topLeft.loadFromFile("C:/Users/olaba/Downloads/topLeft.png");
	topRight.loadFromFile("C:/Users/olaba/Downloads/topRight.png");
	bottomLeft.loadFromFile("C:/Users/olaba/Downloads/bottomLeft.png");
	bottomRight.loadFromFile("C:/Users/olaba/Downloads/bottomRight.png");

	Sprite* map[4];
	map[0] = new Sprite(topLeft);
	map[1] = new Sprite(topRight);
	map[2] = new Sprite(bottomLeft);
	map[3] = new Sprite(bottomRight);

	Image imgMap[4];
	imgMap[0].loadFromFile("C:/Users/olaba/Downloads/topLeft.png");
	imgMap[1].loadFromFile("C:/Users/olaba/Downloads/topRight.png");
	imgMap[2].loadFromFile("C:/Users/olaba/Downloads/bottomLeft.png");
	imgMap[3].loadFromFile("C:/Users/olaba/Downloads/bottomRight.png");

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

		if (player.timer > 0)
			player.timer--;

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

		switch (collidesWithTrans(imgMap[curBg], player.getPos().x, player.getPos().y))
		{
			case 0:
				break;

			case 1:
				player.yStop(false); // should be removed

				// shift y-coordinate to the top

				break;

			case 2:
				player.yStop(true); // should be removed

				// shift y - coordinate to the bottom

				break;

			case 3:
				player.xStop(false); // should be removed

				// shift x-coordinate to the right

				break;

			case 4:
				player.xStop(true); // should be removed

				// shift x-coordinate to the left

				break;

			default:
				break;
		}

		if (collidesWithCoin(imgMap[curBg], player.getPos().x, player.getPos().y)) // might need a cooler
		{
			player.earn();
		}

		player.updateDisplay(window);
		window.display();
	}

	return 0;
}

int collidesWithRest(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 180
		&& backGround.getPixel(x, y + PLAYER_SIZE).g < 180
		&& backGround.getPixel(x, y + PLAYER_SIZE).b < 150)
		return 1;

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 180
		&& backGround.getPixel(x, y - PLAYER_SIZE).g < 180
		&& backGround.getPixel(x, y - PLAYER_SIZE).b < 150)
		return 2;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 180
		&& backGround.getPixel(x - PLAYER_SIZE, y).g < 180
		&& backGround.getPixel(x - PLAYER_SIZE, y).b < 150)
		return 3;

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 180
		&& backGround.getPixel(x + PLAYER_SIZE, y).g < 180
		&& backGround.getPixel(x + PLAYER_SIZE, y).b < 150)
		return 4;

	return 0;
}

int collidesWithWall(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 220
		&& backGround.getPixel(x, y + PLAYER_SIZE).g > 220
		&& backGround.getPixel(x, y + PLAYER_SIZE).b > 220)
		return 1;

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 220
		&& backGround.getPixel(x, y - PLAYER_SIZE).g > 220
		&& backGround.getPixel(x, y - PLAYER_SIZE).b > 220)
		return 2;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 220
		&& backGround.getPixel(x - PLAYER_SIZE, y).g > 220
		&& backGround.getPixel(x - PLAYER_SIZE, y).b > 220)
		return 3;

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 220
		&& backGround.getPixel(x + PLAYER_SIZE, y).g > 220
		&& backGround.getPixel(x + PLAYER_SIZE, y).b > 220)
		return 4;

	return 0;
}

int collidesWithTrans(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 150
		&& backGround.getPixel(x, y + PLAYER_SIZE).g > 200
		&& backGround.getPixel(x, y + PLAYER_SIZE).b > 160)
		return 1;

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 150
		&& backGround.getPixel(x, y - PLAYER_SIZE).g > 200
		&& backGround.getPixel(x, y - PLAYER_SIZE).b > 160)
		return 2;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 150
		&& backGround.getPixel(x - PLAYER_SIZE, y).g > 200
		&& backGround.getPixel(x - PLAYER_SIZE, y).b > 160)
		return 3;

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 150
		&& backGround.getPixel(x + PLAYER_SIZE, y).g > 200
		&& backGround.getPixel(x + PLAYER_SIZE, y).b > 160)
		return 4;

	return 0;
}

bool collidesWithCoin(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 220
		&& backGround.getPixel(x, y + PLAYER_SIZE).g > 180
		&& backGround.getPixel(x, y + PLAYER_SIZE).b < 50)
		return true;

	if (backGround.getPixel(x, y - PLAYER_SIZE).r > 220
		&& backGround.getPixel(x, y - PLAYER_SIZE).g > 180
		&& backGround.getPixel(x, y - PLAYER_SIZE).b < 50)
		return true;

	if (backGround.getPixel(x - PLAYER_SIZE, y).r > 220
		&& backGround.getPixel(x - PLAYER_SIZE, y).g > 180
		&& backGround.getPixel(x - PLAYER_SIZE, y).b < 50)
		return true;

	if (backGround.getPixel(x + PLAYER_SIZE, y).r > 220
		&& backGround.getPixel(x + PLAYER_SIZE, y).g > 180
		&& backGround.getPixel(x + PLAYER_SIZE, y).b < 50)
		return true;
	return false;
}
