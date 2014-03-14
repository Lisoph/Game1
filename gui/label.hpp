#pragma once
#include "widget.hpp"
#include <string>
#include <cstdint>
#include <SDL2/SDL_ttf.h>

// struct _TTF_Font;

namespace Gui
{
  // typedef struct _TTF_Font TTF_Font;
  
  class Label;
}

class Gui::Label: public Gui::Widget
{
protected:
  std::wstring text;  
  TTF_Font *font;
  uint32_t color;
public:
  Label(void);
  Label(std::wstring &&str);
  
  uint32_t Color(void) const { return color; }
  void SetColor(uint32_t _color) { color = _color; }
  inline void SetColor(int r, int g, int b);
  
  void Update(void) override {};
  void Draw(void) override;
};

void Gui::Label::SetColor(int r, int g, int b)
{
  uint32_t color = (b << 8);
  color |= (g << 16);
  color |= (r << 24);
  SetColor(color);
}