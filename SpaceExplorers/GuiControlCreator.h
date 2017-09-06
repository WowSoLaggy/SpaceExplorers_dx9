#pragma once

#include "GuiObject.h"
#include "Cursor.h"
#include "Panel.h"
#include "Button.h"
#include "Text.h"


namespace Controller
{

class GuiControlCreator
{
public:

  static GuiObject* create_guiObject();
  static Cursor* create_cursor();

  static Panel* create_loadScreen_background();

  static Button* create_menu_button();
  static Text* create_menu_text();

  static Panel* create_mainMenu_backGround();
  static Panel* create_ingameMenu_backGround();

};

} // ns Controller
