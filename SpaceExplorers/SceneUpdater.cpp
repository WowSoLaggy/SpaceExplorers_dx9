#include "stdafx.h"
#include "SceneUpdater.h"

#include "Scene.h"


bool SceneUpdater::update()
{
  Scene scene;
  if (!scene.traverseTree(*this))
    return false;

  return true;
}


bool SceneUpdater::visit(Doh3d::ITreeItem& pTreeItem)
{
  return true;
}
