#include "stdafx.h"
#include "Game.h"


bool Game::mainLoop()
{
  Timer timer;
  timer.Start();
  float deltaTime = 0;

  d_gameLogic.onGameStart(d_scene, TEXTURE_DIR, FONT_DIR);

  d_runMainLoop = true;
  while (d_runMainLoop)
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
      if (!d_inputDevice.recreate())
        break;
      continue;
    }

    // Update scene

    if (!d_sceneUpdater.update(d_scene, deltaTime))
      break;

    // Draw scene

    if (!d_sceneDrawer.draw(d_scene))
      break;
    
    // TODO: remove sleep
    Sleep(10);

  } // while (d_runMainLoop)

  return true;
}
