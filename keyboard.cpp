#include "keyboard.hpp"
#include <SDL2/SDL.h>
#include <map>
#include <iostream>

static std::map<int, bool> cachedKeys;
static std::map<int, bool> cachedPressedKeys;

Event<int> Keyboard::KeyPressedEvents;
Event<const std::string&> Keyboard::TextInputEvents;
Event<const Keyboard::TextEditEventData&> Keyboard::TextEditEvents;

void Keyboard::ClearPressedKeys(void)
{
  for(auto it = cachedPressedKeys.begin(); it != cachedPressedKeys.end(); ++it)
    it->second = false;
}

void Keyboard::HandleKeyEvent(int key, Keyboard::KeyEventType keType)
{
  cachedKeys[key] = (keType == KeyEventType::KeyDown) ? true : false;
  if(keType == KeyEventType::KeyDown)
  {
    cachedPressedKeys[key] = true;
    KeyPressedEvents(key);
  }
}

void Keyboard::HandleTextInputEvent(const std::string &input)
{
  TextInputEvents(input);
}

void Keyboard::HandleTextEditEvent(int start, int length, const std::string &text)
{
  TextEditEvents({start, length, text});
}

bool Keyboard::IsKeyDown(int key)
{
  auto it = cachedKeys.find(key);
  return (it != cachedKeys.end()) ? it->second : false;
}

bool Keyboard::IsKeyPressed(int key)
{
  auto it = cachedPressedKeys.find(key);
  return (it != cachedPressedKeys.end()) ? it->second : false;
}