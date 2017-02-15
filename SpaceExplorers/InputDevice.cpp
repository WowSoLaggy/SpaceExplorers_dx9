#include "stdafx.h"
#include "InputDevice.h"


bool InputDevice::init()
{
  return Doh3d::InputMan::init();
}

bool InputDevice::dispose()
{
  return Doh3d::InputMan::dispose();
}


bool InputDevice::check()
{
  return Doh3d::InputMan::isCreated() && Doh3d::InputMan::checkDevices();
}

bool InputDevice::recreate()
{
  LOG(__FUNCTION__);

  if (!Doh3d::InputMan::recreate(getInputPars()))
  {
    echo("ERROR: Can't recreate InputMan.");
    return false;
  }

  return true;
}


Doh3d::InputPars InputDevice::getInputPars()
{
  Doh3d::InputPars inputPars;

  inputPars.mouseSensX() = 1;
  inputPars.mouseSensY() = 1;

  inputPars.mouseAcceleration() = true;

  inputPars.onMouseMove() = std::bind(&InputDevice::OnMouseMove, this);
  inputPars.onMouseDown() = std::bind(&InputDevice::OnMouseDown, this, std::placeholders::_1);
  inputPars.onMouseUp() = std::bind(&InputDevice::OnMouseUp, this, std::placeholders::_1);

  inputPars.onKeyPressed() = std::bind(&InputDevice::OnKeyPressed, this, std::placeholders::_1);
  inputPars.onKeyDown() = std::bind(&InputDevice::OnKeyDown, this, std::placeholders::_1);
  inputPars.onKeyUp() = std::bind(&InputDevice::OnKeyUp, this, std::placeholders::_1);

  return inputPars;
}
