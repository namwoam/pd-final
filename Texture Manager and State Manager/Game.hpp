#ifndef GAME_HPP
#define GAME_HPP

#include "Texture_Manager.hpp"
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <stack>

class GameState;

class Game
{
private:
	void loadTextures();

public:
	std::stack<GameState*> states;

	sf::RenderWindow window;
	Texture_Manager texmgr;
	sf::Sprite background;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	Game();
	~Game();
};

#endif /* GAME_HPP */