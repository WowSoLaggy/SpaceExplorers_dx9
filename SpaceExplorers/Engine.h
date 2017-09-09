#pragma once

#include "RenderDevice.h"
#include "InputDevice.h"
#include "ResourceController.h"
#include "Scene.h"


namespace Controller
{
class Game;
} // ns Controller


namespace Engine
{

class Game;


class Engine
{
public:

  void run(const Doh3d::StartupPars& pStartupPars);

private:

  const std::string GAME_NAME = "The Space Explorers Game";
  const std::string GAME_FILE_NAME = "SpaceExplorers.exe";

  const std::string LOG_DIR_NAME = "Logs";
  const std::string LOG_FILE_NAME = "Log.txt";
  const std::string LOG_FILE_FULL_NAME = LOG_DIR_NAME + "/" + LOG_FILE_NAME;

  const std::string TEXTURE_DIR = "Data/Textures/";
  const std::string FONT_DIR = "Data/Fonts/";

private:

  RenderDevice d_renderDevice;
  InputDevice d_inputDevice;
  ResourceController d_resourceController;

  Controller::Scene d_scene;
  Controller::Game* d_game;

  bool init(const Doh3d::StartupPars& pStartupPars);
  bool mainLoop();
  bool dispose();

  bool onRenderDeviceRecreate();

};

} // ns Engine
