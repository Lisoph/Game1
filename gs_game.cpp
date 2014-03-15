#include "gs_game.hpp"
#include "drawing.hpp"
#include "keyboard.hpp"
#include "menu2.hpp"
#include <SDL2/SDL.h>

GS_Game::GS_Game(void)
: GameState()
{
  Keyboard::KeyPressedEvents += [](int key) -> void
  {
    if(!GS_Game::Instance().IsActive()) return;
    
    if(key == SDLK_ESCAPE)
    {
      GameState::SwitchTo(GS_Menu2::Instance());
    }
  };
}

GS_Game::~GS_Game(void)
{}

void GS_Game::Update(void)
{
  /* TODO: Implement gameplay stuff */
}

void GS_Game::Draw(void)
{
  
}