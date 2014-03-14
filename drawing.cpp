#include "drawing.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "font_cache.hpp"
#include "screen.hpp"
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

vector<FontCache> cachedFonts;

static FontCache *FindCachedFont(TTF_Font *font)
{
  for(auto it = cachedFonts.begin(); it != cachedFonts.end(); ++it)
  {
    if((*it).Font() == font)
      return &(*it);
  }
  
  return nullptr;
}

//  "hello world\naeiou\n\ntest"
static std::vector<std::wstring> SplitString(const std::wstring &str, const wchar_t splitToken) // <<-- Broken
{
  std::vector<std::wstring> lines;
  unsigned long offset = 0;
  
  for(;;)
  {
    unsigned long begin = str.find(splitToken, offset + 1);
    if(begin == std::wstring::npos)
    {
      // if(!str.empty())
      if(str.size() - offset > 0)
      {
        std::wstring line = str.substr(offset, str.size() - offset);
        if(line[0] == L'\n')
        {
          line.erase(line.begin());
        }
        
        lines.push_back(line);
      }
      
      break;
    }
    
    std::wstring line = str.substr(offset, begin - offset);
    if(line[0] == L'\n')
    {
      line.erase(line.begin());
    }
    
    lines.push_back(line);
    offset = begin;
  }
  
  return lines;
}

void Drawing::DrawString(long x, long y, const wstring &str, TTF_Font *font, unsigned long color, bool disco)
{
  FontCache *cachedFont = FindCachedFont(font);
  
  if(!cachedFont)
  {
    cachedFonts.push_back(FontCache(font));
    cachedFont = &cachedFonts.back();
  }
  
  long xOffset = 0, yOffset = 0;
    
  std::vector<std::wstring> lines = SplitString(str, L'\n');
  
  for(auto strIt = lines.begin(); strIt != lines.end(); ++strIt)
  {
    std::wstring line = *strIt;
    // long highestCharHeight = 0;
    long highestCharHeight = TTF_FontHeight(font);
    
    for(auto lineIt = line.begin(); lineIt != line.end(); ++lineIt)
    {
      wchar_t chr = *lineIt;
      
      if(chr == L'\r')
      {
        xOffset = 0;
        continue;
      }
      
      Char &cachedChar = cachedFont->CachedChar(chr);
      SDL_Rect dstRect = {x + xOffset, y + yOffset, cachedChar.width, cachedChar.height};
      
      if(disco)
        SDL_SetTextureColorMod(cachedChar.texture, rand() % 255, rand() % 255, rand() % 255);
      else
        SDL_SetTextureColorMod(cachedChar.texture, color >> 24, (color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8);
      
      SDL_RenderCopy(Screen::Renderer, cachedChar.texture, nullptr, &dstRect);
      xOffset += cachedChar.width;
      
      if(cachedChar.height > highestCharHeight)
        highestCharHeight = cachedChar.height;
    }
    
    yOffset += highestCharHeight;
    xOffset = 0;
  }
}