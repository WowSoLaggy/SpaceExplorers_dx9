#include "stdafx.h"
#include "PrototypeCollection.h"


namespace Model
{

std::vector<Prototype*> PrototypeCollection::d_prototypes;


bool PrototypeCollection::initAllPrototypes()
{
  Doh3d::Position2I tileTextureOffset{ 32, 32 };

  {
    auto* pPrototype = new Prototype();
    pPrototype->setName("Lattice");
    pPrototype->setTextureOffset(tileTextureOffset);
    pPrototype->setMovable(false);
    pPrototype->setPassable(true);
    pPrototype->setTextureName("Lattice_64_64_1_a.png");
    pPrototype->setSize({ 64, 64 });
    pPrototype->setCollisionShape(new Doh3d::RectF({ 0, 0 }, { 64, 64 }));
    d_prototypes.push_back(pPrototype);
  }

  {
    auto* pPrototype = new Prototype();
    pPrototype->setName("Floor");
    pPrototype->setTextureOffset(tileTextureOffset);
    pPrototype->setMovable(false);
    pPrototype->setPassable(true);
    pPrototype->setTextureName("Floor_64_64_1_a.png");
    pPrototype->setSize({ 64, 64 });
    pPrototype->setCollisionShape(new Doh3d::RectF({ 0, 0 }, { 64, 64 }));
    d_prototypes.push_back(pPrototype);
  }

  {
    auto* pPrototype = new Prototype();
    pPrototype->setName("Wall");
    pPrototype->setTextureOffset(tileTextureOffset);
    pPrototype->setMovable(false);
    pPrototype->setPassable(false);
    pPrototype->setTextureName("Wall_64_64_1_a.png");
    pPrototype->setSize({ 64, 64 });
    pPrototype->setCollisionShape(new Doh3d::RectF({ 0, 0 }, { 64, 64 }));
    d_prototypes.push_back(pPrototype);
  }

  {
    auto* pPrototype = new Prototype();
    pPrototype->setName("Door");
    pPrototype->setTextureOffset(tileTextureOffset);
    pPrototype->setMovable(false);
    pPrototype->setPassable(false);
    pPrototype->setTextureName("Door_64_64_6_a.png");
    pPrototype->setSize({ 64, 64 });
    pPrototype->setCollisionShape(new Doh3d::RectF({ 0, 0 }, { 64, 64 }));
    d_prototypes.push_back(pPrototype);
  }


  {
    auto* pPrototype = new Prototype();
    pPrototype->setName("Man");
    pPrototype->setTextureOffset({ 0, -16 });
    pPrototype->setMovable(true);
    pPrototype->setPassable(true);
    pPrototype->setTextureName("Man_64_64_4_a.png");
    pPrototype->setSize({ 64, 64 });
    pPrototype->setCollisionShape(new Doh3d::Circle({ 0, 0 }, 16));
    d_prototypes.push_back(pPrototype);
  }

  {
    auto* pPrototype = new Prototype();
    pPrototype->setName("Circle");
    pPrototype->setTextureOffset({});
    pPrototype->setMovable(false);
    pPrototype->setPassable(true);
    pPrototype->setTextureName("Circle_32_32_1_a.png");
    pPrototype->setSize({ 32, 32 });
    d_prototypes.push_back(pPrototype);
  }

  return true;
}


bool PrototypeCollection::disposeAllPrototypes()
{
  for (auto* pPrototype : d_prototypes)
    delete pPrototype;
  d_prototypes.clear();

  return true;
}


bool PrototypeCollection::loadAllPrototypes()
{
  LOG("Prototype::Load()");

  for (auto* pPrototype : d_prototypes)
  {
    int ti;
    if (!Doh3d::ResourceMan::getTi(pPrototype->getTextureName(), ti))
    {
      echo("ERROR: Can't get TI for prototype (type name: \"", pPrototype->getName(), "\"): \"", pPrototype->getTextureName(), "\".");
      return false;
    }
    pPrototype->setTi(ti);
  }

  return true;
}


const Prototype* PrototypeCollection::find(const std::string& i_name)
{
  LOG(__FUNCTION__);

  auto it = std::find_if(d_prototypes.begin(), d_prototypes.end(),
                         [&](const Prototype* i_prototype) { return i_prototype->getName() == i_name; });
  if (it == d_prototypes.end())
  {
    echo("ERROR: Can't find the prototype with the given name: \"", i_name, "\".");
    return nullptr;
  }

  return *it;
}

} // ns Model
