#pragma once

#ifndef INC_SCENEUPDATER_H
#define INC_SCENEUPDATER_H


#include "Scene.h"


class SceneUpdater
{
public:

  bool update(Scene& scene, float pDt);

};


#endif // INC_SCENEUPDATER_H
