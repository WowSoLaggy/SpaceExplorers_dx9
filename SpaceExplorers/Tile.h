#pragma once

#include "GameObject.h"
#include "SceneObject.h"


namespace Model
{

class Tile : public SceneObject
{
public:

  static const int DEFAULT_TILE_SIZE = 64;

public:

  Tile();
  virtual ~Tile();

  void setTurf(GameObject* i_turf);
  void resetTurf();

  const GameObject* getTurf() const { return d_turf; }
  GameObject* getTurf() { return d_turf; }

private:

  GameObject* d_turf;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;
};

} // ns Model
