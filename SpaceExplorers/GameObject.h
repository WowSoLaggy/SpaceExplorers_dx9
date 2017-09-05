#pragma once

#include "SceneObject.h"
#include "Prototype.h"
#include "MovementModel.h"


class GameObject : public SceneObject,
  public Doh3d::IPositioned2I, public Doh3d::IControlable
{
public:

  GameObject(const Prototype& i_prototype);
  virtual ~GameObject() { }

  virtual const Doh3d::Position2I getPosition() const override;

public:

  // IControlable implementation

  virtual void goUpBegin() override { d_movementModel.setGoUp(true); }
  virtual void goRightBegin() override { d_movementModel.setGoRight(true); }
  virtual void goDownBegin() override { d_movementModel.setGoDown(true); }
  virtual void goLeftBegin() override { d_movementModel.setGoLeft(true); }

  virtual void goUpEnd() override { d_movementModel.setGoUp(false); }
  virtual void goRightEnd() override { d_movementModel.setGoRight(false); }
  virtual void goDownEnd() override { d_movementModel.setGoDown(false); }
  virtual void goLeftEnd() override { d_movementModel.setGoLeft(false); }

private:

  const Prototype& d_prototype;

  MovementModel d_movementModel;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};
