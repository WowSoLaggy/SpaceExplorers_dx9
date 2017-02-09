#pragma once

#ifndef INC_PANEL_H
#define INC_PANEL_H


#include "SceneObject.h"
#include "IGui.h"


class Panel : public virtual SceneObject, public virtual IGui
{
public:

  Panel();
  virtual ~Panel() { }

  virtual bool loadAllTextures() override;

  bool setTexture(const std::string& pTextureName);

private:

  Doh3d::TextureId d_ti;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};


#endif // INC_PANEL_H
