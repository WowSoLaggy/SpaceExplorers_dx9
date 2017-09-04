#pragma once

#include "SceneObject.h"
#include "Prototype.h"


class GameObject : public SceneObject, public Doh3d::IPositioned2
{
public:

  GameObject(const Prototype& i_prototype);
  virtual ~GameObject() { }

  virtual const Doh3d::Position2 getPosition() const override;

private:

  const Prototype& d_prototype;

};
