#include "stdafx.h"
#include "Game.h"


namespace Controller
{

Doh3d::Controller* Game::createNewController()
{
  static int newId = 0;

  auto* pController = new Doh3d::Controller(newId++);
  d_controllers.push_back(pController);

  bindControllerActions(*pController);

  return pController;
}

Doh3d::Controller* Game::getController(Doh3d::ControllerId i_controllerId)
{
  auto it = std::find_if(d_controllers.begin(), d_controllers.end(),
                         [&](auto* i_controller) { return i_controller->getId() == i_controllerId; });
  if (it == d_controllers.end())
    return nullptr;

  return *it;
}

bool Game::removeController(Doh3d::ControllerId i_controllerId)
{
  d_controllers.erase(
    std::remove_if(d_controllers.begin(), d_controllers.end(),
                   [&](auto* i_controller) { return i_controller->getId() == i_controllerId; }),
    d_controllers.end());

  return true;
}


void Game::bindControllerActions(Doh3d::Controller& i_controller)
{
  i_controller.clearBindings();

  i_controller.bindKey(DIK_W, Action::GoUp);
  i_controller.bindKey(DIK_D, Action::GoRight);
  i_controller.bindKey(DIK_S, Action::GoDown);
  i_controller.bindKey(DIK_A, Action::GoLeft);
}

} // ns Controller
