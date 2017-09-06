#pragma once

#include "GameObject.h"


namespace Model
{

class GameObjectCreator
{
public:

  static GameObject* createLattice();
  static GameObject* createMan();

};

} // ns Model
