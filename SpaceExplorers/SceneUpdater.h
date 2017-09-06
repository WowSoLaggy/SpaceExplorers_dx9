#pragma once

#include "Scene.h"


namespace Controller
{

class SceneUpdater
{
public:

  bool update(Scene& scene, float pDt);

};

} // ns Controller
