#pragma once


class MovementModel : public Doh3d::IMovable
{
public:

  void setGoUp(bool i_on) { d_goUp = i_on; }
  void setGoDown(bool i_on) { d_goDown = i_on; }
  void setGoRight(bool i_on) { d_goRight = i_on; }
  void setGoLeft(bool i_on) { d_goLeft = i_on; }

  virtual bool update(float i_dt) override;

private:

  bool d_goUp;
  bool d_goDown;
  bool d_goRight;
  bool d_goLeft;

};
