#include "stdafx.h"
#include "Game.h"


void Game::run(const Doh3d::StartupPars& pStartupPars)
{
  CreateDirectory(LOG_DIR_NAME.c_str(), nullptr);
  LOGINIT(LOG_FILE_FULL_NAME, GAME_NAME, GAME_FILE_NAME);
  LOG(__FUNCTION__);

  if (!registerWinClass(pStartupPars))
    return;

  mainLoop();

  unregisterWinClass();
}


bool Game::registerWinClass(const Doh3d::StartupPars& pStartupPars)
{
  return Doh3d::WinClass::registerClass(pStartupPars, GAME_NAME);
}

bool Game::unregisterWinClass()
{
  Doh3d::WinClass::unregisterClass();
  return true;
}
