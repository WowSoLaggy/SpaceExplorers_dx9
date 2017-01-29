#pragma once

#ifndef INC_PANEL_H
#define INC_PANEL_H


#include "SceneObject.h"


class Panel : public virtual SceneObject, public virtual Doh3d::GPanel
{
public:

  virtual ~Panel() { }

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};


#endif // INC_PANEL_H
