#include "stdafx.h"
#include "GameObject.h"

#include "Map.h"


namespace Model
{

GameObject::GameObject(Map& i_map, const Prototype& i_prototype)
  : d_map(i_map)
  , d_prototype(i_prototype)
  , d_movementModel(*this)
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

  if (!updateAnimation(i_dt))
    return false;

  return true;
}

bool GameObject::draw(Doh3d::Sprite& i_sprite) const
{
  Doh3d::Position2I position =
    d_movementModel.getPosition()
    + d_prototype.getTextureOffset()
    - d_prototype.getSize2();

  int frame = getCurrentFrame();

  if (!i_sprite.draw(Doh3d::ResourceMan::getTexture(d_prototype.getTi()).get(),
                    &Doh3d::ResourceMan::getTexture(d_prototype.getTi()).getFrame(frame),
                    0, position, D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}


const Doh3d::IShape* GameObject::getCollisionShape() const
{
  return d_prototype.getCollisionShape();
}

bool GameObject::isPassable() const
{
  if (isDoor())
    return isOpen();

  return d_prototype.getPassable();
}

} // ns Model
