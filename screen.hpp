#pragma once
#include <SDL2/SDL.h>

namespace Screen
{
  extern SDL_Window *Window;
  extern SDL_Renderer *Renderer;
  
  void Init(void);
  inline void Present(void);
  void Fina(void);
}

void Screen::Present(void)
{
  SDL_RenderPresent(Renderer);
}