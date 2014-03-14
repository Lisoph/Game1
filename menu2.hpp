#pragma once
#include "gamestate.hpp"

class GS_Menu2: public GameState
{
public:
  GS_Menu2(void);
  ~GS_Menu2(void);
  
  void Update(void) override;
  void Draw(void) override;
  
  static inline GS_Menu2 &Instance(void);
};

GS_Menu2 &GS_Menu2::Instance(void)
{
  static GS_Menu2 instance;
  return instance;
}