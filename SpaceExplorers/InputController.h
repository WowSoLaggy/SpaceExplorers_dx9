#pragma once


namespace Controller
{

class Game;
class GuiGroup;


class InputController : public Doh3d::IInputHandler
{

public:

  InputController(Game& i_game);


  Doh3d::Controller* createNewController();
  Doh3d::Controller* getController(Doh3d::ControllerId i_controllerId);
  bool removeController(Doh3d::ControllerId i_controllerId);
  bool removeAllControllers();

  void bindControllerActions(Doh3d::Controller& i_controller);


  // Input handlers

  virtual bool onMouseMove(bool& i_handled) override;
  virtual bool onMouseDown(Doh3d::MouseButton i_button, bool& i_handled) override;
  virtual bool onMouseUp(Doh3d::MouseButton i_button, bool& i_handled) override;

  virtual bool onKeyPressed(Doh3d::Key i_key) override;
  virtual bool onKeyDown(Doh3d::Key i_key) override;
  virtual bool onKeyUp(Doh3d::Key i_key) override;

private:

  Game& d_game;

  std::vector<Doh3d::Controller*> d_controllers;

  GuiGroup* getGuiGroupToUpdate();

};

} // ns Controller
