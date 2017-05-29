#pragma once

#ifndef INC_IGUI_H
#define INC_IGUI_H


#include "SceneObject.h"


class IGui : public SceneObject,
  public Doh3d::IPositioned2, public Doh3d::ITextured, public Doh3d::ISized2,
  public Doh3d::IInputHandler
{
public:

  virtual ~IGui() { }

  bool containsPoint(Doh3d::Position2 pPoint);

  virtual const Doh3d::Position2& getPosition() const override;

};


#endif // INC_IGUI_H
