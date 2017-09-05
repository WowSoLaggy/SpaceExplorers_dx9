#include "stdafx.h"
#include "GuiControlCreator.h"

#include "GuiNames.h"


GuiObject* GuiControlCreator::create_guiObject()
{
  auto* pGuiObject = new GuiObject();
  return pGuiObject;
}

Cursor* GuiControlCreator::create_cursor()
{
  const std::string cursor_texture_fileName = "Cursor_32_32_1_n.png";
  const Doh3d::Size2I cursor_size = { 32, 32 };


  auto* pCursor = new Cursor();
  pCursor->setName(GuiNames::CURSOR);


  if (!pCursor->setTexture(cursor_texture_fileName))
  {
    delete pCursor;
    return nullptr;
  }

  pCursor->setSize(cursor_size);


  return pCursor;
}


Panel* GuiControlCreator::create_loadScreen_background()
{
  const std::string loadScreen_background_texture_fileName = "Loading_256_64_1_n.png";
  const Doh3d::Size2I loadScreen_background_size = { 256, 64 };


  auto* pPanel = new Panel();
  pPanel->setName(GuiNames::LOADING_SCREEN_BACKGROUND);


  if (!pPanel->setTexture(loadScreen_background_texture_fileName))
  {
    delete pPanel;
    return nullptr;
  }

  pPanel->setSize(loadScreen_background_size);


  return pPanel;
}


Panel* GuiControlCreator::create_mainMenu_backGround()
{
  const std::string mainMenu_background_texture_fileName = "MainMenu_1920_1080_1_n.png";
  const Doh3d::Size2I mainMenu_background_size = { 1920, 1080 }; //< TODO: this size should be adapted for the screen resolution
                                                                //< Maybe it should use some option like "stretch" or "fit to screen"


  auto* pPanel = new Panel();
  pPanel->setName(GuiNames::MENU_BACKGROUND);


  if (!pPanel->setTexture(mainMenu_background_texture_fileName))
  {
    delete pPanel;
    return nullptr;
  }

  pPanel->setSize(mainMenu_background_size);


  return pPanel;
}

Button* GuiControlCreator::create_menu_button()
{
  const std::string mainMenu_button_texture_fileName_normal = "Button_256_32_1_n.png";
  const std::string mainMenu_button_texture_fileName_pressed = "ButtonPressed_256_32_1_n.png";
  const std::string mainMenu_button_texture_fileName_selected = "ButtonLight_256_32_1_n.png";
  const std::string mainMenu_button_texture_fileName_disabled = "ButtonBw_256_32_1_n.png";
  const Doh3d::Size2I mainMenu_button_size = { 256, 32 };


  auto* pButton = new Button();
  pButton->setName(GuiNames::MENU_BUTTON);


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

Text* GuiControlCreator::create_menu_text()
{
  auto* pText = new Text();
  pText->setName(GuiNames::MENU_TEXT);

  pText->setFont("Gadugi");

  return pText;
}
