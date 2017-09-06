#include "stdafx.h"
#include "Engine.h"

#include "Game.h"


namespace SpaceExplorers
{
namespace Engine
{

bool Engine::mainLoop()
{
  LOG(__FUNCTION__);

  Timer timer;
  timer.Start();
  float deltaTime = 0;


  bool runMainLoop = true;
  d_game = Game::create(runMainLoop, TEXTURE_DIR, FONT_DIR);
  if (!d_game)
  {
    echo("ERROR: Can't create game.");
    return false;
  }


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

    // Update scene

    if (!d_sceneUpdater.update(d_game->getScene(), deltaTime))
      break;

    // Draw scene

    if (!d_sceneDrawer.draw(d_game->getScene()))
      break;

    // TODO: remove sleep
    Sleep(10);

  } // while (d_runMainLoop)

  return true;
}

} // ns Engine
} // ns SpaceExplorers
