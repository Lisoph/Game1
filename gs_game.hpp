#pragma once
#include "gamestate.hpp"

class GS_Game: public GameState
{
public:
  GS_Game(void);
  ~GS_Game(void);
  
  void Update(void) override;
  void Draw(void) override;
  
  static inline GS_Game &Instance(void);
};

GS_Game &GS_Game::Instance(void)
{
  static GS_Game instance;
  return instance;
}