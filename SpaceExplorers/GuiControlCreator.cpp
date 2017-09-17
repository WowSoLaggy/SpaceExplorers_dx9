#include "stdafx.h"
#include "GuiControlCreator.h"

#include "Cursor.h"
#include "Panel.h"
#include "Button.h"
#include "Text.h"
#include "Grid.h"


namespace Controller
{

View::Cursor* GuiControlCreator::create_cursor()
{
  const std::string cursor_texture_fileName = "Cursor_32_32_1_n.png";
  const Doh3d::Size2I cursor_size = { 32, 32 };


  auto* pCursor = new View::Cursor();


  if (!pCursor->setTexture(cursor_texture_fileName))
  {
    delete pCursor;
    return nullptr;
  }

  pCursor->setSize(cursor_size);


  return pCursor;
}


View::Panel* GuiControlCreator::create_loadScreen_background()
{
  const std::string loadScreen_background_texture_fileName = "Loading_256_64_1_n.png";
  const Doh3d::Size2I loadScreen_background_size = { 256, 64 };


  auto* pPanel = new View::Panel();


  if (!pPanel->setTexture(loadScreen_background_texture_fileName))
  {
    delete pPanel;
    return nullptr;
  }

  pPanel->setSize(loadScreen_background_size);


  return pPanel;
}


View::Panel* GuiControlCreator::create_mainMenu_backGround()
{
  const std::string mainMenu_background_texture_fileName = "MainMenu_1920_1080_1_n.png";
  const Doh3d::Size2I mainMenu_background_size = { 1920, 1080 }; //< TODO: this size should be adapted for the screen resolution
                                                                //< Maybe it should use some option like "stretch" or "fit to screen"


  auto* pPanel = new View::Panel();


  if (!pPanel->setTexture(mainMenu_background_texture_fileName))
  {
    delete pPanel;
    return nullptr;
  }

  pPanel->setSize(mainMenu_background_size);


  return pPanel;
}

View::Button* GuiControlCreator::create_menu_button()
{
  const std::string mainMenu_button_texture_fileName_normal = "Button_256_32_1_n.png";
  const std::string mainMenu_button_texture_fileName_pressed = "ButtonPressed_256_32_1_n.png";
  const std::string mainMenu_button_texture_fileName_selected = "ButtonLight_256_32_1_n.png";
  const std::string mainMenu_button_texture_fileName_disabled = "ButtonBw_256_32_1_n.png";
  const Doh3d::Size2I mainMenu_button_size = { 256, 32 };


  auto* pButton = new View::Button();


  if (!pButton->setTexture(
    mainMenu_button_texture_fileName_normal,
    mainMenu_button_texture_fileName_pressed,
    mainMenu_button_texture_fileName_selected,
    mainMenu_button_texture_fileName_disabled))
  {
    delete pButton;
    return nullptr;
  }

  pButton->setSize(mainMenu_button_size);


  pButton->setFont("Gadugi");
  pButton->setTextAlign(Doh3d::TextAlign::Center);


  return pButton;
}

View::Text* GuiControlCreator::create_menu_text()
{
  auto* pText = new View::Text();

  pText->setFont("Gadugi");

  return pText;
}


View::Panel* GuiControlCreator::create_escapeMenu_backGround()
{
  const std::string escapeMenu_background_texture_fileName = "MenuFade_32_32_1_n.png";
  const Doh3d::Size2I escapeMenu_background_size = { 1920, 1080 };  //< TODO: this size should be adapted for the screen resolution
                                                                    //< Maybe it should use some option like "stretch" or "fit to screen"


  auto* pPanel = new View::Panel();


  if (!pPanel->setTexture(escapeMenu_background_texture_fileName))
  {
    delete pPanel;
    return nullptr;
  }

  pPanel->setSize(escapeMenu_background_size);


  return pPanel;
}


View::Grid* GuiControlCreator::create_grid_hands()
{
  auto* pGrid = new View::Grid();

  if (!pGrid->setTexture(
    "GridUL_13_13_1_n.png",
    "GridUR_13_13_1_n.png",
    "GridBL_13_13_1_n.png",
    "GridBR_13_13_1_n.png",
    "GridU_72_13_1_n.png",
    "GridR_13_72_1_n.png",
    "GridB_72_13_1_n.png",
    "GridL_13_72_1_n.png",
    "GridItem_72_72_1_n.png",
    "GridFrame_68_68_1_n.png"))
  {
    delete pGrid;
    return nullptr;
  }

  pGrid->setGridSize({ 2, 1 });

  return pGrid;
}

} // ns Controller
