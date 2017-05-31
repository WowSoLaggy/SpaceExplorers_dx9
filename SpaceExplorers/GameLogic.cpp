#include "stdafx.h"
#include "GameLogic.h"

#include "SceneObjectCreator.h"
#include "GameController.h"


bool GameLogic::startGame(Scene& pScene, bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir)
{
  LOG(__FUNCTION__);

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

  return true;
}


bool GameLogic::startNewGame(Scene& pScene)
{
  return true;
}
