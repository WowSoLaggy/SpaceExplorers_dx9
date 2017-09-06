#pragma once

#include "GameController.h"


namespace Controller
{

class SceneObjectCreator
{
public:

  static GameController* create_gameController(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);

};

} // ns Controller
