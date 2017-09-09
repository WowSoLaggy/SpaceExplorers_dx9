#pragma once

#include "GameObject.h"


namespace Controller
{

class GameObjectCreator
{
public:

  static Model::GameObject* createLattice();
  static Model::GameObject* createMan();

};

} // ns Model
