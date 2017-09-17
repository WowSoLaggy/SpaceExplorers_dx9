#pragma once


namespace View
{
class Cursor;
class Panel;
class Button;
class Text;
class Grid;
}


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

  static View::Grid* create_grid_hands();

};

} // ns Controller
