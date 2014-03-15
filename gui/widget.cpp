#include "widget.hpp"

using namespace Gui;

void Widget::AddChild(Widget *widget)
{
  children.push_back(widget);
}

void Widget::RemoveChild(Widget *widget)
{
  for(auto it = children.begin(); it != children.end(); ++it)
  {
    if((*it) == widget)
      children.erase(it);
  }
}

void Widget::UpdateChildren(void)
{
  for(auto it = children.begin(); it != children.end(); ++it)
    (*it)->Update();
}

void Widget::DrawChildren(void)
{
  for(auto it = children.begin(); it != children.end(); ++it)
    (*it)->Draw();
}