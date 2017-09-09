#pragma once

#include "Prototype.h"
#include "MovementModel.h"


namespace Model
{

class GameObject
  : public Doh3d::IUpdatable
  , public Doh3d::IDrawable
  , public Doh3d::IControlable
  , public Doh3d::INamed
{
public:

  GameObject(const Prototype& i_prototype);
  virtual ~GameObject() { }

  const Doh3d::Position2F& getPosition() const;
  void setPosition(const Doh3d::Position2F& i_position);

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

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

};

} // ns Model
