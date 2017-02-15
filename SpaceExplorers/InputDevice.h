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
  virtual bool onMouseDown(int pButton) override;
  virtual bool onMouseUp(int pButton) override;

  virtual bool onKeyPressed(int pKey) override;
  virtual bool onKeyDown(int pKey) override;
  virtual bool onKeyUp(int pKey) override;

};


#endif // INC_INPUTDEVICE_H
