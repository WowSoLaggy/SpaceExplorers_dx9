#pragma once

#ifndef INC_GUICREATOR_H
#define INC_GUICREATOR_H


#include "GuiObject.h"
#include "Panel.h"


class GuiCreator
{
public:

  static GuiObject* create_guiObject();

  static Panel* create_loadScreen_background();

};


#endif // INC_GUICREATOR_H
