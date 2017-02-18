#include "stdafx.h"
#include "GameInitializer.h"

#include "Scene.h"
#include "GuiControlCreator.h"  ///< TODO remove this header
#include "GuiController.h"
#include "GuiNames.h"           ///< TODO remove this header


GameInitializer::GameInitializer(const std::string& pTextureDir, const std::string& pFontDir)
  : d_textureDir(pTextureDir), d_fontDir(pFontDir), d_state(State::NotInited)
{
}


bool GameInitializer::updateSelf(float pDt)
{
  LOG(__FUNCTION__);

  switch (d_state)
  {

  case State::NotInited:
    if (!initGameLoadMenu())
      return false;
    break;

  case State::GameLoading:
  case State::GameLoadOk:
  case State::GameLoadFailed:
    if (!checkGameIsLoaded())
      return false;
    break;

  case State::ReadyForMainMenu:
    if (!deleteLoadingGui())
      return false;
    if (!createMainMenu())
      return false;
    if (!deleteSelf())
      return false;
    break;

  default:
  {
    echo("ERROR: Unexpected state for the GameInitializer object.");
    return false;
  }
  }

  return true;
}


bool GameInitializer::initGameLoadMenu()
{
  if (!initResourceManager())
    return false;

  if (!createLoadingGui())
    return false;

  if (!startGameLoadingThread())
    return false;

  return true;
}

bool GameInitializer::checkGameIsLoaded()
{
  if (d_state == State::GameLoading)
    return true;
  if (d_state == State::GameLoadFailed)
    return false;
  if (d_state == State::GameLoadOk)
  {
    d_state = State::ReadyForMainMenu;
    return true;
  }

  return false;
}


bool GameInitializer::initResourceManager()
{
  // TODO: change to calls to teh ResourceController of this project
  Doh3d::ResourceMan::setTextureDir(d_textureDir);
  Doh3d::ResourceMan::setFontDir(d_fontDir);
  if (!Doh3d::ResourceMan::indexResources())
    return false;

  return true;
}

bool GameInitializer::createLoadingGui()
{
  LOG(__FUNCTION__);

  auto* pScene = scene();
  if (!pScene)
  {
    echo("ERROR: Can't find scene to initialize.");
    return false;
  }

  if (!GuiController::createLoadingGui(*pScene))
    return false;

  return true;
}

bool GameInitializer::startGameLoadingThread()
{
  d_state = State::GameLoading;

  std::thread loadGameThread(std::bind(&GameInitializer::loadGame, this));
  loadGameThread.detach();

  return true;
}

void GameInitializer::loadGame()
{
  if (!Doh3d::ResourceMan::loadResources())
  {
    d_state = State::GameLoadFailed;
    return;
  }

  d_state = State::GameLoadOk;
}

bool GameInitializer::deleteLoadingGui()
{
  LOG(__FUNCTION__);

  auto* pScene = scene();
  if (!pScene)
  {
    echo("ERROR: Can't find the scene to create main menu for.");
    return false;
  }

  if (!GuiController::deleteLoadingGui(*pScene))
    return false;

  return true;
}

bool GameInitializer::createMainMenu()
{
  LOG(__FUNCTION__);

  auto* pScene = scene();
  if (!pScene)
  {
    echo("ERROR: Can't find the scene to create main menu for.");
    return false;
  }

  if (!GuiController::createMainMenu(*pScene))
    return false;

  return true;
}

bool GameInitializer::deleteSelf()
{
  deleteThis();
  return true;
}
