#pragma once
#include <SDL2/SDL.h>

namespace Screen
{
  extern SDL_Window *window;
  extern SDL_Renderer *renderer;
  
  void Init(void);
  inline void Present(void);
  void Fina(void);
}

void Screen::Present(void)
{
  SDL_RenderPresent(renderer);
}