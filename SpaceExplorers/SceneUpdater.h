#pragma once

#include "Scene.h"


namespace SpaceExplorers
{
namespace Controller
{

class SceneUpdater
{
public:

  bool update(Scene& scene, float pDt);

};

} // ns Controller
} // ns SpaceExplorers
