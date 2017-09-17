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
  bool isPassable() const;


  void setTurf(GameObject* i_turf);
  void resetTurf();

  void setFloor(GameObject* i_floor);
  void resetFloor();

  void setWall(GameObject* i_wall);
  void resetWall();


  const Doh3d::Vector2I& getCoords() const { return d_coords; }
  void setCoords(const Doh3d::Vector2I& i_coords) { d_coords = i_coords; }

  Doh3d::Vector2F getTopLeft() const {
    return{
      d_coords.x * DEFAULT_TILE_SIZE,
      d_coords.y * DEFAULT_TILE_SIZE };
  }

  Doh3d::Vector2F getCenter() const {
    return{
      d_coords.x * DEFAULT_TILE_SIZE + DEFAULT_TILE_SIZE / 2,
      d_coords.y * DEFAULT_TILE_SIZE + DEFAULT_TILE_SIZE / 2 };
  }


  GameObject* getTurf() { return d_turf; }
  const GameObject* getTurf() const { return d_turf; }

  GameObject* getFloor() { return d_floor; }
  const GameObject* getFloor() const { return d_floor; }

  GameObject* getWall() { return d_wall; }
  const GameObject* getWall() const { return d_wall; }

  GameObject* getTopLayer();
  const GameObject* getTopLayer() const;

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  Doh3d::Vector2I d_coords;

  GameObject* d_turf;
  GameObject* d_floor;
  GameObject* d_wall;

};

} // ns Model
