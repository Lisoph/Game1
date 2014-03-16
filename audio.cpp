#include "audio.hpp"
#include "vox.hpp"
#include <irrklang/irrklang.h>
#include <stdexcept>
#include <iostream>

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
  std::cout << "Dropping engine...\n";
  Engine->drop();
}