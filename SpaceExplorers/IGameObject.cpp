#include "stdafx.h"
#include "IGameObject.h"


const Doh3d::Position2 IGameObject::getPosition() const
{
  auto position = IPositioned2::getPosition();

  if (const auto* pParent = dynamic_cast<const IGameObject*>(parent()))
    position += pParent->getPosition();

  return position;
}
