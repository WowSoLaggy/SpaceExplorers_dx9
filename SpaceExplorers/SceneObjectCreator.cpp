#include "stdafx.h"
#include "SceneObjectCreator.h"


GameController* SceneObjectCreator::create_gameController(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir)
{
  return new GameController(pRunMainLoop, pTextureDir, pFontDir);
}
