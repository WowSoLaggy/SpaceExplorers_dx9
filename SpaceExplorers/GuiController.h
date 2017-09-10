#pragma once

#include "GuiGroup.h"
#include "Cursor.h"


namespace Controller
{

class Game;


class GuiController
  : public Doh3d::IUpdatable
  , public Doh3d::IDrawable
{
public:

  GuiController(Game& i_game);


  virtual bool draw(Doh3d::Sprite& i_sprite) const override;
  virtual bool update(float i_dt) override;


  bool showCursor();
  void hideCursor();


  bool createLoadingGui();
  bool deleteLoadingGui();
  GuiGroup& getLoadingScreenGuiGroup() { return d_groupLoadingScreen; }

  bool createMainMenu();
  bool deleteMainMenu();
  GuiGroup& getMainMenuGuiGroup() { return d_groupMainMenu; }

  bool createEscapeMenu();
  bool deleteEscapeMenu();
  GuiGroup& getEscapeMenuGuiGroup() { return d_groupEscapeMenu; }

  bool createGameGui();
  bool deleteGameGui();
  GuiGroup& getGameGuiGroup() { return d_groupGameGui; }

private:

  Game& d_game;

  View::Cursor* d_cursor;
  bool d_showCursor;

  GuiGroup d_groupLoadingScreen;
  GuiGroup d_groupMainMenu;
  GuiGroup d_groupEscapeMenu;
  GuiGroup d_groupGameGui;

};

} // ns Controller
