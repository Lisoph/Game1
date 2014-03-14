#pragma once
#include <SDL2/SDL.h>
#include <memory>

class Sprite
{
protected:
  // SDL_Texture *texture;
  std::unique_ptr<SDL_Texture> texture;
  // Wait
};