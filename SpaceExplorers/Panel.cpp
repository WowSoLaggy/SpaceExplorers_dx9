#include "stdafx.h"
#include "Panel.h"


bool Panel::updateSelf(float pDt)
{
  return Doh3d::GPanel::updateSelf(pDt);
}

bool Panel::drawSelf(Doh3d::Sprite& pSprite) const
{
  return Doh3d::GPanel::drawSelf(pSprite);
}
