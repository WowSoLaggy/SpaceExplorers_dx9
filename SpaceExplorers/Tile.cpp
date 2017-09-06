#include "stdafx.h"
#include "Tile.h"


namespace SpaceExplorers
{
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


bool Tile::updateSelf(float pDt)
{
  if (d_turf)
  {
    if (!d_turf->update(pDt))
      return false;
  }

  return true;
}

bool Tile::drawSelf(Doh3d::Sprite& pSprite) const
{
  if (d_turf)
  {
    if (!d_turf->draw(pSprite))
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
} // ns SpaceExplorers
