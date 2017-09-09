#pragma once

#include "Cursor.h"
#include "Panel.h"
#include "Button.h"
#include "Text.h"


namespace Controller
{

class GuiControlCreator
{
public:

  static View::Cursor* create_cursor();

  static View::Panel* create_loadScreen_background();

  static View::Button* create_menu_button();
  static View::Text* create_menu_text();

  static View::Panel* create_mainMenu_backGround();
  static View::Panel* create_escapeMenu_backGround();

};

} // ns Controller
