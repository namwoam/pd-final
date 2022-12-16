#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.hpp"
#include "Game_State.hpp"
#include "Texture_Manager.hpp"

void Game::loadTextures()
{
	texmgr.loadTexture("background", "C:/Users/olaba/Downloads/1671090974143.jpg");
}

void Game::pushState(GameState* state)
{
	this->states.push(state);

	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::changeState(GameState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

GameState* Game::peekState()
{
	if (this->states.empty())
		return nullptr;
	return this->states.top();
}

void Game::gameLoop()
{
	while (this->window.isOpen())
	{
		if (peekState() == nullptr)
			continue;
		peekState()->handleInput();
		peekState()->update();
		this->window.clear(sf::Color::Black);
		peekState()->draw();
		this->window.display();
	}
}

Game::Game()
{
	this->loadTextures();

	this->window.create(sf::VideoMode(900, 900), "PD Final", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(60);

	this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
	while (!this->states.empty())
		popState();
}