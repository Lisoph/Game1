#include "gamestate.hpp"

GameState *GameState::currentState = nullptr;

GameState::GameState(void)
: isActive(false)
{}