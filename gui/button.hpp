#pragma once
#include "widget.hpp"
#include "label.hpp"
#include "../event.hpp"

namespace Gui
{
  class Button;
}

class Gui::Button: public Gui::Widget
{
protected:
  Label label;
  Event<void> clickedEvents;
public:
  Button(void);
  Button(const std::wstring &txt);
  
  void Update(void);
  void Draw(void);
  
  Event<void> &ClickedEvents(void) { return clickedEvents; }
};