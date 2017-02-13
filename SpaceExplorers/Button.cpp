#include "stdafx.h"
#include "Button.h"


Button::Button()
{
  d_tiNormal = 0;
  d_tiPressed = 0;
  d_tiSelected = 0;
  d_tiDisabled = 0;

  d_state = ButtonState::Normal;
}


bool Button::updateSelf(float pDt)
{
  return true;
}

bool Button::drawSelf(Doh3d::Sprite& pSprite) const
{
  LOG(__FUNCTION__);

  int ti = d_tiNormal;

  switch (d_state)
  {
  case ButtonState::Normal:
    ti = d_tiNormal;
    break;
  case ButtonState::Pressed:
    ti = d_tiPressed;
    break;
  case ButtonState::Selected:
    ti = d_tiSelected;
    break;
  case ButtonState::Disabled:
    ti = d_tiDisabled;
    break;
  default:
    echo("ERROR: Unknown button state.");
    return false;
    break;
  }

  if (!pSprite.draw(Doh3d::ResourceMan::getTexture(ti).get(), &Doh3d::ResourceMan::getTexture(ti).getFrame(0),
                    0, getPosition(), D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}


bool Button::loadAllTextures()
{
  if (!Doh3d::ResourceMan::getTexture(d_tiNormal).load())
    return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiPressed).load())
    return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiSelected).load())
    return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiDisabled).load())
    return false;

  return true;
}


bool Button::setTexture(
  const std::string& pTextureNameNormal,
  const std::string& pTextureNamePressed,
  const std::string& pTextureNameSelected,
  const std::string& pTextureNameDisabled)
{
  if (!Doh3d::ResourceMan::getTi(pTextureNameNormal, d_tiNormal))
    return false;
  if (!Doh3d::ResourceMan::getTi(pTextureNamePressed, d_tiPressed))
    return false;
  if (!Doh3d::ResourceMan::getTi(pTextureNameSelected, d_tiSelected))
    return false;
  if (!Doh3d::ResourceMan::getTi(pTextureNameDisabled, d_tiDisabled))
    return false;

  return true;
}
