#include "audio.hpp"
#include "vox.hpp"
#include <irrklang/irrklang.h>
#include <stdexcept>

irrklang::ISoundEngine *Audio::Engine = nullptr;

void Audio::Init(void)
{
  Engine = irrklang::createIrrKlangDevice();
  if(!Engine)
    throw std::runtime_error("irrklang::createIrrKlangDevice");
}

void Audio::Fina(void)
{
  Vox::Stop();
  Engine->drop();
}