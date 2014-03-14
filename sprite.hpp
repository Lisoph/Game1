#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "entity.hpp"
#include <string>

class Sprite: public Entity
{
protected:
  std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture;
  Vec2 size;
  Vec2 frameOffset;
  Vec2 frameSize;
  Vec2 textureSize;
public:
  Sprite(void);
  Sprite(const Vec2 &size);
  
  static void TextureDeleter(SDL_Texture *texture) { if(texture) SDL_DestroyTexture(texture); }
  
  bool LoadFromFile(const std::string &file);
  void SetFrame(int frame);
  
  void Update(void) override {}
  void Draw(void) override;
  
  Vec2 &Size(void) { return size; }
};