#pragma once

#include "SceneObject.h"


namespace Model
{

class MapBackground : public SceneObject
{
public:

  virtual ~MapBackground();

  bool setTexture(const std::string& pTexture);

private:

  Doh3d::TextureId d_ti;

  Doh3d::Vector2F d_scale;

  void updateScale();

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;
};

} // ns Model
