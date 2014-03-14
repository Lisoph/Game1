#pragma once
#include <vector>

template <typename... CallbackArgs>
class Event
{
public:
  typedef void(*CallbackType)(CallbackArgs...);
protected:
  std::vector<CallbackType> callbacks;
public:
  Event(void)
  : callbacks(0)
  {}
  
  Event(CallbackType callback)
  : callbacks(0)
  {
    callbacks.push_back(callback);
  }
  
  Event &operator += (CallbackType rhs);
  Event &operator -= (CallbackType rhs);
  void operator () (CallbackArgs... args);
  
  inline void Clear(void) { callbacks.clear(); }
};

template <typename... CallbackArgs>
Event<CallbackArgs...> &Event<CallbackArgs...>::operator += (CallbackType rhs)
{
  callbacks.push_back(rhs);
  return *this;
}

template <typename... CallbackArgs>
Event<CallbackArgs...> &Event<CallbackArgs...>::operator -= (CallbackType rhs)
{
  for(auto it = callbacks.begin(); it != callbacks.end(); ++it)
  {
    if(*it == rhs)
      callbacks.erase(it);
  }
  
  return *this;
}

template <typename... CallbackArgs>
void Event<CallbackArgs...>::operator () (CallbackArgs... args)
{
  for(auto it = callbacks.begin(); it != callbacks.end(); ++it)
    (*it)(args...);
}

//===-----------------===//
// void Specialization
//===-----------------===//

template <>
class Event<void>
{
public:
  typedef void(*CallbackType)(void);
protected:
  std::vector<CallbackType> callbacks;
public:
  Event(void)
  : callbacks(0)
  {}
  
  Event(CallbackType callback)
  : callbacks(0)
  {
    callbacks.push_back(callback);
  }
  
  Event &operator += (CallbackType rhs);
  Event &operator -= (CallbackType rhs);
  void operator () (void);
  
  inline void Clear(void) { callbacks.clear(); }
};