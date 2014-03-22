#include "menu2.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "globals.hpp"
#include "gs_mainmenu.hpp"
#include "gs_game.hpp"
#include "keyboard.hpp"
#include "gs_mainmenu.hpp"
#include "drawing.hpp"
#include "util.hpp"
#include "ttv_chat.hpp"
#include <memory>
#include <cstdlib>
#include <iostream>
#include "vox.hpp"

std::unique_ptr<Gui::Button> backButton, gameButton, sendBtn;
std::wstring curInput;
Net::TTVChat ttvChat;

GS_Menu2::GS_Menu2(void)
: GameState()
{
  Keyboard::KeyPressedEvents += [](int key)
  {
    if(!GS_Menu2::Instance().IsActive()) return;
    
    if(key == SDLK_ESCAPE)
    {
      GameState::SwitchTo(GS_MainMenu::Instance());
    }
    else if(key == SDLK_BACKSPACE)
    {
      if(!curInput.empty())
        curInput.pop_back();
    }
    else if(key == SDLK_RETURN)
    {
      curInput += L'\n';
    }
  };
  
  Keyboard::TextInputEvents += [](const std::string &text)
  {
    if(!GS_Menu2::Instance().IsActive()) return;
    
    curInput += Util::Utf8ToWString(text);
  };
  
  backButton.reset(new Gui::Button(L"Main menu"));
  backButton->Pos()(0) = 10;
  backButton->Pos()(1) = Globals::SCREEN_HEIGHT - backButton->Size()(1) - 10;
  backButton->ClickedEvents() += [](void) -> void { GameState::SwitchTo(GS_MainMenu::Instance()); };
  
  gameButton.reset(new Gui::Button(L"Game"));
  gameButton->Pos() = Gui::Widget::Vec2(Globals::SCREEN_WIDTH / 2 - gameButton->Size()(0) / 2, Globals::SCREEN_HEIGHT / 2 - gameButton->Size()(1) / 2);
  gameButton->ClickedEvents() += [](void) -> void { GameState::SwitchTo(GS_Game::Instance()); };
  
  sendBtn.reset(new Gui::Button(L"Send message"));
  sendBtn->Pos() = Gui::Widget::Vec2(10, 10);
  sendBtn->ClickedEvents() += [](void) -> void { ttvChat.Send(Util::WStringToUtf8(curInput)); };
  
  if(!ttvChat.Connect("singender_holzkuebel", "oauth:dijbmxq6pd4srpbsmc5yy2hcms9d63m", "#singender_holzkuebel"))
  {
    std::cout << "DAMMIT\n";
  }
  
  ttvChat.MessageReceiveEvents() += [](const std::string &msg) -> void
  {
    if(Vox::IsPlaying())
      Vox::Stop();
    
    Vox::Speak(msg);
  };
  // ttvChat.MessageReceiveEvents() += [](const std::string &msg) -> void { std::cout << "\t\t" << msg << '\n'; };
}

GS_Menu2::~GS_Menu2(void)
{
  
}

void GS_Menu2::Update(void)
{
  backButton->Update();
  gameButton->Update();
  sendBtn->Update();
}

void GS_Menu2::Draw(void)
{
  backButton->Draw();
  gameButton->Draw();
  sendBtn->Draw();
  
  Drawing::DrawString(10, 200, curInput, Globals::Font_Default, 0xff0000ff);
}