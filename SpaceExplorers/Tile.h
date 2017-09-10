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

  bool isSpace() const;


  void setTurf(GameObject* i_turf);
  void resetTurf();

  void setFloor(GameObject* i_floor);
  void resetFloor();

  void setWall(GameObject* i_wall);
  void resetWall();


  const GameObject* getTurf() const { return d_turf; }
  GameObject* getTurf() { return d_turf; }

  const GameObject* getFloor() const { return d_floor; }
  GameObject* getFloor() { return d_floor; }

  const GameObject* getWall() const { return d_wall; }
  GameObject* getWall() { return d_wall; }

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  GameObject* d_turf;
  GameObject* d_floor;
  GameObject* d_wall;

};

} // ns Model
