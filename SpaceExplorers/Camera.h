#pragma once

#include "SceneObject.h"


namespace SpaceExplorers
{
namespace Controller
{

class GameObject;


class Camera : public Doh3d::Camera, public SceneObject
{
public:

  void bindToObject(const GameObject* i_object);
  void unbindFromObject();

private:

  const GameObject* d_bindedObject;

  virtual bool updateSelf(float i_dt) override;

};

} // ns Controller
} // ns SpaceExplorers
