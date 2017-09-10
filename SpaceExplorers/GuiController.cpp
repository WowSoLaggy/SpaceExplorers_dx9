#include "stdafx.h"
#include "GuiController.h"

#include "GuiControlCreator.h"
#include "Game.h"


namespace Controller
{

GuiController::GuiController(Game& i_game)
  : d_game(i_game)
  , d_cursor(nullptr)
  , d_showCursor(false)
{
}


bool GuiController::draw(Doh3d::Sprite& i_sprite) const
{
  LOG(__FUNCTION__);

  Doh3d::SpriteTransformGuard spriteTransformGuard(i_sprite);
  i_sprite.resetTransform();

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

  for (auto* gui : d_groupGameGui.getGuis())
  {
    if (!gui->draw(i_sprite))
      return false;
  }

  for (auto* gui : d_groupEscapeMenu.getGuis())
  {
    if (!gui->draw(i_sprite))
      return false;
  }

  if (d_showCursor)
  {
    if (!d_cursor)
    {
      echo("ERROR: No cursor created.");
      return false;
    }

    d_cursor->draw(i_sprite);
  }

  return true;
}

bool GuiController::update(float i_dt)
{
  LOG(__FUNCTION__);

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

  for (auto* gui : d_groupGameGui.getGuis())
  {
    if (!gui->update(i_dt))
      return false;
  }

  if (d_showCursor)
  {
    if (!d_cursor)
    {
      echo("ERROR: No cursor created.");
      return false;
    }

    d_cursor->update(i_dt);
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


  hideCursor();

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


  showCursor();

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


  // Return to game

  auto* pReturnToGame = GuiControlCreator::create_menu_button();
  if (!pReturnToGame)
  {
    echo("ERROR: Can't create the escape menu button.");
    return false;
  }
  pReturnToGame->setText("Return to Game");
  pReturnToGame->setPosition(Doh3d::Screen::getClientRightBottom() - pReturnToGame->getSize() +
                                   Doh3d::Position2I(-64, -64 - 32 - 24 - 32 - 24));
  pReturnToGame->setOnClickEvent([&]() { return d_game.returnFromEscapeMenu(); });
  d_groupEscapeMenu.addGui(pReturnToGame);


  // To Main Menu

  auto* pToMainMenuButton = GuiControlCreator::create_menu_button();
  if (!pToMainMenuButton)
  {
    echo("ERROR: Can't create the escape menu button.");
    return false;
  }
  pToMainMenuButton->setText("Exit to Main Menu");
  pToMainMenuButton->setPosition(Doh3d::Screen::getClientRightBottom() - pToMainMenuButton->getSize() +
                                 Doh3d::Position2I(-64, -64 - 32 - 24));
  pToMainMenuButton->setOnClickEvent([&]() { return d_game.stopGame(); });
  d_groupEscapeMenu.addGui(pToMainMenuButton);


  // Exit

  auto* pExitButton = GuiControlCreator::create_menu_button();
  if (!pExitButton)
  {
    echo("ERROR: Can't create the escape menu button.");
    return false;
  }
  pExitButton->setText("Exit to Desktop");
  pExitButton->setPosition(Doh3d::Screen::getClientRightBottom() - pExitButton->getSize() +
                           Doh3d::Position2I(-64, -64));
  pExitButton->setOnClickEvent([&]() { return d_game.stop(); });
  d_groupEscapeMenu.addGui(pExitButton);


  return true;
}

bool GuiController::deleteEscapeMenu()
{
  d_groupEscapeMenu.deleteAll();
  return true;
}


bool GuiController::createGameGui()
{
  LOG(__FUNCTION__);


  showCursor();

  return true;
}

bool GuiController::deleteGameGui()
{
  d_groupGameGui.deleteAll();
  return true;
}


bool GuiController::showCursor()
{
  LOG(__FUNCTION__);

  if (!d_cursor)
  {
    d_cursor = GuiControlCreator::create_cursor();
    d_cursor->setPosition(Doh3d::Screen::getClientCenter() - d_cursor->getSizeHalf());
  }

  if (!d_cursor)
  {
    echo("ERROR: Can't create cursor.");
    return false;
  }

  d_showCursor = true;

  return true;
}

void GuiController::hideCursor()
{
  d_showCursor = false;
}

} // ns Controller
