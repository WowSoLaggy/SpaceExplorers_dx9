#include "stdafx.h"
#include "SceneUpdater.h"

#include "Scene.h"


bool SceneUpdater::update(Scene& pScene, float pDt)
{
  if (!pScene.updateTree(pDt))
    return false;

  return true;
}
