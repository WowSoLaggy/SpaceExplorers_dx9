#pragma once

#ifndef INC_SCENEDRAWER_H
#define INC_SCENEDRAWER_H


#include "Scene.h"


class SceneDrawer
{
public:

  bool draw(const Scene& pScene);

private:

  Doh3d::Sprite d_sprite;

};


#endif // INC_SCENEDRAWER_H
