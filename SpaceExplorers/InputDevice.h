#pragma once


namespace Engine
{

class Game;


class InputDevice
{
public:

  bool init();
  bool dispose();

  bool check();
  bool recreate(Game& i_game);

private:

  Doh3d::InputPars getInputPars();

  Game* d_game;

};

} // ns Engine
