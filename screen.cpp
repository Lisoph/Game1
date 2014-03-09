#include "screen.hpp"
#include "globals.hpp"
#include <stdexcept>

SDL_Window *Screen::window = nullptr;
SDL_Renderer *Screen::renderer = nullptr;

void Screen::Init(void)
{
  using namespace Globals;
  
  window = SDL_CreateWindow("Uuuuuh... Aeiou!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if(!window) throw std::runtime_error("SDL_CreateWindow");
  
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!renderer) throw std::runtime_error("SDL_CreateRenderer");
}

void Screen::Fina(void)
{
  if(renderer) SDL_DestroyRenderer(renderer);
  if(window) SDL_DestroyWindow(window);
}