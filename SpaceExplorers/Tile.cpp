#include "stdafx.h"
#include "Tile.h"


namespace Model
{

Tile::Tile()
  : d_turf(nullptr)
{
}

Tile::~Tile()
{
  resetTurf();
}


bool Tile::update(float i_dt)
{
  if (d_turf)
  {
    if (!d_turf->update(i_dt))
      return false;
  }

  return true;
}

bool Tile::draw(Doh3d::Sprite& i_sprite) const
{
  if (d_turf)
  {
    if (!d_turf->draw(i_sprite))
      return false;
  }

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

} // ns Model
