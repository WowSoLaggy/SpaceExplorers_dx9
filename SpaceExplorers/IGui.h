#pragma once

#ifndef INC_IGUI_H
#define INC_IGUI_H


#include "SceneObject.h"


class IGui : public SceneObject,
  public Doh3d::IPositioned2I, public Doh3d::ITextured, public Doh3d::ISized2,
  public Doh3d::IInputHandler
{
public:

  virtual ~IGui() { }

  bool containsPoint(Doh3d::Position2I pPoint);

  virtual const Doh3d::Position2I getPosition() const override;

};


#endif // INC_IGUI_H
