#include "gs_game.hpp"
#include "drawing.hpp"
#include "keyboard.hpp"
#include "menu2.hpp"
#include "sprite.hpp"
#include "globals.hpp"
#include "screen.hpp"
#include "resource_manager.hpp"
#include <SDL2/SDL.h>
#include <Eigen/Eigen>
#include <memory>

std::unique_ptr<Sprite> player, enemy;
ResourceManager<int> mgrTest;

GS_Game::GS_Game(void)
: GameState()
{
  Keyboard::KeyPressedEvents += [](int key) -> void
  {
    if(!GS_Game::Instance().IsActive()) return;
    
    if(key == SDLK_ESCAPE)
    {
      GameState::SwitchTo(GS_Menu2::Instance());
    }
  };
  
  player.reset(new Sprite(Sprite::Vec2(128, 128)));
  player->Pos() = Sprite::Vec2(100, 100);
  player->LoadFromFile("sprite.png");
  
  enemy.reset(new Sprite(Sprite::Vec2(128, 128)));
  enemy->Pos() = Sprite::Vec2(300, 300);
  enemy->LoadFromFile("enemy.png");
  enemy->FrameSize() = Sprite::Vec2(64, 64);
  
  
  
  mgrTest.AddResource("myInt", new int(123));
}

GS_Game::~GS_Game(void)
{}

void GS_Game::Update(void)
{
  constexpr float PLAYER_SPEED = 2.0f;
  
  if(Keyboard::IsKeyDown(SDLK_LEFT))
    player->Pos()(0) -= PLAYER_SPEED * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_RIGHT))
    player->Pos()(0) += PLAYER_SPEED * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_UP))
    player->Pos()(1) -= PLAYER_SPEED * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_DOWN))
    player->Pos()(1) += PLAYER_SPEED * Globals::DeltaTime;
  
  player->Update();
  enemy->Update();
}

void GS_Game::Draw(void)
{
  player->Draw();
  enemy->Draw();
  
  Eigen::Vector2f dir = enemy->Pos() - player->Pos();
  dir.normalize();
  Eigen::Vector2f point = (dir * 200.0f) + player->Pos();
  
  SDL_SetRenderDrawColor(Screen::Renderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(Screen::Renderer, (int)player->Pos()(0), (int)player->Pos()(1), (int)point(0), (int)point(1));
}