#pragma once
#include <string>

struct _TTF_Font;

namespace Drawing
{
  typedef struct _TTF_Font TTF_Font;
  
  void DrawString(long x, long y, const std::wstring &str, TTF_Font *font, unsigned long color, bool disco = false);
}