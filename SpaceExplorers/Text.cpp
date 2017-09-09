#include "stdafx.h"
#include "Text.h"


namespace View
{

Text::Text()
{
}


bool Text::update(float i_dt)
{
  return true;
}

bool Text::draw(Doh3d::Sprite& i_sprite) const
{
  if (!d_textContainer.hasText())
    return true;

  if (!i_sprite.draw(d_textContainer.getTexture(), &d_textContainer.getRect(),
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

} // ns View
