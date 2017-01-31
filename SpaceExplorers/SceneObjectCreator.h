#pragma once

#ifndef INC_SCENEOBJECTCREATOR_H
#define INC_SCENEOBJECTCREATOR_H


#include "GameInitializer.h"


class SceneObjectCreator
{
public:

  static GameInitializer* create_gameInitializer(const std::string& pTextureDir, const std::string& pFontDir);

};


#endif // INC_SCENEOBJECTCREATOR_H
