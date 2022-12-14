// #include "Platform/Platform.hpp"
// #include <iostream>
// using namespace sf;

// int main()
// {
// 	util::Platform platform;

// #if defined(_DEBUG)
// 	std::cout << "Hello World!" << std::endl;
// #endif

// 	RenderWindow window;
// 	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
// 	window.create(VideoMode(200.0f * screenScalingFactor, 200.0f * screenScalingFactor), "SFML works!");
// 	platform.setIcon(window.getSystemHandle());

// 	CircleShape shape(window.getSize().x / 2);
// 	shape.setFillColor(Color::White);

// 	Texture shapeTexture;
// 	shapeTexture.loadFromFile("content/sfml.png");
// 	shape.setTexture(&shapeTexture);

#include "Platform/Platform.hpp"
#include "mainChar.hpp"
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main()
{

	RenderWindow window(VideoMode(600, 400), "title");
	Event event;

	Entity player(window.getSize().y / 15);
	Vector2f speed(0, 0);

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
		speed = player.update(speed);
		player.drawTo(window);
		window.display();
	}

	return 0;
}
