#include "stdafx.h"
#include "Map.h"

#include "GameObjectCreator.h"


Map::Map(int i_width, int i_height)
  : d_width(i_width)
  , d_height(i_height)
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
  auto* pMap = new Map(20, 20);

  for (int y = 2; y <= 8; ++y)
  {
    for (int x = 2; x <= 6; ++x)
      pMap->getTileAt(x, y)->setTurf(GameObjectCreator::createLattice());
  }

  return pMap;
}


Tile* Map::getTileAt(int pX, int pY)
{
  return &(d_tiles[pX + d_width * pY]);
}

const Tile* Map::getTileAt(int pX, int pY) const
{
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
  {
    if (!d_background->draw(pSprite))
      return false;
  }

  D3DXMATRIX tileOffsetTransform;

  for (int y = 0; y < d_height; ++y)
  {
    for (int x = 0; x < d_width; ++x)
    {
      D3DXMatrixTranslation(&tileOffsetTransform, (FLOAT)(x * Tile::DEFAULT_TILE_SIZE), (FLOAT)(y * Tile::DEFAULT_TILE_SIZE), 0);

      pSprite.setTransform(&tileOffsetTransform);
      if (!getTileAt(x, y)->draw(pSprite))
        return false;
    }
  }

  return true;
}
