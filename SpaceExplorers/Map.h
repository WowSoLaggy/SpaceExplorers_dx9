#pragma once

#ifndef INC_MAP_H
#define INC_MAP_H


#include "SceneObject.h"
#include "Tile.h"
#include "MapBackground.h"


class Map : public SceneObject
{
public:

  static Map* createMap();

public:

  virtual ~Map();

  Tile* getTileAt(int pX, int pY);
  const Tile* getTileAt(int pX, int pY) const;

private:

  Map(int i_width, int i_height);

  int d_width;
  int d_height;

  std::vector<Tile> d_tiles;

  std::unique_ptr<MapBackground> d_background;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;
};


#endif // INC_MAP_H
