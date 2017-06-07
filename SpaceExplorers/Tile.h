#pragma once

#ifndef INC_TILE_H
#define INC_TILE_H


#include "IGameObject.h"


class Tile : public IGameObject
{
public:

  virtual ~Tile();

private:

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;
};


#endif // INC_TILE_H
