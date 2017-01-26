#include "stdafx.h"
#include "SceneDrawer.h"

#include "Scene.h"


bool SceneDrawer::draw()
{
  if (!Doh3d::Drawer::beginScene())
    return false;

  const Scene scene;
  scene.traverseTree(*this);

  // TODO: remove
  Sleep(10);

  if (!Doh3d::Drawer::endScene())
    return false;

  return true;
}

bool SceneDrawer::visit(Doh3d::ITreeItem& pTreeItem)
{
  return true;
}

bool SceneDrawer::visit(const Doh3d::ITreeItem& pTreeItem) const
{
  return true;
}
