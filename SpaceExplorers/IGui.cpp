#include "stdafx.h"
#include "IGui.h"


bool IGui::containsPoint(Doh3d::Position2 pPoint)
{
  return Doh3d::Geometry::RectI(getPosition(), getSize()).containsPoint(pPoint);
}
