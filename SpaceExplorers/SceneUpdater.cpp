#include "stdafx.h"
#include "SceneUpdater.h"

#include "Scene.h"


bool SceneUpdater::update()
{
  Scene scene;
  if (!scene.updateTree(1))
    return false;

  return true;
}
