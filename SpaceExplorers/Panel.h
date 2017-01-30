#pragma once

#ifndef INC_PANEL_H
#define INC_PANEL_H


#include "SceneObject.h"


class Panel : public virtual SceneObject
{
public:

  Panel();
  virtual ~Panel() { }

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

  bool setTexture(const std::string& pTextureName);

private:

  Doh3d::TextureId d_ti;

};


#endif // INC_PANEL_H
