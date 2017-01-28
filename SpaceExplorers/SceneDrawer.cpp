#include "stdafx.h"
#include "SceneDrawer.h"

#include "Scene.h"


bool SceneDrawer::draw()
{
  if (!Doh3d::Drawer::beginScene())
    return false;

  const Scene scene;
  if (!scene.drawTree(2))
    return false;

  // TODO: remove
  Sleep(10);

  if (!Doh3d::Drawer::endScene())
    return false;

  return true;
}
