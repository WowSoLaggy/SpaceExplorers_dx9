#pragma once

#ifndef INC_INPUTDEVICE_H
#define INC_INPUTDEVICE_H


class InputDevice
{
public:

  bool check();
  bool recreate();

private:

  Doh3d::InputPars getInputPars();

};


#endif // INC_INPUTDEVICE_H
