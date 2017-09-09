#include "stdafx.h"
#include "InputDevice.h"

#include "Game.h"


namespace Engine
{

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

bool InputDevice::recreate(Controller::Game& i_game)
{
  LOG(__FUNCTION__);

  d_game = &i_game;

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

  inputPars.inputHandler() = &d_game->getInputController();

  return inputPars;
}

} // ns Engine
