#include "screen.hpp"
#include "globals.hpp"
#include <stdexcept>

SDL_Window *Screen::Window = nullptr;
SDL_Renderer *Screen::Renderer = nullptr;

void Screen::Init(void)
{
  using namespace Globals;
  
  Window = SDL_CreateWindow("Uuuuuh... Aeiou!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
  if(!Window) throw std::runtime_error("SDL_CreateWindow");
  
  Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
  if(!Renderer) throw std::runtime_error("SDL_CreateRenderer");
}

void Screen::Fina(void)
{
  if(Renderer) SDL_DestroyRenderer(Renderer);
  if(Window) SDL_DestroyWindow(Window);
}