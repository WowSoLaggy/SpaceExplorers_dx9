#include "stdafx.h"
#include "IGui.h"


bool IGui::containsPoint(Doh3d::Position2 pPoint)
{
  return Doh3d::Geometry::RectI(getPosition(), getSize()).containsPoint(pPoint);
}


const Doh3d::Position2 IGui::getPosition() const
{
  auto position = IPositioned2::getPosition();

  if (const auto* pParent = dynamic_cast<const IGui*>(parent()))
    position += pParent->getPosition();

  return position;
}
