#include "stdafx.h"
#include "PrototypeCollection.h"


void PrototypeCollection::loadAllPrototypes()
{
  Prototype prototype;

  prototype.setName("Lattice");
  prototype.setTileBased(true);

  d_prototypes.push_back(prototype);
}


const Prototype* PrototypeCollection::find(const std::string& i_name)
{
  auto it = std::find_if(d_prototypes.begin(), d_prototypes.end(),
                         [&](const Prototype& i_prototype) { return i_prototype.getName() == i_name; });
  if (it == d_prototypes.end())
    return nullptr;

  return &(*it);
}
