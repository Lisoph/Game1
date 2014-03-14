#include "label.hpp"
#include "../drawing.hpp"
#include "../globals.hpp"

using namespace Gui;

Label::Label(void)
: Widget(), text(),
  font(Globals::Font_Default),
  color(0x000000FF)
{}

Label::Label(std::wstring &&str)
: Widget(), text(str),
  font(Globals::Font_Default),
  color(0x000000FF)
{}

void Label::Draw(void)
{
  Drawing::DrawString(pos(0), pos(1), text, font, color);
}