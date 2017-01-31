#pragma once

#ifndef INC_GAMELOGIC_H
#define INC_GAMELOGIC_H


#include "Scene.h"


class GameLogic
{
public:

  void onGameStart(Scene& pScene, const std::string& pTextureDir, const std::string& pFontDir);

};


#endif // INC_GAMELOGIC_H
