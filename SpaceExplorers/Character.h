#pragma once

#include "GameObject.h"


namespace Model
{

enum class ActiveHand
{
  None,
  Right,
  Left
};


class Character
  : public GameObject
  , public Doh3d::INamed
  , public Doh3d::IControlable
{
public:

  Character(const Map& i_map, const Prototype& i_prototype);
  virtual ~Character() { }

  virtual bool isCharacter() const override { return true; }

  ActiveHand getActiveHand() const { return d_activeHand; }
  void setActiveHand(ActiveHand i_activeHand) { d_activeHand = i_activeHand; }

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

  ActiveHand d_activeHand;

};

} // ns Model
