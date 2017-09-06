#pragma once

#include "GameController.h"


namespace SpaceExplorers
{
namespace Controller
{

class SceneObjectCreator
{
public:

  static GameController* create_gameController(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);

};

} // ns Controller
} // ns SpaceExplorers
