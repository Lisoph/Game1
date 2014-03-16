#pragma once

// class irrklang::ISoundEngine;

namespace irrklang { class ISoundEngine; }

namespace Audio
{
  extern irrklang::ISoundEngine *Engine;
  
  void Init(void);
  void Fina(void);
}