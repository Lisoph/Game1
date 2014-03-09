#pragma once

class GameState
{
protected:
  static GameState *currentState;
  
public:  
  GameState(void);
  virtual ~GameState(void) {}
  
  static void UpdateCurrent(void) { if(currentState) currentState->Update(); }
  static void DrawCurrent(void) { if(currentState) currentState->Draw(); }
  
  static inline void SwitchTo(GameState &gameState);
  
  virtual void Update(void) = 0;
  virtual void Draw(void) = 0;
};

void GameState::SwitchTo(GameState &gameState)
{
  currentState = &gameState;
}