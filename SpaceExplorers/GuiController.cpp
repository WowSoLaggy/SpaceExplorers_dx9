#include "stdafx.h"
#include "GuiController.h"

#include "Scene.h"
#include "GuiControlCreator.h"
#include "GuiNames.h"
#include "GameLogic.h"


bool GuiController::createLoadingGui(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pGuiObject = GuiControlCreator::create_guiObject();
  if (!pGuiObject)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }

  pScene.addChildBack(pGuiObject);


  auto* pBackground = GuiControlCreator::create_loadScreen_background();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the loading screen.");
    return false;
  }

  if (!pBackground->loadAllTextures())
    return false;
  pBackground->setPosition(Doh3d::Screen::getClientCenter() - pBackground->getSizeHalf());

  pGuiObject->addChildBack(pBackground);

  return true;
}

bool GuiController::deleteLoadingGui(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pLoadingScreenBackground = pScene.findChild(GuiNames::LOADING_SCREEN_BACKGROUND);
  if (!pLoadingScreenBackground)
  {
    echo("ERROR: Can't find the loading screen background.");
    return false;
  }

  pLoadingScreenBackground->deleteThis();

  return true;
}


bool GuiController::createMainMenu(Scene& pScene)
{
  LOG(__FUNCTION__);

  // TODO: move this to some inline func (maybe search for scene also?)
  auto* pGuiObject = pScene.findChild(GuiNames::GUI_OBJECT);
  if (!pGuiObject)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }


  // TODO: group Gui groups under one more GuiObject with name ("MainMenu" or "Loading", ...)
  // so that all the group can be easily found and deleted


  auto* pBackground = GuiControlCreator::create_mainMenu_backGround();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the main menu.");
    return false;
  }
  pBackground->setPosition(Doh3d::Position2::zero());
  pGuiObject->addChildBack(pBackground);


  auto* pExitButton = GuiControlCreator::create_mainMenu_button();
  if (!pExitButton)
  {
    echo("ERROR: Can't create the main menu button.");
    return false;
  }
  pExitButton->setPosition(Doh3d::Screen::getClientCenter() - pExitButton->getSizeHalf());
  pExitButton->setOnClickEvent([&]() { return GameLogic::stopGame(pScene); });
  pGuiObject->addChildBack(pExitButton);


  auto* pCursor = GuiControlCreator::create_cursor();
  if (!pCursor)
  {
    echo("ERROR: Can't create the cursor.");
    return false;
  }
  pCursor->setPosition(Doh3d::Screen::getClientCenter() - pCursor->getSizeHalf());
  pGuiObject->addChildBack(pCursor);

  return true;
}
