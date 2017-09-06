#include "stdafx.h"
#include "Game.h"

#include "Scene.h"
#include "GuiObject.h"


namespace Controller
{

bool Game::onMouseMove(bool& pHandled)
{
  LOG(__FUNCTION__);

  auto* pGuiObject = Doh3d::findChildByType<GuiObject>(d_scene, 1);
  if (!pGuiObject)
  {
    echo("ERROR: Can't find GuiObject.");
    return false;
  }

  std::function<bool(SceneObject*, bool&)> checkObject = [&](SceneObject* pSceneObject, bool& pHandled)
  {
    for (auto* pChild : pSceneObject->rchildren())
    {
      if (auto* sceneObject = dynamic_cast<SceneObject*>(pChild))
      {
        if (!checkObject(sceneObject, pHandled))
          return false;
        if (pHandled)
          return true;
      }
    }

    if (auto* pGui = dynamic_cast<Doh3d::IInputHandler*>(pSceneObject))
    {
      if (!pGui->onMouseMove(pHandled))
        return false;
    }

    return true;
  };

  checkObject(pGuiObject, pHandled);

  return true;
}

bool Game::onMouseDown(Doh3d::MouseButton pButton, bool& pHandled)
{
  LOG(__FUNCTION__);

  auto* pGuiObject = Doh3d::findChildByType<GuiObject>(d_scene, 1);
  if (!pGuiObject)
  {
    echo("ERROR: Can't find GuiObject.");
    return false;
  }

  std::function<bool(SceneObject*, bool&)> checkObject = [&](SceneObject* pSceneObject, bool& pHandled)
  {
    for (auto* pChild : pSceneObject->rchildren())
    {
      if (auto* sceneObject = dynamic_cast<SceneObject*>(pChild))
      {
        if (!checkObject(sceneObject, pHandled))
          return false;
        if (pHandled)
          return true;
      }
    }

    if (auto* pGui = dynamic_cast<Doh3d::IInputHandler*>(pSceneObject))
    {
      if (!pGui->onMouseDown(pButton, pHandled))
        return false;
    }

    return true;
  };

  checkObject(pGuiObject, pHandled);

  return true;
}

bool Game::onMouseUp(Doh3d::MouseButton pButton, bool& pHandled)
{
  LOG(__FUNCTION__);

  auto* pGuiObject = Doh3d::findChildByType<GuiObject>(d_scene, 1);
  if (!pGuiObject)
  {
    echo("ERROR: Can't find GuiObject.");
    return false;
  }

  std::function<bool(SceneObject*, bool&)> checkObject = [&](SceneObject* pSceneObject, bool& pHandled)
  {
    for (auto* pChild : pSceneObject->rchildren())
    {
      if (auto* sceneObject = dynamic_cast<SceneObject*>(pChild))
      {
        if (!checkObject(sceneObject, pHandled))
          return false;
        if (pHandled)
          return true;
      }
    }

    if (auto* pGui = dynamic_cast<Doh3d::IInputHandler*>(pSceneObject))
    {
      if (!pGui->onMouseUp(pButton, pHandled))
        return false;
    }

    return true;
  };

  checkObject(pGuiObject, pHandled);

  return true;
}


bool Game::onKeyPressed(Doh3d::Key pKey)
{
  if (d_gameState == GameState::InGame)
  {
    for (auto* pController : d_controllers)
      pController->onKeyPressed(pKey);
  }

  return true;
}

bool Game::onKeyDown(Doh3d::Key pKey)
{
  if (d_gameState == GameState::InGame)
  {
    switch (pKey)
    {
    case DIK_ESCAPE: showInGameMenu(); break;
    default:
      for (auto* pController : d_controllers)
        pController->onKeyDown(pKey);
      break;
    }
  }

  return true;
}

bool Game::onKeyUp(Doh3d::Key pKey)
{
  if (d_gameState == GameState::InGame)
  {
    for (auto* pController : d_controllers)
      pController->onKeyUp(pKey);
  }

  return true;
}

} // ns Controller
