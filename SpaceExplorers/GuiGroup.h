#pragma once

#include "IGui.h"


namespace Controller
{

class GuiGroup
{
public:

  void addGui(View::IGui* i_gui);
  void deleteAll();

  std::vector<View::IGui*>& getGuis() { return d_guis; }
  const std::vector<View::IGui*>& getGuis() const { return d_guis; }

private:

  std::vector<View::IGui*> d_guis;

};

} // ns Controller
