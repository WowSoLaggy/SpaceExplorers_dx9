#pragma once

#ifndef INC_GUICONTROLCREATOR_H
#define INC_GUICONTROLCREATOR_H


#include "GuiObject.h"
#include "Cursor.h"
#include "Panel.h"
#include "Button.h"
#include "Text.h"


class GuiControlCreator
{
public:

  static GuiObject* create_guiObject();
  static Cursor* create_cursor();

  static Panel* create_loadScreen_background();

  static Button* create_menu_button();
  static Text* create_menu_text();

  static Panel* create_mainMenu_backGround();

};


#endif // INC_GUICONTROLCREATOR_H
