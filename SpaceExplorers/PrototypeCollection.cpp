#include "stdafx.h"
#include "PrototypeCollection.h"


std::vector<Prototype> PrototypeCollection::d_prototypes;


bool PrototypeCollection::initAllPrototypes()
{
  {
    Prototype prototype;
    prototype.setName("Lattice");
    prototype.setTileBased(true);
    prototype.setMovable(false);
    prototype.setTextureName("Lattice_64_64_1_a.png");
    prototype.setSize({ 64, 64 });
    d_prototypes.push_back(prototype);
  }

  {
    Prototype prototype;
    prototype.setName("Man");
    prototype.setTileBased(false);
    prototype.setMovable(true);
    prototype.setTextureName("Man_64_64_4_a.png");
    prototype.setSize({ 64, 64 });
    d_prototypes.push_back(prototype);
  }

  return true;
}


bool PrototypeCollection::loadAllPrototypes()
{
  LOG("Prototype::Load()");

  for (auto& prototype : d_prototypes)
  {
    int ti;
    if (!Doh3d::ResourceMan::getTi(prototype.getTextureName(), ti))
    {
      echo("ERROR: Can't get TI for prototype (type name: \"", prototype.getName(), "\"): \"", prototype.getTextureName(), "\".");
      return false;
    }
    prototype.setTi(ti);
  }

  return true;
}


const Prototype* PrototypeCollection::find(const std::string& i_name)
{
  LOG(__FUNCTION__);

  auto it = std::find_if(d_prototypes.begin(), d_prototypes.end(),
                         [&](const Prototype& i_prototype) { return i_prototype.getName() == i_name; });
  if (it == d_prototypes.end())
  {
    echo("ERROR: Can't find the prototype with the given name: \"", i_name, "\".");
    return nullptr;
  }

  return &(*it);
}
