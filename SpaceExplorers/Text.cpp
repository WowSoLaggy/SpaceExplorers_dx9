#include "stdafx.h"
#include "Text.h"


Text::Text()
{
}


bool Text::updateSelf(float pDt)
{
  return true;
}

bool Text::drawSelf(Doh3d::Sprite& pSprite) const
{
  if (!d_textContainer.hasText())
    return true;

  if (!pSprite.draw(d_textContainer.getTexture(), &d_textContainer.getRect(),
                    0, (getPosition() + d_textContainer.getPosition()), D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}


bool Text::loadAllTextures()
{
  return true;
}


bool Text::setText(const std::string& pText)
{
  LOG(__FUNCTION__);

  if (!d_textContainer.setText(pText))
  {
    echo("ERROR: Can't set text to the Text.");
    return false;
  }

  updateSize();
  return true;
}

bool Text::setFont(const std::string& pFontName)
{
  LOG(__FUNCTION__);

  if (!d_textContainer.setFont(pFontName))
  {
    echo("ERROR: Can't set font to the Text.");
    return false;
  }

  updateSize();
  return true;
}

bool Text::setTextAlign(Doh3d::TextAlign pTextAlign)
{
  LOG(__FUNCTION__);

  if (!d_textContainer.setTextAlign(pTextAlign))
  {
    echo("ERROR: Can't set text align to the Text.");
    return false;
  }

  updateSize();
  return true;
}


void Text::updateSize()
{
  setSize({ d_textContainer.textWidth(), d_textContainer.textHeight() });
}
