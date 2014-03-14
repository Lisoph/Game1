#pragma once
#include <Eigen/Eigen>
#include <vector>
#include "../entity.hpp"

namespace Gui
{
  class Widget;
}

class Gui::Widget: public Entity
{
public:
  typedef float Scalar;
  // typedef Eigen::Matrix<Scalar, 2, 1> Vec2;
  typedef Entity::Vec2 Vec2;
protected:
  Vec2 /*pos,*/ size;
  Widget *parent;
  std::vector<Widget*> children;
public:
  Widget(void)
  : Entity(), size(0.0f, 0.0f),
    parent(nullptr),
    children()
  {}
  
  virtual ~Widget(void) {}
  
  virtual void Update(void) = 0;
  virtual void Draw(void) = 0;
  
  // Vec2 &Pos(void) { return pos; }
  Vec2 &Size(void) { return size; }
  
  Widget *Parent(void) { return parent; }
  size_t NumChildren(void) const { return children.size(); }
  Widget *Child(size_t index) const { return (index >= NumChildren() || index < 0) ? nullptr : children[index]; }
};