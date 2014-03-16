#pragma once
#include <string>

namespace Vox
{
  void Speak(const std::string &text);
  bool IsPlaying(void);
  void Stop(void);
}