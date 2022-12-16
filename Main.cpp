#include "Game.hpp"
#include "State_Game.hpp"
#include "State_Start.hpp"

int main()
{
	Game game;

	game.pushState(new State_Start(&game));
	game.gameLoop();

	return 0;
}