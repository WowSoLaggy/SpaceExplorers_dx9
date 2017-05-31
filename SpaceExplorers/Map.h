#pragma once

#ifndef INC_MAP_H
#define INC_MAP_H


#include "SceneObject.h"


class Map : public SceneObject
{
public:

  virtual ~Map();

private:

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;
};


#endif // INC_MAP_H
