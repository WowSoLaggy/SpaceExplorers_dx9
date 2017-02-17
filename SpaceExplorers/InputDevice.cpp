#include "stdafx.h"
#include "InputDevice.h"

#include "Scene.h"


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

bool InputDevice::recreate(Scene& pScene)
{
  LOG(__FUNCTION__);

  if (!Doh3d::InputMan::recreate(getInputPars()))
  {
    echo("ERROR: Can't recreate InputMan.");
    return false;
  }

  d_pScene = &pScene;

  return true;
}


Doh3d::InputPars InputDevice::getInputPars()
{
  Doh3d::InputPars inputPars;

  inputPars.mouseSensX() = 1;
  inputPars.mouseSensY() = 1;

  inputPars.mouseAcceleration() = true;

  inputPars.inputHandler() = this;

  return inputPars;
}
