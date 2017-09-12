#pragma once


namespace Model
{

class GameObject;
class Map;
class Tile;


class MovementModel : public Doh3d::IMovable2F
{
public:

  MovementModel(const GameObject& i_gameObject);

  void setGoUp(bool i_on) { d_goUp = i_on; }
  void setGoDown(bool i_on) { d_goDown = i_on; }
  void setGoRight(bool i_on) { d_goRight = i_on; }
  void setGoLeft(bool i_on) { d_goLeft = i_on; }

  virtual bool beforeUpdate(float i_dt) override;
  virtual bool afterUpdate(float i_dt) override;

private:

  bool d_goUp;
  bool d_goDown;
  bool d_goRight;
  bool d_goLeft;

  const GameObject& d_gameObject;

  void collideWithNeighborTiles(const Map& i_map, float i_dt,
                                const Doh3d::Position2F& i_position,
                                Doh3d::Position2F& io_speed,
                                Doh3d::Position2F& io_accel) const;
  bool collideWithTile(const Tile* i_tile, const Doh3d::Position2F& i_position) const;

};

} // ns Model
