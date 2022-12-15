#include <SFML/Graphics.hpp>
#include <iostream>
#include "mainChar.hpp"
using namespace sf;

// bool collideWithWall(Image image, int x, int y);

int main()
{

	RenderWindow window(VideoMode(900, 900), "title", Style::Titlebar | Style::Close);
	Texture t;
	t.loadFromFile("C:/Users/olaba/Downloads/1671090937051.jpg");
	Sprite backGround(t);

	Event event;

	Entity player;
	Vector2f speed(0, 0);
	Clock clock;

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
		window.draw(backGround);
		Time elapsed = clock.restart();
		player.updateMotion(elapsed);
		player.updateDisplay(window);
		window.display();
	}

	return 0;
}

// bool collideWithWall(Image backGround, int x, int y)
// {
// 	Color wallColor(229, 153, 121); // orange
// 	if (backGround.getPixel(x, y + PLAYER_SIZE) == wallColor)
// 		return true;
// 	return false;
// }
