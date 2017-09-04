#pragma once

#include "SceneObject.h"


class Tile : public SceneObject
{
public:

  virtual ~Tile();

private:

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;
};
