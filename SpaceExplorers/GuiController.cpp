#include "stdafx.h"
#include "GuiController.h"

#include "Scene.h"
#include "GuiControlCreator.h"
#include "GuiNames.h"
#include "Game.h"


bool GuiController::createLoadingGui(Scene& pScene)
{
  LOG(__FUNCTION__);


  // Gui object

  auto* pGuiObject = GuiControlCreator::create_guiObject();
  if (!pGuiObject)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }

  pGuiObject->setName(GuiNames::GROUP_GUI);
  pScene.addChildBack(pGuiObject);


  // Loading screen Gui object

  auto* pLoadingScreenGroup = GuiControlCreator::create_guiObject();
  if (!pLoadingScreenGroup)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }

  pLoadingScreenGroup->setName(GuiNames::GROUP_LOADING_SCREEN);
  pGuiObject->addChildBack(pLoadingScreenGroup);


  // Background

  auto* pBackground = GuiControlCreator::create_loadScreen_background();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the loading screen.");
    return false;
  }

  if (!pBackground->loadAllTextures())
    return false;

  pBackground->setPosition(Doh3d::Screen::getClientCenter() - pBackground->getSizeHalf());

  pLoadingScreenGroup->addChildBack(pBackground);

  return true;
}

bool GuiController::deleteLoadingGui(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pLoadingScreenGroup = pScene.findChild(GuiNames::GROUP_LOADING_SCREEN);
  if (!pLoadingScreenGroup)
  {
    echo("ERROR: Can't find the loading screen Gui group.");
    return false;
  }

  pLoadingScreenGroup->deleteThis();

  return true;
}


bool GuiController::createMainMenu(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pGuiObject = pScene.findChild(GuiNames::GROUP_GUI);
  if (!pGuiObject)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }


  // Main menu Gui object

  auto* pMainMenuGroup = GuiControlCreator::create_guiObject();
  if (!pMainMenuGroup)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }

  pMainMenuGroup->setName(GuiNames::GROUP_MAINMENU);
  pGuiObject->addChildBack(pMainMenuGroup);


  // Background

  auto* pBackground = GuiControlCreator::create_mainMenu_backGround();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the main menu.");
    return false;
  }
  pBackground->setPosition(Doh3d::Position2I::zero());
  pMainMenuGroup->addChildBack(pBackground);


  // Start new game

  auto* pStartNewGameButton = GuiControlCreator::create_menu_button();
  if (!pStartNewGameButton)
  {
    echo("ERROR: Can't create the main menu button.");
    return false;
  }
  pStartNewGameButton->setText("Start new game");
  pStartNewGameButton->setPosition(Doh3d::Screen::getClientRightBottom() - pStartNewGameButton->getSize() +
                                   Doh3d::Position2I(-64, -64 - 32 - 24));
  pStartNewGameButton->setOnClickEvent([&]() { return pScene.getGame().startNewGame(); });
  pMainMenuGroup->addChildBack(pStartNewGameButton);


  // Exit

  auto* pExitButton = GuiControlCreator::create_menu_button();
  if (!pExitButton)
  {
    echo("ERROR: Can't create the main menu button.");
    return false;
  }
  pExitButton->setText("Exit to Desktop");
  pExitButton->setPosition(Doh3d::Screen::getClientRightBottom() - pExitButton->getSize() +
                           Doh3d::Position2I(-64, -64));
  pExitButton->setOnClickEvent([&]() { return pScene.getGame().stop(); });
  pMainMenuGroup->addChildBack(pExitButton);


  // Cursor

  auto* pCursor = GuiControlCreator::create_cursor();
  if (!pCursor)
  {
    echo("ERROR: Can't create the cursor.");
    return false;
  }
  pCursor->setPosition(Doh3d::Screen::getClientCenter() - pCursor->getSizeHalf());
  pMainMenuGroup->addChildBack(pCursor);


  return true;
}

bool GuiController::deleteMainMenu(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pMainMenuGroup = pScene.findChild(GuiNames::GROUP_MAINMENU);
  if (!pMainMenuGroup)
  {
    echo("ERROR: Can't find the main menu Gui group.");
    return false;
  }

  pMainMenuGroup->deleteThis();

  return true;
}


bool GuiController::createIngameMenu(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pGuiObject = pScene.findChild(GuiNames::GROUP_GUI);
  if (!pGuiObject)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }


  // Main menu Gui object

  auto* pIngameMenuGroup = GuiControlCreator::create_guiObject();
  if (!pIngameMenuGroup)
  {
    echo("ERROR: Can't create GuiObject.");
    return false;
  }

  pIngameMenuGroup->setName(GuiNames::GROUP_INGAMEMENU);
  pGuiObject->addChildBack(pIngameMenuGroup);


  // Background

  auto* pBackground = GuiControlCreator::create_ingameMenu_backGround();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the ingame menu.");
    return false;
  }
  pBackground->setPosition(Doh3d::Position2I::zero());
  pIngameMenuGroup->addChildBack(pBackground);


  // To Main Menu

  auto* pToMainMenuButton = GuiControlCreator::create_menu_button();
  if (!pToMainMenuButton)
  {
    echo("ERROR: Can't create the ingame menu button.");
    return false;
  }
  pToMainMenuButton->setText("Exit to Main Menu");
  pToMainMenuButton->setPosition(Doh3d::Screen::getClientRightBottom() - pToMainMenuButton->getSize() +
                                   Doh3d::Position2I(-64, -64 - 32 - 24));
  pToMainMenuButton->setOnClickEvent([&]() { return pScene.getGame().startNewGame(); });
  pIngameMenuGroup->addChildBack(pToMainMenuButton);


  // Exit

  auto* pExitButton = GuiControlCreator::create_menu_button();
  if (!pExitButton)
  {
    echo("ERROR: Can't create the ingame menu button.");
    return false;
  }
  pExitButton->setText("Exit to Desktop");
  pExitButton->setPosition(Doh3d::Screen::getClientRightBottom() - pExitButton->getSize() +
                           Doh3d::Position2I(-64, -64));
  pExitButton->setOnClickEvent([&]() { return pScene.getGame().stop(); });
  pIngameMenuGroup->addChildBack(pExitButton);


  // Cursor

  auto* pCursor = GuiControlCreator::create_cursor();
  if (!pCursor)
  {
    echo("ERROR: Can't create the cursor.");
    return false;
  }
  pCursor->setPosition(Doh3d::Screen::getClientCenter() - pCursor->getSizeHalf());
  pIngameMenuGroup->addChildBack(pCursor);


  return true;
}

bool GuiController::deleteIngameMenu(Scene& pScene)
{
  LOG(__FUNCTION__);

  auto* pIngameMenuGroup = pScene.findChild(GuiNames::GROUP_INGAMEMENU);
  if (!pIngameMenuGroup)
  {
    echo("ERROR: Can't find the ingame menu Gui group.");
    return false;
  }

  pIngameMenuGroup->deleteThis();

  return true;
}
