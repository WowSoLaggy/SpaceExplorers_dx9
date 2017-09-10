#pragma once


namespace View
{

class IGui
  : public Doh3d::IPositioned2I
  , public Doh3d::ITextured
  , public Doh3d::ISized2I
  , public Doh3d::IInputHandler
  , public Doh3d::IUpdatable
  , public Doh3d::IDrawable
{
public:

  virtual ~IGui() { }

  bool containsPoint(Doh3d::Position2I pPoint);

};

} // ns View
