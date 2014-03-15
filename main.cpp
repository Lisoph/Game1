#include <SDL2/SDL.h>
#include "game.hpp"
#include "globals.hpp"
#include <iostream>
#include <ctime>

typedef unsigned long ulong;

constexpr ulong Sec(ulong sec) { return sec * CLOCKS_PER_SEC; }
inline ulong uclock() { return static_cast<ulong>(clock()); }

int main(int argc, char **argv)
{
  ulong timeStart, timeEnd, oldTime, frameTime;
  constexpr ulong FPMS  = 1000 / Globals::FPS;
  constexpr float DFPMS = 1000.0f / Globals::DFPS;
  
  ulong frames = 0;
  ulong ftOffset = uclock();
  
  Game::Init();
  oldTime = SDL_GetTicks();
  
  while(Game::Running)
  {
    timeStart = SDL_GetTicks();
    Globals::DeltaTime = static_cast<float>(timeStart - oldTime) / DFPMS;
    oldTime = timeStart;
    
    Game::Update();
    Game::Draw();
    
    timeEnd = SDL_GetTicks();
    frameTime = timeEnd - timeStart;
    if(frameTime < FPMS) SDL_Delay(FPMS - frameTime); // Maybe replace SDL_GetTicks & SDL_Delay with Boost functions -> Probably better time resolution.
   
     
    if(uclock() > ftOffset + Sec(1))
    {
      // std::cout << "FPS: " << frames << '\n';
      Globals::fps = frames;
      frames = 0;
      ftOffset = uclock();
    }
    else ++frames;
  }
  
  Game::Fina();
  return 0;
}