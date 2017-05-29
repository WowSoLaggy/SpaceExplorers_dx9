#include "stdafx.h"
#include "Button.h"

#include "Text.h"


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

  // Draw the main texture

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

  // Draw the text
  
  if (d_textContainer.hasText() &&
    !pSprite.draw(d_textContainer.getTexture(), &d_textContainer.getRect(),
                    0, (getPosition() + d_textContainer.getPosition()), D3DCOLOR_ARGB(255, 255, 255, 255)))
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


bool Button::click()
{
  LOG(__FUNCTION__);

  // TODO: return the visibility check
  if ((d_state == ButtonState::Disabled)/* || (!d_isVisible)*/)
    return true;

  if (d_onClickEvent != nullptr)
  {
    if (!d_onClickEvent())
      return false;
  }

  return true;
}


void Button::setSize(const Doh3d::Size2& pSize)
{
  LOG(__FUNCTION__);

  IGui::setSize(pSize);

  if (!d_textContainer.setBasisPosition(pSize / 2))
    echo("ERROR: Can't set the text basis position for Button.");
}


bool Button::setText(const std::string& pText)
{
  LOG(__FUNCTION__);

  if (!d_textContainer.setText(pText))
  {
    echo("ERROR: Can't set text to the Button.");
    return false;
  }

  return true;
}

bool Button::setFont(const std::string& pFontName)
{
  LOG(__FUNCTION__);

  if (!d_textContainer.setFont(pFontName))
  {
    echo("ERROR: Can't set font to the Button.");
    return false;
  }

  return true;
}

bool Button::setTextAlign(Doh3d::TextAlign pTextAlign)
{
  LOG(__FUNCTION__);

  if (!d_textContainer.setTextAlign(pTextAlign))
  {
    echo("ERROR: Can't set text align to the Button.");
    return false;
  }

  return true;
}
