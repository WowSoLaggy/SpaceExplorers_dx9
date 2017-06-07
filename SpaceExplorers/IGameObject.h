#pragma once

#ifndef INC_IGAMEOBJECT_H
#define INC_IGAMEOBJECT_H


#include "SceneObject.h"


class IGameObject : public SceneObject, public Doh3d::IPositioned2
{
public:

  virtual ~IGameObject() { }

  virtual const Doh3d::Position2 getPosition() const override;

};


#endif // INC_GUIOBJECT_H
