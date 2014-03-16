#include <SDL2/SDL.h>
#include "game.hpp"
#include "globals.hpp"
#include <iostream>
#include <ctime>

typedef unsigned long ulong;

constexpr ulong Sec(ulong sec) { return sec * 1000; }

int main(int argc, char **argv)
{
  ulong timeStart, timeEnd, oldTime, frameTime;
  constexpr ulong FPMS  = 1000 / Globals::FPS;
  constexpr float DFPMS = 1000.0f / Globals::DFPS;
  
  Game::Init();
  oldTime = SDL_GetTicks();
  
  ulong frames = 0;
  ulong ftOffset = SDL_GetTicks();
  
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
   
    
    if(timeEnd > ftOffset + 1000)
    {
      Globals::fps = frames;
      frames = 0;
      ftOffset = timeEnd;
    }
    else
      ++frames;
  }
  
  Game::Fina();
  return 0;
}