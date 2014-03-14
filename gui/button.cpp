#include "button.hpp"
#include "../mouse.hpp"
#include "../drawing.hpp"

using namespace Gui;

Button::Button(void)
: Widget(),
  label(L"<no text>"),
  clickedEvents()
{
  label.SetColor(255, 0, 0);
  size = label.Size();
}

Button::Button(const std::wstring &txt)
: Widget(),
  label(txt),
  clickedEvents()
{
  label.SetColor(255, 0, 0);
  size = label.Size();
}

void Button::Update(void)
{
  static uint32_t color = label.Color(), mouseOverColor = color | 0x666666FF;
  size = label.Size();
  
  if(Mouse::Position(0) > pos(0) && Mouse::Position(0) < pos(0) + size(0) &&
       Mouse::Position(1) > pos(1) && Mouse::Position(1) < pos(1) + size(1))
  {
    label.SetColor(mouseOverColor);
    
    if(Mouse::IsButtonPressed(Mouse::Button::Left))
      clickedEvents();
  }
  else
    label.SetColor(color);
}

void Button::Draw(void)
{
  label.Pos() = pos;
  label.Draw();
}