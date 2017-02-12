#include "stdafx.h"
#include "GuiCreator.h"

#include "GuiNames.h"


GuiObject* GuiCreator::create_guiObject()
{
  auto* pGuiObject = new GuiObject();
  pGuiObject->name() = GuiNames::GUI_OBJECT;
  return pGuiObject;
}


Panel* GuiCreator::create_loadScreen_background()
{
  const std::string loadScreen_background_texture_fileName = "Loading_256_64_1_n.png";
  const Doh3d::Size2 loadScreen_background_size = { 256, 64 };


  auto* pPanel = new Panel();
  pPanel->name() = GuiNames::LOADING_SCREEN_BACKGROUND;


  if (!pPanel->setTexture(loadScreen_background_texture_fileName))
  {
    delete pPanel;
    return nullptr;
  }

  pPanel->setSize(loadScreen_background_size);


  return pPanel;
}
