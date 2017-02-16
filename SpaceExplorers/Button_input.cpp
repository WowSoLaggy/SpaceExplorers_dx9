#include "stdafx.h"
#include "Button.h"


bool Button::onMouseMove()
{
  if (d_state == ButtonState::Disabled)
    return true;

  if (containsPoint(Doh3d::InputMan::getCursorPosition()))
  {
    if (d_state == ButtonState::Normal)
      d_state = ButtonState::Selected;
  }
  else
    d_state = ButtonState::Normal;

  return true;
}

bool Button::onMouseDown(Doh3d::MouseButton pButton)
{
  d_state = ButtonState::Pressed;
  return true;
}

bool Button::onMouseUp(Doh3d::MouseButton pButton)
{
  d_state = ButtonState::Normal;
  return true;
}


bool Button::onKeyPressed(Doh3d::Key pKey)
{
  return true;
}

bool Button::onKeyDown(Doh3d::Key pKey)
{
  return true;
}

bool Button::onKeyUp(Doh3d::Key pKey)
{
  return true;
}
