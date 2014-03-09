#pragma once

struct _TTF_Font;

namespace Globals
{
  typedef struct _TTF_Font TTF_Font;
  
  bool LoadFonts(void);
  void CloseFonts(void);
  
  constexpr long SCREEN_WIDTH  = 640;
  constexpr long SCREEN_HEIGHT = 480;
  constexpr long FPS           = 60;
  constexpr float DFPS         = 60.0f;
  
  //===-----------------------------------===//
  // Global variables
  //===-----------------------------------===//
  extern float DeltaTime;
  extern unsigned long fps;
  
  extern TTF_Font *Font_Default;
  /* Other fonts here */
}