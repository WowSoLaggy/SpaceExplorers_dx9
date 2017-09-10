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
}

Map::~Map()
{
  deleteAllObjects();
  deleteAllTiles();
}


Tile* Map::getTileAt(int pX, int pY)
{
  return &(d_tiles[pX + d_width * pY]);
}

const Tile* Map::getTileAt(int pX, int pY) const
{
  return &(d_tiles[pX + d_width * pY]);
}


void Map::addGameObject(GameObject* i_gameObject)
{
  d_objects.push_back(i_gameObject);
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
