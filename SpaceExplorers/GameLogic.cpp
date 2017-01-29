#include "stdafx.h"
#include "GameLogic.h"

#include "GameInitializer.h"


void GameLogic::onGameStart(Scene& pScene)
{
  pScene.addChildBack(new GameInitializer());
}
