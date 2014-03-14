#include "label.hpp"
#include "../drawing.hpp"
#include "../globals.hpp"

using namespace Gui;

Label::Label(void)
: Widget(), text(),
  font(Globals::Font_Default),
  color(0x000000FF)
{
  CalculateSize();
}

Label::Label(const std::wstring &str)
: Widget(), text(str),
  font(Globals::Font_Default),
  color(0x000000FF)
{
  CalculateSize();
}

void Label::Draw(void)
{
  Drawing::DrawString(pos(0), pos(1), text, font, color);
}

void Label::SetText(const std::wstring &_text)
{
  text = _text;
  CalculateSize();
}

void Label::CalculateSize(void)
{
  int w, h;
  Drawing::Util::StringSize(text, font, &w, &h);
  size(0) = static_cast<Scalar>(w);
  size(1) = static_cast<Scalar>(h);
}