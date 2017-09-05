#include "stdafx.h"
#include "MovementModel.h"

#include "Tile.h"


bool MovementModel::update(float i_dt)
{
  const float MAX_ACCEL = Tile::DEFAULT_TILE_SIZE * 20;
  const float MAX_SPEED = Tile::DEFAULT_TILE_SIZE * 3;
  const float MIN_SPEED = 20;

  // Calc current accel

  Doh3d::Vector2F currentAccel{ 0, 0 };
  Doh3d::Vector2F speed = getSpeed();

  if (d_goUp != d_goDown)
  {
    if (d_goUp) currentAccel.y = -MAX_ACCEL;
    else currentAccel.y = MAX_ACCEL;
  }
  else
  {
    if (speed.y > MIN_SPEED) currentAccel.y = -MAX_ACCEL;
    else if (speed.y < -MIN_SPEED) currentAccel.y = MAX_ACCEL;
    else speed.y = 0;
  }

  if (d_goLeft != d_goRight)
  {
    if (d_goLeft) currentAccel.x = -MAX_ACCEL;
    else currentAccel.x = MAX_ACCEL;
  }
  else
  {
    if (speed.x > MIN_SPEED) currentAccel.x = -MAX_ACCEL;
    else if (speed.x < -MIN_SPEED) currentAccel.x = MAX_ACCEL;
    else speed.x = 0;
  }

  setAccel(currentAccel);
  setSpeed(speed);

  if (!Doh3d::IMovable::update(i_dt))
    return false;

  // Clamp maximum speed

  speed = getSpeed();
  float speedLength = speed.length();
  
  if (speedLength > MAX_SPEED)
  {
    speed /= speedLength / MAX_SPEED;
    setSpeed(speed);
  }

  return true;
}
