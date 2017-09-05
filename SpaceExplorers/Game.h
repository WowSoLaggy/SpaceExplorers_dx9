#pragma once

#ifndef INC_GAME_H
#define INC_GAME_H


#include "RenderDevice.h"
#include "InputDevice.h"
#include "ResourceController.h"
#include "SceneUpdater.h"
#include "SceneDrawer.h"
#include "Scene.h"


class Game
{
public:

  void run(const Doh3d::StartupPars& pStartupPars);

  InputDevice& getInputDevice() { return d_inputDevice; }

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
  SceneUpdater d_sceneUpdater;
  SceneDrawer d_sceneDrawer;
  Scene d_scene;


  bool init(const Doh3d::StartupPars& pStartupPars);
  bool mainLoop();
  bool dispose();

  bool onRenderDeviceRecreate();

};


#endif // INC_GAME_H
