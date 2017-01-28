#pragma once

#ifndef INC_OBJECT_H
#define INC_OBJECT_H


class Object : public Doh3d::IDrawable, public Doh3d::IUpdatable
{
public:

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(int x) const override;

};


#endif // INC_OBJECT_H
