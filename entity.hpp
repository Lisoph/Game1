#pragma once
#include <Eigen/Eigen>

class Entity
{
public:
  typedef float Scalar;
  typedef Eigen::Matrix<Scalar, 2, 1> Vec2;
protected:
  Vec2 pos;
public:
  Entity(void)
  : pos(0, 0)
  {};
  
  Entity(const Vec2 &pos)
  : pos(pos)
  {}
  
  Entity(Vec2 &&pos)
  : pos(pos) // std::move maybe?
  {}
  
  virtual ~Entity(void) {}
  
  Vec2 &Pos(void) { return pos; }
  
  virtual void Update(void) = 0;
  virtual void Draw(void) = 0;
};