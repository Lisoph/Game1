#pragma once
#include "gamestate.hpp"
#include "sprite.hpp"
#include "resource_manager.hpp"

class GS_Game: public GameState
{
  protected:
    ResourceManager<Sprite> spriteManager;
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