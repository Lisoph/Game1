#pragma once
#include <vector>
#include <cwchar>
#include <string>
#include <sstream>

typedef struct _TTF_Font FontType;
typedef struct SDL_Texture TextureType;

struct Char
{
  TextureType *texture;
  int width, height;
};

class FontCache
{
protected:
  long fontHeight; /* This is currently unused */
  std::vector<std::pair<wchar_t, Char>> cachedChars;
  FontType *font;
public:
  FontCache(FontType *font);
  FontCache(const FontCache &copySrc);
  ~FontCache(void);
  
  long FontHeight(void) const { return fontHeight; }
  FontType *Font(void) const { return font; }
  
  Char &CachedChar(wchar_t chr);
  Char &CacheChar(wchar_t);
};