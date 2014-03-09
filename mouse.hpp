#pragma once
#include <Eigen/Eigen>

namespace Mouse
{
  extern Eigen::Vector2i Position;
  
  enum class MouseEventType
  {
    MouseMotion,
    MouseButtonDown,
    MouseButtonUp
  };
  
  enum class Button
  {
    Left = 1,
    Middle,
    Right
  };
  
  void ClearPressedButtons(void);
  void HandleMouseEvent(int x, int y, MouseEventType meType);
  void HandleMouseEvent(Button button, MouseEventType meType);
  
  bool IsButtonDown(Button button);
  inline bool IsButtonUp(Button button) { return !IsButtonDown(button); }
  bool IsButtonPressed(Button button);
}