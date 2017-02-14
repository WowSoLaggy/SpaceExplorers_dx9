#pragma once

#ifndef INC_BUTTON_H
#define INC_BUTTON_H


#include "SceneObject.h"
#include "IGui.h"
#include "ButtonStates.h"


class Button : public virtual SceneObject, public virtual IGui
{
public:

  Button();
  virtual ~Button() { }

  virtual bool loadAllTextures() override;

  bool setTexture(
    const std::string& pTextureNameNormal,
    const std::string& pTextureNamePressed,
    const std::string& pTextureNameSelected,
    const std::string& pTextureNameDisabled);

private:

  Doh3d::TextureId d_tiNormal;
  Doh3d::TextureId d_tiPressed;
  Doh3d::TextureId d_tiSelected;
  Doh3d::TextureId d_tiDisabled;

  ButtonState d_state;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};


#endif // INC_BUTTON_H