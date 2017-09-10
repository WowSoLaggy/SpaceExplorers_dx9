#include "stdafx.h"
#include "IGui.h"


namespace View
{

bool IGui::containsPoint(Doh3d::Position2I pPoint)
{
  return Doh3d::RectI(getPosition(), getSize()).containsPoint(pPoint);
}

} // ns View
