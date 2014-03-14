#include "event.hpp"

Event<void> &Event<void>::operator += (CallbackType rhs)
{
  callbacks.push_back(rhs);
  return *this;
}

Event<void> &Event<void>::operator -= (CallbackType rhs)
{
  for(auto it = callbacks.begin(); it != callbacks.end(); ++it)
  {
    if(*it == rhs)
      callbacks.erase(it);
  }
  
  return *this;
}

void Event<void>::operator () (void) // Yup
{
  for(auto it = callbacks.begin(); it != callbacks.end(); ++it)
    (*it)();
}