#include "stdafx.h"
#include "GuiGroup.h"


namespace Controller
{

void GuiGroup::addGui(View::IGui* i_gui)
{
  if (!i_gui)
    return;

  d_guis.push_back(i_gui);
}

void GuiGroup::deleteAll()
{
  for (auto* pGui : d_guis)
    delete pGui;

  d_guis.clear();
}

} // ns Controller
