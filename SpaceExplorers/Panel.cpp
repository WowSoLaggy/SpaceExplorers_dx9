#include "stdafx.h"
#include "Panel.h"


namespace View
{

Panel::Panel()
  : d_ti(0)
  , d_fitScreen(false)
{
}


bool Panel::update(float i_dt)
{
  return true;
}

bool Panel::draw(Doh3d::Sprite& i_sprite) const
{
  Doh3d::SpriteTransformGuard spriteTransformGuard(i_sprite);

  if (d_fitScreen)
  {
    i_sprite.setTranslation(Doh3d::Position2I::zero());
    i_sprite.setScale(d_scale);
  }

  if (!i_sprite.draw(Doh3d::ResourceMan::getTexture(d_ti).get(), &Doh3d::ResourceMan::getTexture(d_ti).getFrame(0),
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


bool Panel::setTexture(const std::string& i_textureName)
{
  if (!Doh3d::ResourceMan::getTi(i_textureName, d_ti))
    return false;
  
  return true;
}


void Panel::setFitScreen(bool i_fitScreen)
{
  d_fitScreen = i_fitScreen;
  updateScale();
}

void Panel::updateScale()
{
  D3DXVECTOR2 scaleCenter(0, 0);
  D3DXVECTOR2 sizeOrig = D3DXVECTOR2(
    (FLOAT)Doh3d::RenderMan::getRenderPars().resolutionWidth(),
    (FLOAT)Doh3d::RenderMan::getRenderPars().resolutionHeight());
  auto backgroundSize = Doh3d::ResourceMan::getTexture(d_ti).getSize();
  d_scale = { sizeOrig.x / backgroundSize.x, sizeOrig.y / backgroundSize.y };
  if (d_scale.x > d_scale.y)
    d_scale.y = d_scale.x;
  else
    d_scale.x = d_scale.y;
}

} // ns View
