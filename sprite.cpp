#include "sprite.hpp"
#include "globals.hpp"
#include "screen.hpp"
#include <stdexcept>
#include <iostream>
#include <SDL2/SDL_image.h>

// static ResourceManager<SDL_Texture, TextureDeleter> Sprite::textureManager;
Sprite::RMType Sprite::textureManager;

Sprite::Sprite(void)
: texture(nullptr, TextureDeleter),
  size(0, 0), frameOffset(0, 0),
  frameSize(32, 32),
  textureSize(0, 0),
  rot(0.0f)
{}

Sprite::Sprite(const Sprite::Vec2 &size)
: texture(nullptr, TextureDeleter),
  size(size), frameOffset(0, 0),
  frameSize(32, 32),
  textureSize(0, 0),
  rot(0.0f)
{}

void Sprite::Draw(void)
{
  SDL_Rect srcRect = {static_cast<int>(frameOffset(0)), static_cast<int>(frameOffset(1)), static_cast<int>(frameSize(0)), static_cast<int>(frameSize(1))};
  // SDL_Rect dstRect = {static_cast<int>(pos(0)), static_cast<int>(pos(1)), static_cast<int>(size(0)), static_cast<int>(size(1))}; // Old origin
  SDL_Rect dstRect = {static_cast<int>(pos(0) - (size(0) / 2)), static_cast<int>(pos(1) - (size(1) / 2)), static_cast<int>(size(0)), static_cast<int>(size(1))};
  SDL_RenderCopyEx(Screen::Renderer, texture.get(), &srcRect, &dstRect, rot, nullptr, SDL_FLIP_NONE);
}

bool Sprite::LoadFromFile(const std::string &file)
{
  SDL_Texture *foo = textureManager.Resource(file);
  if(foo)
  {
    std::cout << "Sprite texture already loaded!\n";
    
    texture.reset(foo);
    return true;
  }
  
  std::cout << "Loading sprite from file\n";
  
  SDL_Surface *surface = IMG_Load(file.c_str());
  if(!surface) return false;
  
  SDL_Texture *_texture = SDL_CreateTextureFromSurface(Screen::Renderer, surface);
  if(!_texture) throw std::runtime_error("SDL_CreateTextureFromSurface");
  
  textureSize(0) = surface->w;
  textureSize(1) = surface->h;
  SDL_FreeSurface(surface);
  
  texture.reset(_texture);
  
  textureManager.AddResource(file, _texture);
  
  return true;
}

void Sprite::SetFrame(int frame)
{
  // Placeholder code
  frameOffset(0) = frameSize(0) * frame;
}