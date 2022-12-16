#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

bool collideWithWall(Image image, int x, int y);

int main()
{

	RenderWindow window(VideoMode(900, 900), "PD Final", Style::Titlebar | Style::Close);

	Texture topLeft, topRight, bottomLeft, bottomRight;
	topLeft.loadFromFile("C:/Users/olaba/Downloads/1671090937051.jpg");
	topRight.loadFromFile("C:/Users/olaba/Downloads/1671090952623.jpg");
	bottomLeft.loadFromFile("C:/Users/olaba/Downloads/1671090962853.jpg");
	bottomRight.loadFromFile("C:/Users/olaba/Downloads/1671090974143.jpg");

	Sprite* map[4];
	map[0] = new Sprite(topLeft);
	map[1] = new Sprite(topRight);
	map[2] = new Sprite(bottomLeft);
	map[3] = new Sprite(bottomRight);

	Image imgMap[4];
	imgMap[0].loadFromFile("C:/Users/olaba/Downloads/1671090937051.jpg");
	imgMap[1].loadFromFile("C:/Users/olaba/Downloads/1671090952623.jpg");
	imgMap[2].loadFromFile("C:/Users/olaba/Downloads/1671090962853.jpg");
	imgMap[3].loadFromFile("C:/Users/olaba/Downloads/1671090974143.jpg");

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
				player.processEvents(event.key.code, true);
			if (event.type == Event::KeyReleased)
				player.processEvents(event.key.code, false);
		}

		window.clear();
		window.draw(*map[curBg]);
		Time elapsed = clock.restart();
		player.updateMotion(elapsed);
		std::cout
			<< (int)imgMap[curBg].getPixel(player.getPos().x, player.getPos().y).g
			<< " ";
		if (collideWithWall(imgMap[curBg], player.getPos().x, player.getPos().y))
			player.stop();
		player.updateDisplay(window);
		window.display();
	}

	return 0;
}

bool collideWithWall(Image backGround, int x, int y)
{
	if (backGround.getPixel(x, y + PLAYER_SIZE).r > 200 && backGround.getPixel(x, y + PLAYER_SIZE).g < 200)
		return true;
	return false;
}