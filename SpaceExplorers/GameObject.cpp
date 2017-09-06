#include "stdafx.h"
#include "GameObject.h"


namespace SpaceExplorers
{
namespace Model
{

GameObject::GameObject(const Prototype& i_prototype)
  : d_prototype(i_prototype)
{
}


const Doh3d::Position2I GameObject::getPosition() const
{
  auto position = IPositioned2I::getPosition();

  if (const auto* pParent = dynamic_cast<const GameObject*>(parent()))
    position += pParent->getPosition();

  return position;
}


bool GameObject::updateSelf(float pDt)
{
  if (d_prototype.getMovable() && !d_movementModel.update(pDt))
    return false;

  Doh3d::Position2I newPosition = d_prototype.getTileBased() ?
    d_movementModel.getPosition() :
    d_movementModel.getPosition() - d_prototype.getSize2();

  setPosition(newPosition);

  return true;
}

bool GameObject::drawSelf(Doh3d::Sprite& pSprite) const
{
  if (!pSprite.draw(Doh3d::ResourceMan::getTexture(d_prototype.getTi()).get(),
                    &Doh3d::ResourceMan::getTexture(d_prototype.getTi()).getFrame(0),
                    0, getPosition(), D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}

} // ns Model
} // ns SpaceExplorers
