#pragma once

#ifndef INC_IGUI_H
#define INC_IGUI_H


class IGui : public Doh3d::IPositioned, public Doh3d::ITextured, public Doh3d::ISized,
  public Doh3d::IInputHandler
{
public:

  virtual ~IGui() { }

};


#endif // INC_IGUI_H
