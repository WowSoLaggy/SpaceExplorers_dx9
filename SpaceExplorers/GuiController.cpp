#include "stdafx.h"
#include "GuiController.h"

#include "GuiControlCreator.h"
#include "Game.h"


namespace Controller
{

GuiController::GuiController(Game& i_game)
  : d_game(i_game)
{
}


bool GuiController::draw(Doh3d::Sprite& i_sprite) const
{
  for (auto* gui : d_groupLoadingScreen.getGuis())
  {
    if (!gui->draw(i_sprite))
      return false;
  }

  for (auto* gui : d_groupMainMenu.getGuis())
  {
    if (!gui->draw(i_sprite))
      return false;
  }

  for (auto* gui : d_groupEscapeMenu.getGuis())
  {
    if (!gui->draw(i_sprite))
      return false;
  }

  return true;
}

bool GuiController::update(float i_dt)
{
  for (auto* gui : d_groupLoadingScreen.getGuis())
  {
    if (!gui->update(i_dt))
      return false;
  }

  for (auto* gui : d_groupMainMenu.getGuis())
  {
    if (!gui->update(i_dt))
      return false;
  }

  for (auto* gui : d_groupEscapeMenu.getGuis())
  {
    if (!gui->update(i_dt))
      return false;
  }

  return true;
}


bool GuiController::createLoadingGui()
{
  LOG(__FUNCTION__);


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

  d_groupLoadingScreen.addGui(pBackground);


  return true;
}

bool GuiController::deleteLoadingGui()
{
  d_groupLoadingScreen.deleteAll();
  return true;
}


bool GuiController::createMainMenu()
{
  LOG(__FUNCTION__);


  // Background

  auto* pBackground = GuiControlCreator::create_mainMenu_backGround();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the main menu.");
    return false;
  }
  pBackground->setPosition(Doh3d::Position2I::zero());
  d_groupMainMenu.addGui(pBackground);


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
  pStartNewGameButton->setOnClickEvent([&]() { return d_game.startNewGame(); });
  d_groupMainMenu.addGui(pStartNewGameButton);


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
  pExitButton->setOnClickEvent([&]() { return d_game.stop(); });
  d_groupMainMenu.addGui(pExitButton);


  // Cursor

  auto* pCursor = GuiControlCreator::create_cursor();
  if (!pCursor)
  {
    echo("ERROR: Can't create the cursor.");
    return false;
  }
  pCursor->setPosition(Doh3d::Screen::getClientCenter() - pCursor->getSizeHalf());
  d_groupMainMenu.addGui(pCursor);


  return true;
}

bool GuiController::deleteMainMenu()
{
  d_groupMainMenu.deleteAll();
  return true;
}


bool GuiController::createEscapeMenu()
{
  LOG(__FUNCTION__);


  // Background

  auto* pBackground = GuiControlCreator::create_escapeMenu_backGround();
  if (!pBackground)
  {
    echo("ERROR: Can't create the background for the escape menu.");
    return false;
  }
  pBackground->setPosition(Doh3d::Position2I::zero());
  d_groupEscapeMenu.addGui(pBackground);


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
  pToMainMenuButton->setOnClickEvent([&]() { return d_game.startNewGame(); });
  d_groupEscapeMenu.addGui(pToMainMenuButton);


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
  pExitButton->setOnClickEvent([&]() { return d_game.stop(); });
  d_groupEscapeMenu.addGui(pExitButton);


  // Cursor

  auto* pCursor = GuiControlCreator::create_cursor();
  if (!pCursor)
  {
    echo("ERROR: Can't create the cursor.");
    return false;
  }
  pCursor->setPosition(Doh3d::Screen::getClientCenter() - pCursor->getSizeHalf());
  d_groupEscapeMenu.addGui(pCursor);


  return true;
}

bool GuiController::deleteEscapeMenu()
{
  d_groupEscapeMenu.deleteAll();
  return true;
}

} // ns Controller
