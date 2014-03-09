#pragma once
#include "event.hpp"

namespace Keyboard
{
  extern Event<int> KeyPressedEvents;
  
  enum class KeyEventType
  {
    KeyDown,
    KeyUp
  };
  
  void ClearPressedKeys(void);
  void HandleKeyEvent(int key, KeyEventType keType);
  
  bool IsKeyDown(int key);
  inline bool IsKeyUp(int key) { return !IsKeyDown(key); }
  bool IsKeyPressed(int key);
}