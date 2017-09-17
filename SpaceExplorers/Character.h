#pragma once

#include "GameObject.h"


namespace Model
{

enum class Hand
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

  Character(Map& i_map, const Prototype& i_prototype);
  virtual ~Character() { }

  virtual bool isCharacter() const override { return true; }

  Hand getActiveHand() const { return d_activeHand; }
  void setActiveHand(Hand i_activeHand) { d_activeHand = i_activeHand; }

  GameObject* getObjectInHand(Hand i_hand) { return d_itemsInHands[i_hand]; }
  void setObjectInHand(Hand i_hand, GameObject* i_object) { d_itemsInHands[i_hand] = i_object; }
  GameObject* removeObjectFromHand(Hand i_hand);

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

  Hand d_activeHand;
  std::map<Hand, GameObject*> d_itemsInHands;

};

} // ns Model
