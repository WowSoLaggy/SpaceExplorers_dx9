#include "stdafx.h"
#include "GameObjectCreator.h"

#include "PrototypeCollection.h"


GameObject* GameObjectCreator::createLattice()
{
  auto* pPrototype = PrototypeCollection::find("Lattice");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new GameObject(*pPrototype);
  return pGameObject;
}

GameObject* GameObjectCreator::createMan()
{
  auto* pPrototype = PrototypeCollection::find("Man");
  if (!pPrototype)
    return nullptr;

  auto* pGameObject = new GameObject(*pPrototype);
  return pGameObject;
}
