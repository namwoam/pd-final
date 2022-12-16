#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>

#include "Game_State.hpp"
#include "State_Game.hpp"

void State_Game::draw()
{
	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	return;
}

void State_Game::update()
{
	return;
}

void State_Game::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
			case sf::Event::Closed: {
				this->game->window.close();
				break;
			}

			case sf::Event::KeyPressed: {
				player.processEvents(event.key.code, true);
				break;
			}

			case sf::Event::KeyReleased: {
				player.processEvents(event.key.code, false);
			}

			default: break;
		}
	}

	return;
}

State_Game::State_Game(Game* game)
{
	this->game = game;
}