#pragma once


class Scene;


class InputDevice : public Doh3d::IInputHandler
{
public:

  bool init();
  bool dispose();

  bool check();
  bool recreate(Scene& pScene);

  Doh3d::Controller* createNewController();
  Doh3d::Controller* getController(Doh3d::ControllerId i_controllerId);
  bool removeController(Doh3d::ControllerId i_controllerId);

private:

  Doh3d::InputPars getInputPars();

  Scene* d_pScene;

  std::vector<Doh3d::Controller*> d_controllers;

  
  // Input handlers

  virtual bool onMouseMove(bool& pHandled) override;
  virtual bool onMouseDown(Doh3d::MouseButton pButton, bool& pHandled) override;
  virtual bool onMouseUp(Doh3d::MouseButton pButton, bool& pHandled) override;

  virtual bool onKeyPressed(Doh3d::Key pKey) override;
  virtual bool onKeyDown(Doh3d::Key pKey) override;
  virtual bool onKeyUp(Doh3d::Key pKey) override;

};
