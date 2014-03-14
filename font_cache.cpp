#include "font_cache.hpp"
#include "screen.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iostream>

FontCache::FontCache(TTF_Font *font)
: fontHeight(0), cachedChars(), font(font)
{
  fontHeight = TTF_FontHeight(font);
}

FontCache::FontCache(const FontCache &copySrc)
: fontHeight(copySrc.fontHeight),
  cachedChars(std::move(copySrc.cachedChars)),
  font(copySrc.font)
{}

FontCache::~FontCache(void)
{
  for(auto it = cachedChars.begin(); it != cachedChars.end(); ++it)
  {
    SDL_DestroyTexture(it->second.texture);
  }
  
  cachedChars.clear();
}

Char &FontCache::CachedChar(wchar_t chr)
{
  for(auto it = cachedChars.begin(); it != cachedChars.end(); ++it)
  {
    if(it->first == chr)
      return (Char&)(it->second);
  }
  
  return CacheChar(chr);
}

Char &FontCache::CacheChar(wchar_t chr)
{
  // SDL_Surface *surface = TTF_RenderGlyph_Shaded(font, chr, {255, 255, 255, 255}, {255, 0, 255, 255});
  SDL_Surface *surface = TTF_RenderGlyph_Blended(font, chr, {255, 255, 255, 255});
  if(!surface) throw std::runtime_error(TTF_GetError());
  
  //SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
  
  Char newCachedChar = {SDL_CreateTextureFromSurface(Screen::Renderer, surface), surface->w, surface->h};
  SDL_FreeSurface(surface);
  
  cachedChars.push_back(std::make_pair(chr, newCachedChar));
  return cachedChars.back().second;
}