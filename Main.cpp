#include <SFML/Graphics.hpp>
#include <iostream>
#include "mainChar.hpp"
using namespace sf;

int main()
{

	RenderWindow window(VideoMode(600, 400), "title");
	Event event;

	Entity player(window.getSize().y / 15);
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
		Time elapsed = clock.restart();
		speed = player.update(speed , elapsed);
		player.drawTo(window);
		window.display();
	}

	return 0;
}
