#pragma once

#include "GameObject.h"
#include "Character.h"


namespace Model
{
class Map;
}


namespace Controller
{

class GameObjectCreator
{
public:

  static Model::GameObject* createLattice(Model::Map& i_map);
  static Model::GameObject* createFloor(Model::Map& i_map);
  static Model::GameObject* createWall(Model::Map& i_map);
  static Model::GameObject* createDoor(Model::Map& i_map);
  
  static Model::Character* createMan(Model::Map& i_map);

  static Model::GameObject* createRods(Model::Map& i_map);

  static Model::GameObject* createCircle(Model::Map& i_map);

};

} // ns Model
