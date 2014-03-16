#include "gs_game.hpp"
#include "drawing.hpp"
#include "keyboard.hpp"
#include "menu2.hpp"
#include "sprite.hpp"
#include "globals.hpp"
#include "screen.hpp"
#include "resource_manager.hpp"
#include "mesh.hpp"
#include <SDL2/SDL.h>
#include <Eigen/Eigen>
#include <memory>
#include <sstream>
#include <string>
#include "drawing.hpp"
#include "vox.hpp"
#include "gui/button.hpp"

// std::unique_ptr<Sprite> player, enemy, frankerZ;
// ResourceManager<Sprite> spriteManager;
Mesh mesh;
std::wstring debug;
std::unique_ptr<Gui::Button> btn1;

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
  
  // player.reset(new Sprite(Sprite::Vec2(128, 128)));
  Sprite *player = new Sprite(Sprite::Vec2(128, 128));
  spriteManager.AddResource("Player Sprite", player);
  player->Pos() = Sprite::Vec2(100, 100);
  player->LoadFromFile("sprite.png");
  
  // enemy.reset(new Sprite(Sprite::Vec2(128, 128)));
  Sprite *enemy = new Sprite(Sprite::Vec2(128, 128));
  spriteManager.AddResource("Enemy Sprite", enemy);
  enemy->Pos() = Sprite::Vec2(Globals::SCREEN_WIDTH - enemy->Size()(0) / 2, Globals::SCREEN_HEIGHT - enemy->Size()(1) / 2);
  enemy->LoadFromFile("enemy.png");
  enemy->FrameSize() = Sprite::Vec2(64, 64);
  
  // frankerZ.reset(new Sprite(Sprite::Vec2(256, 256)));
  Sprite *frankerZ = new Sprite(Sprite::Vec2(256, 256));
  spriteManager.AddResource("FrankerZ Sprite", frankerZ);
  frankerZ->LoadFromFile("ttvemotes/FrankerZ.png");
  frankerZ->FrameSize() = Sprite::Vec2(40, 30);
  frankerZ->Pos() = Sprite::Vec2(Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 + 200);
  
  mesh.AddVertex(Eigen::Vector2f(-100.0f, -100.0f));
  mesh.AddVertex(Eigen::Vector2f(120.0f, -90.0f));
  mesh.AddVertex(Eigen::Vector2f(40.0f, 30.0f));
  mesh.AddVertex(Eigen::Vector2f(-100.0f, 100.0f));
  
  // mesh.AddVertexAt(Eigen::Vector2f(-50.0f, 0.0f), mesh.NumVertices() - 1);
  
  const Eigen::AlignedBox2f &aabb = mesh.AABB();
  
  std::basic_stringstream<wchar_t> wss;
  wss << L"min(" << aabb.min()(0) << L", " << aabb.min()(1) << L"), max(" << aabb.max()(0) << L", " << aabb.max()(1) << L")\n";
  debug = wss.str();
  
  btn1.reset(new Gui::Button(L"Click me"));
  btn1->Pos() = Gui::Button::Vec2(5, 200);
  btn1->ClickedEvents() += [](void) -> void { if(!Vox::IsPlaying()) Vox::Speak("Hello yankee, accelerating accelerator safety. Alert, alien is not ok. Please die."); };
}

GS_Game::~GS_Game(void)
{
  std::cout << "GS_Game destructor\n";
}

void GS_Game::Update(void)
{
  constexpr float PLAYER_SPEED = 2.0f;
  
  Sprite *player = spriteManager.Resource("Player Sprite");
  Sprite *enemy = spriteManager.Resource("Enemy Sprite");
  
  if(Keyboard::IsKeyDown(SDLK_LEFT))
    player->Pos()(0) -= PLAYER_SPEED * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_RIGHT))
    player->Pos()(0) += PLAYER_SPEED * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_UP))
    player->Pos()(1) -= PLAYER_SPEED * Globals::DeltaTime;
  if(Keyboard::IsKeyDown(SDLK_DOWN))
    player->Pos()(1) += PLAYER_SPEED * Globals::DeltaTime;
  
  /*player->Update();
  enemy->Update();
  frankerZ->Update();*/
  const size_t max = spriteManager.NumResources();
  for(size_t i = 0; i < max; ++i)
    spriteManager.Resource(i)->Update();
  
  if(enemy->Rot() > 360.0f)
    enemy->Rot() -= 360.0f;
  enemy->Rot() += 2.0f * Globals::DeltaTime;
  
  mesh.Pos() = player->Pos();
  mesh.Update();
  
  btn1->Update();
}

void GS_Game::Draw(void)
{
  Sprite *player = spriteManager.Resource("Player Sprite");
  Sprite *enemy = spriteManager.Resource("Enemy Sprite");
  
  /*player->Draw();
  enemy->Draw();
  frankerZ->Draw();*/
  const size_t max = spriteManager.NumResources();
  for(size_t i = 0; i < max; ++i)
    spriteManager.Resource(i)->Draw();
  
  Eigen::Vector2f dir = enemy->Pos() - player->Pos();
  
  dir.normalize();
  Eigen::Vector2f point = (dir * 200.0f) + player->Pos();
  
  SDL_SetRenderDrawColor(Screen::Renderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(Screen::Renderer, static_cast<int>(player->Pos()(0)), static_cast<int>(player->Pos()(1)), static_cast<int>(point(0)), static_cast<int>(point(1)));
  
  // mesh.Draw();
  btn1->Draw();
  
  Drawing::DrawString(5, 5, debug, Globals::Font_Default, 0, true);
}