#pragma once

#ifndef INC_GAMELOGIC_H
#define INC_GAMELOGIC_H


#include "Game.h"
#include "Scene.h"


class GameLogic
{
public:

  static bool startGame(Game& i_game, Scene& pScene, bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);
  static bool stopGame(Scene& pScene);

  static bool startNewGame(Scene& pScene);

private:

  static Game* d_game;

  static bool createMap(Scene& pScene);
  static bool createCamera(Scene& pScene);
  static bool createController(Scene& pScene);

};


#endif // INC_GAMELOGIC_H
