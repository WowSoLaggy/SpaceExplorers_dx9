#include "stdafx.h"
#include "GameController.h"

#include "Scene.h"
#include "GuiController.h"
#include "PrototypeCollection.h"


namespace Controller
{

GameController::GameController(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir)
  : d_runMainLoop(pRunMainLoop), d_textureDir(pTextureDir), d_fontDir(pFontDir), d_state(State::NotInited)
{
}


void GameController::stopGame()
{
  d_state = State::GameStopping;
}


bool GameController::updateSelf(float pDt)
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
    break;

  case State::InGame:
    break;

  case State::GameStopping:
    if (!unloadGame())
      return false;
    break;

  case State::GameStopped:
    break;

  default:
  {
    echo("ERROR: Unexpected state for the GameInitializer object.");
    return false;
  }
  }

  return true;
}


bool GameController::initGameLoadMenu()
{
  if (!initResourceManager())
    return false;

  if (!createLoadingGui())
    return false;

  if (!startGameLoadingThread())
    return false;

  return true;
}

bool GameController::checkGameIsLoaded()
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


bool GameController::initResourceManager()
{
  // TODO: change to calls to the ResourceController of this project
  Doh3d::ResourceMan::setTextureDir(d_textureDir);
  Doh3d::ResourceMan::setFontDir(d_fontDir);
  if (!Doh3d::ResourceMan::indexResources())
    return false;

  return true;
}

bool GameController::createLoadingGui()
{
  LOG(__FUNCTION__);

  auto* pScene = getScene();
  if (!pScene)
  {
    echo("ERROR: Can't find scene to initialize.");
    return false;
  }

  if (!GuiController::createLoadingGui(*pScene))
    return false;

  return true;
}

bool GameController::startGameLoadingThread()
{
  d_state = State::GameLoading;

  std::thread loadGameThread(std::bind(&GameController::loadGame, this));
  loadGameThread.detach();

  return true;
}

void GameController::loadGame()
{
  if (!Doh3d::ResourceMan::loadResources())
  {
    d_state = State::GameLoadFailed;
    return;
  }

  if (!PrototypeCollection::initAllPrototypes())
  {
    d_state = State::GameLoadFailed;
    return;
  }

  if (!PrototypeCollection::loadAllPrototypes())
  {
    d_state = State::GameLoadFailed;
    return;
  }

  d_state = State::GameLoadOk;
}

bool GameController::deleteLoadingGui()
{
  LOG(__FUNCTION__);

  auto* pScene = getScene();
  if (!pScene)
  {
    echo("ERROR: Can't find the scene to create main menu for.");
    return false;
  }

  if (!GuiController::deleteLoadingGui(*pScene))
    return false;

  return true;
}

bool GameController::createMainMenu()
{
  LOG(__FUNCTION__);

  auto* pScene = getScene();
  if (!pScene)
  {
    echo("ERROR: Can't find the scene to create main menu for.");
    return false;
  }

  if (!GuiController::createMainMenu(*pScene))
    return false;

  d_state = State::InGame;

  return true;
}


bool GameController::unloadGame()
{
  d_state = State::GameStopped;
  d_runMainLoop = false;
  return true;
}

} // ns Controller
