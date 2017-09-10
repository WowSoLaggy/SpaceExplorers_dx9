#include "stdafx.h"
#include "MapController.h"

#include "Game.h"
#include "Map.h"
#include "Scene.h"
#include "Camera.h"
#include "GameObjectCreator.h"


namespace Controller
{

MapController::MapController(Game& i_game)
  : d_game(i_game)
{
}


bool MapController::createMap(int i_width, int i_height)
{
  d_map = new Model::Map(20, 20);
  if (!d_map)
    return false;

  for (int y = 2; y <= 8; ++y)
  {
    for (int x = 2; x <= 6; ++x)
    {
      d_map->getTileAt(x, y)->setTurf(GameObjectCreator::createLattice());
    }
  }

  auto* pMan = GameObjectCreator::createMan();
  pMan->setPosition({ 160, 160 });
  pMan->setName("Player");
  d_map->addGameObject(pMan);

  return true;
}

bool MapController::deleteMap()
{
  LOG(__FUNCTION__);

  if (!d_map)
  {
    echo("ERROR: Can't delete map - no map.");
    return false;
  }

  delete d_map;
  d_map = nullptr;

  return true;
}


bool MapController::update(float i_dt)
{
  return true;
}

bool MapController::draw(Doh3d::Sprite& i_sprite) const
{
  if (!d_map)
    return true;

  if (!d_map->getMapBackgound().draw(i_sprite))
    return false;

  auto* pCamera = d_game.getScene().getCamera();
  if (!pCamera)
    return false;

  Doh3d::SpriteTransformGuard spriteTransformGuard(i_sprite);

  const Doh3d::Position2I cameraTranslation = -pCamera->getPosition();
  Doh3d::Position2I currentTranslation;

  for (int y = 0; y < d_map->getHeight(); ++y)
  {
    for (int x = 0; x < d_map->getWidth(); ++x)
    {
      currentTranslation = cameraTranslation +
        Doh3d::Position2I(x * Model::Tile::DEFAULT_TILE_SIZE, y * Model::Tile::DEFAULT_TILE_SIZE);
      i_sprite.setTranslation(currentTranslation);

      if (!d_map->getTileAt(x, y)->draw(i_sprite))
        return false;
    }
  }

  i_sprite.setTranslation(cameraTranslation);

  return true;
}

} // ns Controller
