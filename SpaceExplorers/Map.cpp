#include "stdafx.h"
#include "Map.h"


Map::Map()
  : d_width(20)
  , d_height(20)
{
  d_background.reset(new MapBackground());
  d_background->setTexture("Space_1920_1024_1_n.png");

  d_tiles.resize(d_width * d_height);
}

Map::~Map()
{
}


Map* Map::createMap()
{
  return new Map();
}


Tile* Map::getTileAt(int pX, int pY)
{
  if (pX < 0 || d_width <= pX ||
      pY < 0 || d_height <= pY)
  {
    assert(false);
    return nullptr;
  }

  return &(d_tiles[pX + d_width * pY]);
}


bool Map::updateSelf(float pDt)
{
  for (auto& tile : d_tiles)
  {
    if (!tile.update(pDt))
      return false;
  }

  return true;
}

bool Map::drawSelf(Doh3d::Sprite& pSprite) const
{
  if (d_background.get())
    d_background->draw(pSprite);

  for (auto& tile : d_tiles)
  {
    if (!tile.draw(pSprite))
      return false;
  }

  return true;
}
