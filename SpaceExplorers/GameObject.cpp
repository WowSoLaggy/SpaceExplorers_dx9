#include "stdafx.h"
#include "GameObject.h"


namespace Model
{

GameObject::GameObject(const Prototype& i_prototype)
  : d_prototype(i_prototype)
{
}


const Doh3d::Position2F& GameObject::getPosition() const
{
  return d_movementModel.getPosition();
}

void GameObject::setPosition(const Doh3d::Position2F& i_position)
{
  d_movementModel.setPosition(i_position);
}


bool GameObject::update(float i_dt)
{
  if (d_prototype.getMovable() && !d_movementModel.update(i_dt))
    return false;

  Doh3d::Position2I newPosition = d_prototype.getTileBased() ?
    d_movementModel.getPosition() :
    d_movementModel.getPosition() - d_prototype.getSize2();

  setPosition(newPosition);

  return true;
}

bool GameObject::draw(Doh3d::Sprite& i_sprite) const
{
  if (!i_sprite.draw(Doh3d::ResourceMan::getTexture(d_prototype.getTi()).get(),
                    &Doh3d::ResourceMan::getTexture(d_prototype.getTi()).getFrame(0),
                    0, getPosition(), D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}

} // ns Model
