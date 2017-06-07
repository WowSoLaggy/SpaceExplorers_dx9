#pragma once

#ifndef INC_MAPBACKGROUND_H
#define INC_MAPBACKGROUND_H


#include "SceneObject.h"


class MapBackground : public SceneObject
{
public:

  virtual ~MapBackground();

  bool setTexture(const std::string& pTexture);

private:

  Doh3d::TextureId d_ti;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;
};


#endif // INC_TILE_H
