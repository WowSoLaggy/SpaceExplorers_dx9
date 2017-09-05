#include "stdafx.h"
#include "GameLogic.h"

#include "SceneObjectCreator.h"
#include "GameController.h"
#include "GuiController.h"
#include "Map.h"
#include "Camera.h"


Game* GameLogic::d_game = nullptr;


bool GameLogic::startGame(Game& i_game, Scene& pScene, bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir)
{
  LOG(__FUNCTION__);

  d_game = &i_game;

  auto* pGameController = SceneObjectCreator::create_gameController(pRunMainLoop, pTextureDir, pFontDir);
  if (!pGameController)
  {
    echo("ERROR: Can't create GameController.");
    return false;
  }

  pScene.addChildBack(pGameController);

  return true;
}

bool GameLogic::stopGame(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pGameController = Doh3d::findChildByType<GameController>(pScene, 1);
  if (!pGameController)
  {
    echo("ERROR: Can't find GameController.");
    return false;
  }

  pGameController->stopGame();

  d_game = nullptr;

  return true;
}


bool GameLogic::startNewGame(Scene& pScene)
{
  if (!GuiController::deleteMainMenu(pScene))
    return false;
  
  if (!createMap(pScene))
    return false;

  if (!createCamera(pScene))
    return false;

  if (!createController(pScene))
    return false;

  return true;
}


bool GameLogic::createMap(Scene& pScene)
{
  auto* pMap = Map::createMap();
  if (!pMap)
    return false;

  pMap->setName("Map");
  pScene.addChildBack(pMap);

  return true;
}

bool GameLogic::createCamera(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pCamera = new Camera();
  pCamera->setName("Camera");
  pCamera->setPosition({ 0, 0 });
  pScene.addChildBack(pCamera);

  auto* pPlayer = dynamic_cast<GameObject*>(pScene.findChild("Player", 2));
  if (!pPlayer)
  {
    echo("ERROR: Can't find Player.");
    return false;
  }

  pCamera->bindToObject(pPlayer);

  return true;
}

bool GameLogic::createController(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pController = d_game->getInputDevice().createNewController();

  auto* pPlayer = dynamic_cast<GameObject*>(pScene.findChild("Player", 2));
  if (!pPlayer)
  {
    echo("ERROR: Can't find Player.");
    return false;
  }

  pController->bindObject(pPlayer);

  return true;
}
