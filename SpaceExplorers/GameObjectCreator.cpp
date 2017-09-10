#include "stdafx.h"
#include "GameObjectCreator.h"

#include "PrototypeCollection.h"
#include "Map.h"


namespace Controller
{

Model::GameObject* GameObjectCreator::createLattice(const Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Lattice");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

Model::GameObject* GameObjectCreator::createFloor(const Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Floor");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

Model::GameObject* GameObjectCreator::createWall(const Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Wall");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}


Model::GameObject* GameObjectCreator::createMan(const Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Man");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

Model::GameObject* GameObjectCreator::createCircle(const Model::Map& i_map)
{
  auto* pPrototype = Model::PrototypeCollection::find("Circle");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(i_map, *pPrototype);
  return pGameObject;
}

} // ns Model
