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
  pSprite.setTransform(&d_transformMatrix);

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

  updateScale();

  return true;
}


void MapBackground::updateScale()
{
  // TODO: Create SDK class 'TextureController' that contains Texture, frame controls, scales, stretches, transform matrices etc...

  D3DXVECTOR2 scaleCenter(0, 0);
  D3DXVECTOR2 sizeOrig = D3DXVECTOR2(
    (FLOAT)Doh3d::RenderMan::getRenderPars().resolutionWidth(),
    (FLOAT)Doh3d::RenderMan::getRenderPars().resolutionHeight());
  auto backgroundSize = Doh3d::ResourceMan::getTexture(d_ti).getSize();
  D3DXVECTOR2 scale = D3DXVECTOR2(sizeOrig.x / backgroundSize.x, sizeOrig.y / backgroundSize.y);
  if (scale.x > scale.y)
    scale.y = scale.x;
  else
    scale.x = scale.y;
  D3DXMatrixTransformation2D(&d_transformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);
}
