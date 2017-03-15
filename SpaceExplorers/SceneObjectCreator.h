#pragma once

#ifndef INC_SCENEOBJECTCREATOR_H
#define INC_SCENEOBJECTCREATOR_H


#include "GameController.h"


class SceneObjectCreator
{
public:

  static GameController* create_gameController(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);

};


#endif // INC_SCENEOBJECTCREATOR_H
