#include "stdafx.h"
#include "PrototypeCollection.h"


namespace Model
{

std::vector<Prototype> PrototypeCollection::d_prototypes;


bool PrototypeCollection::initAllPrototypes()
{
  Doh3d::Position2I tileTextureOffset{ 32, 32 };

  {
    Prototype prototype;
    prototype.setName("Lattice");
    prototype.setTextureOffset(tileTextureOffset);
    prototype.setMovable(false);
    prototype.setPassable(true);
    prototype.setTextureName("Lattice_64_64_1_a.png");
    prototype.setSize({ 64, 64 });
    d_prototypes.push_back(prototype);
  }

  {
    Prototype prototype;
    prototype.setName("Floor");
    prototype.setTextureOffset(tileTextureOffset);
    prototype.setMovable(false);
    prototype.setPassable(true);
    prototype.setTextureName("Floor_64_64_1_a.png");
    prototype.setSize({ 64, 64 });
    d_prototypes.push_back(prototype);
  }

  {
    Prototype prototype;
    prototype.setName("Wall");
    prototype.setTextureOffset(tileTextureOffset);
    prototype.setMovable(false);
    prototype.setPassable(false);
    prototype.setTextureName("Wall_64_64_1_a.png");
    prototype.setSize({ 64, 64 });
    d_prototypes.push_back(prototype);
  }


  {
    Prototype prototype;
    prototype.setName("Man");
    prototype.setTextureOffset({ 0, -16 });
    prototype.setMovable(true);
    prototype.setPassable(true);
    prototype.setTextureName("Man_64_64_4_a.png");
    prototype.setSize({ 64, 64 });
    d_prototypes.push_back(prototype);
  }

  {
    Prototype prototype;
    prototype.setName("Circle");
    prototype.setTextureOffset({});
    prototype.setMovable(false);
    prototype.setPassable(true);
    prototype.setTextureName("Circle_32_32_1_a.png");
    prototype.setSize({ 32, 32 });
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

} // ns Model
