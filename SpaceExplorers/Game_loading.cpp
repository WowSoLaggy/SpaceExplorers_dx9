#include "stdafx.h"
#include "Game.h"

#include "PrototypeCollection.h"
#include "Scene.h"


namespace Controller
{

bool Game::initGameLoadMenu()
{
  if (!initResourceManager())
    return false;

  if (!createLoadingGui())
    return false;

  if (!startGameLoadingThread())
    return false;

  return true;
}

bool Game::checkGameIsLoaded()
{
  if (d_gameState == GameState::Loading)
    return true;
  if (d_gameState == GameState::LoadFailed)
    return false;
  if (d_gameState == GameState::LoadOk)
  {
    d_gameState = GameState::ReadyForMainMenu;
    return true;
  }

  return false;
}


bool Game::initResourceManager()
{
  // TODO: change to calls to the ResourceController of this project
  Doh3d::ResourceMan::setTextureDir(d_textureDir);
  Doh3d::ResourceMan::setFontDir(d_fontDir);
  if (!Doh3d::ResourceMan::indexResources())
    return false;

  return true;
}

bool Game::createLoadingGui()
{
  return d_guiController.createLoadingGui();
}

bool Game::startGameLoadingThread()
{
  d_gameState = GameState::Loading;

  std::thread loadGameThread(std::bind(&Game::loadGame, this));
  loadGameThread.detach();

  return true;
}

void Game::loadGame()
{
  if (!Doh3d::ResourceMan::loadResources())
  {
    d_gameState = GameState::LoadFailed;
    return;
  }

  if (!Model::PrototypeCollection::initAllPrototypes())
  {
    d_gameState = GameState::LoadFailed;
    return;
  }

  if (!Model::PrototypeCollection::loadAllPrototypes())
  {
    d_gameState = GameState::LoadFailed;
    return;
  }

  d_gameState = GameState::LoadOk;
}

bool Game::deleteLoadingGui()
{
  return d_guiController.deleteLoadingGui();
}

bool Game::createMainMenu()
{
  if (!d_guiController.createMainMenu())
    return false;

  d_gameState = GameState::MainMenu;

  return true;
}


bool Game::unloadGame()
{
  d_gameState = GameState::Stopped;
  d_runMainLoop = false;
  return true;
}

} // ns Controller
