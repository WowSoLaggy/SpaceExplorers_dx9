#include "stdafx.h"
#include "InputController.h"

#include "Game.h"
#include "Scene.h"
#include "GuiGroup.h"


namespace Controller
{

InputController::InputController(Game& i_game)
  : d_game(i_game)
{
}


GuiGroup* InputController::getGuiGroupToUpdate()
{
  switch (d_game.getGameState())
  {
  case GameState::MainMenu:
    return &d_game.getGuiController().getMainMenuGuiGroup();
  case GameState::EscapeMenu:
    return &d_game.getGuiController().getEscapeMenuGuiGroup();
  }

  return nullptr;
}


bool InputController::onMouseMove(bool& pHandled)
{
  auto* pGuiGroup = getGuiGroupToUpdate();
  if (!pGuiGroup)
    return true;

  for (auto* pGui : pGuiGroup->getGuis())
  {
    bool handled = false;
    if (!pGui->onMouseMove(handled))
      return false;
    if (handled)
      return true;
  }

  return true;
}

bool InputController::onMouseDown(Doh3d::MouseButton pButton, bool& pHandled)
{
  auto* pGuiGroup = getGuiGroupToUpdate();
  if (!pGuiGroup)
    return true;

  for (auto* pGui : pGuiGroup->getGuis())
  {
    bool handled = false;
    if (!pGui->onMouseDown(pButton, handled))
      return false;
    if (handled)
      return true;
  }

  return true;
}

bool InputController::onMouseUp(Doh3d::MouseButton pButton, bool& pHandled)
{
  auto* pGuiGroup = getGuiGroupToUpdate();
  if (!pGuiGroup)
    return true;

  for (auto* pGui : pGuiGroup->getGuis())
  {
    bool handled = false;
    if (!pGui->onMouseUp(pButton, handled))
      return false;
    if (handled)
      return true;
  }

  return true;
}


bool InputController::onKeyPressed(Doh3d::Key pKey)
{
  if (d_game.getGameState() == GameState::InGame)
  {
    for (auto* pController : d_controllers)
      pController->onKeyPressed(pKey);
  }

  return true;
}

bool InputController::onKeyDown(Doh3d::Key pKey)
{
  if (d_game.getGameState() == GameState::InGame)
  {
    switch (pKey)
    {
    case DIK_ESCAPE: d_game.showInGameMenu(); break;
    default:
      for (auto* pController : d_controllers)
        pController->onKeyDown(pKey);
      break;
    }
  }

  return true;
}

bool InputController::onKeyUp(Doh3d::Key pKey)
{
  if (d_game.getGameState() == GameState::InGame)
  {
    for (auto* pController : d_controllers)
      pController->onKeyUp(pKey);
  }

  return true;
}

} // ns Controller
