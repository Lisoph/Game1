#include "globals.hpp"
#include <SDL2/SDL_ttf.h>

float Globals::DeltaTime = 1.0f;
unsigned long Globals::fps = 0;

Globals::TTF_Font *Globals::Font_Default = nullptr;





bool Globals::LoadFonts(void)
{
  Font_Default = TTF_OpenFont("arial.ttf", 24);
  if(!Font_Default) return false;
  
  return true;
}

void Globals::CloseFonts(void)
{
  TTF_CloseFont(Font_Default);
}