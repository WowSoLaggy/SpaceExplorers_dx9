#include "stdafx.h"
#include "SceneObjectCreator.h"


GameInitializer* SceneObjectCreator::create_gameInitializer(const std::string& pTextureDir, const std::string& pFontDir)
{
  return new GameInitializer(pTextureDir, pFontDir);
}
