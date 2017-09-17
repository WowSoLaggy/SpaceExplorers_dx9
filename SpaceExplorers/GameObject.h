#pragma once

#include "Prototype.h"
#include "MovementModel.h"
#include "States.h"


namespace Model
{

class Map;


class GameObject
  : public Doh3d::IUpdatable
  , public Doh3d::IDrawable
  , public Doh3d::IControlable
  , public Doh3d::INamed
  , public Doh3d::ICollidable
  , public Doh3d::IAnimated
{
public:

  GameObject(const Map& i_map, const Prototype& i_prototype);
  virtual ~GameObject() { }

  const Doh3d::Position2F& getPosition() const;
  void setPosition(const Doh3d::Position2F& i_position);

  const Map& getMap() const { return d_map; }
  const Prototype& getPrototype() const { return d_prototype; }

  virtual const Doh3d::IShape* getCollisionShape() const;

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

  StateSet& getStates() { return d_stateSet; }
  const StateSet& getStates() const { return d_stateSet; }

  virtual const Doh3d::AnimationSet& getAnimationSet() const override { return d_prototype.getAnimationSet(); }


  bool isDoor() const { return d_prototype.getBehaviour() == Model::Behaviour::Door; }
  bool isCharacter() const { return d_prototype.getBehaviour() == Model::Behaviour::Character; }
  bool isPickable() const { return d_prototype.getPickable(); }

  bool isOpen() const { return d_stateSet.Test(State::Open); }
  bool isPassable() const;


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

  const Map& d_map;
  const Prototype& d_prototype;

  MovementModel d_movementModel;

  StateSet d_stateSet;
};

} // ns Model
