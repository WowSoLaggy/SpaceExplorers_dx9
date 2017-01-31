#include "stdafx.h"
#include "GuiCreator.h"


GuiObject* GuiCreator::create_guiObject()
{
  return new GuiObject();
}


Panel* GuiCreator::create_loadScreen_background()
{
  const std::string texture_fileName_loadScreen_background = "Loading_256_64_1_n.png";

  auto* pPanel = new Panel();

  if (!pPanel->setTexture(texture_fileName_loadScreen_background))
  {
    delete pPanel;
    return false;
  }

  return pPanel;
}
