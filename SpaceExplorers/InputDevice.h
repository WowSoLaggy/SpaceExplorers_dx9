#pragma once

#ifndef INC_INPUTDEVICE_H
#define INC_INPUTDEVICE_H


class Scene;


class InputDevice : public Doh3d::IInputHandler
{
public:

  bool init();
  bool dispose();

  bool check();
  bool recreate(Scene& pScene);

private:

  Doh3d::InputPars getInputPars();

  Scene* d_pScene;

  
  // Input handlers

  virtual bool onMouseMove(bool& pHandled) override;
  virtual bool onMouseDown(Doh3d::MouseButton pButton, bool& pHandled) override;
  virtual bool onMouseUp(Doh3d::MouseButton pButton, bool& pHandled) override;

  virtual bool onKeyPressed(Doh3d::Key pKey) override;
  virtual bool onKeyDown(Doh3d::Key pKey) override;
  virtual bool onKeyUp(Doh3d::Key pKey) override;

};


#endif // INC_INPUTDEVICE_H
