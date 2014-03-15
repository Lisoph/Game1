#pragma once
#include <Eigen/Eigen>
#include <vector>
#include "entity.hpp"

class Geometry: public Entity
{
  protected:
    std::vector<Eigen::Vector2f> vertices;
    Eigen::AlignedBox2f aabb;
  public:
    Geometry(void);
    Geometry(const Entity::Vec2 &pos);
    
    size_t NumVertices(void) { return vertices.size(); }
    const Eigen::Vector2f &Vertex(size_t index);
    
    void AddVertex(const Eigen::Vector2f &vert) { vertices.push_back(vert); CalculateAABB(); }
    void AddVertexAt(const Eigen::Vector2f &vert, size_t index);
    
    void RemoveVertex(size_t index);
    void RemoveVertex(const Eigen::Vector2f &vert);
    
    const Eigen::AlignedBox2f &AABB(void) const { return aabb; }
    
    void Update(void) override {}
    void Draw(void) override;
  protected:
    void CalculateAABB(void);
};