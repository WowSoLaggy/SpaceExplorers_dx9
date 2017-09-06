#include "stdafx.h"
#include "Panel.h"


namespace View
{

Panel::Panel()
{
  d_ti = 0;
}


bool Panel::updateSelf(float pDt)
{
  return true;
}

bool Panel::drawSelf(Doh3d::Sprite& pSprite) const
{
  if (!pSprite.draw(Doh3d::ResourceMan::getTexture(d_ti).get(), &Doh3d::ResourceMan::getTexture(d_ti).getFrame(0),
                    0, getPosition(), D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}


bool Panel::loadAllTextures()
{
  if (!Doh3d::ResourceMan::getTexture(d_ti).load())
    return false;

  return true;
}


bool Panel::setTexture(const std::string& pTextureName)
{
  if (!Doh3d::ResourceMan::getTi(pTextureName, d_ti))
    return false;
  
  return true;
}

} // ns View
