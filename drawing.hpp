#pragma once
#include <string>

struct _TTF_Font;

namespace Drawing
{
  typedef struct _TTF_Font TTF_Font;
  
  void DrawString(int x, int y, const std::wstring &str, TTF_Font *font, unsigned long color, bool disco = false);
  
  namespace Util
  {
    void CharSize(wchar_t chr, TTF_Font *font, int *w, int *h);
    void StringSize(const std::wstring &str, TTF_Font *font, int *w, int *h);
  }
}