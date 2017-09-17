#include "stdafx.h"
#include "Map.h"

#include "GameObjectCreator.h"
#include "Scene.h"
#include "Camera.h"


namespace Model
{

Map::Map(int i_width, int i_height)
  : d_width(i_width)
  , d_height(i_height)
{
  d_background.setTexture("Space_1920_1024_1_n.png");
  d_tiles.resize(d_width * d_height);

  for (int y = 0; y < d_height; ++y)
  {
    for (int x = 0; x < d_width; ++x)
    {
      d_tiles[x + y * d_width].setCoords({ x, y });
    }
  }
}

Map::~Map()
{
  deleteAllObjects();
  deleteAllTiles();
}


Tile* Map::getTileAt(int pX, int pY)
{
  if (pX < 0 || pY < 0 || pX >= d_width || pY >= d_height)
    return nullptr;

  return &(d_tiles[pX + d_width * pY]);
}

const Tile* Map::getTileAt(int pX, int pY) const
{
  if (pX < 0 || pY < 0 || pX >= d_width || pY >= d_height)
    return nullptr;

  return &(d_tiles[pX + d_width * pY]);
}


Tile* Map::getTileUnderPosition(const Doh3d::Position2F& i_position)
{
  int x = (int)i_position.x / Tile::DEFAULT_TILE_SIZE;
  int y = (int)i_position.y / Tile::DEFAULT_TILE_SIZE;

  return getTileAt(x, y);
}

const Tile* Map::getTileUnderPosition(const Doh3d::Position2F& i_position) const
{
  int x = (int)i_position.x / Tile::DEFAULT_TILE_SIZE;
  int y = (int)i_position.y / Tile::DEFAULT_TILE_SIZE;

  return getTileAt(x, y);
}


void Map::addGameObject(GameObject* i_gameObject)
{
  if (!i_gameObject)
    return;

  if (i_gameObject->getPrototype().getBehaviour() == Model::Behaviour::Character)
    d_objects.push_back(i_gameObject);
  else
    d_objects.insert(d_objects.begin(), i_gameObject);
}


void Map::deleteAllObjects()
{
  for (auto* pGameObject : d_objects)
    delete pGameObject;
  d_objects.clear();
}

void Map::deleteAllTiles()
{
  d_tiles.clear();
}

} // ns Model
