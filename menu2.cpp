#include "menu2.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "globals.hpp"
#include "gs_mainmenu.hpp"
#include <memory>

std::unique_ptr<Gui::Button> backButton;

GS_Menu2::GS_Menu2(void)
: GameState()
{
  backButton.reset(new Gui::Button(L"Back"));
  backButton->Pos()(1) = Globals::SCREEN_HEIGHT - backButton->Size()(1);
  backButton->ClickedEvents() += [](void) -> void { GameState::SwitchTo(GS_MainMenu::Instance()); };
}

GS_Menu2::~GS_Menu2(void)
{
  
}

void GS_Menu2::Update(void)
{
  backButton->Update();
}

void GS_Menu2::Draw(void)
{
  backButton->Draw();
}