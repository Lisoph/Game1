#include "menu2.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "globals.hpp"
#include "gs_mainmenu.hpp"
#include "gs_game.hpp"
#include "keyboard.hpp"
#include "gs_mainmenu.hpp"
#include <memory>

std::unique_ptr<Gui::Button> backButton, gameButton;

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
  };
  
  backButton.reset(new Gui::Button(L"Main menu"));
  backButton->Pos()(1) = Globals::SCREEN_HEIGHT - backButton->Size()(1);
  backButton->ClickedEvents() += [](void) -> void { GameState::SwitchTo(GS_MainMenu::Instance()); };
  
  gameButton.reset(new Gui::Button(L"Game"));
  gameButton->Pos() = Gui::Widget::Vec2(Globals::SCREEN_WIDTH / 2 - gameButton->Size()(0) / 2, Globals::SCREEN_HEIGHT / 2 - gameButton->Size()(1) / 2);
  gameButton->ClickedEvents() += [](void) -> void { GameState::SwitchTo(GS_Game::Instance()); };
}

GS_Menu2::~GS_Menu2(void)
{
  
}

void GS_Menu2::Update(void)
{
  backButton->Update();
  gameButton->Update();
}

void GS_Menu2::Draw(void)
{
  backButton->Draw();
  gameButton->Draw();
}