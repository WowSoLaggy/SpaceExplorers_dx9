#include "stdafx.h"
#include "Engine.h"


namespace SpaceExplorers
{
namespace Engine
{

void Engine::run(const Doh3d::StartupPars& pStartupPars)
{
  CreateDirectory(LOG_DIR_NAME.c_str(), nullptr);
  LOGINIT(LOG_FILE_FULL_NAME, GAME_NAME, GAME_FILE_NAME);
  LOG(__FUNCTION__);

  if (!init(pStartupPars))
    return;

  mainLoop();

  dispose();
}


bool Engine::init(const Doh3d::StartupPars& pStartupPars)
{
  if (!Doh3d::WinClass::registerClass(pStartupPars, GAME_NAME))
    return false;

  if (!d_renderDevice.init())
    return false;
  if (!d_inputDevice.init())
    return false;
  if (!d_resourceController.init())
    return false;

  return true;
}

bool Engine::dispose()
{
  // Ignore return values, try to do all disposes

  d_resourceController.dispose();
  d_inputDevice.dispose();
  d_renderDevice.dispose();

  Doh3d::WinClass::unregisterClass();

  return true;
}


bool Engine::onRenderDeviceRecreate()
{
  if (!d_sceneDrawer.onRenderDeviceRecreate())
    return false;

  return true;
}

} // ns Engine
} // ns SpaceExplorers
