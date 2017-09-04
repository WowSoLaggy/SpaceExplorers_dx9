#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(const Prototype& i_prototype)
  : d_prototype(i_prototype)
{
}


const Doh3d::Position2 GameObject::getPosition() const
{
  auto position = IPositioned2::getPosition();

  if (const auto* pParent = dynamic_cast<const GameObject*>(parent()))
    position += pParent->getPosition();

  return position;
}


bool GameObject::updateSelf(float pDt)
{
  return true;
}

bool GameObject::drawSelf(Doh3d::Sprite& pSprite) const
{
  return true;
}
