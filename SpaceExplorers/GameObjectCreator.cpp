#include "stdafx.h"
#include "GameObjectCreator.h"

#include "PrototypeCollection.h"
#include "Map.h"


namespace Controller
{

Model::GameObject* GameObjectCreator::createLattice(Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Lattice");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

Model::GameObject* GameObjectCreator::createFloor(Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Floor");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

Model::GameObject* GameObjectCreator::createWall(Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Wall");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

Model::GameObject* GameObjectCreator::createDoor(Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Door");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}


Model::Character* GameObjectCreator::createMan(Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Man");
  if (!pPrototype)
    return nullptr;

  auto* pCharacter = new Model::Character(i_map, *pPrototype);
  return pCharacter;
}


Model::GameObject* GameObjectCreator::createRods(Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Rods");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}


Model::GameObject* GameObjectCreator::createCircle(Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Circle");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

} // ns Model
