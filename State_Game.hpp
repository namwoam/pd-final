#ifndef STATE_GAME_HPP
#define STATE_GAME_HPP

#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>

#include "Character.hpp"
#include "game_state.hpp"

class State_Game : public GameState
{
private:
	Entity player;

public:
	virtual void draw();
	virtual void update();
	virtual void handleInput();

	State_Game(Game* game);
};

#endif /* STATE_GAME_HPP */