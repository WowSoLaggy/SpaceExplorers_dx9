#include "stdafx.h"
#include "Panel.h"


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
  LOG(__FUNCTION__);
  int hRes;

  // TODO: remove it from here
  D3DXVECTOR3 d_position(0, 0, 0);
  hRes = pSprite.draw(Doh3d::ResourceMan::getTexture(d_ti).get(), &Doh3d::ResourceMan::getTexture(d_ti).getFrame(0),
                      0, &d_position, D3DCOLOR_ARGB(255, 255, 255, 255));
  if (hRes != S_OK)
  {
    echo("ERROR: Can't draw sprite.");
    return false;
  }

  return true;
}


bool Panel::setTexture(const std::string& pTextureName)
{
  if (!Doh3d::ResourceMan::getTi(pTextureName, d_ti))
    return false;

  // TODO: This should not be here
  if (!Doh3d::ResourceMan::getTexture(d_ti).load())
    return false;
  
  return true;
}
