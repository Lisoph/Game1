#include "mesh.hpp"
#include "screen.hpp"
#include <stdexcept>
#include <SDL2/SDL.h>

Mesh::Mesh(void)
: Entity(), vertices()
{}

Mesh::Mesh(const Entity::Vec2 &pos)
: Entity(pos), vertices()
{}

const Eigen::Vector2f &Mesh::Vertex(size_t index)
{
  if(index < 0 || index > NumVertices())
    throw std::runtime_error("You're outta range, dude! ~ Sincerly mesh.cpp");
  
  return vertices[index];
}

void Mesh::AddVertex(const Eigen::Vector2f &vert)
{
  vertices.push_back(vert);
  CalculateAABB();
}

void Mesh::AddVertexAt(const Eigen::Vector2f &vert, size_t index)
{
  if(index < 0)
    throw std::runtime_error("You're outta range, dude! ~ Sincerly mesh.cpp");
  
  if(index > NumVertices())
    index = NumVertices() - 1;
  
  vertices.insert(vertices.begin() + index, vert);
  CalculateAABB();
}

void Mesh::RemoveVertex(size_t index)
{
  if(index < 0 || index > NumVertices())
    throw std::runtime_error("You're outta range, dude! ~ Sincerly mesh.cpp");
  
  vertices.erase(vertices.begin() + index);
  CalculateAABB();
}

void Mesh::RemoveVertex(const Eigen::Vector2f &vert)
{
  for(auto it = vertices.begin(); it != vertices.end(); ++it)
  {
    if((*it) == vert)
      vertices.erase(it);
  }
  
  CalculateAABB();
}

void Mesh::Draw(void)
{
  // DANGER: Placeholder code!
  
  for(auto it = vertices.begin(); it != vertices.end() - 1; ++it)
  {
    Eigen::Vector2f &vec = *it;
    Eigen::Vector2f &vec2 = *(it + 1);
    
    SDL_SetRenderDrawColor(Screen::Renderer, 255, 0, 255, 255);
    SDL_RenderDrawLine(Screen::Renderer, vec(0) + pos(0), vec(1) + pos(1), vec2(0) + pos(0), vec2(1) + pos(1));
  }
  
  Eigen::Vector2f &vec = vertices.back();
  Eigen::Vector2f &vec2 = vertices.front();
  SDL_RenderDrawLine(Screen::Renderer, vec(0) + pos(0), vec(1) + pos(1), vec2(0) + pos(0), vec2(1) + pos(1));
}

void Mesh::CalculateAABB(void)
{
  float left = 0.0f, right = 0.0f, top = 0.0f, bottom = 0.0f;
  
  for(auto it = vertices.begin(); it != vertices.end(); ++it)
  {
    Eigen::Vector2f &vec = *it;
    
    if(vec(0) < left) left = vec(0);
    else if(vec(0) > right) right = vec(0);
    if(vec(1) < top) top = vec(1);
    else if(vec(1) > bottom) bottom = vec(1);
  }
  
  aabb.min() = Eigen::Vector2f(left, top);
  aabb.max() = Eigen::Vector2f(right, bottom);
}