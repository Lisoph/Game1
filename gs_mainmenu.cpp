#include "gs_mainmenu.hpp"
#include "screen.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "drawing.hpp"
#include "globals.hpp"
#include <cmath>
#include <sstream>
#include <string>
#include "mouse.hpp"
#include "keyboard.hpp"
#include "gui/label.hpp"
#include <SDL2/SDL.h>
#include <memory>

typedef std::basic_stringstream<wchar_t> wstringstream;

float tpx = 0.0f, tpy = 0.0f;
float rot = 0.0f;
constexpr float Pi = 3.14f; // Good enough
std::wstring foo = L"";
std::unique_ptr<Gui::Label> label;


GS_MainMenu::GS_MainMenu(void)
{
  /*Keyboard::KeyPressedEvents += [](int key)->void
  {
    if(key == '\r') key = '\n';
    if(key == 8)
    {
      if(!foo.empty())
        foo.pop_back();
    }
    else
      foo += static_cast<wchar_t>(key);
  };*/
  
  label = std::unique_ptr<Gui::Label>(new Gui::Label(L"Label test"));
  label->Pos() = Gui::Widget::Vec2(10, 100);
}

GS_MainMenu::~GS_MainMenu(void)
{
  //delete label.get(); // Gotta love unique_ptr
}

void GS_MainMenu::Update(void)
{
  tpx = std::cos(rot) * 128.0f + static_cast<float>(Globals::SCREEN_WIDTH / 2);
  tpy = std::sin(rot) * 128.0f + static_cast<float>(Globals::SCREEN_HEIGHT / 2);
  
  if(rot > Pi * 2.0f)
  {
    rot -= Pi * 2.0f;
  }
  else rot += ((Pi / 2) / 180.0f) * Globals::DeltaTime;
  
  if(Keyboard::IsKeyDown(SDLK_RIGHT))
  {
    label->Pos() += Gui::Label::Vec2(1, 0) * Globals::DeltaTime;
  }
  if(Keyboard::IsKeyDown(SDLK_LEFT))
  {
    label->Pos() += Gui::Label::Vec2(-1, 0) * Globals::DeltaTime;
  }
  
  label->Update();
}

void GS_MainMenu::Draw(void)
{
  SDL_SetRenderDrawColor(Screen::renderer, 155, 0, 0, 255);
  SDL_RenderDrawLine(Screen::renderer, Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2, static_cast<int>(tpx), static_cast<int>(tpy));
  
  wstringstream wss;
  
  wss << L"FPS: " << Globals::fps;
  
  Drawing::DrawString(static_cast<int>(tpx), static_cast<int>(tpy), wss.str(), Globals::Font_Default, 0xcc884400);
  
  Drawing::DrawString(Mouse::Position(0) + 10, Mouse::Position(1), foo, Globals::Font_Default, 0xcc884400, true);
  Drawing::DrawString(0, 0, L"test", Globals::Font_Default, 0xcc884400, true);
  
  label->Draw();
}