#pragma once
#include "event.hpp"
#include <string>

namespace Keyboard
{
  struct TextEditEventData;
  
  extern Event<int> KeyPressedEvents;
  extern Event<const std::string&> TextInputEvents;
  extern Event<const TextEditEventData&> TextEditEvents;
  
  enum class KeyEventType
  {
    KeyDown,
    KeyUp
  };
  
  void ClearPressedKeys(void);
  void HandleKeyEvent(int key, KeyEventType keType);
  void HandleTextInputEvent(const std::string &input);
  void HandleTextEditEvent(int start, int length, const std::string &text);
  
  bool IsKeyDown(int key);
  inline bool IsKeyUp(int key) { return !IsKeyDown(key); }
  bool IsKeyPressed(int key);
}

struct Keyboard::TextEditEventData
{
  int start;
  int length;
  const std::string &text;
};