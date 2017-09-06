#include "stdafx.h"
#include "Button.h"


namespace View
{

bool Button::onMouseMove(bool& pHandled)
{
  pHandled = false;

  if (d_state == ButtonState::Disabled)
    return true;

  if (containsPoint(Doh3d::InputMan::getCursor().getPosition()))
  {
    pHandled = true;

    if (d_state == ButtonState::Normal)
      d_state = ButtonState::Selected;
  }
  else
    d_state = ButtonState::Normal;

  return true;
}

bool Button::onMouseDown(Doh3d::MouseButton pButton, bool& pHandled)
{
  pHandled = false;

  if (d_state == ButtonState::Disabled)
    return true;

  // TODO: add MBUTTON_LEFT to the Doh3d::MouseButton class or something like this
  // to avoid using of DirectX defines
  if (pButton != MBUTTON_LEFT)
    return true;

  if (containsPoint(Doh3d::InputMan::getCursor().getPosition()))
  {
    pHandled = true;
    d_state = ButtonState::Pressed;
  }
  else
    d_state = ButtonState::Normal;

  return true;
}

bool Button::onMouseUp(Doh3d::MouseButton pButton, bool& pHandled)
{
  LOG(__FUNCTION__);

  pHandled = false;

  if (pButton != MBUTTON_LEFT)
    return true;

  if (containsPoint(Doh3d::InputMan::getCursor().getPosition()))
  {
    pHandled = true;

    if (d_state == ButtonState::Pressed)
    {
      if (!click())
        return false;
    }

    d_state = ButtonState::Selected;
  }
  else
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

} // ns View
