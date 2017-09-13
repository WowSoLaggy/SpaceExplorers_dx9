#include "stdafx.h"
#include "InputController.h"

#include "Game.h"
#include "Scene.h"
#include "GuiGroup.h"
#include "GameObject.h"
#include "Interaction.h"


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


bool InputController::onMouseMove(bool& i_handled)
{
  auto* pGuiGroup = getGuiGroupToUpdate();
  if (!pGuiGroup)
    return true;

  for (auto* pGui : pGuiGroup->getGuis())
  {
    if (!pGui->onMouseMove(i_handled))
      return false;
    if (i_handled)
      return true;
  }

  return true;
}

bool InputController::onMouseDown(Doh3d::MouseButton i_button, bool& i_handled)
{
  if (auto* pGuiGroup = getGuiGroupToUpdate())
  {
    for (auto* pGui : pGuiGroup->getGuis())
    {
      if (!pGui->onMouseDown(i_button, i_handled))
        return false;
      if (i_handled)
        return true;
    }
  }

  if (d_game.getGameState() == GameState::InGame)
  {
    if (i_button == Doh3d::MouseButton::Left)
    {
      if (!d_controllers.empty())
      {
        if (auto* pController = d_controllers.front())
        {
          Interaction::interact(
            dynamic_cast<Model::GameObject*>(pController->getBindedObject()),
            d_game.getMapController().hitTest());
        }
      }
    }
  }

  return true;
}

bool InputController::onMouseUp(Doh3d::MouseButton i_button, bool& i_handled)
{
  auto* pGuiGroup = getGuiGroupToUpdate();
  if (!pGuiGroup)
    return true;

  for (auto* pGui : pGuiGroup->getGuis())
  {
    if (!pGui->onMouseUp(i_button, i_handled))
      return false;
    if (i_handled)
      return true;
  }

  return true;
}


bool InputController::onKeyPressed(Doh3d::Key i_key)
{
  if (d_game.getGameState() == GameState::InGame)
  {
    for (auto* pController : d_controllers)
      pController->onKeyPressed(i_key);
  }

  return true;
}

bool InputController::onKeyDown(Doh3d::Key i_key)
{
  if (d_game.getGameState() == GameState::InGame)
  {
    switch (i_key)
    {
    case DIK_ESCAPE: d_game.showEscapeMenu(); break;
    default:
      for (auto* pController : d_controllers)
        pController->onKeyDown(i_key);
      break;
    }
  }
  else if (d_game.getGameState() == GameState::EscapeMenu)
  {
    switch (i_key)
    {
    case DIK_ESCAPE: d_game.returnFromEscapeMenu(); break;
    }
  }

  return true;
}

bool InputController::onKeyUp(Doh3d::Key i_key)
{
  if (d_game.getGameState() == GameState::InGame)
  {
    for (auto* pController : d_controllers)
      pController->onKeyUp(i_key);
  }

  return true;
}

} // ns Controller
