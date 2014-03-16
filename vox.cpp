#include "vox.hpp"
#include "audio.hpp"
#include <irrklang/irrklang.h>
#include <vector>
#include <sstream>
#include <cctype>
#include <iostream>

static irrklang::ISound *curSpeakSound = nullptr;
static std::string toSpeak;
static std::vector<std::string> wordsToSpeak;
static size_t wordsToSpeakIndex = 0;
static bool playing = false;

void SpeakNextWord(void);

class SoundStopReceiver: public irrklang::ISoundStopEventReceiver
{
public:
  void OnSoundStopped(irrklang::ISound *sound, irrklang::E_STOP_EVENT_CAUSE cause, void *usrData)
  {
    // sound->drop(); // This crashes the game when quitting.
    SpeakNextWord();
  }
};

static void StringToLower(std::string &str)
{
  for(size_t i = 0; i < str.length(); ++i)
  {
    char &ch = str[i];
    if(ch >= 'A' && ch <= 'Z')
      ch += 32;
  }
}

static void StripWhitespaces(std::string &str)
{
  for(auto it = str.begin(); it != str.end(); ++it)
  {
    if(isspace(*it))
      str.erase(it);
  }
}

void SpeakNextWord(void)
{
  static SoundStopReceiver ssr;

  if(wordsToSpeakIndex >= wordsToSpeak.size())
  {
    // std::cout << "All words spoken!" << std::endl;
    curSpeakSound = nullptr;
    playing = false;
    return;
  }

  std::string file("vox/");
  file.append(wordsToSpeak[wordsToSpeakIndex]);
  file.append(".wav");
  
  // std::cout << "Playing sound " << file << std::endl;
  
  curSpeakSound = Audio::Engine->play2D(file.c_str(), false, true);
  if(!curSpeakSound) return;
  
  curSpeakSound->setSoundStopEventReceiver(&ssr);
  curSpeakSound->setIsPaused(false);

  ++wordsToSpeakIndex;
}

void Vox::Speak(const std::string &text)
{
  std::istringstream ss(text);
  std::string word;
  
  Stop();
  
  toSpeak = text;

  for(auto it = text.begin(); it != text.end(); ++it)
  {
    char ch = *it;
    
    if(isalnum(ch))
      word += ch;
    else
    {
      std::string after = "";
      
      if(ch == '.')
        after = "_period";
      else if(ch == ',')
        after = "_comma";
      
      StringToLower(word);
      StripWhitespaces(word);
      
      if(!word.empty())
      {
        wordsToSpeak.push_back(word);
        word.clear();
      }
      
      if(!after.empty())
        wordsToSpeak.push_back(after);
    }
  }

  playing = true;
  
  if(curSpeakSound)
    curSpeakSound->stop();
  
  SpeakNextWord();
}

bool Vox::IsPlaying(void)
{
  return playing;
}

void Vox::Stop(void)
{
  if(curSpeakSound)
  {
    curSpeakSound->drop();
    curSpeakSound = nullptr;
  }
  
  toSpeak = "";
  wordsToSpeak.clear();
  wordsToSpeakIndex = 0;
}