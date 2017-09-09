#include "stdafx.h"
#include "Camera.h"

#include "GameObject.h"


namespace Controller
{

void Camera::bindToObject(const Model::GameObject* i_object)
{
  if (d_bindedObject == i_object)
    return;

  unbindFromObject();

  if (!i_object)
    return;

  d_bindedObject = i_object;
}

void Camera::unbindFromObject()
{
  if (d_bindedObject)
    d_bindedObject = nullptr;
}


bool Camera::update(float i_dt)
{
  if (!d_bindedObject)
    return true;

  setPosition(d_bindedObject->getPosition() - Doh3d::Screen::getClientCenter());

  return true;
}

} // ns Controller
