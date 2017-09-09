#include "stdafx.h"
#include "GameObjectCreator.h"

#include "PrototypeCollection.h"


namespace Controller
{

Model::GameObject* GameObjectCreator::createLattice()
{
  auto* pPrototype = Model::PrototypeCollection::find("Lattice");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(*pPrototype);
  return pGameObject;
}

Model::GameObject* GameObjectCreator::createMan()
{
  auto* pPrototype = Model::PrototypeCollection::find("Man");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new Model::GameObject(*pPrototype);
  return pGameObject;
}

} // ns Model
