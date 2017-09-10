#pragma once

#include "GameObject.h"


namespace Model
{
class Map;
}


namespace Controller
{

class GameObjectCreator
{
public:

  static Model::GameObject* createLattice(const Model::Map& i_map);
  static Model::GameObject* createMan(const Model::Map& i_map);

};

} // ns Model
