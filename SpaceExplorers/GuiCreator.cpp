#include "stdafx.h"
#include "GuiCreator.h"


GuiObject* GuiCreator::create_guiObject()
{
  return new GuiObject();
}


Panel* GuiCreator::create_loadScreen_background()
{
  // TODO: Where should these consts be kept?
  const std::string loadScreen_background_texture_fileName = "Loading_256_64_1_n.png";
  const Doh3d::Size2 loadScreen_background_size = { 256, 64 };


  auto* pPanel = new Panel();


  if (!pPanel->setTexture(loadScreen_background_texture_fileName))
  {
    delete pPanel;
    return false;
  }

  pPanel->setSize(loadScreen_background_size);


  return pPanel;
}
