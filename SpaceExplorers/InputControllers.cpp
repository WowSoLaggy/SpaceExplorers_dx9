#include "stdafx.h"
#include "InputDevice.h"


Doh3d::Controller* InputDevice::createNewController()
{
  static int newId = 0;

  auto* pController = new Doh3d::Controller(newId++);
  d_controllers.push_back(pController);

  return pController;
}

Doh3d::Controller* InputDevice::getController(Doh3d::ControllerId i_controllerId)
{
  auto it = std::find_if(d_controllers.begin(), d_controllers.end(),
                         [&](auto* i_controller) { return i_controller->getId() == i_controllerId; });
  if (it == d_controllers.end())
    return nullptr;

  return *it;
}

bool InputDevice::removeController(Doh3d::ControllerId i_controllerId)
{
  d_controllers.erase(
    std::remove_if(d_controllers.begin(), d_controllers.end(),
                   [&](auto* i_controller) { return i_controller->getId() == i_controllerId; }),
    d_controllers.end());

  return true;
}
