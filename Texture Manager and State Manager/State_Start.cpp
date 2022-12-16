#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>

#include "Game_State.hpp"
#include "State_Game.hpp"
#include "State_Start.hpp"

void State_Start::loadGame()
{
	this->game->pushState(new State_Game(this->game));

	return;
}

void State_Start::draw()
{

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	return;
}

void State_Start::update()
{
	return;
}

void State_Start::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
			case sf::Event::Closed: {
				game->window.close();
				break;
			}
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape)
					this->game->window.close();
				else if (event.key.code == sf::Keyboard::Space)
					this->loadGame();
				break;
			}
			default: break;
		}
	}

	return;
}

State_Start::State_Start(Game* game)
{
	this->game = game;
}