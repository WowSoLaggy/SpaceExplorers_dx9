#include "stdafx.h"
#include "IGui.h"


bool IGui::containsPoint(Doh3d::Position2I pPoint)
{
  return Doh3d::Geometry::RectI(getPosition(), getSize()).containsPoint(pPoint);
}


const Doh3d::Position2I IGui::getPosition() const
{
  auto position = IPositioned2I::getPosition();

  if (const auto* pParent = dynamic_cast<const IGui*>(parent()))
    position += pParent->getPosition();

  return position;
}
