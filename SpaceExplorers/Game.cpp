#include "stdafx.h"
#include "Game.h"

#include "SceneObjectCreator.h"
#include "GuiController.h"
#include "Map.h"
#include "Camera.h"


Game* Game::create(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir)
{
  LOG(__FUNCTION__);

  auto* pGame = new Game();

  auto* pGameController = SceneObjectCreator::create_gameController(pRunMainLoop, pTextureDir, pFontDir);
  if (!pGameController)
  {
    echo("ERROR: Can't create GameController.");
    return nullptr;
  }

  pGame->getScene().addChildBack(pGameController);

  return pGame;
}


Game::Game()
  : d_scene(*this)
  , d_gameState(GameState::Unknown)
{
}


bool Game::stop()
{
  LOG(__FUNCTION__);

  d_gameState = GameState::Unknown;

  auto* pGameController = Doh3d::findChildByType<GameController>(d_scene, 1);
  if (!pGameController)
  {
    echo("ERROR: Can't find GameController.");
    return false;
  }

  pGameController->stopGame();

  return true;
}


bool Game::startNewGame()
{
  if (!GuiController::deleteMainMenu(d_scene))
    return false;

  if (!createMap())
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
  if (!GuiController::createIngameMenu(d_scene))
    return false;

  d_gameState = GameState::EscapeMenu;

  return true;
}


bool Game::createMap()
{
  auto* pMap = Map::createMap();
  if (!pMap)
    return false;

  pMap->setName("Map");
  d_scene.addChildFront(pMap);

  return true;
}

bool Game::createBindCamera()
{
  LOG(__FUNCTION__);

  auto* pCamera = new Camera();
  pCamera->setName("Camera");
  pCamera->setPosition({ 0, 0 });
  d_scene.addChildBack(pCamera);

  auto* pPlayer = dynamic_cast<GameObject*>(d_scene.findChild("Player", 2));
  if (!pPlayer)
  {
    echo("ERROR: Can't find Player.");
    return false;
  }

  pCamera->bindToObject(pPlayer);

  return true;
}

bool Game::createBindController()
{
  LOG(__FUNCTION__);

  auto* pController = createNewController();
  if (!pController)
  {
    echo("ERROR: Can't create controller.");
    return false;
  }

  auto* pPlayer = dynamic_cast<GameObject*>(d_scene.findChild("Player", 2));
  if (!pPlayer)
  {
    echo("ERROR: Can't find Player.");
    return false;
  }

  pController->bindObject(pPlayer);

  return true;
}
