#include "stdafx.h"
#include "Engine.h"

#include "GameLogic.h"


bool Engine::mainLoop()
{
  Timer timer;
  timer.Start();
  float deltaTime = 0;


  bool runMainLoop = true;
  GameLogic::startGame(*this, d_scene, runMainLoop, TEXTURE_DIR, FONT_DIR);


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
      if (!d_inputDevice.recreate(d_scene))
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
