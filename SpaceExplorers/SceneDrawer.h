#pragma once

#include "Scene.h"


class SceneDrawer
{
public:

  bool draw(const Scene& pScene);

  bool onRenderDeviceRecreate();

private:

  Doh3d::Sprite d_sprite;

};
