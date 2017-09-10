#pragma once

#include "Tile.h"
#include "MapBackground.h"


namespace Model
{

class Map
{
public:

  Map( int i_width, int i_height);
  virtual ~Map();

  int getWidth() { return d_width; }
  int getHeight() { return d_height; }

  MapBackground& getMapBackgound() { return d_background; }
  const MapBackground& getMapBackgound() const { return d_background; }

  Tile* getTileAt(int pX, int pY);
  const Tile* getTileAt(int pX, int pY) const;

  Tile* getTileUnderPosition(const Doh3d::Position2F& i_position);
  const Tile* getTileUnderPosition(const Doh3d::Position2F& i_position) const;

  std::vector<GameObject*>& getObjects() { return d_objects; }
  const std::vector<GameObject*>& getObjects() const { return d_objects; }

  void addGameObject(GameObject* i_gameObject);

private:

  int d_width;
  int d_height;

  MapBackground d_background;

  std::vector<Tile> d_tiles;
  std::vector<GameObject*> d_objects;

  void deleteAllObjects();
  void deleteAllTiles();
};

} // ns Model
