#include "stdafx.h"
#include "Game.h"


bool Game::mainLoop()
{
  LOG(__FUNCTION__);

  Timer timer;
  timer.Start();
  float deltaTime = 0;

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
      continue;
    }

    // InputMan

    if (!d_inputDevice.check())
    {
      if (!d_inputDevice.recreate())
        break;
      continue;
    }

    // Draw
    
    if (!Doh3d::Drawer::beginScene())
      break;

    // TODO: remove
    Sleep(10);

    if (!Doh3d::Drawer::endScene())
      break;

    // TODO: remove
    Sleep(10);

  } // while (d_runMainLoop)

  return true;
}
