#pragma once

#ifndef INC_GAMELOGIC_H
#define INC_GAMELOGIC_H


#include "Scene.h"


class GameLogic
{
public:

  static bool startGame(Scene& pScene, bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);
  static bool stopGame(Scene& pScene);

  static bool startNewGame(Scene& pScene);

private:

  static bool createMap(Scene& pScene);
  static bool createCamera(Scene& pScene);

};


#endif // INC_GAMELOGIC_H
