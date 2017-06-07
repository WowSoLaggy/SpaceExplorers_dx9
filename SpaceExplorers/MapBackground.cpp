#include "stdafx.h"
#include "MapBackground.h"


MapBackground::~MapBackground()
{
}


bool MapBackground::updateSelf(float pDt)
{
  return true;
}

bool MapBackground::drawSelf(Doh3d::Sprite& pSprite) const
{
  if (!pSprite.draw(Doh3d::ResourceMan::getTexture(d_ti).get(), &Doh3d::ResourceMan::getTexture(d_ti).getFrame(0),
                    0, Doh3d::Position2(0, 0), D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}


bool MapBackground::setTexture(const std::string& pTexture)
{
  if (!Doh3d::ResourceMan::getTi(pTexture, d_ti))
    return false;
  return true;
}
