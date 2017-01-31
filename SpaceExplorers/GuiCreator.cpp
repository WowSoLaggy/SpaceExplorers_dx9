#include "stdafx.h"
#include "GuiCreator.h"


GuiObject* GuiCreator::create_guiObject()
{
  return new GuiObject();
}


Panel* GuiCreator::create_loadScreen_backGround()
{
  const std::string texture_fileName_loadScreen_backGround = "Loading_256_64_1_n.png";

  auto* pPanel = new Panel();

  if (!pPanel->setTexture(texture_fileName_loadScreen_backGround))
  {
    delete pPanel;
    return false;
  }

  return pPanel;
}
