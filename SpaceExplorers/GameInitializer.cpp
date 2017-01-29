#include "stdafx.h"
#include "GameInitializer.h"

#include "Scene.h"
#include "GuiCreator.h"


GameInitializer::GameInitializer()
{
  d_state = State::NotInited;
}

bool GameInitializer::updateSelf(float pDt)
{
  switch (d_state)
  {

  case State::NotInited:
    if (!initGameLoadMenu())
      return false;
    break;

  case State::GameLoading:
    if (!checkGameIsLoaded())
      return false;
    break;

  default:
    break;
  }

  return true;
}


bool GameInitializer::initGameLoadMenu()
{
  if (auto* pScene = scene())
  {
    auto* pGui = GuiCreator::create_gui();
    pScene->addChildBack(pGui);
    pGui->addChildBack(GuiCreator::create_loadScreen_backGround());
  }

  d_state = State::GameLoading;
  return true;
}

bool GameInitializer::checkGameIsLoaded()
{
  return true;
}
