#include "stdafx.h"
#include "GameInitializer.h"

#include "Scene.h"
#include "GuiCreator.h"


GameInitializer::GameInitializer(const std::string& pTextureDir, const std::string& pFontDir)
  : d_textureDir(pTextureDir), d_fontDir(pFontDir), d_state(State::NotInited)
{
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
  if (!initResourceManager())
    return false;

  if (!createLoadingGui())
    return false;

  if (!startGameLoadingThread())
    return false;

  return true;
}

bool GameInitializer::checkGameIsLoaded()
{
  if (d_state != State::GameLoaded)
    return true;

  return true;
}


bool GameInitializer::initResourceManager()
{
  Doh3d::ResourceMan::setTextureDir(d_textureDir);
  Doh3d::ResourceMan::setFontDir(d_fontDir);
  if (!Doh3d::ResourceMan::init())
    return false;

  return true;
}

bool GameInitializer::createLoadingGui()
{
  LOG(__FUNCTION__);

  auto* pScene = scene();
  if (!pScene)
  {
    echo("ERROR: Can't find scene to initialize.");
    return false;
  }


  auto* pGuiObject = GuiCreator::create_guiObject();
  if (!pGuiObject)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }

  pScene->addChildBack(pGuiObject);


  auto* pBackground = GuiCreator::create_loadScreen_background();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the loading screen.");
    return false;
  }

  if (!pBackground->loadAllTextures())
    return false;

  pGuiObject->addChildBack(pBackground);

  return true;
}

bool GameInitializer::startGameLoadingThread()
{
  d_state = State::GameLoading;

  std::thread loadGameThread(std::bind(&GameInitializer::loadGame, this));
  loadGameThread.detach();

  return true;
}

void GameInitializer::loadGame()
{
  // TODO:
}
