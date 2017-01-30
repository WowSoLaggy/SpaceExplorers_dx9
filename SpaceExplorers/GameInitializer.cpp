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
  LOG(__FUNCTION__);

  auto* pScene = scene();
  if (!pScene)
  {
    echo("ERROR: Can't find scene to initialize.");
    return false;
  }

  // TODO: This should be in some another place (I am more than sure)
  {
    const std::string c_textureDir = "Data/Textures/";
    const std::string c_fontDir = "Data/Fonts/";
    Doh3d::ResourceMan::setTextureDir(c_textureDir);
    Doh3d::ResourceMan::setFontDir(c_fontDir);
    Doh3d::ResourceMan::init();
  }

  auto* pGui = GuiCreator::create_gui();
  pScene->addChildBack(pGui);
  pGui->addChildBack(GuiCreator::create_loadScreen_backGround());

  d_state = State::GameLoading;
  return true;
}

bool GameInitializer::checkGameIsLoaded()
{
  return true;
}
