#include "stdafx.h"
#include "MovementModel.h"

#include "Tile.h"
#include "GameObject.h"
#include "Map.h"


namespace Model
{

MovementModel::MovementModel(const GameObject& i_gameObject)
  : d_goUp(false)
  , d_goRight(false)
  , d_goDown(false)
  , d_goLeft(false)
  , d_gameObject(i_gameObject)
{
}


bool MovementModel::beforeUpdate(float i_dt)
{
  const float MAX_ACCEL = Tile::DEFAULT_TILE_SIZE * 20;
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

  auto position = getPosition();

  collideWithNeighborTiles(d_gameObject.getMap(), i_dt, position, speed, currentAccel);

  auto* pTile = d_gameObject.getMap().getTileUnderPosition(position);
  if (!pTile || pTile->isSpace())
  {
    // Open space - no control. We can only control accel if have any collision
    setAccel({ 0, 0 });
  }
  else
    setAccel(currentAccel);

  setSpeed(speed);

  return true;
}

bool MovementModel::afterUpdate(float i_dt)
{
  auto position = getPosition();

  auto* pTile = d_gameObject.getMap().getTileUnderPosition(position);
  if (!pTile || pTile->isSpace())
  {
    // Open space
    setAccel({ 0, 0 });
    return true;
  }


  const float MAX_SPEED = Tile::DEFAULT_TILE_SIZE * 3;

  // Clamp maximum speed

  auto speed = getSpeed();
  float speedLength = speed.length();

  if (speedLength > MAX_SPEED)
  {
    speed /= speedLength / MAX_SPEED;
    setSpeed(speed);
  }

  return true;
}


void MovementModel::collideWithNeighborTiles(const Map& i_map, float i_dt,
                                             const Doh3d::Position2F& i_position,
                                             Doh3d::Position2F& io_speed,
                                             Doh3d::Position2F& io_accel) const
{
  auto* pTile = i_map.getTileUnderPosition(i_position);
  if (!pTile)
    return;

  auto curCoords = pTile->getCoords();

  auto collideUp = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x, curCoords.y - 1),
                           i_position + io_speed * i_dt);
  };
  auto collideDown = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x, curCoords.y + 1),
                           i_position + io_speed * i_dt);
  };
  auto collideLeft = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x - 1, curCoords.y),
                           i_position + io_speed * i_dt);
  };
  auto collideRight = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x + 1, curCoords.y),
                           i_position + io_speed * i_dt);
  };
  auto collideUpRight = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x + 1, curCoords.y - 1),
                           i_position + io_speed * i_dt);
  };
  auto collideDownRight = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x + 1, curCoords.y + 1),
                           i_position + io_speed * i_dt);
  };
  auto collideUpLeft = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x - 1, curCoords.y - 1),
                           i_position + io_speed * i_dt);
  };
  auto collideDownLeft = [&]() -> bool
  {
    return collideWithTile(i_map.getTileAt(curCoords.x - 1, curCoords.y + 1),
                           i_position + io_speed * i_dt);
  };

  if (collideUp() || collideDown())
  {
    io_speed.y = 0;
    io_accel.y = 0;
  }

  if (collideLeft() || collideRight())
  {
    io_speed.x = 0;
    io_accel.x = 0;
  }

  if (collideUpLeft() || collideUpRight() ||
      collideDownLeft() || collideDownRight())
  {
    io_speed.x = 0;
    io_accel.x = 0;
    io_speed.y = 0;
    io_accel.y = 0;
  }
}

bool MovementModel::collideWithTile(const Tile* i_tile, const Doh3d::Position2F& i_position) const
{
  if (!i_tile || i_tile->isPassable())
    return false;

  auto* pGameObject = i_tile->getTopLayer();
  if (!pGameObject)
    return false;

  auto* pShape1 = pGameObject->getCollisionShape();
  if (!pShape1)
    return false;

  auto* pShape2 = d_gameObject.getCollisionShape();
  if (!pShape2)
    return false;

  return Doh3d::Collider::collide(*pShape1, *pShape2,
                                  i_tile->getTopLeft(), i_position);
}

} // ns Model
