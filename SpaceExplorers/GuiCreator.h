#pragma once

#ifndef INC_GUICREATOR_H
#define INC_GUICREATOR_H


#include "GuiObject.h"
#include "Panel.h"
#include "Cursor.h"


class GuiCreator
{
public:

  static GuiObject* create_guiObject();
  static Cursor* create_cursor();

  static Panel* create_loadScreen_background();

  static Panel* create_mainMenu_backGround();

};


#endif // INC_GUICREATOR_H
