#include "stdafx.h"
#include "MovementModel.h"

#include "Tile.h"


bool MovementModel::update(float i_dt)
{
  const float MAX_SPEED = Tile::DEFAULT_TILE_SIZE * 3;

  Doh3d::Vector2F currentSpeed{ 0, 0 };

  if (d_goUp != d_goDown)
  {
    if (d_goUp) currentSpeed.y = -MAX_SPEED;
    else currentSpeed.y = MAX_SPEED;
  }

  if (d_goLeft != d_goRight)
  {
    if (d_goLeft) currentSpeed.x = -MAX_SPEED;
    else currentSpeed.x = MAX_SPEED;
  }

  setSpeed(currentSpeed);

  return Doh3d::IMovable::update(i_dt);
}
