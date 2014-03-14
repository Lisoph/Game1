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
#include "sprite.hpp"

typedef std::basic_stringstream<wchar_t> wstringstream;

float tpx = 0.0f, tpy = 0.0f;
float rot = 0.0f;
constexpr float Pi = 3.14f; // Good enough
std::unique_ptr<Gui::Label> label;
std::wstring status = L"Ok";
Sprite spr(Sprite::Vec2(128, 128));

GS_MainMenu::GS_MainMenu(void)
{
  Keyboard::KeyPressedEvents += [](int key) -> void
  {
    if(key == SDLK_l)
      spr.SetFrame(1);
    else if(key == SDLK_k)
      spr.SetFrame(0);
  };
  
  label = std::unique_ptr<Gui::Label>(new Gui::Label(L"Label test"));
  label->Pos() = Gui::Widget::Vec2(10, 100);
  spr.Pos() = Sprite::Vec2(200, 10);
  
  if(!spr.LoadFromFile("sprite.png"))
    status = L"Sprite not found!";
}

GS_MainMenu::~GS_MainMenu(void) {}

void GS_MainMenu::Update(void)
{
  tpx = std::cos(rot) * 128.0f + static_cast<float>(Globals::SCREEN_WIDTH / 2);
  tpy = std::sin(rot) * 128.0f + static_cast<float>(Globals::SCREEN_HEIGHT / 2);
  
  if(rot > Pi * 2.0f)
  {
    rot -= Pi * 2.0f;
  }
  else rot += ((Pi / 2) / 180.0f) * Globals::DeltaTime;
  
  constexpr float SPEED = 5.0f;
  
  if(Keyboard::IsKeyDown(SDLK_RIGHT))
    spr.Pos() += Sprite::Vec2(SPEED, 0) * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_LEFT))
    spr.Pos() += Sprite::Vec2(-SPEED, 0) * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_UP))
    spr.Pos() += Sprite::Vec2(0, -SPEED) * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_DOWN))
    spr.Pos() += Sprite::Vec2(0, SPEED) * Globals::DeltaTime;
  
  label->Update();
}

void GS_MainMenu::Draw(void)
{
  SDL_SetRenderDrawColor(Screen::Renderer, 155, 0, 0, 255);
  SDL_RenderDrawLine(Screen::Renderer, Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2, static_cast<int>(tpx), static_cast<int>(tpy));
  
  wstringstream wss;
  
  wss << L"FPS: " << Globals::fps;
  
  Drawing::DrawString(static_cast<int>(tpx), static_cast<int>(tpy), wss.str(), Globals::Font_Default, 0xcc884400);
  Drawing::DrawString(0, 0, status, Globals::Font_Default, 0xcc884400, true);
  
  label->Draw();
  spr.Draw();
}