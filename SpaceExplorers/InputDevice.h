#pragma once

#ifndef INC_INPUTDEVICE_H
#define INC_INPUTDEVICE_H


class InputDevice : public Doh3d::IInputHandler
{
public:

  bool init();
  bool dispose();

  bool check();
  bool recreate();

private:

  Doh3d::InputPars getInputPars();


  // Input handlers

  virtual bool onMouseMove() override;
  virtual bool onMouseDown(Doh3d::MouseButton pButton) override;
  virtual bool onMouseUp(Doh3d::MouseButton pButton) override;

  virtual bool onKeyPressed(Doh3d::Key pKey) override;
  virtual bool onKeyDown(Doh3d::Key pKey) override;
  virtual bool onKeyUp(Doh3d::Key pKey) override;

};


#endif // INC_INPUTDEVICE_H
