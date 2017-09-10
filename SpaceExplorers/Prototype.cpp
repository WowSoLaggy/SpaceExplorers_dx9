#include "stdafx.h"
#include "Prototype.h"


namespace Model
{

Prototype::Prototype()
  : d_collisionShape(nullptr)
{
}

Prototype::~Prototype()
{
  resetCollisionShape();
}


void Prototype::setCollisionShape(const Doh3d::IShape* i_shape)
{
  if (i_shape == d_collisionShape)
    return;

  resetCollisionShape();

  if (!i_shape)
    return;

  d_collisionShape = i_shape;
}

void Prototype::resetCollisionShape()
{
  if (d_collisionShape)
  {
    delete d_collisionShape;
    d_collisionShape = nullptr;
  }
}

} // ns Model
