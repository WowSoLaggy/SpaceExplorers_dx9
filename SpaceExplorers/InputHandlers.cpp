#include "stdafx.h"
#include "InputDevice.h"

#include "Scene.h"
#include "GuiObject.h"


bool InputDevice::onMouseMove()
{
  LOG(__FUNCTION__);

  if (!d_pScene)
  {
    echo("ERROR: InputDevice has no scene.");
    return false;
  }

  auto* pGuiObject = Doh3d::findChildByType<GuiObject>(*d_pScene, 1);
  if (!pGuiObject)
  {
    echo("ERROR: Can't find GuiObject.");
    return false;
  }

  std::function<bool(SceneObject*)> checkObject = [&](SceneObject* pSceneObject)
  {
    // TODO: check whether the "rchildren" works, check when there will be guis to check it on
    for (auto* pChild : pSceneObject->rchildren())
    {
      if (auto* sceneObject = dynamic_cast<SceneObject*>(pChild))
      {
        if (checkObject(sceneObject))
          return true;
      }
    }

    if (auto* pGui = dynamic_cast<Doh3d::IInputHandler*>(pSceneObject))
    {
      if (pGui->onMouseMove())
        return true;
    }

    return false;
  };

  checkObject(pGuiObject);

  return true;
}

bool InputDevice::onMouseDown(Doh3d::MouseButton pButton)
{
  LOG(__FUNCTION__);

  if (!d_pScene)
  {
    echo("ERROR: InputDevice has no scene.");
    return false;
  }

  auto* pGuiObject = Doh3d::findChildByType<GuiObject>(*d_pScene, 1);
  if (!pGuiObject)
  {
    echo("ERROR: Can't find GuiObject.");
    return false;
  }

  std::function<bool(SceneObject*)> checkObject = [&](SceneObject* pSceneObject)
  {
    // TODO: check whether the "rchildren" works, check when there will be guis to check it on
    for (auto* pChild : pSceneObject->rchildren())
    {
      if (auto* sceneObject = dynamic_cast<SceneObject*>(pChild))
      {
        if (checkObject(sceneObject))
          return true;
      }
    }

    if (auto* pGui = dynamic_cast<Doh3d::IInputHandler*>(pSceneObject))
    {
      if (pGui->onMouseDown(pButton))
        return true;
    }

    return false;
  };

  checkObject(pGuiObject);

  return true;
}

bool InputDevice::onMouseUp(Doh3d::MouseButton pButton)
{
  LOG(__FUNCTION__);

  if (!d_pScene)
  {
    echo("ERROR: InputDevice has no scene.");
    return false;
  }

  auto* pGuiObject = Doh3d::findChildByType<GuiObject>(*d_pScene, 1);
  if (!pGuiObject)
  {
    echo("ERROR: Can't find GuiObject.");
    return false;
  }

  std::function<bool(SceneObject*)> checkObject = [&](SceneObject* pSceneObject)
  {
    // TODO: check whether the "rchildren" works, check when there will be guis to check it on
    for (auto* pChild : pSceneObject->rchildren())
    {
      if (auto* sceneObject = dynamic_cast<SceneObject*>(pChild))
      {
        if (checkObject(sceneObject))
          return true;
      }
    }

    if (auto* pGui = dynamic_cast<Doh3d::IInputHandler*>(pSceneObject))
    {
      if (pGui->onMouseUp(pButton))
        return true;
    }

    return false;
  };

  checkObject(pGuiObject);

  return true;
}


bool InputDevice::onKeyPressed(Doh3d::Key pKey)
{
  return true;
}

bool InputDevice::onKeyDown(Doh3d::Key pKey)
{
  return true;
}

bool InputDevice::onKeyUp(Doh3d::Key pKey)
{
  return true;
}
