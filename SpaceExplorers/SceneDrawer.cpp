#include "stdafx.h"
#include "SceneDrawer.h"

#include "Scene.h"


bool SceneDrawer::draw(const Scene& pScene)
{
  if (!Doh3d::Drawer::beginScene())
    return false;

  if (!d_sprite.begin())
    return false;


  if (!pScene.draw(d_sprite))
    return false;

  // TODO: remove sleep
  Sleep(10);


  if (!d_sprite.end())
    return false;

  if (!Doh3d::Drawer::endScene())
    return false;

  return true;
}


bool SceneDrawer::onRenderDeviceRecreate()
{
  if (!d_sprite.reload())
    return false;

  return true;
}
