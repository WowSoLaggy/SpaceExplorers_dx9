#pragma once

#ifndef INC_GUICREATOR_H
#define INC_GUICREATOR_H


#include "Gui.h"
#include "Panel.h"


class GuiCreator
{
public:

  static Gui* create_gui();

  static Panel* create_loadScreen_backGround();

};


#endif // INC_GUICREATOR_H
