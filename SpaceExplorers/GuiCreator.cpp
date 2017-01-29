#include "stdafx.h"
#include "GuiCreator.h"


Gui* GuiCreator::create_gui()
{
  return new Gui();
}


Panel* GuiCreator::create_loadScreen_backGround()
{
  auto* pPanel = new Panel();

  return pPanel;
}
