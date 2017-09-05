#pragma once

#include "Engine.h"
#include "Scene.h"


class GameLogic
{
public:

  static bool startGame(Engine& i_engine, Scene& pScene, bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);
  static bool stopGame(Scene& pScene);

  static bool startNewGame(Scene& pScene);

private:

  static Engine* d_engine;

  static bool createMap(Scene& pScene);
  static bool createCamera(Scene& pScene);
  static bool createController(Scene& pScene);

};
