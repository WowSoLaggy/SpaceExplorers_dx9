#include "stdafx.h"
#include "Tile.h"


namespace Model
{

Tile::Tile()
  : d_turf(nullptr)
  , d_floor(nullptr)
  , d_wall(nullptr)
{
}

Tile::~Tile()
{
  resetWall();
  resetFloor();
  resetTurf();
}


bool Tile::update(float i_dt)
{
  if (auto* pTopLayer = getTopLayer())
    pTopLayer->update(i_dt);

  return true;
}

bool Tile::draw(Doh3d::Sprite& i_sprite) const
{
  if (auto* pTopLayer = getTopLayer())
    pTopLayer->draw(i_sprite);

  return true;
}


void Tile::setTurf(GameObject* i_turf)
{
  if (i_turf == d_turf)
    return;

  if (d_turf)
    resetTurf();

  if (!i_turf)
    return;

  d_turf = i_turf;
}

void Tile::resetTurf()
{
  if (d_turf)
  {
    delete d_turf;
    d_turf = nullptr;
  }
}

void Tile::setFloor(GameObject* i_floor)
{
  if (i_floor == d_floor)
    return;

  if (d_floor)
    resetFloor();

  if (!i_floor)
    return;

  d_floor = i_floor;
}

void Tile::resetFloor()
{
  if (d_floor)
  {
    delete d_floor;
    d_floor = nullptr;
  }
}

void Tile::setWall(GameObject* i_wall)
{
  if (i_wall == d_wall)
    return;

  if (d_wall)
    resetWall();

  if (!i_wall)
    return;

  d_wall = i_wall;
}

void Tile::resetWall()
{
  if (d_wall)
  {
    delete d_wall;
    d_wall = nullptr;
  }
}


bool Tile::isSpace() const
{
  return !getTopLayer();
}

bool Tile::isPassable() const
{
  if (auto* pTopLayer = getTopLayer())
    return pTopLayer->getPrototype().getPassable();
  return true;
}


GameObject* Tile::getTopLayer()
{
  if (d_wall) return d_wall;
  if (d_floor) return d_floor;
  if (d_turf) return d_turf;

  return nullptr;
}

const GameObject* Tile::getTopLayer() const
{
  if (d_wall) return d_wall;
  if (d_floor) return d_floor;
  if (d_turf) return d_turf;

  return nullptr;
}

} // ns Model
