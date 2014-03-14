#include "game.hpp"
#include "globals.hpp"
#include "screen.hpp"
#include "gamestate.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "gs_mainmenu.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

bool Game::Running = true;

void Game::Init(void)
{
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
  Screen::Init();
  Globals::LoadFonts();
  
  GameState::SwitchTo(GS_MainMenu::Instance());
} 

void Game::Update(void)
{
  static SDL_Event event;
  
  Keyboard::ClearPressedKeys();
  Mouse::ClearPressedButtons();
  
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
      Keyboard::HandleKeyEvent(event.key.keysym.sym, (event.type == SDL_KEYDOWN) ? Keyboard::KeyEventType::KeyDown : Keyboard::KeyEventType::KeyUp);
    }
    else if(event.type == SDL_MOUSEMOTION)
    {
      Mouse::HandleMouseEvent(event.motion.x, event.motion.y, Mouse::MouseEventType::MouseMotion);
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
      Mouse::HandleMouseEvent(static_cast<Mouse::Button>(event.button.button), (event.type == SDL_MOUSEBUTTONDOWN) ? Mouse::MouseEventType::MouseButtonDown : Mouse::MouseEventType::MouseButtonUp);
    }
    
    else if(event.type == SDL_QUIT)
      Running = false;
  }
  
  if(Keyboard::IsKeyPressed(SDLK_ESCAPE))
    Running = false;
  
  GameState::UpdateCurrent();
}

void Game::Draw(void)
{
  SDL_SetRenderDrawColor(Screen::Renderer, 254, 251, 236, 255);
  
  SDL_RenderClear(Screen::Renderer);
  
  GameState::DrawCurrent();
  Screen::Present();
}

void Game::Fina(void)
{
  Globals::CloseFonts();
  Screen::Fina();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}