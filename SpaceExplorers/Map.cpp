#include "stdafx.h"
#include "Map.h"

#include "GameObjectCreator.h"
#include "Scene.h"


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

  
  auto* pMan = GameObjectCreator::createMan();
  pMan->getMovementModel().setPosition({ 160, 160 });
  pMan->setName("Player");
  pMap->addChildBack(pMan);


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
  LOG(__FUNCTION__);

  if (d_background.get())
  {
    if (!d_background->draw(pSprite))
      return false;
  }

  auto* pScene = getScene();
  if (!pScene)
  {
    echo("ERROR: Can't find its own scene.");
    return false;
  }

  auto* pCamera = pScene->findChild("Camera", 1);
  if (!pCamera)
  {
    echo("ERROR: Can't find camera.");
    return false;
  }

  Doh3d::Position2I cameraTranslation = pSprite.getTranslation();
  Doh3d::Position2I currentTranslation;

  for (int y = 0; y < d_height; ++y)
  {
    for (int x = 0; x < d_width; ++x)
    {
      currentTranslation = cameraTranslation +
        Doh3d::Position2I(x * Tile::DEFAULT_TILE_SIZE, y * Tile::DEFAULT_TILE_SIZE);
      pSprite.setTranslation(currentTranslation);
      
      if (!getTileAt(x, y)->draw(pSprite))
        return false;
    }
  }

  pSprite.setTranslation(cameraTranslation);

  return true;
}
