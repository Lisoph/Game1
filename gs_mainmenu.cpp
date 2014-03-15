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
#include "gui/button.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include "sprite.hpp"
#include "menu2.hpp"
#include "game.hpp"

typedef std::basic_stringstream<wchar_t> wstringstream;

float tpx = 0.0f, tpy = 0.0f;
float rot = 0.0f;
constexpr float Pi = 3.14f; // Good enough
std::wstring status = L"Ok";
Sprite spr(Sprite::Vec2(128, 128));

std::unique_ptr<Gui::Label> label;
std::unique_ptr<Gui::Button> button, resetButton, menu2Button;

GS_MainMenu::GS_MainMenu(void)
: GameState()
{
  Keyboard::KeyPressedEvents += [](int key) -> void
  {
    if(!GS_MainMenu::Instance().IsActive()) return;
    
    if(key == SDLK_l)
      spr.SetFrame(1);
    else if(key == SDLK_k)
      spr.SetFrame(0);
    else if(key == SDLK_ESCAPE)
    {
      Game::Running = false;
    }
  };
  
  label.reset(new Gui::Label(L"Label test"));
  label->Pos() = Gui::Widget::Vec2(10, 100);
  
  button.reset(new Gui::Button(L"Hi, I'm a button!"));
  button->Pos() = Gui::Widget::Vec2(10, 400);
  button->ClickedEvents() += [](void) -> void { status = L"Button clicked!"; };
  
  resetButton.reset(new Gui::Button(L"Reset text"));
  resetButton->Pos() = (button->Pos() + Gui::Widget::Vec2(button->Size()(0) + 50, 0));
  resetButton->ClickedEvents() += [](void) -> void { status = L"Ok"; };
  
  menu2Button.reset(new Gui::Button(L"Goto Menu2"));
  menu2Button->Pos()(0) = (Globals::SCREEN_WIDTH / 2) - (menu2Button->Size()(0) / 2);
  menu2Button->Pos()(1) = (Globals::SCREEN_HEIGHT / 2) - (menu2Button->Size()(1) / 2);
  menu2Button->ClickedEvents() += [](void) -> void { GameState::SwitchTo(GS_Menu2::Instance()); };
  
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
  button->Update();
  resetButton->Update();
  menu2Button->Update();
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
  button->Draw();
  resetButton->Draw();
  menu2Button->Draw();
  
  spr.Draw();
}