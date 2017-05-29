#include "stdafx.h"
#include "IGui.h"


bool IGui::containsPoint(Doh3d::Position2 pPoint)
{
  return Doh3d::Geometry::RectI(getPosition(), getSize()).containsPoint(pPoint);
}


const Doh3d::Position2& IGui::getPosition() const
{
  if (const auto* pParent = dynamic_cast<const IGui*>(parent()))
  {
    // TODO: Think about how this can be done better without the static one
    static Doh3d::Position2 position = IPositioned2::getPosition() + pParent->getPosition();
    return position;
  }

  return IPositioned2::getPosition();
}
