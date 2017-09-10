#include "stdafx.h"
#include "Scene.h"

#include "Game.h"
#include "Camera.h"


namespace Controller
{

bool Scene::draw(const Game& i_game)
{
  if (!Doh3d::Drawer::beginScene())
    return false;

  if (!d_sprite.begin())
    return false;


  if (!i_game.draw(d_sprite))
    return false;

  // TODO: remove sleep
  Sleep(10);


  if (!d_sprite.end())
    return false;

  if (!Doh3d::Drawer::endScene())
    return false;

  return true;
}


bool Scene::onRenderDeviceRecreate()
{
  if (!d_sprite.reload())
    return false;

  return true;
}


bool Scene::updateCamera(float i_dt)
{
  if (d_camera)
  {
    if (!d_camera->update(i_dt))
      return false;
  }

  return true;
}

} // ns Controller
