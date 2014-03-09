#include "mouse.hpp"
#include <map>
// #include <iostream>

Eigen::Vector2i Mouse::Position;
static std::map<int, bool> cachedButtons;
static std::map<int, bool> cachedPressedButtons;

static inline int ButtonToInt(Mouse::Button button)
{
  return static_cast<int>(button);
}

void Mouse::ClearPressedButtons(void)
{
  for(auto it = cachedPressedButtons.begin(); it != cachedPressedButtons.end(); ++it)
    it->second = false;
}

void Mouse::HandleMouseEvent(int x, int y, Mouse::MouseEventType meType)
{
  Position(0) = x;
  Position(1) = y;
}

void Mouse::HandleMouseEvent(Mouse::Button button_, Mouse::MouseEventType meType)
{
  int button = ButtonToInt(button_);
  
  bool oldState = cachedButtons[button];
  cachedButtons[button] = (meType == MouseEventType::MouseButtonDown) ? true : false;
  
  if(oldState == true && cachedButtons[button] == false)
  {
    cachedPressedButtons[button] = true;
    // std::cout << "Clicked\n";
  }
}

bool Mouse::IsButtonDown(Mouse::Button button)
{
  auto it = cachedButtons.find(ButtonToInt(button));
  return (it != cachedButtons.end()) ? it->second : false;
}

bool Mouse::IsButtonPressed(Mouse::Button button)
{
  auto it = cachedPressedButtons.find(ButtonToInt(button));
  return (it != cachedPressedButtons.end()) ? it->second : false;
}