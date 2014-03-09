#pragma once
#include "gamestate.hpp"

class GS_MainMenu: public GameState
{
public:
  GS_MainMenu(void);
  ~GS_MainMenu(void);
  
  inline static GS_MainMenu &Instance(void);
  
  void Update(void) override;
  void Draw(void) override;
};

GS_MainMenu &GS_MainMenu::Instance(void)
{
  static GS_MainMenu instance;
  return instance;
}