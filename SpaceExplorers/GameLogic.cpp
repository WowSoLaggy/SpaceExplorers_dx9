#include "stdafx.h"
#include "GameLogic.h"

#include "SceneObjectCreator.h"


void GameLogic::onGameStart(Scene& pScene, const std::string& pTextureDir, const std::string& pFontDir)
{
  pScene.addChildBack(SceneObjectCreator::create_gameInitializer(pTextureDir, pFontDir));
}
