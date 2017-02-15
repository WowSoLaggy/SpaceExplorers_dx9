#pragma once

#ifndef INC_INPUTDEVICE_H
#define INC_INPUTDEVICE_H


class InputDevice
{
public:

  bool init();
  bool dispose();

  bool check();
  bool recreate();

private:

  Doh3d::InputPars getInputPars();


  // Input handlers

  bool OnMouseMove();
  bool OnMouseDown(int pButton);
  bool OnMouseUp(int pButton);

  bool OnKeyPressed(int pKey);
  bool OnKeyDown(int pKey);
  bool OnKeyUp(int pKey);

};


#endif // INC_INPUTDEVICE_H
