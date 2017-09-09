#pragma once


namespace Controller
{
class Game;
} // ns Controller


namespace Engine
{

class InputDevice
{
public:

  bool init();
  bool dispose();

  bool check();
  bool recreate(Controller::Game& i_game);

private:

  Doh3d::InputPars getInputPars();

  Controller::Game* d_game;

};

} // ns Engine
