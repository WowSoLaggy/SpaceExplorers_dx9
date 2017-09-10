#include "stdafx.h"
#include "Game.h"

#include "GuiController.h"
#include "Map.h"
#include "Camera.h"
#include "Scene.h"
#include "GameObject.h"


namespace Controller
{

Game::Game(Scene& i_scene, bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir)
  : d_scene(i_scene)
  , d_gameState(GameState::NotInited)
  , d_textureDir(pTextureDir)
  , d_fontDir(pFontDir)
  , d_runMainLoop(pRunMainLoop)
  , d_inputController(*this)
  , d_guiController(*this)
  , d_mapController(*this)
{
}


bool Game::stop()
{
  d_gameState = GameState::Stopping;
  return true;
}


bool Game::draw(Doh3d::Sprite& i_sprite) const
{
  if (!d_mapController.draw(i_sprite))
    return false;

  if (!d_guiController.draw(i_sprite))
    return false;

  return true;
}


bool Game::update(float i_dt)
{
  LOG(__FUNCTION__);

  switch (d_gameState)
  {

  case GameState::NotInited:
    if (!initGameLoadMenu())
      return false;
    break;

  case GameState::Loading:
  case GameState::LoadOk:
  case GameState::LoadFailed:
    if (!checkGameIsLoaded())
      return false;
    break;

  case GameState::ReadyForMainMenu:
    if (!deleteLoadingGui())
      return false;
    if (!createMainMenu())
      return false;
    break;

  case GameState::MainMenu:
  case GameState::InGame:
  case GameState::EscapeMenu:
    if (!updateControllers(i_dt))
      return false;
    break;

  case GameState::Stopping:
    if (!unloadGame())
      return false;
    break;

  case GameState::Stopped:
    break;

  default:
  {
    echo("ERROR: Unexpected GameState.");
    return false;
  }
  }

  return true;
}


bool Game::startNewGame()
{
  if (!d_guiController.deleteMainMenu())
    return false;

  if (!d_mapController.createMap(20, 20))
    return false;

  if (!createBindCamera())
    return false;

  if (!createBindController())
    return false;

  d_gameState = GameState::InGame;

  return true;
}

bool Game::showInGameMenu()
{
  if (!d_guiController.createEscapeMenu())
    return false;

  d_gameState = GameState::EscapeMenu;

  return true;
}


bool Game::createBindCamera()
{
  LOG(__FUNCTION__);

  auto* pCamera = new Camera();
  d_scene.setCamera(pCamera);
  pCamera->setPosition({ 0, 0 });

  auto* pMap = d_mapController.getMap();

  auto it = std::find_if(pMap->getObjects().cbegin(), pMap->getObjects().cend(),
                         [](const Model::GameObject* i_gameObject) { return i_gameObject->getName() == "Player"; });
  if (it == pMap->getObjects().cend())
  {
    echo("ERROR: Can't find Player.");
    return false;
  }

  pCamera->bindToObject(*it);

  return true;
}

bool Game::createBindController()
{
  LOG(__FUNCTION__);

  auto* pController = d_inputController.createNewController();
  if (!pController)
  {
    echo("ERROR: Can't create controller.");
    return false;
  }

  auto* pMap = d_mapController.getMap();

  auto it = std::find_if(pMap->getObjects().cbegin(), pMap->getObjects().cend(),
                         [](const Model::GameObject* i_gameObject) { return i_gameObject->getName() == "Player"; });
  if (it == pMap->getObjects().cend())
  {
    echo("ERROR: Can't find Player.");
    return false;
  }

  pController->bindObject(*it);

  return true;
}

bool Game::updateControllers(float i_dt)
{
  if (!d_mapController.update(i_dt))
    return false;
  if (!d_guiController.update(i_dt))
    return false;

  return true;
}

} // ns Controller
