#include "stdafx.h"
#include "SceneObjectCreator.h"


namespace SpaceExplorers
{
namespace Controller
{

GameController* SceneObjectCreator::create_gameController(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir)
{
  return new GameController(pRunMainLoop, pTextureDir, pFontDir);
}

} // ns Controller
} // ns SpaceExplorers
