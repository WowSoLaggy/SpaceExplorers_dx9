#pragma once

#include "GuiGroup.h"


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


  bool createLoadingGui();
  bool deleteLoadingGui();
  GuiGroup& getLoadingScreenGuiGroup() { return d_groupLoadingScreen; }

  bool createMainMenu();
  bool deleteMainMenu();
  GuiGroup& getMainMenuGuiGroup() { return d_groupMainMenu; }

  bool createEscapeMenu();
  bool deleteEscapeMenu();
  GuiGroup& getEscapeMenuGuiGroup() { return d_groupEscapeMenu; }

private:

  Game& d_game;

  GuiGroup d_groupLoadingScreen;
  GuiGroup d_groupMainMenu;
  GuiGroup d_groupEscapeMenu;

};

} // ns Controller
