#include "stdafx.h"
#include "Engine.h"

#include "Game.h"


namespace Engine
{

bool Engine::mainLoop()
{
  Timer timer;
  timer.Start();
  float deltaTime = 0;


  bool runMainLoop = true;
  d_game = new Controller::Game(d_scene, runMainLoop, TEXTURE_DIR, FONT_DIR);


  while (runMainLoop)
  {
    if (Doh3d::winPeekExit())
      break;

    deltaTime = (float)timer.Restart();

    // RenderMan

    if (!d_renderDevice.check())
    {
      if (!d_renderDevice.recreate(GAME_NAME))
        break;

      if (!onRenderDeviceRecreate())
        break;

      continue;
    }

    // InputMan

    if (!d_inputDevice.check())
    {
      if (!d_inputDevice.recreate(*d_game))
        break;
      continue;
    }

    // Update game

    if (!d_game->update(deltaTime))
      break;

    // Draw game

    if (!d_scene.draw(*d_game))
      break;

    // TODO: remove sleep
    Sleep(10);

  } // while (d_runMainLoop)

  return true;
}

} // ns Engine
