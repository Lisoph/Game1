#include "sprite.hpp"
#include "globals.hpp"
#include "screen.hpp"
#include <stdexcept>
#include <SDL2/SDL_image.h>

Sprite::Sprite(void)
: texture(nullptr, TextureDeleter),
  size(0, 0), frameOffset(0, 0),
  frameSize(32, 32),
  textureSize(0, 0)
{}

Sprite::Sprite(const Sprite::Vec2 &size)
: texture(nullptr, TextureDeleter),
  size(size), frameOffset(0, 0),
  frameSize(32, 32),
  textureSize(0, 0)
{}

void Sprite::Draw(void)
{
  SDL_Rect srcRect = {static_cast<int>(frameOffset(0)), static_cast<int>(frameOffset(1)), static_cast<int>(frameSize(0)), static_cast<int>(frameSize(1))};
  SDL_Rect dstRect = {static_cast<int>(pos(0)), static_cast<int>(pos(1)), static_cast<int>(size(0)), static_cast<int>(size(1))};
  SDL_RenderCopy(Screen::Renderer, texture.get(), &srcRect, &dstRect);
}

bool Sprite::LoadFromFile(const std::string &file)
{
  SDL_Surface *surface = IMG_Load(file.c_str());
  if(!surface) return false;
  
  SDL_Texture *_texture = SDL_CreateTextureFromSurface(Screen::Renderer, surface);
  if(!_texture) throw std::runtime_error("SDL_CreateTextureFromSurface");
  
  textureSize(0) = surface->w;
  textureSize(1) = surface->h;
  SDL_FreeSurface(surface);
  
  texture.reset(_texture);
  return true;
}

void Sprite::SetFrame(int frame)
{
  frameOffset(0) = frameSize(0) * frame;
}