#pragma once

#include "GameObject.h"


namespace Model
{

class Tile
  : public Doh3d::IDrawable
  , public Doh3d::IUpdatable
{
public:

  static const int DEFAULT_TILE_SIZE = 64;

public:

  Tile();
  virtual ~Tile();

  void setTurf(GameObject* i_turf);
  void resetTurf();

  bool isSpace() const;

  const GameObject* getTurf() const { return d_turf; }
  GameObject* getTurf() { return d_turf; }

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  GameObject* d_turf;

};

} // ns Model
